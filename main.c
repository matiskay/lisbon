#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAXIMUN_LENGTH_OF_THE_INPUT_STRING 300
#define MAX_REPL_ARGUMENT_SIZE 100

// Colors
// TODO: Promote this to a header file something called rainbow.h
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KMAG  "\x1B[35m"
#define RESET "\033[0m"


#define PROMPT KGRN"lisbon:"KMAG"%.3i"KGRN">"RESET" "

// TODO: Create a function to get all the values of the string something like var_dump

void display_header(void);
void display_help(void);

char* get_line(void);

/**
 * TODO: Use Ncurses
 * Reference: http://viget.com/extend/game-programming-in-c-with-the-ncurses-library */
// gcc main.c -lncurses

/**
 * UI
 * - insert vertex
 *   > vertex <integer-value>
 * - insert edge
 *   > edge <integer-value> <integer-value>
 * - remove vertex
 *   > remove <integer-value>
 * - print graph
 *   > print
 * - exit
 *   > exit
 * - help
 **/
int main(int argc, char **argv) {
    char* line;
    int line_number;
    char command[MAX_REPL_ARGUMENT_SIZE];
    char variable1[MAX_REPL_ARGUMENT_SIZE];
    char variable2[MAX_REPL_ARGUMENT_SIZE];
    int flag_is_graph_initialized;
    Vertex* graph;

    flag_is_graph_initialized = 0;
    line_number = 1;
    graph = NULL;

    display_header();

    // TODO: Refactor this mess
    while (1) {
        printf(PROMPT, line_number);

        line = get_line();

        // Reset variables
        variable1[0] = '\0';
        variable2[0] = '\0';

        if (strcmp(line, "exit") == 0) {
            printf("Do you really want to exit ([y]/n)? ");

            line = get_line();

            if (strcmp(line, "y") == 0) {
                break;
            }

        } else if (strcmp(line, "print") == 0) {
            graph_print(graph);
        } else if (strcmp(line, "destroy") == 0) {
            graph = graph_destroy(graph);
        } else if (strcmp(line, "help") == 0) {
            display_help();
        } else {

            sscanf(line, "%s %s %s", command, variable1, variable2);

            if (strcmp(command, "vertex") == 0) {
                if (strlen(variable1) > 0) {
                    if (flag_is_graph_initialized) {
                        graph = graph_insert_vertex(graph, atoi(variable1));
                    } else {
                        graph = graph_create_vertex(atoi(variable1));
                        flag_is_graph_initialized = 1;
                    }
                } else {
                    printf(KRED "Error: Please add one argument. \nUsage:   vertex <int>\n" RESET);
                }
            } else if (strcmp(command, "remove_vertex") == 0) {
                if (strlen(variable1) > 0) {
                    graph = graph_remove_vertex(graph, atoi(variable1));
                } else {
                    printf("Please provide a vertex to the command. \n");
                }
            } else if (strcmp(command, "is_connected") == 0) {
                if (graph != NULL) {

                    if (strlen(variable1) > 0) {
                        if (graph_is_connected(graph, atoi(variable1)) == 0) {
                            printf("=> no \n");
                        } else {
                            printf("=> yes \n");
                        }
                    } else {
                        printf("Please specify the vertex to start. is_connected <vertex-value> \n");
                    }
                } else {
                    printf("The graph is empty. Please add a vertex. \n");
                }

            } else if (strcmp(command, "edge") == 0) {
                if (strlen(variable1) > 0 && strlen(variable2) > 0) {
                    graph = graph_create_edge_between_vertex(graph, atoi(variable1), atoi(variable2));
                } else {
                    printf(KRED "Error: Please add two arguments. \nUsage:   edge <int> <int>\n" RESET);
                }
            } else {
                if (strlen(command) > 0 && strlen(line) > 0) {
                    printf("%s is an undefined command.\n", line);
                } else {
                    printf("Please provide a command.\n");
                }

            }
        }

        line_number++;
    }

    return 0;
}

// TODO: Check overflow
char* get_line() {
    char* line;
    int index;

    line = malloc(MAXIMUN_LENGTH_OF_THE_INPUT_STRING);
    index = 0;

    line[index] = (char) getchar();

    // This command includes "\n" at the end
    while (line[index] != '\n') {
        index++;
        if (line[index] != '\n') {
            line[index] = (char) getchar();
        }
    }

    line[index] = '\0';

    return line;
}

void display_header() {
    printf("   __ _     _                     " KGRN "|   Lisbon\n" RESET);
    printf("  / /(_)___| |__   ___  _ __      " KGRN "|" RESET KMAG "   A basic graph REPL \n" RESET);
    printf(" / / | / __| '_ \\ / _ \\| '_ \\     " KGRN "|" RESET " \n");
    printf("/ /__| \\__ \\ |_) | (_) | | | |    " KGRN "|" RESET "   Data Structures and Applications\n");
    printf("\\____/_|___/_.__/ \\___/|_| |_|    " KGRN "|" RESET "   GA-024\n");
    printf("\n");
}

// TODO: He want the path to the other nodes.
void display_help() {
    printf("   exit                                     :      Exit the program.\n");
    printf("   help                                     :      Help for the program.\n");
    printf("   print                                    :      Print the graph.\n");
    printf("   vertex <integer-number>                  :      Add vertex to the graph.\n");
    printf("   edge <integer-number> <integer-number>   :      Create a vertex between vertexs.\n");
    printf("   is_connected                             :      Check if the current graph is connected.\n");
    printf("   destroy                                  :      Destroy the graph.\n");
    printf("   remove_vertex                            :      Remove Vertex from the graph.\n");
}
