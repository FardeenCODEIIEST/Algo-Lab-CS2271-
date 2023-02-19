#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For a random seed

/* We will be generating uniformly distributed dataset of 10e7 numbers each being
in the range of 0-100.
*/

/*For generating uniformly distributed numbers we just take any random number and
  take its remainder when divided by the max-value of the dataset, thus ensuring
  occurrence of any number in the range is equally likely.
*/
const long long TOTAL = 10e6;
const int MAX = 100;

int main()
{
  /*For generating random numbers*/
  srand(time(0));

  /*Writing the dataset into a csv file*/
  FILE *fp = fopen("uniform_distribution.csv", "w");
  for (int i = 0; i < TOTAL; i++)
  {
    fprintf(fp, "%d\n", rand() % MAX);
  }
  printf("The Uniform Distribution Dataset has been successfully generated.\n");
  fclose(fp);
  return 0;
}