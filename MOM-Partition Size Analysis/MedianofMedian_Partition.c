#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

void insertion_sort(int arr[], int start, int final)
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

int median(int arr[], int start, int final)
{
  insertion_sort(arr, start, final);
  int mid = (start + final) / 2;
  return arr[mid];
}

int median_of_median(int arr[], int arr_size, int divide_size)
{
  if (arr_size < divide_size)
  {
    return median(arr, 0, arr_size - 1);
  }

  int total_group = arr_size / divide_size;
  int elements_in_last = arr_size % divide_size;

  int next_size;

  if (elements_in_last == 0)
    next_size = total_group;
  else
    next_size = total_group + 1;

  int next_arr[next_size];

  for (int i = 0; i < next_size; i++)
  {
    if (i == next_size - 1)
      next_arr[i] = median(arr, divide_size * i, arr_size - 1);
    else
      next_arr[i] = median(arr, divide_size * i, divide_size * (i + 1) - 1);
  }

  return median_of_median(next_arr, next_size, divide_size);
}

int partition(int *arr, int start, int final)
{
  int pivot_value = arr[start];

  int left = start;
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

int find_partition_size_MoM(int *arr, int arr_size, int divide_size)
{
  int val = median_of_median(arr, arr_size, divide_size);
  int i;
  for (i = 0; i < arr_size; i++)
    if (arr[i] == val)
    {
      break;
    }
  swap(&arr[0], &arr[i]);
  return partition(arr, 0, arr_size - 1);
}

void toArray(int *arr, int n)
{

  FILE *fin = fopen("uniform_distribution.csv", "r");

  int temp = 0;
  for (int i = 0; i < n; i++)
  {
    int skip_line = rand() % 20;

    for (int j = 0; j < skip_line; j++)
      ;

    fscanf(fin, "%d\n", &temp);
    arr[i] = (int)temp;
  }

  fclose(fin);
}

int main()
{
  srand(time(0));

  const int max_arr_size = 1e5;

  int divide_size = 7;
  int rounds = 10;
  int part_size;
  float avg_part_size;

  FILE *fout = fopen("MoM_uniform_part_7_obs.csv", "w");
  fprintf(fout, "Size,Avg Partition Size\n");

  for (int arr_size = 100; arr_size <= max_arr_size; arr_size += 100)
  {
    int arr[arr_size];
    avg_part_size = 0;

    for (int i = 0; i < rounds; i++)
    {
      toArray(arr, arr_size);

      part_size = find_partition_size_MoM(arr, arr_size, divide_size);

      avg_part_size += part_size;
    }

    avg_part_size = avg_part_size / rounds;

    printf("Size: %d Avg Part Size: %f \n", arr_size, avg_part_size);
    fprintf(fout, "%d,%f\n", arr_size, avg_part_size);
  }

  fclose(fout);
  return 0;
}