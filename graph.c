#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define DEBUG 0
#define SHOW_INFO 0

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
  vertex->next_vertex_in_graph = NULL;
  vertex->is_visited = 0;

  return vertex;
}

Vertex* graph_create_empty_vertex() {
  Vertex* vertex;
  vertex = (Vertex*) malloc(sizeof(Vertex));

  // Zero by default.
  // Condition:
  //   All the values of the graph must greater than 0
  vertex->value = 0;
  vertex->next_edge = NULL;
  vertex->next_vertex_in_graph = NULL;
  vertex->is_visited = 0;

  return vertex;
}

/* Create basic scaffold for edge. */
Edge* graph_create_edge() {
  Edge* edge;
  edge = (Edge*) malloc(sizeof(Edge));

  edge->destination_vertex = NULL;
  edge->next_edge_in_graph = NULL;
  return edge;
}

/* This function will find the values on the graph and then make the connections */
/* TODO: Return messages as codes. This implies to change the function to make operations over the graph and return codes. */
/* TODO: Refactor!!!! */
Vertex* graph_create_edge_between_vertex(Vertex* graph, int vertex_value1, int vertex_value2) {
    Vertex* vertex1;
    Vertex* vertex2;

    Edge* edge1;
    Edge* edge2;
    edge1 = graph_create_edge();
    edge2 = graph_create_edge();

    // Inception :)
    for (vertex1 = graph; vertex1 != NULL; vertex1 = vertex1->next_vertex_in_graph) {
        for (vertex2 = graph; vertex2 != NULL; vertex2 = vertex2->next_vertex_in_graph) {
            if (vertex1->value == vertex_value1 && vertex2->value == vertex_value2) {
                /* Create the edge between this two vertex */
//                printf("Creating edge between %d <-----> %d \n", vertex1->value, vertex2->value);

                /* Vertex1 --> Vertex2 */
                edge1->destination_vertex = vertex2;
                edge1->next_edge_in_graph = vertex1->next_edge;
                vertex1->next_edge = edge1;

                /* Vertex2 --> Vertex1 */
                edge2->destination_vertex = vertex1;
                edge2->next_edge_in_graph = vertex2->next_edge;
                vertex2->next_edge = edge2;
            }
        }
    }

    return graph;
}

int graph_is_there_an_edge_between_vertex(Vertex *graph, int vertex_value1, int vertex_value2) {
    Vertex* vertex1;
    Vertex* vertex2;

    Edge* aux_edge1;
    Edge* aux_edge2;

    int flag_vertex1_vertex2_is_connected;
    int flag_vertex2_vertex1_is_connected;

    flag_vertex1_vertex2_is_connected = 0;
    flag_vertex2_vertex1_is_connected = 0;

    for (vertex1 = graph; vertex1 != NULL; vertex1 = vertex1->next_vertex_in_graph) {
        for (vertex2 = graph; vertex2 != NULL; vertex2 = vertex2->next_vertex_in_graph) {
            if (vertex1->value == vertex_value1 && vertex2->value == vertex_value2) {
//                printf("---> is there an edge? %d <-----> %d \n", vertex1->value, vertex2->value);
//                printf("---> is there an edge? %d <-----> %d \n", vertex1->next_edge->destination_vertex->value, vertex2->next_edge->destination_vertex->value);
                // Find in all the edges

                for (aux_edge1 = vertex1->next_edge; aux_edge1 != NULL; aux_edge1 = aux_edge1->next_edge_in_graph) {

                    printf("Mess here !!lll \n");

                    printf("Get the aux value: %d \n", aux_edge1->destination_vertex->value);

                    if (aux_edge1->destination_vertex->value == vertex2->value) {
                        printf("found 1\n");
                        flag_vertex1_vertex2_is_connected = 1;
                    }
                }

                for (aux_edge2 = vertex2->next_edge; aux_edge2 != NULL; aux_edge2 = aux_edge2->next_edge_in_graph) {
                    if (aux_edge2->destination_vertex->value == vertex1->value) {
//                        printf("found 2\n");
                        flag_vertex2_vertex1_is_connected = 1;
                    }
                }
            }
        }
    }

    if (flag_vertex1_vertex2_is_connected && flag_vertex2_vertex1_is_connected) {
        return 1;
    }

    return 0;
}

void graph_vertex_set_value(Vertex* vertex, int value) {
  vertex->value = value;
}

