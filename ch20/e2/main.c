#include <signal.h>
#include <stdio.h>

int main(void) {
  // TODO: can the name of act be sigaction (can an object share a type's name)?
  struct sigaction act;
  // TODO: does act need to be zeroed?
  act.sa_handler = SIG_IGN;
  sigaction(SIGUSR1, &act, NULL);
  // TODO: inform user exit code to expect if signal actually delivered
  kill(0, SIGUSR1);
  // if process not abnormally terminated by now, it ignored the signal
  fprintf(stderr, "process ignored self-sent signal\n");
  // TODO: how do you ensure compiler supports c11 features in code? e.g., implicit returns and explicit returns without specifying a return value gauarantees exit(0)
  // is implicit return, or explicit return without return value, from main undefined behavior in c89? the book does not seem to indicate whether exit is called at all
  return 0;
}
