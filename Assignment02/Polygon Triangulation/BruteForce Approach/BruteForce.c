/* Here we will be solving the polygon triangulation problem using a
  recursive approach*/

/* Idea will be to divide the polygon into 3 parts:-
  1. Two convex sub polygons
  2. A triangle
  At each step we will be finding the minimum perimeter value,
  Our base case will reach when the there are 3 vertices as no further splitting
  can be done*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265
// Maximum Vertices the Polygon can have
#define MAX 20

// Maximum value of abscissa and ordinates
#define MAX_VAL 200

// Total number of polygons to be generated
#define TOTAL 50

#define X0 100      // ref abscissa of center of circle circumscribing the polygon
#define Y0 100      // ref ordinate of center of circle circumscribing the polygon
#define THETA_REF 0 // Ref. theta value for the demoivre's circle

typedef struct
{
  double x;
  double y;
} Vertex;

// typedef struct
// {
//   int total_vertices;
//   Vertex vertices[MAX];
// } Polygon;

double min(double a, double b)
{
  return (a < b) ? a : b;
}

// Generating the vertices randomly
Vertex generateVertex()
{
  Vertex v;
  v.x = rand() % MAX_VAL;
  v.y = rand() % MAX_VAL;
  return v;
}

int dist_sq(Vertex v1, Vertex v2)
{
  return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

double dist(Vertex v1, Vertex v2)
{
  return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

int crossProduct(Vertex v1, Vertex v2) // vertex direction vector
{
  return v1.x * v2.y - v1.y * v2.x;
}

// Function to determine if a polygon is convex
// int isConvex(Polygon poly)
// {
//   int n = poly.total_vertices;
//   int crossproduct = 0;
//   for (int i = 0; i < n; i++)
//   {
//     Vertex v1 = poly.vertices[i];
//     Vertex v2 = poly.vertices[(i + 1) % n];
//     Vertex v3 = poly.vertices[(i + 2) % n];
//     int cp = crossProduct((Vertex){v2.x - v1.x, v2.y - v1.y}, (Vertex){v3.x - v2.x, v3.y - v2.y});
//     if (i == 0)
//     {
//       crossproduct = cp;
//     }
//     else if (crossproduct * cp < 0)
//     {
//       return 0;
//     }
//   }
//   return 1;
// }

int orientation(Vertex v1, Vertex v2, Vertex v3) // for setting the orientation using cross product
{
  int res = (v2.y - v1.y) * (v3.x - v2.x) - (v2.x - v1.x) * (v3.y - v2.y);
  if (res == 0)
  { // collinear
    return 0;
  }
  return (res > 0) ? 1 : 2; // cw or acw
}

int compare(const void *a, const void *b)
{
  Vertex *v1 = (Vertex *)a;
  Vertex *v2 = (Vertex *)b;

  int o = orientation((Vertex){0, 0}, *v1, *v2);
  if (o == 0)
  {
    return (dist_sq((Vertex){0, 0}, *v2) >= dist_sq((Vertex){0, 0}, *v1)) ? -1 : 1;
  }
  return (o == 2) ? -1 : 1;
}

// Graham Scan algorithm; Convex Hull
void convex_hull(Vertex *points, int n)
{
  int ymin = points[0].y, min = 0;
  for (int i = 1; i < n; i++)
  {
    int y = points[i].y;
    if ((y < ymin) || (y == ymin && points[i].x < points[min].x)) // finding bottom leftmost point{
    {
      ymin = points[i].y;
      min = i;
    }
  }
  // swapping with the first point
  Vertex temp = points[0];
  points[0] = points[min];
  points[min] = temp;
  qsort(points + 1, n - 1, sizeof(Vertex), compare);
  int m = 1; // current number of points
  for (int i = 1; i < n; i++)
  {
    while (i < n - 1 && orientation((Vertex){0, 0}, points[i], points[i + 1]) == 0)
    {
      i++; // ignoring the collinear points
    }
    points[m] = points[i];
    m++;
  }
  if (m < 3)
  {
    return;
  }
}

void order_vertices(Vertex *points, int n)
{
  int x[n], y[n];
  for (int i = 0; i < n; i++)
  {
    x[i] = points[i].x;
    y[i] = points[i].y;
  }
  int i = 0;
  for (int j = 1; j < n; j++)
  {
    if (x[j] < x[i])
    {
      i = j;
    }
    else if (x[j] == x[i] && y[j] < y[i])
    {
      i = j;
    }
  }
  double theta[n];
  for (int j = 0; j < n; j++)
  {
    if (x[j] == x[i])
    {
      if (y[j] > y[i])
      {
        theta[j] = PI / 2;
      }
      else
      {
        theta[j] = -PI / 2;
      }
    }
    else
    {
      theta[j] = atan((double)(y[j] - y[i]) / (double)(x[j] - x[i]));
    }
  }
  double sigma[n];
  for (int j = 0; j < n; j++)
  {
    sigma[j] = theta[j];
  }
  for (int j = 0; j < n; j++)
  {
    for (int k = j + 1; k < n; k++)
    {
      if (sigma[k] < sigma[j])
      {
        double temp = sigma[k];
        sigma[k] = sigma[j];
        sigma[j] = temp;
        int temp_x = x[k];
        x[k] = x[j];
        x[j] = temp_x;
        int temp_y = y[k];
        y[k] = y[j];
        y[j] = temp_y;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    points[i].x = x[i];
    points[i].y = y[i];
  }
}

double cost(Vertex *points, int i, int j, int k)
{
  Vertex v1 = points[i];
  Vertex v2 = points[j];
  Vertex v3 = points[k];
  return dist(v1, v2) + dist(v2, v3) + dist(v3, v1);
}

double minTriangulationCost(Vertex *points, int i, int j)
{
  // Base Case
  if (j <= i + 1)
  {
    return 0;
  }
  double ans = 1e7;
  for (int k = i + 1; k < j; k++)
  {
    ans = min(ans, (minTriangulationCost(points, i, k) + minTriangulationCost(points, k, j) + cost(points, i, k, j)));
  }
  return ans;
}

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
  double minCost;
  FILE *fout = fopen("ObservationBruteForce.csv", "w");
  FILE *fp = fopen("Results.txt", "w");
  fprintf(fout, "Vertices,Avg.Time Taken\n");
  for (int i = 3; i <= MAX; i++)
  {
    float time_sum = 0;
    int cnt = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Vertex points[i];
      radius = rand() % 100;
      // fprintf(fp, "Radius: %d\n", radius);
      generate(points, i, radius);
      fprintf(fp, "Number of Vertices: %d\n", i);
      for (int k = 0; k < i; k++)
      {
        fprintf(fp, "%0.2f,%0.2f\n", points[k].x, points[k].y);
      }
      float start = clock();
      minCost = minTriangulationCost(points, 0, i - 1);
      fprintf(fp, "Cost of Triangulation is %f\n", minCost);
      float end = clock();
      float time_req = (end - start) * 1000 / CLOCKS_PER_SEC;
      printf("Time taken for round %d is %0.4fms\n", j + 1, time_req);
      time_sum += time_req;
      fprintf(fp, "\n");
    }
    fprintf(fout, "%d,%0.4f\n", i, time_sum / TOTAL);
  }
  printf("\nFiles have been generated successfully\n");
  fclose(fp);
  fclose(fout);
  return 0;
}
