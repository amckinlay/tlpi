#include <signal.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>

static void basichandler(int signo) {}

int mysiginterrupt(int sig, int flag) {
  struct sigaction act;

  if (sigaction(sig, NULL, &act)) return -1;
  if (flag)
    act.sa_flags &= ~SA_RESTART;
  else
    act.sa_flags |= SA_RESTART;
  // TODO assuming support for setting SID_DFL for all signals
  sigaction(sig, &act, NULL);

  return 0;
}

int main(void) {
  struct sigaction act;
  sigset_t set;
  char buf[128];
  ssize_t size;

  sigemptyset(&set);
  act.sa_handler = basichandler;
  act.sa_mask = set;
  act.sa_flags = SA_RESTART;
  sigaction(SIGINT, &act, NULL);

  // TODO possible to modify interrupt setting before handler set?
  mysiginterrupt(SIGINT, 1);

  printf("use SIGINT to interrupt read\n");
  while ((size = read(STDIN_FILENO, buf, 127))) {
    if (size == -1) {
      if (errno == EINTR) {
        printf("detected interrupt\n");
        return 0;
      } else {
        perror("read");
        return 2;
      }
    } else {
      printf("possible signal interruption\n");
    }
  };
  // eof
  return 1;
}
