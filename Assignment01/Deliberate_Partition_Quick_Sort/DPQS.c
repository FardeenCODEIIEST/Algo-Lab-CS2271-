#include "C:\Users\joyab\Documents\Programming\4th Sem\Algorithm\Final\MasterProgram.c"
#include<string.h>

void main()
{
    clock_t start, end;
    double CPU_time;
    ui comp,swaps,stackcount;

    for (ui n = 64; n <= pow(2,14); n*=2)
    {
        for (ui i = 0; i < 10; i++)
        {
            Uniform_Distribution("UD_Data_Set.csv",0,10000000,n);
            for (ui ratio = 10; ratio < 100000; ratio*=10)
            {
                comp = swaps = stackcount = 0;

                double *arr = (double*)malloc(n*sizeof(double));
                Read_Data_from_File("UD_Data_Set.csv",arr);

                start = clock();
                sleep(1);
                quick_sort_ratio(arr,0,n-1,&comp,ratio);
                end = clock();
                CPU_time = (double)(end - start) / CLOCKS_PER_SEC;
                CPU_time--;

                isSorted(arr,n);

                Store_Result_in_File("DPQS_Result1.csv",n,comp,swaps,ratio,CPU_time);
            }
            for (ui ratio = 5; ratio < 500000; ratio*=10)
            {
                comp = swaps = stackcount = 0;

                double *arr = (double*)malloc(n*sizeof(double));
                Read_Data_from_File("UD_Data_Set.csv",arr);

                start = clock();
                sleep(1);
                quick_sort_ratio(arr,0,n-1,&comp,ratio);
                end = clock();
                CPU_time = (double)(end - start) / CLOCKS_PER_SEC;
                CPU_time--;

                isSorted(arr,n);

                Store_Result_in_File("DPQS_Result1.csv",n,comp,swaps,ratio,CPU_time);
            }
        }
        

        for (ui i = 0; i < 10; i++)
        {
            Normal_Distribution("ND_Data_Set.csv",100000,100,n);
            for (ui ratio = 10; ratio < 100000; ratio*=10)
            {
                comp = swaps = stackcount = 0;

                double *arr = (double*)malloc(n*sizeof(double));
                Read_Data_from_File("ND_Data_Set.csv",arr);

                start = clock();
                sleep(1);
                quick_sort_ratio(arr,0,n-1,&comp,ratio);
                end = clock();
                CPU_time = (double)(end - start) / CLOCKS_PER_SEC;
                CPU_time--;

                isSorted(arr,n);

                Store_Result_in_File("DPQS_Result2.csv",n,comp,swaps,ratio,CPU_time);
            }
            for (ui ratio = 5; ratio < 500000; ratio*=10)
            {
                comp = swaps = stackcount = 0;

                double *arr = (double*)malloc(n*sizeof(double));
                Read_Data_from_File("ND_Data_Set.csv",arr);

                start = clock();
                sleep(1);
                quick_sort_ratio(arr,0,n-1,&comp,ratio);
                end = clock();
                CPU_time = (double)(end - start) / CLOCKS_PER_SEC;
                CPU_time--;

                isSorted(arr,n);

                Store_Result_in_File("DPQS_Result2.csv",n,comp,swaps,ratio,CPU_time);
            }
        }
    }
    printf("\nEnd of program\n\a");   
}