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
#define X0 0
#define Y0 0
#define THETA_REF 0

typedef struct
{
  int x;
  int y;
} Vertex;

// typedef struct
// {
//   int total_vertices;
//   Vertex vertices[MAX];
// } Polygon;

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

/*
  The idea to check whether a polygon is convex or not is to check the
  cross product of adjacent sides in the polygon and if the sign(direction)
  of the cross product is different for different pairs of adjacent sides
  then we can surely say that the polygon is concave.
  Eg:- convex polygon

         A .............. B
           .            .
           .            .
        C  .............. D

    For the above figure if we take the cross product opf sides say AC and CD then
    the direction of cross product is upwards and this direction stays same for
    any pair of adjacent sides in ABCD. So ABCD is a convex polygon

    Concave Polygon

            A .       .B
              . .   . .
              .   .   .
              .   C   .
              .       .
              .       .
              .       .
            D ......... E

    For the above case we can see that the direction of cross product of sides
    BC and CA is downwards while that of DE and EB is upwards and we can say
    that ADEBC is a concave polygon which is what we would find.
    So the key to check is to find whether the cross-product changes sign for
    any pair of adjacent sides.

*/
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

int main()
{
  srand(time(0));
  FILE *fp = fopen("PolygonDataset.txt", "w");
  for (int i = 3; i <= MAX; i++)
  {
    int cnt = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Vertex points[i];
      for (int k = 0; k < i; k++)
      {
        points[k] = generateVertex();
      }
      convex_hull(points, i);
      order_vertices(points, i);
      fprintf(fp, "Number of Vertices: %d\n", i);
      for (int k = 0; k < i; k++)
      {
        fprintf(fp, "%d,%d\n", points[k].x, points[k].y);
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