Vertex* graph_insert_vertex(Vertex* graph, int value) {
  Vertex* aux_vertex;
  Vertex* new_vertex;

  int is_vertex_in_graph;
  is_vertex_in_graph = 0;

  /* Passing to all the vertex of the graph to check if the vertex is already in the graph */
  for (aux_vertex = graph; aux_vertex != NULL; aux_vertex = aux_vertex->next_vertex_in_graph) {
    if (aux_vertex->value == value) {

      if (SHOW_INFO) {
        printf("[INFO] The vertex (%d) exists in the graph G. \n", value);
      }
      is_vertex_in_graph = 1;
    }
  }

  if (!is_vertex_in_graph) {
    if (DEBUG) {
      printf("(1) -- Current value of the graph (%d) to graph. \n", graph->value);
      printf("   (2) -- Insertion of the node (%d) to graph. \n", value);
    }

    new_vertex = graph_create_vertex(value); 
    new_vertex->next_vertex_in_graph = graph;

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
    int number_of_connections;

    number_of_connections = 0;

    for (vertex1 = graph; vertex1 != NULL; vertex1 = vertex1->next_vertex_in_graph) {

        printf("Vertex (%d) \n", vertex1->value);

        for (edge = vertex1->next_edge; edge != NULL; edge = edge->next_edge_in_graph) {
            vertex2 = edge->destination_vertex;
            if (vertex2 != NULL) {
                printf("   Destination vertex (%d) \n", vertex2->value);
            }
            number_of_connections++;
        }

        if (!number_of_connections) {
            printf("   This vertex doesn't have any edge.\n");
        }

        number_of_connections = 0;
    }

}

/* Check if the current vertex from the graph is conexed */
/* Check if there is a path between a note in the graph and the node value using a greedy algorithm. */
int graph_is_connected(Vertex* graph, int value) {
    Vertex* vertex1;
    Vertex* vertex2;

    Edge* next_edge;
    Edge* found_edge;

    vertex1 = graph;

    /* Find the vertex in the graph that initialize the process. If G = (V, E) check if v in V */
    while (vertex1 != NULL && vertex1->value != value) {
        vertex1 = vertex1->next_vertex_in_graph;
    }

    if (!vertex1) {
        /* The vertex doesn't exists in the graph */
        return -1;
    }

    /* Set all the visits to 0 */
    for (vertex2 = graph; vertex2; vertex2->is_visited = 0, vertex2 = vertex2->next_vertex_in_graph);

    vertex1->is_visited = 1;

    if (SHOW_INFO) {
        printf("Exploration for the vertex (%d):   \n", vertex1->value);
    }

    do {
        found_edge = NULL;
        for (vertex2 = graph; vertex2; vertex2 = vertex2->next_vertex_in_graph) {
            if (vertex2->is_visited) {
                for (next_edge = vertex2->next_edge; next_edge != NULL; next_edge = next_edge->next_edge_in_graph) {
                    // Check if vertex was visited
                    printf("Show me the value %d -- %d \n", vertex2->value, next_edge->destination_vertex->value);
                    if (! next_edge->destination_vertex->is_visited) {
                        found_edge = next_edge;
                    }
                }
            }
        }

        if (found_edge) {
            found_edge->destination_vertex->is_visited = 1;
            if (SHOW_INFO) {
                printf("Exploration for the vertex (%d):   \n", found_edge->destination_vertex->value);
            }
        }
    } while (found_edge);

    printf("----------- end! \n");

    // Check if all the vertex on the graph was visited.
    for(vertex2 = graph; vertex2 && vertex2->is_visited; vertex2 = vertex2->next_vertex_in_graph);

    // Is the graph connected?
    // vertex2 is NULL if all the vertex in the graph were visited.
    if (vertex2) {
        // The graph if not connected
        return 0;
    }

    // The graph is connected
    return 1;
}

Edge* graph_remove_edge(Edge* edge, int vertex_value) {
  Edge* previous_edge;
  Edge* aux_edge;

  previous_edge = NULL;
  aux_edge = edge;

  while (aux_edge != NULL && aux_edge->destination_vertex->value != vertex_value) {
    previous_edge = aux_edge;
    aux_edge = aux_edge->next_edge_in_graph;
  }

  if (aux_edge == NULL) {
    return edge;
  }
  
  if (previous_edge == NULL) {
    edge = aux_edge->next_edge_in_graph;
  } else {
    previous_edge->next_edge_in_graph = aux_edge->next_edge_in_graph;
  }

  free(previous_edge);

  return edge;
}


int graph_is_vertex_in_graph(Vertex* graph, int value) {
    Vertex* aux_vertex;

    for (aux_vertex = graph; aux_vertex != NULL; aux_vertex = aux_vertex->next_vertex_in_graph) {
        if (aux_vertex->value == value) {
            return 1;
        }
    }

    return 0;
}

/*
 * Remove Vertex from graph G = (V, E)
 * Strategy:
 */

Vertex* graph_remove_vertex(Vertex* graph, int vertex_value) {
    Vertex* previous_vertex;
    Vertex* current_vertex;
    Vertex* aux_vertex;

    Edge* aux_edge1;
    Edge* aux_edge2;

    previous_vertex = NULL;

    // Find the vertex to be remove it

    for (current_vertex = graph; current_vertex != NULL; current_vertex = current_vertex->next_vertex_in_graph) {
//        printf("Never Rich this place \n");

        printf("Current Vertex value %d\n", current_vertex->value);

        if (current_vertex->value == vertex_value) {
            // Found the current vertex and the previous vertex.
            printf("Found value %d\n", current_vertex->value);
            break;
        }
        previous_vertex = current_vertex;
    }

    if (current_vertex == NULL) {
        printf("The current vertex is NULL. There is nothing to remove. \n");
        return graph;
    }

    printf("Current  Vertex to be remove it %d \n", current_vertex->value);
    printf("Previous Vertex to the one that be remove it %d \n", previous_vertex->value);

    // If the vertex is not in the graph return the same graph.

    // If found the vertex. Remove the edges.
    // Next edge should be called next_edge
    for (aux_edge2 = current_vertex->next_edge; aux_edge2 != NULL; aux_edge2 = aux_edge2->next_edge_in_graph) {

        // Walk to all the vertex in the graph.
        for (aux_vertex = graph; aux_vertex != NULL; aux_vertex = aux_vertex->next_vertex_in_graph) {

            // Check if the edges is connected to one node then remove it.
            if (aux_edge2->destination_vertex == aux_vertex && aux_vertex != current_vertex) {
                aux_vertex->next_edge = graph_remove_edge(aux_vertex->next_edge, current_vertex->value);
            }
        }
    }

    aux_edge1 = current_vertex->next_edge;

    //printf("(1)----> destination_vertex:    %d\n", aux_edge1->destination_vertex->value);

    // Remove all the conections in the aux_edge
    while (aux_edge1 != NULL) {
        Edge* new_edge;

//        if (aux_edge1->next_edge_in_graph != NULL) {
//            new_edge = aux_edge1->next_edge_in_graph;
//            free(aux_edge1);
//            aux_edge1 = new_edge;
//        } else {
//            aux_edge1 = NULL;
//        }
        new_edge = aux_edge1->next_edge_in_graph;
        free(aux_edge1);
        aux_edge1 = new_edge;
        current_vertex->next_edge = aux_edge1;
    }

    current_vertex->next_edge = aux_edge1;

    if (previous_vertex == NULL) {
        graph = current_vertex->next_vertex_in_graph;
    } else {
        previous_vertex->next_vertex_in_graph = current_vertex->next_vertex_in_graph;
    }

    free(current_vertex);

    return graph;
}

Vertex* graph_destroy(Vertex* graph) {
  Vertex* aux_vertex;

  for (aux_vertex = graph; aux_vertex != NULL; aux_vertex = aux_vertex->next_vertex_in_graph) {
    aux_vertex->next_edge = graph_free_edge(aux_vertex->next_edge);
  }

  graph = graph_free_vertex(graph);

  return graph;
}

Vertex* graph_free_vertex(Vertex* vertex) {
  Vertex* aux_vertex;

  aux_vertex = vertex;

  while (aux_vertex != NULL) {
    Vertex* current_vertex = aux_vertex->next_vertex_in_graph;
    free(aux_vertex);
    aux_vertex = current_vertex;
  }

  return aux_vertex;
}

Edge* graph_free_edge(Edge* edge) {
  Edge* aux_edge = edge;

  while (aux_edge != NULL) {
    Edge* current_edge = aux_edge->next_edge_in_graph;
    free(aux_edge);
    aux_edge = current_edge;
  }

  return aux_edge;
}