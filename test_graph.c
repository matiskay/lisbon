#include <stdio.h>
#include "minunit.h"
#include "graph.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KMAG  "\x1B[35m"
#define RESET "\033[0m"

int tests_run = 0;

static char * test_remove_vertex_including_edges() {
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_create_vertex(20);
    graph = graph_create_vertex(30);
    graph = graph_create_vertex(40);

    graph = graph_create_edge_between_vertex(graph, 10, 20);
    graph = graph_create_edge_between_vertex(graph, 40, 20);

    graph = graph_remove_vertex(graph, 20);

    mu_assert("test_is_vertex_in_graph failed 20 it's in the graph", graph_is_vertex_in_graph(graph, 20) == 0);
    mu_assert("10 and 20 are not connected.", graph_is_there_an_edge_between_vertex(graph, 10, 20) == 0);
    mu_assert("40 and 20 are not connected.", graph_is_there_an_edge_between_vertex(graph, 40, 20) == 0);
    return 0;
}

static char * test_remove_vertex() {
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_create_vertex(20);
    graph = graph_create_vertex(30);
    graph = graph_create_vertex(40);

    graph = graph_remove_vertex(graph, 20);

    mu_assert("test_is_vertex_in_graph failed 20 it's in the graph", graph_is_vertex_in_graph(graph, 20) == 0);
    return 0;
}

static char * test_is_vertex_in_graph() {
    Vertex* graph;

    graph = graph_create_vertex(10);

    mu_assert("test_is_vertex_in_graph failed 10 it's in the graph", graph_is_vertex_in_graph(graph, 10) == 1);
    return 0;
}

static char * test_is_vertex_not_in_graph() {
    Vertex* graph;

    graph = graph_create_vertex(10);

    mu_assert("test_is_vertex_in_graph failed 20 it is not the graph", graph_is_vertex_in_graph(graph, 20) == 0);
    return 0;
}

// TODO: Write function to compare test
// * Write to file and compare outputs.
static char * test_print_graph() {
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);

    printf("\nTesting Print Graph \n");
    printf("-------------------------------\n");

    graph_print(graph);

    printf("\n-------------------------------\n");

    return 0;
}

static char * test_print_graph_simple_connection() {
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);
    graph = graph_create_edge_between_vertex(graph, 20, 10);

    printf("\nTesting Print Graph \n");
    printf("-------------------------------\n");

    graph_print(graph);

    printf("\n-------------------------------\n");

    return 0;
}

static char * test_print_graph_multiple_connections() {
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);
    graph = graph_insert_vertex(graph, 30);
    graph = graph_insert_vertex(graph, 40);
    graph = graph_insert_vertex(graph, 50);

    graph = graph_create_edge_between_vertex(graph, 10, 20);
    graph = graph_create_edge_between_vertex(graph, 20, 30);
    graph = graph_create_edge_between_vertex(graph, 40, 50);

    printf("\nTesting Print Graph \n");
    printf("-------------------------------\n");

    graph_print(graph);

    printf("\n-------------------------------\n");

    return 0;
}

static char * test_is_there_not_edge_between_nodes() {
//    printf("Testing test_test_create_edge \n");
//    printf("---------------------------------------\n");
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);

    mu_assert("test_is_there_not_edge_between_nodes 10 - 20 fail",
              graph_is_there_an_edge_between_vertex(graph, 10, 20) == 0);
    mu_assert("test_is_there_not_edge_between_nodes 20 - 10 fail",
              graph_is_there_an_edge_between_vertex(graph, 20, 10) == 0);
    return 0;
}

static char * test_test_create_edge_many_nodes() {
//    printf("Testing test_test_create_edge \n");
//    printf("---------------------------------------\n");
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);
    graph = graph_insert_vertex(graph, 30);
    graph = graph_insert_vertex(graph, 40);
    graph = graph_insert_vertex(graph, 50);
    graph = graph_insert_vertex(graph, 60);
    graph = graph_insert_vertex(graph, 70);
    graph = graph_insert_vertex(graph, 80);
    graph = graph_insert_vertex(graph, 90);

    graph = graph_create_edge_between_vertex(graph, 10, 20);
    graph = graph_create_edge_between_vertex(graph, 70, 80);
    graph = graph_create_edge_between_vertex(graph, 80, 10);
    graph = graph_create_edge_between_vertex(graph, 10, 70);
