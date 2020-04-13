#include <sigaction.h> // this may not be right
#include <sigatomic.h>

int main(void) {
  int ret;
	// sigaction
  // TODO: can the name of act be sigaction (can an object share a type's name)?
  struct sigaction act;
  act.sa_handler = // here I realize my plan to install handler fails because the exercise requires SIG_IGN, which uninstalls handler
  ret = sigaction(SIG_USR1, act, NULL);
	// kill self
	// test flag
	// exit_success or exit_failure
}
