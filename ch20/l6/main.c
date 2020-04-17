#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  pid_t pid;
  int signum;

  if (argc != 4 && argc != 5) {
    printf("expected 3 or 4 arguments, got %d\n", argc);
    exit(EXIT_FAILURE);
  }

  pid = atol(argv[1]);
  signum = atoi(argv[3]);
  for (int n = atoi(argv[2]); n > 0; --n) {
    kill(pid, signum);
  }

  if (argc == 5) {
    kill(pid, atoi(argv[4]));
  }
}
