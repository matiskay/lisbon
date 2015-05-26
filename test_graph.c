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

static char * test_create_graph() {
  Vertex* graph;

  graph = graph_create_vertex(10);
  graph = graph_insert_vertex(graph, 20);
  graph = graph_insert_vertex(graph, 30);
  graph = graph_create_edge_between_vertex(graph, 20, 30);
  graph = graph_create_edge_between_vertex(graph, 20, 10);
  graph = graph_create_edge_between_vertex(graph, 30, 10);
  graph = graph_create_edge_between_vertex(graph, 30, 20);
  graph = graph_create_edge_between_vertex(graph, 30, 20);

  graph = graph_create_edge_between_vertex(graph, 30, 40);

  printf("----------------------------------------------\n\n");
  graph_print(graph);
  printf("\n\n----------------------------------------------\n");

  mu_assert("error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * test_unit() {
  mu_assert("error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_unit);
  mu_run_test(test_create_graph);
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
