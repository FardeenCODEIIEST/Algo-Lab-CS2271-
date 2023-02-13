#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Here we are considering Sorting in Ascending order*/

void merge(int arr[], int l, int mid, int h)
{
  int count = 0; // Counting number of exchange segments
  int size1 = mid - l + 1;
  int size2 = h - mid;
  int *left = (int *)malloc(size1 * sizeof(int));
  int *right = (int *)malloc(size2 * sizeof(int));
  for (int i = 0; i < size1; i++)
  {
    left[i] = arr[l + i];
  }
  for (int i = 0; i < size2; i++)
  {
    right[i] = arr[mid + i + 1];
  }
  int c1 = 0, c2 = 0, c3 = l;
  while (c1 < size1 && c2 < size2)
  {
    if (left[c1] <= right[c2])
    {
      arr[c3] = left[c1];
      c3++;
      c1++;
      count++;
    }
    else
    {
      arr[c3] = right[c2];
      c2++;
      c3++;
      count++;
    }
  }
  while (c1 < size1)
  {
    arr[c3] = left[c1];
    c1++;
    c3++;
    count++;
  }
  while (c2 < size2)
  {
    arr[c3] = right[c2];
    c2++;
    c3++;
    count++;
  }
  free(left);
  free(right);
}
void mergeSort(int *a, int start, int end)
{
  if (start < end)
  {
    int mid = (start + (end - start) / 2);
    mergeSort(a, start, mid);
    mergeSort(a, mid + 1, end);
    merge(a, start, mid, end);
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
    float start = clock();
    mergeSort(a, 0, n - 1);
    float end = clock();
    if (isSorted(a, n))
    {
      fprintf(fp, "Sorted Array:\n");
      for (int i = 0; i < n; i++)
      {
        fprintf(fp, "%d ", a[i]);
      }
      fprintf(fp, "\n");
      fprintf(fp, "Run-time for case-%d: %0.6fms\n\n", i + 1, (end - start) * 1000 / CLOCKS_PER_SEC);
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