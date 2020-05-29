#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TODO how many signals are there?
#define COUNT_SIZE 32

static int count[COUNT_SIZE];
static volatile sig_atomic_t gotSigint;

void all_handler(int signum) {
  count[signum]++;
  if (signum == SIGINT)
    gotSigint = 1;
}

int main(int argc, char **argv) {
  struct sigaction sa;
  sigset_t sigset;

  if (argc > 2)
    exit(1);

  sa.sa_handler = all_handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  // TODO what happens if sig not supported?
  for (int sig = 1; sig < COUNT_SIZE; sig++)
    sigaction(sig, &sa, NULL);

  if (argc == 2) {
    sigfillset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
    // SIGALRM may cause sleep to return early here, and may be discarded
    sleep(atoi(argv[1]));

    sigpending(&sigset);
    for (int sig = 1; sig < COUNT_SIZE; sig++)
      if (sigismember(&sigset, sig))
        printf("signal %d is pending\n", sig);

    sigemptyset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
  }

  while (!gotSigint);

  for (int sig = 1; sig < COUNT_SIZE; sig++)
    printf("signal %d: %d\n", sig, count[sig]);
}
