#include <signal.h>
#include <stdio.h>

int main(void) {
  struct sigaction act;

  act.sa_handler = SIG_IGN;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction(SIGUSR1, &act, NULL);
 
  fprintf(stderr, "killing self with SIGUSR1 (signal number %d)\n", SIGUSR1);
  kill(0, SIGUSR1); // if process does not terminate here it survived signal
 
  fprintf(stderr, "process survived self-kill\n");
}
