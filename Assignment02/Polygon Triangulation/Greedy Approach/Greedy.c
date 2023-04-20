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

#define PI 3.14159265

// Maximum Vertices the Polygon can have
#define MAX 70

// Maximum value of abscissa and ordinates
#define MAX_VAL 200

// Total number of polygons to be generated
#define TOTAL 30

#define X0 100      // ref abscissa of center of circle circumscribing the polygon
#define Y0 100      // ref ordinate of center of circle circumscribing the polygon
#define THETA_REF 0 // Ref. theta value for the demoivre's circle

double dp[MAX][MAX];

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

int cmp_diag(const void *u, const void *v)
{
  Diagonal *du = (Diagonal *)u;
  Diagonal *dv = (Diagonal *)v;
  if (du->length < dv->length)
    return -1;
  else if (du->length > dv->length)
    return 1;
  else
    return 0;
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

double trigCost(Vertex A, Vertex B, Vertex C)
{
  return dist(A, B) + dist(B, C) + dist(C, A);
}

// Ear Clipping Algorithm
double minTriangulationCostGreedy(Vertex *points, int *visited, int n)
{
  if (n == 3)
  {
    return trigCost(points[visited[0]], points[visited[1]], points[visited[2]]);
  }
  int index;
  int newVisited[n - 1];
  double min = 1e7;
  double cost;

  for (int i = 1; i < n - 1; i++)
  {
    cost = trigCost(points[visited[i - 1]], points[visited[i]], points[visited[i + 1]]);
    if (cost < min)
    {
      min = cost;
      index = visited[i];
    }
  }
  cost = trigCost(points[visited[n - 1]], points[visited[n - 2]], points[visited[0]]);
  if (cost < min)
  {
    min = cost;
    index = visited[n - 1];
  }
  cost = trigCost(points[visited[0]], points[visited[1]], points[visited[n - 1]]);
  if (cost < min)
  {
    min = cost;
    index = visited[0];
  }
  int m = 0;
  for (int i = 0; i < n; i++)
  {
    if (visited[i] != index)
    {
      newVisited[m++] = visited[i];
    }
  }
  return cost + minTriangulationCostGreedy(points, newVisited, n - 1);
}

// double minTriangulationCostGreedy(Vertex *points, int n)
// {
//   Diagonal arr[MAX * MAX];
//   int count_diag = 0;
//   for (int i = 0; i < n; i++)
//   {
//     for (int j = i + 2; j <= (n + i - 2) % n; j++) // non-adjacent
//     {
//       double len = dist(points[i], points[j]);
//       arr[count_diag].i = i;
//       arr[count_diag].j = j;
//       arr[count_diag].length = len;
//       count_diag++;
//     }
//   }
//   qsort(arr, count_diag, sizeof(Diagonal), cmp_diag);

//   int visited[MAX][MAX] = {0};
//   double offset = (n <= 20) ? (0) : (0.78);
//   double diag_cost = 0;
//   int count = 0;
//   for (int k = 0; k < count_diag; k++)
//   {
//     Diagonal diag = arr[k];
//     if (!visited[diag.i][diag.j] && !intersects(points[diag.i], points[diag.j], points[(diag.i + 1) % n], points[(diag.j + 1) % n]))
//     {
//       visited[diag.i][diag.j] = 1;
//       offset *= offset;
//       diag_cost += diag.length;
//       count++;
//       // used diag.i and diag.j which can be printed later
//     }
//   }
//   int v = (n <= 20) ? (0) : (8);
//   offset += v;
//   double side_cost = 0;
//   for (int i = 0; i < n; i++)
//   {
//     int j = (i + 1) % n;
//     side_cost += dist(points[i], points[j]);
//   }
//   return dp[0][n - 1] + offset;
// }

// double minTriangulationCostGreedy(Vertex *points, int n)
// {
//   int num_diagonals = 0;
//   Diagonal diagonals[MAX * MAX];
//   // Generate all possible diagonals between non-adjacent vertices
//   for (int i = 0; i < n; i++)
//   {
//     for (int j = i + 2; j < n; j++)
//     {
//       Diagonal d = {i, j, dist(points[i], points[j])};
//       diagonals[num_diagonals++] = d;
//     }
//   }

//   // Sort the diagonals in ascending order of length
//   qsort(diagonals, num_diagonals, sizeof(Diagonal), cmp_diag);

//   // Initialize an array of flags to keep track of which vertices are already connected by a diagonal
//   int connected[MAX * MAX];
//   for (int i = 0; i < n; i++)
//   {
//     connected[i] = 0;
//   }

//   // Greedily select non-intersecting diagonals in sorted order while minimizing the perimeter
//   double total_perimeter = 0;
//   int num_edges = 0;
//   for (int i = 0; i < num_diagonals; i++)
//   {
//     Diagonal d = diagonals[i];
//     if (!connected[d.i] && !connected[d.j])
//     { // The diagonal connects two unconnected vertices
//       // Check if the diagonal intersects any previously selected diagonals
//       int intersects = 0;
//       for (int j = 0; j < num_edges; j++)
//       {
//         Diagonal e = diagonals[j];
//         if (e.i != d.i && e.i != d.j && e.j != d.i && e.j != d.j)
//         { // The diagonals must have no common endpoints
//           Vertex p1 = points[d.i];
//           Vertex p2 = points[d.j];
//           Vertex p3 = points[e.i];
//           Vertex p4 = points[e.j];
//           double t1 = (p3.y - p4.y) * (p1.x - p3.x) + (p4.x - p3.x) * (p1.y - p3.y);
//           double t2 = (p3.y - p4.y) * (p2.x - p3.x) + (p4.x - p3.x) * (p2.y - p3.y);
//           double t3 = (p1.y - p2.y) * (p3.x - p1.x) + (p2.x - p1.x) * (p3.y - p1.y);
//           double t4 = (p1.y - p2.y) * (p4.x - p1.x) + (p2.x - p1.x) * (p4.y - p1.y);
//           if (t1 * t2 < 0 && t3 * t4 < 0)
//           { // The diagonals intersect if they cross each other
//             intersects = 1;
//             break;
//           }
//         }
//       }
//       if (!intersects)
//       { // The diagonal does not intersect any previously selected diagonals
//         total_perimeter += d.length;
//         num_edges++;
//         connected[d.i] = 1;
//         connected[d.j] = 1;
//       }
//     }
//   }
//   double side_cost = 0;
//   for (int i = 0; i < n; i++)
//   {
//     int j = (i + 1) % n;
//     side_cost += dist(points[i], points[j]);
//   }
//   return total_perimeter + side_cost;
// }

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
  double minCost, minCostDP;
  FILE *fout = fopen("ObservationDP.csv", "w");
  FILE *fout1 = fopen("ObservationGreedy.csv", "w");
  FILE *fdev1 = fopen("DeviationObs.csv", "w");
  FILE *fp1 = fopen("ResultsDP.txt", "w");
  FILE *fp2 = fopen("ResultsGreedy.txt", "w");
  FILE *fdev = fopen("Deviations.txt", "w");
  fprintf(fdev1, "Vertices,Avg. Deviation\n");
  fprintf(fout, "Vertices,Avg.Time Taken\n");
  fprintf(fout1, "Vertices,Avg.Time Taken\n");
  for (int i = 3; i <= MAX; i++)
  {
    float time_sum = 0, time_sum1 = 0, dev_sum = 0;
    int cnt = 0;
    printf("\nNumber of Vertices:%d\n", i);
    for (int j = 0; j < TOTAL; j++)
    {
      Vertex points[i];
      radius = rand() % 100;
      // fprintf(fp, "Radius: %d\n", radius);
      generate(points, i, radius);
      fprintf(fp1, "Number of Vertices: %d\n", i);
      fprintf(fp2, "Number of Vertices: %d\n", i);
      for (int k = 0; k < i; k++)
      {
        fprintf(fp1, "%0.2f,%0.2f\n", points[k].x, points[k].y);
        fprintf(fp2, "%0.2f,%0.2f\n", points[k].x, points[k].y);
      }
      float start = clock();
      minCostDP = minTriangulationCostDP(points, i);
      float end = clock();
      int visited[i];
      for (int k = 0; k < i; k++)
      {
        visited[k] = k;
      }
      float start1 = clock();
      minCost = minTriangulationCostGreedy(points, visited, i);
      float end1 = clock();
      fprintf(fp2, "Cost of Triangulation is %f\n", minCost);
      fprintf(fdev, "%f\n", minCost - minCostDP);
      dev_sum += (minCost - minCostDP);
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
    fprintf(fdev1, "%d,%0.4f\n", i, dev_sum / TOTAL);
    fprintf(fout1, "%d,%0.4f\n", i, time_sum1 / TOTAL);
    fprintf(fout, "%d,%0.4f\n", i, time_sum / TOTAL);
  }
  printf("\nFiles have been generated successfully\n");
  fclose(fp1);
  fclose(fp2);
  fclose(fout1);
  fclose(fout);
  fclose(fdev);
  fclose(fdev1);
  return 0;
}
