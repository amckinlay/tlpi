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
  sigset_t sigset;

  if (argc > 2)
    exit(1);

  for (int sig = 1; sig < COUNT_SIZE; sig++)
    signal(sig, all_handler);

  if (argc == 2) {
    sigfillset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
    sleep(atoi(argv[1]));
    sigpending(&sigset);
    for (int sig = 1; sig < COUNT_SIZE; sig++)
      if (sigismember(&sigset, sig))
        printf("signal %d is pending\n", sig);
    // TODO are pending signals delivered synchronously upon unblock? aka. will
    // all pending signals be delivered before program termination?
    sigemptyset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, NULL);
  }

  while (!gotSigint);

  for (int sig = 1; sig < COUNT_SIZE; sig++)
    printf("signal %d: %d\n", sig, count[sig]);
}
