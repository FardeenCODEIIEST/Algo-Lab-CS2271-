#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Median of Median approach taking 5 elements in each group

#define MAX 100
#define ROUNDS 12

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
  int ele_in_last_group = size % divide_size;

  int next_arr_size;

  if (ele_in_last_group == 0)
  {
    next_arr_size = total_groups;
  }
  else
  {
    next_arr_size = total_groups + 1;
  }

  int next_arr[next_arr_size];

  for (int i = 0; i < next_arr_size; i++)
  {
    if (i == next_arr_size - 1)
    {
      next_arr[i] = median(arr, divide_size * i, size - 1);
    }
    else
    {
      next_arr[i] = median(arr, divide_size * i, divide_size * (i + 1) - 1);
    }
  }
  return median_of_medians(next_arr, next_arr_size, divide_size);
}
int main()
{
  srand(time(0));
  int size = 8;
  FILE *fp = fopen("Observation.csv", "w");
  fprintf(fp, "MOM,Direct Median\n");
  for (int j = 0; j < ROUNDS; j++)
  {
    int arr[size];
    int copy[size];
    for (int i = 0; i < size; i++)
    {
      arr[i] = rand() % MAX;
    }
    for (int i = 0; i < size; i++)
    {
      copy[i] = arr[i];
    }
    fprintf(fp, "%d,%d\n", median_of_medians(arr, size, 5), median(copy, 0, size - 1));
    size *= 2;
  }
  printf("File has been generated successfully\n");
  fclose(fp);
  return 0;
}
