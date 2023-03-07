#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Here we are considering Sorting in Ascending order*/

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
// Inplace Quick Sort
int partition(int *arr, int initial, int final)
{
  // Taking initial element as the pivot element
  int pivot_value = arr[initial];
  int left = initial;
  int right = final;

  while (1)
  {
    while (arr[left] < pivot_value)
      left++;

    while (pivot_value < arr[right])
      right--;

    if (arr[left] == arr[right])
    {
      if (left == right)
        return left;
      else
        right--;
    }
    else if (left < right)
      swap(&arr[left], &arr[right]);
    else
      return left;
  }
}

void quickSort(int *a, int start, int end)
{
  if (start < end)
  {
    int pivot_index = partition(a, start, end);
    quickSort(a, start, pivot_index);
    quickSort(a, pivot_index + 1, end);
  }
}

int isSorted(int *a, int n)
{
  for (int i = 0; i < n - 1; i++)
  {
    if (a[i] > a[i + 1])
      return 0;
  }
  return 1;
}
int main()
{
  srand(time(0));
  FILE *fp = fopen("Result.txt", "w");
  for (int i = 0; i < 500; i++)
  {
    int n = 128; // Size of each array
    int *a = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
      a[i] = rand() % 100;
    }
    fprintf(fp, "Unsorted Array:\n");
    for (int i = 0; i < n; i++)
    {
      fprintf(fp, "%d ", a[i]);
    }
    fprintf(fp, "\n");
    double start = clock();
    quickSort(a, 0, n - 1);
    double end = clock();
    if (isSorted(a, n))
    {
      fprintf(fp, "Sorted Array:\n");
      for (int i = 0; i < n; i++)
      {
        fprintf(fp, "%d ", a[i]);
      }
      fprintf(fp, "\n");
      fprintf(fp, "Run-time for case-%d: %0.6fms\n\n", i + 1, (double)(end - start) * 1000 / CLOCKS_PER_SEC);
      free(a);
    }
    else
    {
      fprintf(fp, "Algorithm failed: Array is not sorted\n\n");
      free(a);
      break;
    }
  }
  fprintf(fp, "Algorithm has been successfully executed\n");
  fclose(fp);
  return 0;
}
