#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include<math.h>

#define MAX_FILENAMES 100
#define MAX_FILENAME_LEN 50

typedef struct
{
    char symbol;
    int freq;
    double prob;
    char code[40];
    int top;
} char_data;

void count_characters(const char* filename, int* num_chars, int * original_file_size, char_data** char_freq);
int compare_chars(const void* a, const void* b);
void sort_char_by_freq(char_data* char_freq, int num_chars);
void display_char_codes(char_data* char_freq, int num_chars);

char check_duplicate_codes(char_data* char_freq, int num_chars);
void encoding(char_data* char_freq, int * encoded_filesize, int num_chars, const char* text_file, const char* encoded_text, const char* codebook);



void count_characters(const char* filename, int* num_chars, int * original_file_size, char_data** char_freq)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Failed to open file %s\n", filename);
        *num_chars = 0;
        *char_freq = NULL;
        return;
    }
    
    // creating array of 256 struct elements and initialize frequencies to 0
    char_data freq_array[256] = {0};

    int c;
    int total_chars = 0;
    
    while ((c = fgetc(fp)) != EOF)
    {
        // incrementing frequency of character in freq_array
        if(!freq_array[c].freq)
            (*num_chars)++;
        freq_array[c].symbol = (char)c;
        freq_array[c].freq++;
        total_chars++;
    }

    fclose(fp);

    *original_file_size = total_chars*8;

    // sort freq_array in non-increasing order
    qsort(freq_array, 256, sizeof(char_data), compare_chars);

    *char_freq = (char_data*) malloc(*num_chars * sizeof(char_data));
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        if (freq_array[i].freq > 0)
        {
            (*char_freq)[j].symbol = freq_array[i].symbol;
            (*char_freq)[j].freq = freq_array[i].freq;
            (*char_freq)[j].prob = (double) freq_array[i].freq / total_chars;
            (*char_freq)[j].top = -1;
            j++;
        }
    }
}

int compare_chars(const void* a, const void* b)
{
    const char_data* pair1 = (const char_data*) a;
    const char_data* pair2 = (const char_data*) b;
    if (pair1->freq == pair2->freq)
        return pair1->symbol - pair2->symbol;
    return pair2->freq - pair1->freq;
}
void sort_char_by_freq(char_data* char_freq, int num_chars)
{
    qsort(char_freq, num_chars, sizeof(char_data), compare_chars);
}

void display_char_codes(char_data* char_freq, int num_chars)
{
    if(check_duplicate_codes(char_freq,num_chars)=='1')
        printf("\nFailure");

    printf("\nCharacter frequencies:\n");
    printf("Symbol\t| Frequency | Probability | Code\n");
    printf("--------|-----------|-------------|------\n");

    for (int i = 0; i < num_chars; i++)
    {
        if(char_freq[i].symbol == '\n')
            printf("<enter>\t| %d\t  | %lf\t  | %s\n", char_freq[i].freq, char_freq[i].prob, char_freq[i].code);
        
        else if(char_freq[i].symbol == ' ')
            printf("<space>\t| %d\t  | %lf\t  | %s\n", char_freq[i].freq, char_freq[i].prob, char_freq[i].code);
        
        else
            printf("%c\t| %d\t  | %lf\t  | %s\n", char_freq[i].symbol, char_freq[i].freq, char_freq[i].prob, char_freq[i].code);
    }
}

void shannon_fano(char_data* char_freq, int start, int end, int num_chars)
{
    if (start >= end)
        return;

    double total_prob = 0;
    for (int i = start; i <= end; i++)
        total_prob += char_freq[i].prob;

    double half_prob = total_prob / 2.0;
    double current_prob = 0;
    int split_index = -1;//start;

    if(end - start >= 2)
        for (int i = start; i <= end; i++)
        {
            current_prob += char_freq[i].prob;
            if (current_prob >= half_prob)
            {
                split_index = i-1;
                if(split_index < start)
                    split_index++;
                break;
            }
        }
    else
        split_index = start;

    //Check 1: printf("\nStart = %d, End = %d, Split index = %d",start,end,split_index); fflush(stdin); getchar();

    for (int i = start; i <= split_index; i++)
    {
        char_freq[i].code[++char_freq[i].top] = '0';
        char_freq[i].code[char_freq[i].top+1] = '\0';
    }
    for (int i = split_index + 1; i <= end; i++)
    {
        char_freq[i].code[++char_freq[i].top] = '1';
        char_freq[i].code[char_freq[i].top+1] = '\0';
    }

    //Check 2: display_char_codes(char_freq,num_chars);
    shannon_fano(char_freq, start, split_index, num_chars);
    shannon_fano(char_freq, split_index+1, end, num_chars);
}

char check_duplicate_codes(char_data* char_freq, int num_chars)
{
    char* codes[num_chars];
    for (int i = 0; i < num_chars; i++)
        codes[i] = char_freq[i].code;

    qsort(codes, num_chars, sizeof(char*), strcmp);

    // Check for duplicate codes
    for (int i = 1; i < num_chars; i++)
    {
        if (strcmp(codes[i], codes[i-1]) == 0)
        {
            printf("\nDuplicate code: %s\n", codes[i]);
            return '1';
        }
    }
    return '0';
}