//    printf("---------------------------------------\n");

    graph_print(graph);

    mu_assert("test_create_edge_many_nodes 10 - 20 fail", graph_is_there_an_edge_between_vertex(graph, 10, 20) == 1);
    mu_assert("test_create_edge_many_nodes 20 - 10 fail", graph_is_there_an_edge_between_vertex(graph, 20, 10) == 1);
    mu_assert("test_create_edge_many_nodes 70 - 80 fail", graph_is_there_an_edge_between_vertex(graph, 70, 80) == 1);
    mu_assert("test_create_edge_many_nodes 80 - 70 fail", graph_is_there_an_edge_between_vertex(graph, 80, 70) == 1);
    mu_assert("test_create_edge_many_nodes 80 - 10 fail", graph_is_there_an_edge_between_vertex(graph, 80, 10) == 1);
    mu_assert("test_create_edge_many_nodes 10 - 80 fail", graph_is_there_an_edge_between_vertex(graph, 10, 80) == 1);
    mu_assert("test_create_edge_many_nodes 60 !- 80 fail", graph_is_there_an_edge_between_vertex(graph, 60, 80) == 0);
    mu_assert("test_create_edge_many_nodes 80 !- 60 fail", graph_is_there_an_edge_between_vertex(graph, 80, 60) == 0);
    mu_assert("test_create_edge_many_nodes 10 - 70 fail", graph_is_there_an_edge_between_vertex(graph, 10, 70) == 1);
    mu_assert("test_create_edge_many_nodes 70 - 10 fail", graph_is_there_an_edge_between_vertex(graph, 70, 10) == 1);
    return 0;
}

static char * test_test_create_edge() {
//    printf("Testing test_test_create_edge \n");
//    printf("---------------------------------------\n");
    Vertex* graph;

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);

    graph = graph_create_edge_between_vertex(graph, 10, 20);
//    printf("---------------------------------------\n");

    mu_assert("test_test_create_edge 10 - 20 fail", graph_is_there_an_edge_between_vertex(graph, 10, 20) == 1);
    mu_assert("test_test_create_edge 20 - 10 fail", graph_is_there_an_edge_between_vertex(graph, 20, 10) == 1);
    return 0;
}

static char * test_construction() {
    Vertex* graph;

    printf("Test construction \n\n");

    graph = graph_create_vertex(10);
    graph = graph_insert_vertex(graph, 20);
    graph = graph_insert_vertex(graph, 30);
    graph = graph_insert_vertex(graph, 40);
    graph = graph_insert_vertex(graph, 50);
    graph = graph_insert_vertex(graph, 60);
    graph = graph_insert_vertex(graph, 70);
    graph = graph_insert_vertex(graph, 80);

    graph = graph_create_edge_between_vertex(graph, 10, 20);
    graph = graph_create_edge_between_vertex(graph, 70, 80);
    graph = graph_create_edge_between_vertex(graph, 80, 10);
    graph_print(graph);
    mu_assert("error, test_construction", 1 == 1);
    return 0;
}

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
//  mu_run_test(test_construction);
    mu_run_test(test_test_not_connected_graph);
    mu_run_test(test_graph_connected_graph);
    mu_run_test(test_test_create_edge);
    mu_run_test(test_test_create_edge_many_nodes);
    mu_run_test(test_print_graph);
    mu_run_test(test_print_graph_simple_connection);
    mu_run_test(test_print_graph_multiple_connections);
    mu_run_test(test_is_vertex_in_graph);
    mu_run_test(test_is_vertex_not_in_graph);
    mu_run_test(test_remove_vertex);
    mu_run_test(test_remove_vertex_including_edges);
//    mu_run_test(test_is_there_not_edge_between_nodes);
//  mu_run_test(test_graph_remove_vertex);
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
