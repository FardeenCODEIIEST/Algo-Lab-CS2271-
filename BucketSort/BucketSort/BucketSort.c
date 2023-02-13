#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
  float data;
  struct node *next;
  struct node *prev;
} node;

node *insert(node *list, float d)
{
  node *new_node = (node *)malloc(sizeof(node));
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->data = d;

  if (list == NULL)
    list = new_node;
  else
  {
    node *temp = list;

    while (temp->next != NULL)
      temp = temp->next;

    temp->next = new_node;
    new_node->prev = temp;
  }

  return list;
}

node *delete_head(node *list, float *d)
{
  node *temp = list;
  list = list->next;

  if (list != NULL && list->prev != NULL)
    list->prev = NULL;

  *d = temp->data;
  free(temp);

  return list;
}

void swap(float *a, float *b)
{
  float c = *a;
  *a = *b;
  *b = c;
}

node *insertion_sort(node *list, int *count)
{
  if (list != NULL)
  {
    node *ahead = list->next;

    while (ahead != NULL)
    {
      node *rev = ahead;

      while (rev->prev != NULL && rev->prev->data > rev->data)
      {
        swap(&(rev->data), &(rev->prev->data));
        rev = rev->prev;
        (*count)++;
      }
      ahead = ahead->next;
      (*count)++;
    }

    return list;
  }
  return NULL; // if list is null
}

void bucket_sort(float *arr, int n, int *count)
{
  node *bins[n];

  for (int i = 0; i < n; i++)
    bins[i] = NULL;

  int initial = 0;

  for (int i = 0; i < n; i++) // Insertion of elements in each bin
  {
    initial = floor(n * arr[i]);
    bins[initial] = insert(bins[initial], arr[i]);
  }

  for (int i = 0; i < n; i++) // insertion sort on each bin
    bins[i] = insertion_sort(bins[i], count);

  initial = 0;
  float temp;

  for (int i = 0; i < n; i++)
  {
    while (bins[i] != NULL)
    {
      bins[i] = delete_head(bins[i], &temp);
      arr[initial] = temp;
      initial++;
    }
  }
}

int is_array_sorted(float *arr, int length)
{
  for (int i = 0; i < length - 1; i++)
    if (arr[i] > arr[i + 1])
      return 0;

  return 1;
}

void text_to_arr(float *arr, int n)
{

  FILE *fin = fopen("normalized_normal_distribution.csv", "r");
  char a[6];
  fscanf(fin, "%s\n", a);
  float temp = 0;
  for (int i = 0; i < n; i++)
  {
    int skip_line = rand() % 10;

    for (int j = 0; j < skip_line; j++)
      ;

    fscanf(fin, "%f\n", &temp);
    arr[i] = temp;
  }

  fclose(fin);
}

void main()
{
  srand(time(0));

  int rounds = 17;
  int sub_rounds = 15;

  FILE *fout = fopen("bucket_normal_obs.csv", "w");

  fprintf(fout, "Size,Avg_Comparison,Avg_Time\n");

  int n = 2;
  for (int p = 0; p < rounds; p++)
  {
    long sum_count = 0;
    float sum_time = 0;

    for (int i = 0; i < sub_rounds; i++)
    {
      float a[n];
      text_to_arr(a, n);
      for (int i = 0; i < n; i++)
      {
        a[i] /= 100;
      }
      int count = 0;

      float start_time = clock();
      bucket_sort(a, n, &count);
      float end_time = clock();

      sum_count += count;

      float time_taken = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
      sum_time += time_taken;

      if (is_array_sorted(a, sizeof(a) / sizeof(int)))
        printf("Size = %d Run %d: %d comparisons, %0.6f ms\n", n, i + 1, count, time_taken);
      else
      {
        printf("Array Not Sorted\n");
        break;
      }
    }

    float avg_time = sum_time / sub_rounds;
    long avg_count = sum_count / sub_rounds;
    fprintf(fout, "%d,%ld,%0.6f\n", n, avg_count, avg_time);
    n *= 2;
  }

  fclose(fout);
}