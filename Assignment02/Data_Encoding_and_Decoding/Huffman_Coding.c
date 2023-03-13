#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int ui;

#define MAX_TREE_HT 100

struct MinHeapNode
{
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};
typedef struct MinHeapNode MinHeapNode;

struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};
typedef struct MinHeap MinHeap;

// To create a new min heap node
struct MinHeapNode* new_node(char data, unsigned freq)
{
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->left = node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

// To create a min heap of given capacity
MinHeap* create_min_heap(unsigned capacity)
{
    MinHeap* min_heap = (MinHeap*)malloc(sizeof(MinHeap));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = (MinHeapNode**)malloc(min_heap->capacity * sizeof(MinHeapNode*));
    return min_heap;
}

void swap_nodes(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* min_heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < min_heap->size && min_heap->array[left]->freq < min_heap->array[smallest]->freq)
        smallest = left;

    if (right < min_heap->size && min_heap->array[right]->freq < min_heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swap_nodes(&min_heap->array[smallest], &min_heap->array[idx]);
        min_heapify(min_heap, smallest);
    }
}

bool is_leaf_node(MinHeapNode* node)
{
    return !(node->left) && !(node->right);
}

// To build the min heap
void build_min_heap(MinHeap* min_heap)
{
    int n = min_heap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; --i)
        min_heapify(min_heap, i);
}

// To insert a new node into the min heap
void insert_min_heap(MinHeap* min_heap, MinHeapNode* node)
{
    ++min_heap->size;
    int i = min_heap->size - 1;

    while (i && node->freq < min_heap->array[(i-1)/2]->freq)
    {
        min_heap->array[i] = min_heap->array[(i-1)/2];
        i = (i-1)/2;
    }

    min_heap->array[i] = node;
}

// To extract the minimum node from the min heap
MinHeapNode* extract_min(MinHeap* min_heap)
{
    MinHeapNode* temp = min_heap->array[0];
    min_heap->array[0] = min_heap->array[min_heap->size - 1];

    --min_heap->size;
    min_heapify(min_heap, 0);

    return temp;
}


// To build a Huffman tree
MinHeapNode* build_huffman_tree(char * data, int * freq, int size)
{
    MinHeapNode *left, *right, *top;

    // Creating a min heap and inserting all characters of data (ofc)
    MinHeap* min_heap = create_min_heap(size);

    for (int i = 0; i < size; ++i)
        insert_min_heap(min_heap, new_node(data[i], freq[i]));

    // The Huffman tree
    while (min_heap->size > 1)
    {
        left = extract_min(min_heap);
        right = extract_min(min_heap);

        top = new_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insert_min_heap(min_heap, top);
    }

    return extract_min(min_heap);
}

// To print Huffman codes
void print_huffman_codes(MinHeapNode* root, int  * arr, int top)
{
    // Assigning 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        print_huffman_codes(root->left, arr, top + 1);
    }

    // Assigning 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        print_huffman_codes(root->right, arr, top + 1);
    }

    // If a leaf node, print character and its code
    if (is_leaf_node(root))
    {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

// To perform Huffman encoding
void huffman_encoding(char data[], int freq[], int size)
{
    MinHeapNode* root = build_huffman_tree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;

    print_huffman_codes(root, arr, top);
}

// To perform Huffman decoding
void huffman_decoding(MinHeapNode* root, char* encoded_str)
{
    MinHeapNode* curr_node = root;
    ui i = 0;

    while (encoded_str[i] != '\0')
    {
        if (encoded_str[i] == '0')
            curr_node = curr_node->left;
        else
            curr_node = curr_node->right;

        if (is_leaf_node(curr_node))
        {
            printf("%c", curr_node->data);
            curr_node = root;
        }

        i++;
    }
}

// To free the memory allocated for the Huffman tree
void free_huffman_tree(MinHeapNode* root)
{
    if (!root)
        return;

    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}


// Main function
void main()
{
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    ui freq[] = { 5, 9, 12, 13, 16, 45 };
    ui size = sizeof(data) / sizeof(data[0]);

    huffman_encoding(data, freq, size);
}
