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
int partition(int *arr, int initial, int final, int *count)
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
    else if (left < right) // Here Count will increase by 1
    {
      (*count)++;
      swap(&arr[left], &arr[right]);
    }
    else
      return left;
  }
}

void quickSort(int *a, int start, int end, int *count)
{
  if (start < end)
  {
    int pivot_index = partition(a, start, end, count);
    quickSort(a, start, pivot_index, count);
    quickSort(a, pivot_index + 1, end, count);
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

void fileToArray(int *arr, int n) // reading the csv file into an array
{
  FILE *fi = fopen("normal_distribution.csv", "r");
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
  FILE *fp = fopen("normal_distribution_obs.csv", "w");
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
      quickSort(a, 0, n - 1, &count);
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