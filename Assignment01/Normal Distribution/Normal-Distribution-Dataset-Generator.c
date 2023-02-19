#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For a random seed

/* We will be generating normally distributed dataset of 10e7 numbers each being
in the range of 0-200.
*/

/*For generating normally distributed numbers we take the consecutive sum
 modulo of any random number with the ratio of the max value in the range
 with the number of elements we take in each sub group.
*/

const long long TOTAL = 10e7;
const int MAX = 200;
const int SUB_ELEMENTS = 10;

int main()
{
  /*For generating random numbers*/
  srand(time(0));

  /*Writing the dataset into a csv file*/
  FILE *fp = fopen("normal_distribution.csv", "w");
  for (int i = 0; i < TOTAL; i++)
  {
    int sum = 0;
    for (int j = 0; j < SUB_ELEMENTS; j++)
    {
      sum += rand() % (MAX / SUB_ELEMENTS); // This ensures the frequency near mean to be high.
    }
    fprintf(fp, "%d\n", sum);
  }
  fclose(fp);
  printf("The Normal Distribution Dataset has been successfully generated.\n");
  return 0;
}