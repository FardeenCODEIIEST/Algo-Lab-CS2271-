#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
#define ROUNDS 15
#define COUNTER 1000

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
  int ele_in_last = size % divide_size;

  int next_size;

  if (ele_in_last == 0)
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

int main()
{
  srand(time(0));

  int arr_size = 100000;
  float start_time, end_time, time_taken;
  float avg_time;
  int divide_size;

  FILE *fp = fopen("Observation.csv", "w");
  fprintf(fp, "Divide Size,Avg Time\n");

  int arr[arr_size];
  for (int i = 1; i <= COUNTER; i++)
  {
    divide_size = 2 * i + 1;
    avg_time = 0;
    for (int j = 0; j < ROUNDS; j++)
    {
      for (int j1 = 0; j1 < arr_size; j1++)
      {
        arr[j1] = rand() % MAX;
      }
      start_time = clock();
      int median = median_of_medians(arr, arr_size, divide_size);
      end_time = clock();
      time_taken = (float)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
      avg_time += time_taken;
    }
    avg_time /= ROUNDS;
    printf("Divide Size: %4d Avg Time: %3.6fms\n", divide_size, avg_time);
    fprintf(fp, "%d,%f\n", divide_size, avg_time);
  }
  fclose(fp);
  return 0;
}