#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void uniform_generator(int low, int up, int N)
{
    FILE *fp = fopen("/Users/anishbanerjee/Desktop/uniform_dataset.txt", "w");
    fprintf(fp,"%d\n",N);
    for (int i = 0; i < N; i++) {
        double rand_num = (double) rand() / RAND_MAX * (up-low);
        rand_num += low;
        fprintf(fp, "%lf\n", rand_num);
    }
    fclose(fp);
}

double standard_deviation (double data[], int n, int mean)
{
    double ssd = 0.0;
    for (int i=0; i<n; i++)
    {
        double diff = data[i] - mean;
        ssd+= diff * diff;
    }
    return sqrt (ssd/n);
}

double randn(void)
{
    double u = ((double) rand() / RAND_MAX) * 2 - 1;
    double v = ((double) rand() / RAND_MAX) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return randn();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
}

void normal_generator(int low, int up, int N)
{
    srand(time(0));
    FILE *fp = fopen("/Users/anishbanerjee/Desktop/normal_dataset.txt", "w");
    int n = up-low+1;
    double data[n];
    for (int i=0; i<n; i++)
        data[i]=low+i;
    double mean = 0.0;
    for (int i=0; i<n; i++)
    {
        mean+=data[i];
    }
    mean/=n;
    double std_dev = standard_deviation(data, n, mean);
    printf("Mean: %f, SD = %f \n",mean,std_dev);
    fprintf(fp,"%d\n",N);
    for (int i=0; i<N; i++)
    {
        double rand_num = mean + std_dev * randn();
        fprintf(fp, "%lf\n",rand_num);
    }
    fclose(fp);
}

int main()
{
    int choice;
    printf("MENU\n1.Uniform Generator\n2.Normal Generator\nAnything else to terminate\nEnter choice: ");
    scanf("%d",&choice);
    if (choice <= 2)
    {
        int low,up,N;
        printf("Enter lower bound: ");
        scanf("%d",&low);
        printf("Enter upper bound: ");
        scanf("%d",&up);
        printf("Enter number of data to be generated in the data-set: ");
        scanf("%d",&N);
        if (choice == 1)
        {
            uniform_generator(low, up, N);
            printf("The Uniform data-set has been generated in the text file named 'uniform_dataset.txt' on the Desktop \n");
        }
        else if (choice == 2)
        {
            normal_generator(low, up, N);
            printf("The Normal data-set has been generated in the text file named 'normal_dataset.txt' on the Desktop \n");

        }
    }
}
