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

// Maximum Vertices the Polygon can have
#define MAX 20

// Maximum value of abscissa and ordinates
#define MAX_VAL 200

// Total number of polygons to be generated
#define TOTAL 50

typedef struct
{
  int x;
  int y;
} Vertex;

typedef struct
{
  int total_vertices;
  Vertex vertices[MAX];
} Polygon;

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

double dist(Vertex v1, Vertex v2)
{
  return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

int crossProduct(Vertex v1, Vertex v2) // vertex direction vector
{
  return v1.x * v2.y - v1.y * v2.x;
}

// Function to determine if a polygon is convex
int isConvex(Polygon poly)
{
  int n = poly.total_vertices;
  int crossproduct = 0;
  for (int i = 0; i < n; i++)
  {
    Vertex v1 = poly.vertices[i];
    Vertex v2 = poly.vertices[(i + 1) % n];
    Vertex v3 = poly.vertices[(i + 2) % n];
    int cp = crossProduct((Vertex){v2.x - v1.x, v2.y - v1.y}, (Vertex){v3.x - v2.x, v3.y - v2.y});
    if (i == 0)
    {
      crossproduct = cp;
    }
    else if (crossproduct * cp < 0)
    {
      return 0;
    }
  }
  return 1;
}

Polygon generatePolygon(int n)
{
  Polygon P;
  P.total_vertices = n;
  Vertex arr[n];
  arr[0] = generateVertex();
  for (int i = 1; i < n; i++)
  {
    Vertex v;
    do
    {
      v = generateVertex();
    } while (!isConvex((Polygon){i, arr}));
    arr[i] = v;
  }
  for (int i = 0; i < n; i++)
  {
    P.vertices[i] = arr[i];
  }
  return P;
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

int main()
{
  srand(time(0));
  double minCost;
  FILE *fout = fopen("ObservationBruteForce.csv", "w");
  FILE *fp = fopen("Results.txt", "w");
  fprintf(fout, "Vertices,Avg.Time Taken\n");
  for (int i = 3; i <= MAX; i++)
  {
    float time_sum = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Polygon poly;
      do
      {
        poly = generatePolygon(i);
      } while (!isConvex(poly));
      Vertex points[i];
      fprintf(fp, "Number of Vertices: %d\n", poly.total_vertices);
      for (int k = 0; k < poly.total_vertices; k++)
      {
        points[k].x = poly.vertices[k].x;
        points[k].y = poly.vertices[k].y;
        fprintf(fp, "%d,%d\n", poly.vertices[k].x, poly.vertices[k].y);
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
  return 0;
}
