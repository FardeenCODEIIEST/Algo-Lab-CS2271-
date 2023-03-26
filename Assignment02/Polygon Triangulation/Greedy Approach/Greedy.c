/* Here we will be solving the polygon triangulation problem using a
  DP approach*/

/*
  We will use the tabulation method to save the computated result
  and will return the result bottom-up. Idea will be same as that of \
  the recursive approach but here we will be remembering the previously
  computed result to reduce the computation time
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Maximum Vertices the Polygon can have
#define MAX 70

// Maximum value of abscissa and ordinates
#define MAX_VAL 100

// Total number of polygons to be generated
#define TOTAL 50

double dp[MAX][MAX];

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

typedef struct
{
  int i;         // start
  int j;         // end
  double length; // length of diagonal
} Diagonal;

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

int cmp_diag(const void *u, const void *v)
{
  Diagonal *du = (Diagonal *)u;
  Diagonal *dv = (Diagonal *)v;
  return (du->length < dv->length) ? 1 : -1;
}

int cmp(const void *a, const void *b)
{
  Vertex *p1 = (Vertex *)a;
  Vertex *p2 = (Vertex *)b;
  return (p1->x - p2->x);
}

// Checking for non-intersecting diagonals
int intersects(Vertex a, Vertex b, Vertex c, Vertex d)
{
  int d1 = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  int d2 = (b.x - a.x) * (d.y - a.y) - (d.x - a.x) * (b.y - a.y);
  int d3 = (d.x - c.x) * (a.y - c.y) - (a.x - c.x) * (d.y - c.y);
  int d4 = (d.x - c.x) * (b.y - c.y) - (b.x - c.x) * (d.y - c.y);
  return (d1 * d2 < 0) && (d3 * d4 < 0);
}

int orientation(Vertex v1, Vertex v2, Vertex v3) // for setting the orientation using cross product
{
  int res = (v2.y - v1.y) * (v3.x - v2.x) - (v2.x - v1.x) * (v3.y - v2.y);
  if (res == 0)
  { // collinear
    return 0;
  }
  return (res > 0) ? 1 : 2; // cw or acw
}

// Shoelace theorem for ordering of vertices
void sort_vertices(Vertex *points, int n)
{
  int leftmost = 0;
  for (int i = 1; i < n; i++)
  { // finding the leftmost point
    if (points[i].x < points[leftmost].x)
    {
      leftmost = i;
    }
  }
  // swap leftmost with first point
  Vertex temp = points[0];
  points[0] = points[leftmost];
  points[leftmost] = temp;

  qsort(points + 1, n - 1, sizeof(Vertex), cmp);
  int ct = 1; // Number of points in the sorted array
  // for (int i = 1; i < n; i++) // remove collinear
  // {
  //   while (i < n - 1 && orientation(points[0], points[i], points[i + 1]) == 0)
  //   {
  //     i++;
  //   }
  //   points[ct] = points[i];
  //   ct++;
  // }
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
  sort_vertices(arr, n); // ordering the vertices
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

// double minTriangulationCost(Vertex *points, int i, int j)
// {
//   // Base Case
//   if (j <= i + 1)
//   {
//     return 0;
//   }
//   double ans = 1e7;
//   for (int k = i + 1; k < j; k++)
//   {
//     ans = min(ans, (minTriangulationCost(points, i, k) + minTriangulationCost(points, k, j) + cost(points, i, k, j)));
//   }
//   return ans;
// }

double minTriangulationCostDP(Vertex *points, int n)
{
  double Max = 1e7;
  if (n <= 2)
  {
    return 0;
  }
  /* dp[i][j] will store the min triangulation cost for vertices from points
    i to j. Final ans will dp[0][n-1]
  */
  for (int m = 0; m < n; m++)
  {
    for (int i = 0, j = m; i < n; i++, j++)
    {
      if (j <= i + 1)
      {
        dp[i][j] = 0.0;
      }
      else
      {
        dp[i][j] = Max;
        for (int k = i + 1; k < j; k++)
        {
          double ans = dp[i][k] + dp[k][j] + cost(points, i, j, k); // i,j and j,k diagonals
          dp[i][j] = min(dp[i][j], ans);
        }
      }
    }
  }
  return dp[0][n - 1];
}

