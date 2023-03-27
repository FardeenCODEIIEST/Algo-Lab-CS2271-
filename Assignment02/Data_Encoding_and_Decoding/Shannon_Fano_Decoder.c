#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct CodebookEntry
{
    int ascii;
    char code[20];  // Maximum size of a Shannon Fano code
};
typedef struct CodebookEntry CodebookEntry;

void read_codebook(const char *filename, CodebookEntry *codebook, int *numchars);
void display_codebook(CodebookEntry *codebook, int numchars);

struct SF_Node
{
    CodebookEntry entry;
    struct SF_Node * left;
    struct SF_Node * right;
};
typedef struct SF_Node SF_Node;

/*SF_Node *allocate(CodebookEntry entry)
{
    SF_Node *temp = (SF_Node*)malloc(sizeof(SF_Node));
    temp->entry.ascii = entry.ascii;
    strcpy(temp->entry.code,entry.code);
    temp->left = temp->right = NULL;
    return temp;
    //printf("\nAllocated: %d %s",temp->entry.ascii,temp->entry.code);
}*/

SF_Node *false_allocate()
{
    SF_Node *temp = (SF_Node*)malloc(sizeof(SF_Node));
    temp->entry.ascii = -1;
    strcpy(temp->entry.code,"\0");
    temp->left = temp->right = NULL;
    return temp;
}

SF_Node *insertNode(SF_Node *root, CodebookEntry entry)
{
    if (!root)
        root = false_allocate();

    SF_Node *temp = root;

    for (int i = 0; i < strlen(entry.code); i++)
    {
        if (entry.code[i] == '0')
        {
            if (!temp->left)
                temp->left = false_allocate();
            temp = temp->left;
        }
        else if (entry.code[i] == '1')
        {
            if (!temp->right)
                temp->right = false_allocate();
            temp = temp->right;
        }
    }

    temp->entry.ascii = entry.ascii;
    strcpy(temp->entry.code, entry.code);

    return root;
}

bool is_binary_tree(SF_Node *node)
{
    if (node == NULL)
        return 1;
    if (node->left != NULL && node->right != NULL)
        return is_binary_tree(node->left) && is_binary_tree(node->right);
    if (node->left == NULL && node->right == NULL)
        return 1;
    if (node->left == NULL && node->right != NULL)
        return is_binary_tree(node->right);
    if (node->left != NULL && node->right == NULL)
        return is_binary_tree(node->left);
    return 0;
}


void displayTree(SF_Node *t)
{
    if (t)
    {
        displayTree(t->left);
        if(t->entry.ascii > 0)
            printf("%d %s\n", t->entry.ascii, t->entry.code);
        displayTree(t->right);
    }
}

void decodeText(SF_Node *t, const char *encoded_file, const char *decoded_file)
{
    FILE *fp1 = fopen(encoded_file, "r");
    if (fp1 == NULL)
    {
        printf("Error: Could not open encoded text file\n");
        fclose(fp1);
        exit(1);
    }

    FILE *fp2 = fopen(decoded_file, "w");
    if (fp2 == NULL)
    {
        printf("Error: Could not open codebook file\n");
        fclose(fp1);
        fclose(fp2);
        exit(1);
    }

    SF_Node *temp = t;

    int c;
    while ((c = fgetc(fp1)) != EOF)
    {
        if (c == '0')
            temp = temp->left;
        else if (c == '1')
            temp = temp->right;

        if (temp->entry.ascii != -1)
        {
            fputc(temp->entry.ascii, fp2);
            temp = t;
        }
    }

    fclose(fp1);
    fclose(fp2);
}

// Function to read in a Shannon Fano codebook from a file
void read_codebook(const char *filename, CodebookEntry *codebook, int *numchars)
{
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Could not open codebook file\n");
        exit(1);
    }

    fscanf(fp, "%d\n", numchars);

    for (int i = 0; i < *numchars; i++)
        fscanf(fp, "%d %s\n", &codebook[i].ascii, codebook[i].code);

    fclose(fp);
}

void display_codebook(CodebookEntry *codebook, int numchars)
{
    printf("ASCII\tCode\n");
    printf("-----\t----\n");
    for (int i = 0; i < numchars; i++)
    {
        if((char)codebook[i].ascii == '\n')
            printf("<enter>\t %s\n", codebook[i].code);
        
        else if((char)codebook[i].ascii == ' ')
            printf("<space>\t %s\n", codebook[i].code);
        
        else
            printf("%c\t %s\n", codebook[i].ascii, codebook[i].code);
    }
}

bool compareFiles(const char *file1, const char *file2)
{
    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");

    if (fp1 == NULL || fp2 == NULL)
    {
        printf("Error: Could not open files\n");
        fclose(fp1);
        fclose(fp2);
        exit(1);
    }

    int ch1 = fgetc(fp1);
    int ch2 = fgetc(fp2);

    while (ch1 != EOF && ch2 != EOF)
    {
        if (ch1 != ch2)
        {
            fclose(fp1);
            fclose(fp2);
            return false;
        }

        ch1 = fgetc(fp1);
        ch2 = fgetc(fp2);
    }

    if (ch1 == EOF && ch2 == EOF)
    {
        fclose(fp1);
        fclose(fp2);
        return true;
    }
    else
    {
        fclose(fp1);
        fclose(fp2);
        return false;
    }
}

int main() 
{
    CodebookEntry codebook[256] = {0};
    int numchars;

    char original_file[] = "Text_Sample1.txt";
    char encoded_file[] = "Text_Sample1_Shannon_Fano_Encoded.txt";
    char decoded_file[] = "Text_Sample1_Shannon_Fano_Decoded.txt";
    char codebook_file[] = "Text_Sample1_Shannon_Fano_Codebook.txt";

    read_codebook(codebook_file, codebook, &numchars);
    
    SF_Node * SF_tree = NULL;

    for (int i = 0; i < numchars; i++)
        SF_tree = insertNode(SF_tree,codebook[i]);
    
    if(is_binary_tree(SF_tree)==true)
        printf("\nOh yes!");
    
    //displayTree(SF_tree);

    decodeText(SF_tree, encoded_file, decoded_file);

    if(compareFiles(original_file, decoded_file)==true)
        printf("\nSuccess!");

    printf("\nEnd of program");

    return 0;
}
