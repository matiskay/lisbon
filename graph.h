// Avoid: forward declaration of 'struct node'
// If you add the declaration here you expose the struct to be public.
// You can hide the structure but you have to create a method to get the values.
// Never use typedef inside structs. It may cause conflicts.
// --> incompatible pointer types assigning to 'struct Edge *'

/**
 * A -> B
 * A: vertex
 */
struct vertex {
  int value;
  int is_visited;
  /* NOTE: The name should be next vertex in the graph */
  /* TODO: Renamte this variable to next_vertex_of_the_graph; */
  struct vertex* next_vertex_in_graph; /* Next vertex in the collection of vertex, next vertex doesn't mean connected  */
  /* The name should be edge */
  /* It should be called edge_to */
  struct edge* next_edge;
};

/* 
 * A -> B
 * B: Destination Vertex
 */
struct edge {
  /* destination Vertex */
  /* vertex_to */
  struct vertex* destination_vertex;
  // Next Edge in the graph
  // This a collection of edges from the graph. Rename this variable to next_edge_of_the_graph
  struct edge* next_edge_in_graph;
};

typedef struct vertex Vertex;
typedef struct edge Edge;

Vertex* graph_create_vertex(int);
Vertex* graph_create_empty_vertex(void);
Vertex* graph_create_edge_between_vertex(Vertex*, int, int);

Edge* graph_create_edge(void);

void graph_vertex_set_value(Vertex*, int);
Vertex* graph_insert_vertex(Vertex*, int);
Vertex* graph_remove_vertex(Vertex*, int);
Edge* graph_remove_edge(Edge*, int);

// This should be the initial node
// Every graph at least has a node
void graph_print(Vertex*);
int graph_is_connected(Vertex*, int);

Vertex* graph_destroy(Vertex*);
Vertex* graph_free_vertex(Vertex*);
Edge* graph_free_edge(Edge*);

int graph_is_there_an_edge_between_vertex(Vertex *, int, int);
int graph_is_vertex_in_graph(Vertex*, int);
