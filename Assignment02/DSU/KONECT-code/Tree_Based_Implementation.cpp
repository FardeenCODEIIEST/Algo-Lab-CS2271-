#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

const long long number_vertices = 23947347; // As per KONECT dataset website
const long long number_edges = 57708624;

struct node
{
  node *parent;   // parent of the node
  long long rank; // rank of the node
};

struct edge
{
  long long source;
  long long dest;
};

node vertices[number_vertices];

// Initialisation of all nodes to a default value; creation of new set

void MAKE_SET(node *p)
{
  p->parent = p; // initially a node is its own parent
  p->rank = 0;   // initially rank of the node is 0
}

// Find the representative element
node *FIND_SET(node *p)
{
  if (p != p->parent)
    p->parent = FIND_SET(p->parent);
  return p->parent;
}

// Link two nodes based on their rank

void LINK(node *x, node *y)
{
  if (x->rank > y->rank)
  {
    y->parent = x;
  }
  else if (x->rank < y->rank)
  {
    x->parent = y;
  }
  else
  {
    y->parent = x;
    x->rank++;
  }
}

// Union of two sets

void UNION(edge e)
{
  if (e.source != e.dest)
  {
    LINK(FIND_SET(&vertices[e.source]), FIND_SET(&vertices[e.dest]));
  }
}

// edge updation

void edge_update(edge &present_edge, ifstream &fin)
{
  if (!fin.eof())
  {
    char s[150];
    fin.getline(s, 150);

    if (s[0] == '%') // removinf comments
    {
      while (s[0] == '%')
      {
        fin.getline(s, 150);
      }
    }

    stringstream stream; // creating a string stream object
    stream << s;         // Adding s to the string stream object

    char number[20];

    stream >> number; // Reading number from the string stream
    // atoi convert string to number
    present_edge.source = atoi(number) - 1; // 0 based indexing

    stream >> number;
    present_edge.dest = atoi(number) - 1;
  }
}

int main()
{
  char file_path[] = "D:/college/AlgoLabCS2271/Assignments/Assignment02/DSU/Dataset/KONECT/dimacs9-USA/out.dimacs9-USA";
  char observation_path[] = "D:/college/AlgoLabCS2271/Assignments/Assignment02/DSU/KONECT-code/observation_tree.txt";

  double avg_time = 0;
  double start = clock();
  for (int i = 0; i < number_vertices; i++)
  {
    MAKE_SET(&vertices[i]);
  }

  ifstream fin(file_path, ios::in);

  ofstream fout(observation_path, ios::out);

  edge t;
  for (int i = 0; i < number_edges; i++)
  {
    edge_update(t, fin);
    UNION(t);
    cout << (double)i / number_edges * 100 << "% completed \r";
  }

  fin.close();

  float end = clock();
  avg_time = (end - start) * 1000 / CLOCKS_PER_SEC;
  fout << "Number of vertices: " << number_vertices << "\n";
  fout << "Number of edges: " << number_edges << "\n";
  fout << "Average Time Taken for union-find operation: " << avg_time << "ms"
       << "\n";
  fout.close();
  return 0;
}