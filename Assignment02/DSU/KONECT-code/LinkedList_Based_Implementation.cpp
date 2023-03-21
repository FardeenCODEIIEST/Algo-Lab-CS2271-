#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

const long long number_vertices = 23947347; // As per KONECT dataset website
const long long number_edges = 57708624;

struct node;

struct ConComp // Structure for the connected components
{
  ConComp *next;
  ConComp *prev;
  node *head;
  node *tail;
  long long length;
};

struct node
{
  ConComp *parent;
  long long data;
  node *next;
};

struct edge
{
  long long source;
  long long dest;
};

// Initialisation of all nodes to a default value; creation of new set

void MAKE_SET(long long index, ConComp *start)
{
  ConComp *temp = start->next;

  ConComp *ans = new ConComp;
  ans->length = 1;
  ans->next = temp;
  start->next = ans;
  ans->prev = start; // doubly linked list

  if (temp != NULL)
  {
    temp->prev = ans;
  }

  ans->head = new node;
  ans->tail = ans->head; // initially head will be tail
  ans->head->data = index;
  ans->head->parent = ans;
  ans->head->next = NULL;
}

// Find the representative element
ConComp *FIND_SET(long long val, ConComp *start)
{
  ConComp *temp = start->next;
  while (temp != NULL)
  {
    node *node_temp = temp->head;
    while (node_temp != NULL)
    {
      if (node_temp->data == val)
      {
        return node_temp->parent;
      }
      node_temp = node_temp->next;
    }
    temp = temp->next;
  }
  return NULL;
}

// Link two nodes based on their rank

void LINK(ConComp *x, ConComp *y)
{
  if (x != y)
  {
    ConComp *max, *min;
    if (x->length > y->length)
    {
      max = x;
      min = y;
    }
    else
    {
      max = y;
      min = x;
    }
    max->length += min->length;
    node *point_diff = min->head;
    max->tail->next = min->head;
    max->tail = min->head;

    while (point_diff != NULL)
    {
      point_diff->parent = max;
      point_diff = point_diff->next;
    }
    if (min->prev != NULL)
    {
      min->prev->next = min->next;
    }
    if (min->next != NULL)
    {
      min->next->prev = min->prev;
    }
    delete min;
  }
}

// Union of two sets

void UNION(edge e, ConComp *start)
{
  if (e.source != e.dest)
  {
    LINK(FIND_SET(e.source, start), FIND_SET(e.dest, start));
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
  char observation_path[] = "D:/college/AlgoLabCS2271/Assignments/Assignment02/DSU/KONECT-code/observation_linkedlist.txt";

  double avg_time = 0;
  double start_clock = clock();

  ConComp *start = new ConComp;
  start->head = NULL;
  start->tail = NULL;
  start->length = 0;
  start->next = NULL;
  start->prev = NULL;

  for (int i = 0; i < number_vertices; i++)
  {
    MAKE_SET(i, start);
  }

  ifstream fin(file_path, ios::in);

  ofstream fout(observation_path, ios::out);

  edge t;
  for (int i = 0; i < number_edges; i++)
  {
    edge_update(t, fin);
    UNION(t, start);
    cout << (double)i / number_edges * 100 << "% completed \r";
  }

  fin.close();

  float end_clock = clock();
  avg_time = (end_clock - start_clock) * 1000 / CLOCKS_PER_SEC;
  fout << "Number of vertices: " << number_vertices << "\n";
  fout << "Number of edges: " << number_edges << "\n";
  fout << "Average Time Taken for union-find operation: " << avg_time << "ms"
       << "\n";
  fout.close();
  return 0;
}