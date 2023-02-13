#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

void insertion_sort(int *arr, int start, int final)
{
  for (int i = start; i <= final; i++)
  {
    int temp = arr[i];
    int pos = i - 1;
    while (pos >= start && arr[pos] > temp)
    {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = temp;
  }
}

int median(int *arr, int start, int final)
{
  insertion_sort(arr, start, final);
  int mid = (start + final) / 2;
  return arr[mid];
}

int median_of_medians(int *arr, int size, int divide_size)
{
  if (size < divide_size)
  {
    return median(arr, 0, size - 1);
  }
  int total_groups = size / divide_size;
  int ele_int_last = size % divide_size;

  int next_size;
  if (ele_int_last == 0)
  {
    next_size = total_groups;
  }
  else
  {
    next_size = total_groups + 1;
  }
  int next_arr[next_size];
  for (int i = 0; i < next_size; i++)
  {
    if (i == next_size - 1)
    {
      next_arr[i] = median(arr, divide_size * i, size - 1);
    }
    else
    {
      next_arr[i] = median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }
  }
  return median_of_medians(next_arr, next_size, divide_size);
}

int partition(int *arr, int start, int final)
{
  int pivot_value = arr[start];

  int left = start;
  int right = final;
  while (1)
  {
    while (arr[left] < pivot_value)
    {
      left++;
    }
    while (arr[right] > pivot_value)
    {
      right--;
    }
    if (arr[left] == arr[right])
    {
      if (left == right)
      {
        return left;
      }
      else
      {
        return right--;
      }
    }
    else if (left < right)
    {
      swap(&arr[left], &arr[right]);
    }
    else
    {
      return left;
    }
  }
}

int partition_size(int *arr, int size, int divide_size)
{
  int median = median_of_medians(arr, size, divide_size);
  for (int i = 0; i < size; i++)
  {
    if (arr[i] == median)
    {
      swap(&arr[0], &arr[i]);
      return partition(arr, 0, size - 1);
    }
  }
}

void toArray(int *arr, int n)
{
  FILE *fin = fopen("normal_distribution.csv", "r");
  for (int i = 0; i < n; i++)
  {
    int skip = rand() % 15;
    for (int j = 0; j < skip; j++)
      ;
    fscanf(fin, "%d\n", &arr[i]);
  }
  fclose(fin);
}

int main()
{
  const int SIZE = 100000;
  srand(time(0));

  int divide_size = 7;
  int rounds = 15;
  int parti_size;
  float avg_parti_size;

  FILE *fp = fopen("MOM_normal_part_7_obs.csv", "w");
  fprintf(fp, "Size,Avg Partition Size\n");
  for (int sz = 100; sz <= SIZE; sz += 100)
  {
    int arr[sz];
    avg_parti_size = 0;
    for (int i = 0; i < rounds; i++)
    {
      toArray(arr, sz);
      parti_size = partition_size(arr, sz, divide_size);
      avg_parti_size += parti_size;
    }
    avg_parti_size /= rounds;
    printf("Size: %d Avg Partition Size: %f\n", sz, avg_parti_size);
    fprintf(fp, "%d,%f\n", sz, avg_parti_size);
  }
  fclose(fp);
  return 0;
}
