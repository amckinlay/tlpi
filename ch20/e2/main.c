#include <signal.h>
#include <stdio.h>

int main(void) {
  sigset_t set;
  struct sigaction act;

  fprintf(stderr, "blocking SIGUSR1\n");
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  sigprocmask(SIG_BLOCK, &set, NULL);

  fprintf(stderr, "killing process with SIGUSR1\n");
  raise(SIGUSR1);

  fprintf(stderr, "ignoring SIGUSR1\n");
  act.sa_handler = SIG_IGN;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction(SIGUSR1, &act, NULL);

  fprintf(stderr, "unblocking SIGUSR1\n");
  sigprocmask(SIG_UNBLOCK, &set, NULL);

  fprintf(stderr, "process terminating successfully!\n");
}
