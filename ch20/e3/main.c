#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void pausedler(int signo) {
  printf("signal %d delivered, pausing\n", signo);
  pause();
}

// usage: deliver SIGINT twice, if $? reports 128 + SIGINT, then SA_RESETHAND
// and SA_NODEFER flags worked
int main(void) {
  struct sigaction act;
  sigset_t set;

  // TODO why isn't & necessary?
  act.sa_handler = pausedler;
  sigemptyset(&set);
  act.sa_mask = set;
  act.sa_flags = SA_RESETHAND | SA_NODEFER;
  sigaction(SIGINT, &act, NULL);
  printf("pausing\n");
  pause();
}
