#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int count = 0;
#define BUCKET_SIZE 100

void bucketSort(float arr[], int size)
{
    if (size <= 1)
        return;

    float* buckets[BUCKET_SIZE];
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        buckets[i] = (float*)malloc(sizeof(float) * size);
    }
    int counts[BUCKET_SIZE] = {0};
    for (int i = 0; i < size; i++)
    {
        int bucketIndex = (int)(arr[i] * BUCKET_SIZE);
        buckets[bucketIndex][counts[bucketIndex]] = arr[i];
        counts[bucketIndex]++;
    }

    int index = 0;
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        int currentCount = counts[i];
        if (currentCount > 1)
        {
            for (int j = 1; j < currentCount; j++)
            {
                float key = buckets[i][j];
                int k = j - 1;
                while (k >= 0) {
                    if (buckets[i][k] <= key)
                    {
                        count++;
                        break;
                    }
                    buckets[i][k + 1] = buckets[i][k];
                    k--;
                }
                buckets[i][k + 1] = key;
            }
        }
        for (int j = 0; j < currentCount; j++)
        {
            arr[index++] = buckets[i][j];
        }
    }
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        free(buckets[i]);
    }
}

void swap (float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void print_array (float a[], int n)
{
    for (int i=0; i<n; i++)
        printf("%f ",a[i]);
    printf("\n");
}

int partition(float arr[], int low, int high)
{
    float pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        count+=1;
        if (arr[j] <= pivot)
        {
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    float temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int median_of_3 (float a[], int l, int r)
{
    int mid = (l+r)/2;
    if (a[r] < a[l])
        swap (&a[l],&a[r]);
    if (a[mid] < a[l])
        swap (&a[l],&a[mid]);
    if (a[r] < a[mid])
        swap (&a[mid],&a[r]);
    return mid;
}

void quick_sort (float a[], int l, int r)
{
    if (r <= l)
        return;
    int median = median_of_3(a, l, r);
    swap (&a[l], &a[median]);
    float j = partition(a, l, r);
    quick_sort(a, l, j-1);
    quick_sort(a, j+1, r);
}


void randomQuickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        int randomIndex = low + rand() % (high - low);
        float temp = arr[randomIndex];
        arr[randomIndex] = arr[high];
        arr[high] = temp;
        int partitionIndex = partition(arr, low, high);
        randomQuickSort(arr, low, partitionIndex - 1);
        randomQuickSort(arr, partitionIndex + 1, high);
    }
}

void merge(float arr[], float left[], int leftSize, float right[], int rightSize)
{
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize)
    {
        count+=1;
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        } else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < leftSize)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(float arr[], int size)
{
    if (size < 2)
        return;
    int mid = size / 2;
    float left[mid];
    float right[size - mid];
    for (int i = 0; i < mid; i++)
        left[i] = arr[i];
    for (int i = mid; i < size; i++)
        right[i - mid] = arr[i];
    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);
}

void uniform_generator(int low, int up, int N)
{
    FILE *fp = fopen("/Users/anishbanerjee/Desktop/uniform_dataset.txt", "w");
    FILE *fs = fopen("/Users/anishbanerjee/Desktop/master_result.txt", "a");
    //fprintf(fs,"\nUNIFORM DATASET\n");
    fprintf(fp,"%d\n",N);
    for (int i = 0; i < N; i++)
    {
        double rand_num = (double) rand() / RAND_MAX * (up-low);
        rand_num += low;
        fprintf(fp, "%lf\n", rand_num);
        //fprintf(fs, "%lf ", rand_num);
    }
    fclose(fp);
    fclose(fs);
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
    FILE *fs = fopen("/Users/anishbanerjee/Desktop/master_result.txt", "a");
    //fprintf(fs,"\nNORMAL DATASET\n");
    fprintf(fp,"%d\n",N);
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
    //printf("Mean: %f, SD = %f \n",mean,std_dev);
    for (int i=0; i<N; i++)
    {
        double rand_num = mean + std_dev * randn();
        fprintf(fp, "%lf\n",rand_num);
        //fprintf(fs, "%lf ",rand_num);
    }
    fclose(fp);
    fclose(fs);
}

