// Avoid: note: forward declaration of 'struct node'
// If you add the declaration here you expose the struct to be public.
// You can hide the structure but you have to create a method to get the values.
// Never use typedef inside structs. It may cause conflicts.
// --> incompatible pointer types assigning to 'struct Edge *'

/**
 * A -> B
 * A: vertex
 * B: final_vertex
 */
struct vertex {
  int value;
  int is_visited;
  /* NOTE: The name should be next vertex in the graph */
  struct vertex* next_vertex; /* Next vertex in the collection of vertex, next vertex doesn't mean connected  */
  /* The name should be edge */
  struct edge* next_edge;
};

/* 
 * A -> B
 * A: Initial Vertex
 * B: Final Vertex
 */
struct edge {
  /* destination Vertex */
  struct vertex* destination_vertex;
  // Next Edge in the graph
  struct edge* next_edge; /* TODO: What is the purpose of this structure? */
};

typedef struct vertex Vertex;
typedef struct edge Edge;

Vertex* graph_create_vertex(int);
Vertex* graph_create_edge_between_vertex(Vertex*, int, int);

/* TODO: Create vertex */
Edge* graph_create_edge(void);

void graph_vertex_set_value(Vertex*, int);
Vertex* graph_insert_vertex(Vertex*, int);
void graph_exclude_vertex(Vertex*);
// This should be the initial node
// Every graph at least has a node
void graph_print(Vertex*);
int graph_is_connected(Vertex*, int);
