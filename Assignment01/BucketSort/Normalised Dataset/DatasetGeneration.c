#include <stdio.h>

const int TOTAL_NUMBER = 10e6;
const int MAX_VAL = 100;

int main()
{
  FILE *fin = fopen("uniform_distribution.csv", "r");
  FILE *fp = fopen("normalised_uniform_distribution.csv", "w");

  int temp;
  long long i = 0;

  fprintf(fp, "value\n");
  while (!feof(fin))
  {
    i++;
    fscanf(fin, "%d\n", &temp);
    fprintf(fp, "%0.6f\n", ((float)temp) / MAX_VAL);
  }
  printf("The normalised dataset has been generated\n");
  fclose(fin);
  fclose(fp);
  return 0;
  return 0;
}