double minTriangulationCostGreedy(Vertex *points, int n)
{
  Diagonal arr[MAX * MAX];
  int taken[MAX][MAX] = {0};
  int count_diag = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 2; j <= n - 2; j++) // non-adjacent
    {
      if (!taken[i][j] && !taken[j][i])
      {
        taken[i][j] = 1;
        taken[j][i] = 1;
        double len = dist(points[i], points[j]);
        arr[count_diag].i = i;
        arr[count_diag].j = j;
        arr[count_diag].length = len;
        count_diag++;
      }
    }
  }
  qsort(arr, count_diag, sizeof(Diagonal), cmp_diag);

  int visited[MAX][MAX] = {0};
  double diag_cost = 0;
  for (int k = 0; k < count_diag; k++)
  {
    Diagonal diag = arr[k];
    if (!visited[diag.i][diag.j] && !intersects(points[diag.i], points[diag.j], points[(diag.i + 1) % n], points[(diag.j + 1) % n]))
    {
      visited[diag.i][diag.j] = 1;
      diag_cost += diag.length;
      // used diag.i and diag.j which can be printed later
    }
  }
  double side_cost = 0;
  for (int i = 0; i < n; i++)
  {
    int j = (i + 1) % n;
    side_cost += dist(points[i], points[j]);
  }
  return diag_cost + side_cost;
}

int main()
{
  srand(time(0));
  double minCost, minCostDP;
  FILE *fout = fopen("ObservationDP.csv", "w");
  FILE *fout1 = fopen("ObservationGreedy.csv", "w");
  FILE *fp1 = fopen("ResultsDP.txt", "w");
  FILE *fp2 = fopen("ResultsGreedy.txt", "w");
  FILE *fdev = fopen("Deviations.txt", "w");
  fprintf(fout, "Vertices,Avg.Time Taken\n");
  fprintf(fout1, "Vertices,Avg.Time Taken\n");
  for (int i = 3; i <= MAX; i++)
  {
    float time_sum = 0, time_sum1 = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Polygon poly;
      do
      {
        poly = generatePolygon(i);
      } while (!isConvex(poly));
      sort_vertices(poly.vertices, poly.total_vertices);
      Vertex points[i];
      fprintf(fp1, "Number of Vertices: %d\n", poly.total_vertices);
      fprintf(fp2, "Number of Vertices:%d\n", poly.total_vertices);
      for (int k = 0; k < poly.total_vertices; k++)
      {
        points[k].x = poly.vertices[k].x;
        points[k].y = poly.vertices[k].y;
        fprintf(fp1, "%d,%d\n", poly.vertices[k].x, poly.vertices[k].y);
        fprintf(fp2, "%d,%d\n", poly.vertices[k].x, poly.vertices[k].y);
      }
      float start1 = clock();
      minCost = minTriangulationCostGreedy(points, i);
      float end1 = clock();
      fprintf(fp2, "Cost of Triangulation is %f\n", minCost);
      float start = clock();
      minCostDP = minTriangulationCostDP(points, i);
      float end = clock();
      fprintf(fdev, "%f\n", minCostDP - minCost);
      fprintf(fp1, "Cost of Triangulation is %f\n", minCostDP);
      float time_req = (end - start) * 1000 / CLOCKS_PER_SEC;
      float time_req1 = (end1 - start1) * 1000 / CLOCKS_PER_SEC;
      printf("Time taken for round %d using DP is %0.4fms\n", j + 1, time_req);
      printf("Time taken for round %d using Greedy is %0.4fms\n", j + 1, time_req1);
      time_sum += time_req;
      time_sum1 += time_req1;
      fprintf(fp1, "\n");
      fprintf(fp2, "\n");
    }
    fprintf(fout1, "%d,%0.4f\n", i, time_sum1 / TOTAL);
    fprintf(fout, "%d,%0.4f\n", i, time_sum / TOTAL);
  }
  printf("\nFiles have been generated successfully\n");
  fclose(fp1);
  fclose(fp2);
  fclose(fout1);
  fclose(fout);
  fclose(fdev);
  return 0;
}
