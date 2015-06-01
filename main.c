#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAXIMUN_LENGTH_OF_THE_INPUT_STRING 300

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

// TODO: Create a function to get all the values of the string something like var_dump

static void finish(int sig);

char* get_line(void); 

/* Add function signatures here */

/* Reference: http://viget.com/extend/game-programming-in-c-with-the-ncurses-library */
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
  char command[100];
  char variable1[100];
  char variable2[100];
  char character;
  int flag_is_graph_initialized;
  Vertex* graph;

  flag_is_graph_initialized = 0;
  line_number = 1;

  printf("   __ _     _                     " KGRN "|   Lisbon\n" RESET); 
  printf("  / /(_)___| |__   ___  _ __      " KGRN "|" RESET KMAG "   A basic graph REPL \n" RESET);
  printf(" / / | / __| '_ \\ / _ \\| '_ \\     " KGRN "|" RESET " \n");
  printf("/ /__| \\__ \\ |_) | (_) | | | |    " KGRN "|" RESET "   Data Structures and Applications\n");
  printf("\\____/_|___/_.__/ \\___/|_| |_|    " KGRN "|" RESET "   GA-024\n");
  printf("\n");
                              

  while (1) {
    printf("lisbon:%.3i> ", line_number);
    line = get_line();

    if (strcmp(line, "exit") == 0) {
      printf("Do you really want to exit ([y]/n)? ");
      line = get_line();
      if (strcmp(line, "y") == 0) {
        break;
      }
    } else if(strcmp(line, "print") == 0) {
      graph_print(graph);
    } else if(strcmp(line, "destroy") == 0) {
      graph = graph_destroy(graph);
    } else if (strcmp(line, "help") == 0) {
      printf("   exit                                     :      Exit the program.\n");
      printf("   help                                     :      Help for the program.\n");
      printf("   print                                    :      Print the graph.\n");
      printf("   vertex <integer-number>                  :      Add vertex to the graph.\n");
      printf("   edge <integer-number> <integer-number>   :      Create a vertex between vertexs.\n");
      printf("   is_connected                             :      Check if the current graph is connected.\n");
      printf("   destroy                                  :      Create a vertex between vertexs.\n");
    } else {

      sscanf(line, "%s %s %s", command, variable1, variable2);

      if (strcmp(command, "vertex") == 0) {
        if (variable1) {
          if (flag_is_graph_initialized) {
            graph = graph_insert_vertex(graph, atoi(variable1));
          } else {
            graph = graph_create_vertex(atoi(variable1));
            flag_is_graph_initialized = 1;
          }
        }
      } else if(strcmp(command, "is_connected") == 0) {
        if (graph_is_connected(graph, atoi(variable1)) == 0) {
          printf("=> no \n");
        } else {
          printf("=> yes \n");
        }
      } else if (strcmp(command, "edge") == 0) {
        graph = graph_create_edge_between_vertex(graph, atoi(variable1), atoi(variable2));
      } else {
        printf("%s is an undefined command \n", line);
      }
    }

    line_number++;
  }

  return 0;
}

char* get_line() {
  char* line;
  int index;

  line = malloc(MAXIMUN_LENGTH_OF_THE_INPUT_STRING);
  index = 0;

  line[index] = getchar();
  
  // This command includes "\n" at the end
  while (line[index] != '\n') {
    index++;
    if (line[index] != '\n') {
      line[index] = getchar();
    }
  }

  line[index] = '\0';

  return line;
}
