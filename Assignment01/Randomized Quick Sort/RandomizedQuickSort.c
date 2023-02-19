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

// Randomising the pivot position
int randomized_partition(int *a, int start, int end, int *count)
{
  int p = start + rand() % (end - start);
  swap(&a[start], &a[p]);
  return partition(a, start, end, count);
}

// Randomising the selection of pivot under a deliberation
int randomized_select(int *arr, int start, int end, int pos_to_find, int *count)
{
  if (start == end)
    return start;

  // Edge cases
  if (pos_to_find < start)
  {
    printf("Index is less than start index\n");
    exit(0);
  }

  if (pos_to_find > end)
  {
    printf("Index is more than end index\n");
    exit(0);
  }

  int q = randomized_partition(arr, start, end, count);

  if (pos_to_find < q + 1)
    return randomized_select(arr, start, q, pos_to_find, count);
  else
    return randomized_select(arr, q + 1, end, pos_to_find, count);
}

// deliberately doing the partitions
void quickSort_1_1000_part(int *a, int start, int end, int *count)
{
  if (start < end)
  {
    int pos_to_find = start + (end - start) / 1000;
    int pivot_index = randomized_select(a, start, end, pos_to_find, count);
    quickSort_1_1000_part(a, start, pivot_index, count);
    quickSort_1_1000_part(a, pos_to_find + 1, end, count);
  }
}

void quickSort_1_5000_part(int *a, int start, int end, int *count)
{
  if (start < end)
  {
    int pos_to_find = start + (end - start) / 5000;
    int pivot_index = randomized_select(a, start, end, pos_to_find, count);
    quickSort_1_5000_part(a, start, pivot_index, count);
    quickSort_1_5000_part(a, pos_to_find + 1, end, count);
  }
}

void quickSort_1_10000_part(int *a, int start, int end, int *count)
{
  if (start < end)
  {
    int pos_to_find = start + (end - start) / 10000;
    int pivot_index = randomized_select(a, start, end, pos_to_find, count);
    quickSort_1_10000_part(a, start, pivot_index, count);
    quickSort_1_10000_part(a, pos_to_find + 1, end, count);
  }
}

// Randomly doing the partitions
void quickSort_random(int *a, int start, int end, int *count)
{
  if (start < end)
  {
    int pivot_index = randomized_partition(a, start, end, count);
    quickSort_random(a, start, pivot_index, count);
    quickSort_random(a, pivot_index + 1, end, count);
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
  FILE *fp = fopen("uniform_distribution_obs_quick_1_10000_part.csv", "w");
  int rounds = 15;
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
      quickSort_1_10000_part(a, 0, n - 1, &count);
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