#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define DEBUG 1

// Question: Can I assign a NULL to an integer and then use this value to check if the graph has no value
// Question: I can use a negative number for the graph.
// Note: My assumption for this problem will be that all the values are positive so I can use the negative for
// testing.
// TODO: Add constraint when there is not enough memory
Vertex* graph_create_vertex(int value) {
  Vertex* vertex;
  vertex = (Vertex*) malloc(sizeof(Vertex));

  vertex->value = value;
  vertex->next_edge = NULL;
  vertex->next_vertex = NULL;
  vertex->is_visited = 0;

  return vertex;
}

/* Create basic scaffold for edge. */
Edge* graph_create_edge() {
  Edge* edge;
  edge = (Edge*) malloc(sizeof(Edge));

  edge->next_vertex = NULL;
  edge->next_edge = NULL;
  return edge;
}

/* This function will find the values on the graph and then make the connections */
Vertex* graph_create_edge_between_vertex(Vertex* graph, int vertex_value1, int vertex_value2) {
  Vertex* vertex1;
  Vertex* vertex2;

  Edge* edge1;
  Edge* edge2;
  
  int counter;
  counter = 0;

  for (vertex1 = graph; vertex1 != NULL; vertex1 = vertex1->next_vertex) {

    for (vertex2 = graph; vertex2 != NULL; vertex2 = vertex2->next_vertex) {
      /* Create the edge between this two vertex */
      if (vertex1->value == vertex_value1 && vertex2->value == vertex_value2) {
        edge1 = graph_create_edge();
        edge2 = graph_create_edge();

        /* Vertex1 --> Vertex2 */
        edge1->next_vertex = vertex2;
        edge1->next_edge = vertex1->next_edge;
        vertex1->next_edge = edge1;

        /* Vertex2 -> Vertex1 */
        edge2->next_vertex = vertex1;
        edge2->next_edge = vertex2->next_edge;
        vertex2->next_edge = edge2;
        counter++;
      }
    }
  }

  if (! counter) {
    printf("[INFO] 'graph_create_edge_between_vertex': It's imposible to create an edge between (%d) and (%d) because at least one of then is not a vertex of the Graph.\n", vertex_value1, vertex_value2);
  }

  return graph;
}

void graph_vertex_set_value(Vertex* vertex, int value) {
  vertex->value = value;
}

Vertex* graph_insert_vertex(Vertex* graph, int value) {
  Vertex* aux_vertex;
  Vertex* new_vertex;

  int is_vertex_in_graph;
  is_vertex_in_graph = 0;

  /* Passing to all the vertex of the graph to check if the vertex is alredy in the graph */
  for (aux_vertex = graph; aux_vertex != NULL; aux_vertex = aux_vertex->next_vertex) {
    if (aux_vertex->value == value) {
      printf("[INFO] The vertex (%d) exists in the graph G. \n", value);
      is_vertex_in_graph = 1;
    }
  }

  if (!is_vertex_in_graph) {
    if (DEBUG) {
      printf("(1) -- Current value of the graph (%d) to graph. \n", graph->value);
      printf("   (2) -- Insertion of the node (%d) to graph. \n", value);
    }

    new_vertex = graph_create_vertex(value); 
    new_vertex->next_vertex = graph;

    if (DEBUG) {
      printf("      (3) -- Final value of the graph (%d) to graph. \n", graph->value);
      printf("      (3) -- Final value of the new_vertex (%d) to graph. \n", new_vertex->value);
    }
  }
  return new_vertex;
}

void graph_print(Vertex* graph) {
  Vertex* vertex1;
  Vertex* vertex2;
  Edge* edge;

  /* *
   * NOTE: This information can be used for statistics
   * */
  int number_of_vertex;
  int number_of_edges;

  number_of_vertex = 0;
  number_of_edges = 0;

  for (vertex1 = graph; vertex1 != NULL; vertex1 = vertex1->next_vertex) {
    printf("Vertex (%d) \n", vertex1->value);
    if (vertex1->next_edge == NULL) {
      printf("   This vertex doesn't have any edge.\n");
    } else {
      for (edge = vertex1->next_edge; edge != NULL; edge = edge->next_edge) {
        vertex2 = edge->next_vertex;
        printf("   Destination vertex (%d) \n", vertex2->value);
      }
      number_of_vertex++;
    }
  }

  /*
  if ((number_of_vertex == 0) && (number_of_edges == 0)) {
    printf("The graph is empty\n");
  }
  */
}
