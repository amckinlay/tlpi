#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // TODO parse pid correctly
  pid_t pid;
  int sig;

  if (argc != 3) {
    fprintf(stderr, "argc != 2\n");
    return EXIT_FAILURE;
  }

  // TODO prevent UB
  pid = atol(argv[1]);
  sig = atoi(argv[2]);

  if (kill(pid, sig)) {
    perror("kill");
    return EXIT_FAILURE;
  }
}