int main()
{
    FILE *fgraph = fopen("/Users/anishbanerjee/Desktop/master_graph_results.txt","w");
    fclose (fgraph);
    FILE *ftime = fopen("/Users/anishbanerjee/Desktop/master_time_graph_results.txt","w");
    fclose (ftime);
    printf("MASTER PROGRAM TO COMPARE OPERATIONS ON SORTS\n");
    long counter[8];
    float tcounter[8];
    counter[0]=0;
    counter[1]=0;
    counter[2]=0;
    counter[3]=0;
    counter[4]=0;
    counter[5]=0;
    counter[6]=0;
    counter[7]=0;
    tcounter[0]=0;
    tcounter[1]=0;
    tcounter[2]=0;
    tcounter[3]=0;
    tcounter[4]=0;
    tcounter[5]=0;
    tcounter[6]=0;
    tcounter[7]=0;
    FILE *fp = fopen("/Users/anishbanerjee/Desktop/master_result.txt", "w");
    fclose(fp);
    int low,up,N;
    printf("Enter lower bound: ");
    scanf("%d",&low);
    printf("Enter upper bound: ");
    scanf("%d",&up);
    printf("\nGenerating...Working on Results...\n");
    FILE *fres1 = fopen("/Users/anishbanerjee/Desktop/easy_master_result.txt","w");
    fprintf(fres1,"SUMMARISED RESULTS: \n");
    fprintf(fres1,"Lower Bound: %d\n", low);
    fprintf(fres1,"Upper Bound: %d\n", up);
    fprintf(fres1,"Constant is calculated w.r.t. \n-> n log2 n for Merge, Quick and Randomised Quick Sort \n-> n for Bucket Sort \n");
    fclose(fres1);
    for (int pow=1; pow<=16; pow++)
    {
        counter[0]=0;
        counter[1]=0;
        counter[2]=0;
        counter[3]=0;
        counter[4]=0;
        counter[5]=0;
        counter[6]=0;
        counter[7]=0;
        
        tcounter[0]=0;
        tcounter[1]=0;
        tcounter[2]=0;
        tcounter[3]=0;
        tcounter[4]=0;
        tcounter[5]=0;
        tcounter[6]=0;
        tcounter[7]=0;
        
        int mpow=1, runpow=1;
        for (int j=1; j<=pow; j++)
        {
            mpow *=2;
        }
        N = mpow;
        runpow=4;
        if (N>10)
            runpow=10;
        FILE *fres = fopen("/Users/anishbanerjee/Desktop/master_result.txt", "a");
        fprintf(fres,"\nNUMBER OF ELEMENTS: %d\n",N);
        fclose(fres);
        for (int i=1; i<=runpow; i++)
        {
        
            FILE *fres = fopen("/Users/anishbanerjee/Desktop/master_result.txt", "a");
            fprintf(fres,"\nDATASET COMBINATION: %d\n",i);
            fclose(fres);
            uniform_generator(low, up, N);
            normal_generator(low, up, N);
            
            //merge_sort
            fres = fopen("/Users/anishbanerjee/Desktop/master_result.txt","a");
            fprintf(fres,"\n\nMERGE SORT:\n");
            count = 0;
            fputs("\nUNIFORM DATASET\n",fres);
            FILE *fp = fopen("/Users/anishbanerjee/Desktop/uniform_dataset.txt","r");
            int n;
            fscanf(fp,"%d ",&n);
            float arr[n];
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            clock_t start = clock();
            mergeSort(arr, n);
            clock_t end = clock();
            double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[0]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[0]+=time_taken*1000;
            fclose(fp);
            count = 0;
            fprintf(fres,"\nNORMAL DATASET\n");
            fp = fopen("/Users/anishbanerjee/Desktop/normal_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            start = clock();
            mergeSort(arr, n);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[1]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[1]+=time_taken*1000;
            fclose(fp);
            fclose(fres);
            
            //randomized quick sort
            fres = fopen("/Users/anishbanerjee/Desktop/master_result.txt","a");
            fprintf(fres,"\nRANDOMISED QUICK SORT:\n");
            fputs("\nUNIFORM DATASET\n",fres);
            count=0;
            fp = fopen("/Users/anishbanerjee/Desktop/uniform_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            start = clock();
            randomQuickSort(arr, 0, n - 1);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[2]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[2]+=time_taken*1000;
            fclose(fp);
            count = 0;
            fprintf(fres,"\nNORMAL DATASET\n");
            fp = fopen("/Users/anishbanerjee/Desktop/normal_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            start = clock();
            randomQuickSort(arr, 0, n - 1);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[3]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[3]+=time_taken*1000;
            fclose(fp);
            fclose(fres);
            count = 0;
            
            //quick sort
            fres = fopen("/Users/anishbanerjee/Desktop/master_result.txt","a");
            fprintf(fres,"\nQUICK SORT:\n");
            fputs("\nUNIFORM DATASET\n",fres);
            count=0;
            fp = fopen("/Users/anishbanerjee/Desktop/uniform_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            start = clock();
            quick_sort(arr, 0, n - 1);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[4]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[4]+=time_taken*1000;
            fclose(fp);
            count = 0;
            fprintf(fres,"\nNORMAL DATASET\n");
            fp = fopen("/Users/anishbanerjee/Desktop/normal_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            start = clock();
            quick_sort(arr, 0, n - 1);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[5]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[5]+=time_taken*1000;
            fclose(fp);
            fclose(fres);
            count = 0;
            
            //bucket sort
            fres = fopen("/Users/anishbanerjee/Desktop/master_result.txt","a");
            fprintf(fres,"\nBUCKET SORT:\n");
            fputs("\nUNIFORM DATASET\n",fres);
            count=0;
            fp = fopen("/Users/anishbanerjee/Desktop/uniform_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            float max = arr[0];
            float min = arr[0];
            for (int i = 0; i < n; i++)
            {
                if (arr[i] > max)
                {
                    max = arr[i];
                }
                if (arr[i] < min)
                    min = arr[i];
            }
            max+=0.001;
            for (int i = 0; i < n; i++)
            {
                arr[i] = (float)(arr[i] - min)/(float)(max - min);
            }
            start = clock();
            bucketSort(arr, n);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[6]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n", time_taken*1000);
            tcounter[6]+=time_taken*1000;
            fclose(fp);
            count = 0;
            fprintf(fres,"\nNORMAL DATASET\n");
            fp = fopen("/Users/anishbanerjee/Desktop/normal_dataset.txt","r");
            fscanf(fp,"%d ",&n);
            for (int i=0; i<n; i++)
            {
                fscanf(fp,"%f\n",&arr[i]);
            }
            max = arr[0];
            min = arr[0];
            for (int i = 0; i < n; i++)
            {
                if (arr[i] > max)
                {
                    max = arr[i];
                }
                if (arr[i] < min)
                    min = arr[i];
            }
            max+=0.001;
            for (int i = 0; i < n; i++)
            {
                arr[i] = (float)(arr[i] - min)/(float)(max - min);
            }
            start = clock();
            bucketSort(arr, n);
            end = clock();
            time_taken = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(fres,"\nNumber of comparisons made: %d\n",count);
            counter[7]+=count;
            fprintf(fres,"Time taken: %f milliseconds\n\n\n", time_taken*1000);
            tcounter[7]+=time_taken*1000;
            fclose(fp);
            fclose(fres);
            count = 0;
            
        }

        FILE *fgraph = fopen("/Users/anishbanerjee/Desktop/master_graph_results.txt","a");
        FILE *ftime = fopen("/Users/anishbanerjee/Desktop/master_time_graph_results.txt","a");
        fres = fopen("/Users/anishbanerjee/Desktop/easy_master_result.txt","a");
        fprintf(fres,"\nRESULTS FOR DATASET SIZE %d:\n\n",N);
        
        fprintf(fres,"MERGE SORT: UNIFORM DATASET \n");
        double avgcount = counter[0]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        double avgtime = tcounter[0]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow*pow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow*pow)));
        
        fprintf(fgraph,"%d %f ",N,(avgcount/(mpow*pow)));
        fprintf(ftime,"%d %f ",N,(avgtime/(mpow*pow)));
        
        fprintf(fres,"MERGE SORT: NORMAL DATASET \n");
        avgcount = counter[1]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[1]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow*pow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow*pow)));
        
        fprintf(fgraph,"%f ",(avgcount/(mpow*pow)));
        fprintf(ftime,"%f ",(avgtime/(mpow*pow)));
        
        fprintf(fres,"RANDOMISED QUICK SORT: UNIFORM DATASET \n");
        avgcount = counter[2]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[2]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow*pow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow*pow)));
        
        fprintf(fgraph,"%f ",(avgcount/(mpow*pow)));
        fprintf(ftime,"%f ",(avgtime/(mpow*pow)));
        
        fprintf(fres,"RANDOMISED QUICK SORT: NORMAL DATASET \n");
        avgcount = counter[3]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[3]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow*pow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow*pow)));
        
        fprintf(fgraph,"%f ",(avgcount/(mpow*pow)));
        fprintf(ftime,"%f ",(avgtime/(mpow*pow)));
        
        fprintf(fres,"QUICK SORT: UNIFORM DATASET \n");
        avgcount = counter[4]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[4]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow*pow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow*pow)));
        
        fprintf(fgraph,"%f ",(avgcount/(mpow*pow)));
        fprintf(ftime,"%f ",(avgtime/(mpow*pow)));
        
        fprintf(fres,"QUICK SORT: NORMAL DATASET \n");
        avgcount = counter[5]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[5]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow*pow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow*pow)));
        
        fprintf(fgraph,"%f ",(avgcount/(mpow*pow)));
        fprintf(ftime,"%f ",(avgtime/(mpow*pow)));
        
        fprintf(fres,"BUCKET SORT: UNIFORM DATASET \n");
        avgcount = counter[6]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[6]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow)));
        
        fprintf(fgraph,"%f ",(avgcount/(mpow)));
        fprintf(ftime,"%f ",(avgtime/(mpow)));
        
        fprintf(fres,"BUCKET SORT: UNIFORM DATASET \n");
        avgcount = counter[7]/runpow;
        fprintf(fres,"Average Number of comparisons: %.0f\n",avgcount);
        avgtime = tcounter[7]/runpow;
        fprintf(fres,"Average Time Taken: %.4f\n",avgtime);
        fprintf(fres,"Constant (Comparisons): %.4f\n",(avgcount/(mpow)));
        fprintf(fres,"Constant (Time): %.4f\n",(avgtime/(mpow)));
        
        fprintf(fgraph,"%f \n",(avgcount/(mpow)));
        fprintf(ftime,"%f \n",(avgtime/(mpow)));
        
        fclose(fres);
        fclose(ftime);
        fclose (fgraph);
        
        
    }
    printf("\nDetailed analysis is available in the file: master_result.txt \nSummarized Results are in the file: easy_master_result.txt \nBoth files can be found on the Desktop \nThe Results have been generated!\n");

    
    printf("\nVarious Python files are available on the Desktop for a graphical comparative study, namely \n->'algolab1_graph.py' for Number of Comparisons \n->'ALGOLAB1_TIME_GRAPHS.py' for Time Taken \nPlease run the code in the IDLE already installed in this system to view the graphs associated with these results, which have been obtained above.\n\nThank you!\n");
}

