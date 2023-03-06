#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Maximum Vertices the Polygon can have
#define MAX 50

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

// Generating the vertices randomly
Vertex generateVertex()
{
  Vertex v;
  v.x = rand() % MAX_VAL;
  v.y = rand() % MAX_VAL;
  return v;
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

int main()
{
  srand(time(0));
  FILE *fp = fopen("PolygonDatasetRAW.txt", "w");
  for (int i = 3; i <= MAX; i++)
  {
    int cnt = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Polygon poly;
      do
      {
        poly = generatePolygon(i);
      } while (!isConvex(poly));
      // fprintf(fp, "Number of Vertices: %d\n", poly.total_vertices);
      for (int k = 0; k < poly.total_vertices; k++)
      {
        fprintf(fp, "%d,%d\n", poly.vertices[k].x, poly.vertices[k].y);
      }
      // fprintf(fp, "\n");
      cnt++;
      printf("\r%f %% done", ((float)cnt) / TOTAL * 100);
    }
  }
  printf("\nFile has been generated successfully\n");
  fclose(fp);
  return 0;
}
