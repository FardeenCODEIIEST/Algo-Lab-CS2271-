#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Here we are considering Sorting in Ascending order*/

void merge(int arr[], int l, int mid, int h, int *count)
{ // Count variable counts the number of exchange segments
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
      (*count)++;
    }
    else
    {
      arr[c3] = right[c2];
      c2++;
      c3++;
      (*count)++;
    }
  }
  while (c1 < size1)
  {
    arr[c3] = left[c1];
    c1++;
    c3++;
    (*count)++;
  }
  while (c2 < size2)
  {
    arr[c3] = right[c2];
    c2++;
    c3++;
    (*count)++;
  }
  free(left);
  free(right);
}
void mergeSort(int *a, int start, int end, int *count)
{
  if (start < end)
  {
    int mid = (start + (end - start) / 2);
    mergeSort(a, start, mid, count);
    mergeSort(a, mid + 1, end, count);
    merge(a, start, mid, end, count);
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
void fileToArray(int *arr, int n)
{
  FILE *fi = fopen("uniform_distribution.csv", "r");
  int temp;
  for (int i = 0; i < n; i++)
  {
    int k = rand() % 10; // Used to skip lines
    for (int t = 0; t < k; t++)
      ;
    fscanf(fi, "%d\n", &temp);
    arr[i] = (int)temp;
  }
  fclose(fi);
}
int main()
{
  srand(time(0));
  FILE *fp = fopen("uniform_distribution_obs_merge.csv", "w");
  int rounds = 18;
  int range = 50;
  int n = 2; // Initial Size
  fprintf(fp, "Size,Avg_Comparisons,Avg_Time_Taken\n");
  for (int i = 1; i <= rounds; i++)
  {
    long long count_sum = 0;
    float time_sum = 0;
    for (int i = 0; i < range; i++)
    {
      int a[n];
      fileToArray(a, n);
      int count = 0;
      float start_time = clock();
      mergeSort(a, 0, n - 1, &count);
      float end_time = clock();
      float time_required = (end_time - start_time) * 1000 / CLOCKS_PER_SEC;
      count_sum += count;
      time_sum += time_required;
      if (isSorted(a, n))
      {
        printf("Size=%d Run %d:%d comparisons, %0.6f ms time taken\n", n, i + 1, count, time_required);
      }
      else
      {
        printf("Array Not Sorted\n");
        break;
      }
    }
    float time_avg = (time_sum) / (range);
    long long count_avg = (count_sum) / (range);
    fprintf(fp, "%d,%lld,%0.6f\n", n, count_avg, time_avg);
    n *= 2; // Increasing size twice after each round
  }
  fclose(fp);
  return 0;
}