#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265

// Maximum Vertices the Polygon can have
#define MAX 50

// Maximum value of abscissa and ordinates
#define MAX_VAL 200

// Total number of polygons to be generated
#define TOTAL 50

#define X0 100      // ref abscissa of center of circle circumscribing the polygon
#define Y0 100      // ref ordinate of center of circle circumscribing the polygon
#define THETA_REF 0 // Ref. theta value for the demoivre's circle

typedef struct Vertex
{
  double x;
  double y;
} Vertex;

void generate(Vertex *arr, int n, int radius)
{
  for (int i = 0; i < n; i++)
  {
    arr[i].x = X0 + radius * cos((2 * PI * i) / n);
    arr[i].y = Y0 + radius * sin((2 * PI * i) / n);
  }
}

int main()
{
  srand(time(0));
  int radius;
  FILE *fp = fopen("PolygonDataset.txt", "w");
  for (int i = 3; i <= MAX; i++)
  {
    int cnt = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Vertex points[i];
      radius = rand() % 100; // ranging from 0 to 100
      generate(points, i, radius);
      fprintf(fp, "Number of Vertices: %d\n", i);
      // fprintf(fp, "Radius is %d\n", radius);
      for (int k = 0; k < i; k++)
      {
        fprintf(fp, "%0.2f,%0.2f\n", points[k].x, points[k].y);
      }
      fprintf(fp, "\n");
      cnt++;
      printf("\r%f %% done", ((float)cnt) / TOTAL * 100);
    }
  }
  printf("\nFile has been generated successfully\n");
  fclose(fp);
  return 0;
}