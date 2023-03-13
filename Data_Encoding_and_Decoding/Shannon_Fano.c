#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include<math.h>

typedef struct
{
    char symbol;
    int freq;
    double prob;
    char code[20];
    int top;
} char_data;

void count_characters(const char* filename, int* num_chars, char_data** char_freq);
int compare_chars(const void* a, const void* b);
void sort_char_by_freq(char_data* char_freq, int num_chars);
void display_char_codes(char_data* char_freq, int num_chars);
//void shannon_fano(char_data* char_freq, int start, int end);
char check_duplicate_codes(char_data* char_freq, int num_chars);


void count_characters(const char* filename, int* num_chars, char_data** char_freq)
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
        freq_array[c].symbol = (char)c;
        freq_array[c].freq++;
        total_chars++;
    }

    fclose(fp);

    // sort freq_array in non-increasing order
    qsort(freq_array, 256, sizeof(char_data), compare_chars);

    // copy positive frequency elements to char_freq
    *num_chars = 0;
    for (int i = 0; i < 256; i++)
    {
        if (freq_array[i].freq > 0)
            (*num_chars)++;
    }
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

// comparison function for qsort to sort char_data in non-increasing order by frequency
int compare_char_freq(const void* a, const void* b)
{
    char_data* fa = (char_data*) a;
    char_data* fb = (char_data*) b;
    return fb->freq - fa->freq;
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

    if(end - start > 2)
        for (int i = start; i <= end; i++)
        {
            current_prob += char_freq[i].prob;
            if (current_prob >= half_prob)
            {
                split_index = i-1;
                break;
            }
        }
    else
        split_index = start;

    //printf("\nStart = %d, End = %d, Split index = %d",start,end,split_index);

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

    //display_char_codes(char_freq,num_chars);

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


int main()
{
    int num_chars;
    char_data * char_freq = NULL;
    count_characters("Text_Sample3.txt", &num_chars, &char_freq);
    printf("Number of characters: %d\n", num_chars);
    shannon_fano(char_freq,0,num_chars-1,num_chars);
    display_char_codes(char_freq,num_chars);
    printf("%lf",calc_avg_code_len(char_freq,num_chars));
    free(char_freq);

    return 0;
}