double calc_avg_code_len(char_data* char_freq, int num_chars)
{
    double avg_len = 0;

    for (int i = 0; i < num_chars; i++)
        avg_len += (double) char_freq[i].prob * strlen(char_freq[i].code);

    return avg_len;
}

void encoding(char_data* char_freq, int * encoded_file_size, int num_chars, const char* text_file, const char* encoded_text, const char* codebook)
{
    FILE* fp1 = fopen(text_file, "r");
    FILE* fp2 = fopen(encoded_text,"w");
    FILE* fp3 = fopen(codebook,"w");
    if (fp1 == NULL)
    {
        printf("Failed to open file %s\n", text_file);
        return;
    }
    if(fp2 == NULL)
    {
        printf("Failed to open file %s\n", encoded_text);
        fclose(fp1);
        return;
    }
    if(fp3 == NULL)
    {
        printf("Failed to open file %s\n", codebook);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
        return;
    }
    
    // creating array of 256 struct elements and initialize frequencies to 0
    char_data freq_array[256] = {0};

    for (int i = 0; i < num_chars; i++)
        freq_array[(int)char_freq[i].symbol] = char_freq[i];

    fprintf(fp3, "%d\n", num_chars);

    // Write the character frequency table to the output file
    for (int i = 0; i < num_chars; i++)
        fprintf(fp3, "%d %s\n", char_freq[i].symbol, char_freq[i].code);

    // Rewind the input file
    rewind(fp1);

    int c;
    while ((c = fgetc(fp1)) != EOF)
    {
        fprintf(fp2,"%s",freq_array[c].code);
        *encoded_file_size += strlen(freq_array[c].code);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}

double calculate_entropy(const char *filename)
{
    FILE *fp;
    int total_chars = 0, freq[256] = {0};
    double probability, entropy = 0;

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Could not open file\n");
        exit(1);
    }

    // Count the frequency of each character in the file
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        freq[c]++;
        total_chars++;
    }

    // Calculate the probability of each character and the entropy
    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            probability = (double)freq[i] / (double)total_chars;
            entropy += probability * log2(probability);
        }
    }
    entropy = -entropy;

    fclose(fp);

    return entropy;
}

void read_file_list(const char *filename, char file_list[][MAX_FILENAME_LEN], int *num_files)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        exit(1);
    }
    
    int i = 0;
    char line[MAX_FILENAME_LEN];
    while (fgets(line, MAX_FILENAME_LEN, fp) != NULL)
    {
        // Remove newline character at end of line
        line[strcspn(line, "\n")] = 0;
        
        // Copy filename into array
        strncpy(file_list[i], line, MAX_FILENAME_LEN);
        i++;
        
        // Check if we have read too many filenames
        if (i == MAX_FILENAMES) {
            fprintf(stderr, "Error: too many filenames in file %s\n", filename);
            exit(1);
        }
    }
    
    *num_files = i;
    
    fclose(fp);
}

void write_record_to_file(char* filename, int *original_file_size, int *encoded_file_size, double *entropy, double *avg_code_length, int num_files)
{
    FILE* fp = fopen(filename, "w"); // Open file for appending
    
    if (fp == NULL)
    {
        printf("Error opening file %s", filename);
        return;
    }
    
    fprintf(fp, "Original Size,Encoded Size,Entropy,Avg Code Len\n");
    for (int i = 0; i < num_files; i++)
    {
        fprintf(fp, "%d,%d,%.5f,%.5f\n", original_file_size[i], encoded_file_size[i], entropy[i], avg_code_length[i]); // Write to file
    }
    fclose(fp); // Close file
}


int main()
{
    char keep_record[] = "Result_Record.csv";
    char original_files[MAX_FILENAMES][MAX_FILENAME_LEN];
    char encoded_files[MAX_FILENAMES][MAX_FILENAME_LEN];
    char decoded_files[MAX_FILENAMES][MAX_FILENAME_LEN];
    char codebook_files[MAX_FILENAMES][MAX_FILENAME_LEN];
    
    int original_file_size[MAX_FILENAMES]={0};
    int encoded_file_size[MAX_FILENAMES]= {0};
    double entropy[MAX_FILENAMES]={0};
    double avg_code_length[MAX_FILENAMES] ={0};

    int num_files;

    read_file_list("Original_File_List.txt", original_files, &num_files);
    read_file_list("Encoded_File_List.txt", encoded_files, &num_files);
    read_file_list("Decoded_File_List.txt", decoded_files, &num_files);
    read_file_list("Codebook_File_List.txt", codebook_files, &num_files);

    for (int i = 0; i < num_files; i++)
    {
        int num_chars=0;
        char_data * char_freq = NULL;
        
        count_characters(original_files[i],&num_chars,&original_file_size[i],&char_freq);
        shannon_fano(char_freq,0,num_chars-1,num_chars);
        encoding(char_freq, &encoded_file_size[i], num_chars, original_files[i], encoded_files[i], codebook_files[i]);
        
        entropy[i]= calculate_entropy(original_files[i]);
        avg_code_length[i] = calc_avg_code_len(char_freq,num_chars);

        free(char_freq);
    }

    for (int i = 0; i < num_files; i++)
        printf("\n%lf",entropy[i]);

    write_record_to_file(keep_record,original_file_size,encoded_file_size,entropy,avg_code_length,num_files);
    
    printf("\nEnd of program");
    return 0;
}