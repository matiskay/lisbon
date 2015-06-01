#include <stdio.h>
#include "minunit.h"
#include "graph.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

int tests_run = 0;

static char * test_graph_remove_vertex() {
  Vertex* graph;

  graph = graph_create_vertex(10);
  graph = graph_insert_vertex(graph, 20);
  graph = graph_insert_vertex(graph, 30);
  graph = graph_insert_vertex(graph, 40);
  graph = graph_insert_vertex(graph, 50);

  graph = graph_create_edge_between_vertex(graph, 10, 40);
  graph = graph_create_edge_between_vertex(graph, 40, 50);
  graph = graph_create_edge_between_vertex(graph, 50, 20);
  graph = graph_create_edge_between_vertex(graph, 20, 30);
  graph = graph_create_edge_between_vertex(graph, 20, 10);
  graph_print(graph);

  printf("\n\nRemoving 10 from graph\n\n");
  graph = graph_remove_vertex(graph, 10);
  graph_print(graph);

  printf("\n\nRemoving 20 from graph\n\n");
  graph = graph_remove_vertex(graph, 20);
  graph_print(graph);

  printf("\n\nRemoving 40 from graph\n\n");
  graph = graph_remove_vertex(graph, 40);
  graph_print(graph);

  graph = graph_destroy(graph);

  graph_print(graph);


  /*
  mu_assert("error, test_unit 1 != 1", graph_is_connected(graph, 10) == 1);
  */
  return 0;
}


static char * test_graph_connected_graph() {
  Vertex* graph;

  graph = graph_create_vertex(10);
  graph = graph_insert_vertex(graph, 20);
  graph = graph_insert_vertex(graph, 30);
  graph = graph_insert_vertex(graph, 40);
  graph = graph_insert_vertex(graph, 50);

  graph = graph_create_edge_between_vertex(graph, 10, 40);
  graph = graph_create_edge_between_vertex(graph, 40, 50);
  graph = graph_create_edge_between_vertex(graph, 50, 20);
  graph = graph_create_edge_between_vertex(graph, 20, 30);
  graph = graph_create_edge_between_vertex(graph, 20, 10);

  mu_assert("error, test_unit 1 != 1", graph_is_connected(graph, 10) == 1);
  return 0;
}

static char * test_test_not_connected_graph() {
  Vertex* graph;

  graph = graph_create_vertex(10);
  graph = graph_insert_vertex(graph, 20);
  graph = graph_insert_vertex(graph, 30);
  graph = graph_insert_vertex(graph, 40);
  graph = graph_insert_vertex(graph, 50);

  graph = graph_create_edge_between_vertex(graph, 10, 20);
  graph = graph_create_edge_between_vertex(graph, 20, 30);
  graph = graph_create_edge_between_vertex(graph, 40, 50);

  mu_assert("test_test_not_connected_graph", graph_is_connected(graph, 10) == 0);
  return 0;
}

static char * test_unit() {
  mu_assert("error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_unit);
  mu_run_test(test_test_not_connected_graph);
  mu_run_test(test_graph_connected_graph);
  mu_run_test(test_graph_remove_vertex);
  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
    printf("-_-_-_-_-_-_-_,------,      o \n");
    printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("-_-_-_-_-_-_-~|__( X .X)  +     + \n");
    printf("_-_-_-_-_-_-_- \"\"  \"\" \n");
    printf(KRED "✗ %s \n" RESET, result);
  }
  else {
    printf("-_-_-_-_-_-_-_,------,      o \n");
    printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("-_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
    printf("_-_-_-_-_-_-_-  \"\"  \"\" \n");
    printf(KGRN " ✓ ALL TESTS PASSED \n" RESET);
  }
  printf("Tests run: %d\n", tests_run);
  return result != 0;
}
