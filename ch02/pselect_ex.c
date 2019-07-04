#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <signal.h>

#define TIMEOUT 3
#define BUF_LEN 1024

int main(void)
{
  struct timespec ts;

  fd_set readfds, tmpfds;
  int ret;
  char buf[BUF_LEN+1];
  int len;
  sigset_t sigs;

  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  ts.tv_sec = TIMEOUT;
  ts.tv_nsec = 0;

  sigfillset(&sigs);

  while(1) {
    tmpfds = readfds;

    ret = pselect(STDIN_FILENO + 1, &tmpfds, NULL, NULL, &ts, &sigs);

    if (ret == -1) {
      perror("select");
    } else if (ret == 0) {
      printf("%d 초 지났음\n", TIMEOUT);
    } else {
      if (FD_ISSET(STDIN_FILENO, &tmpfds)) {
        len = read(STDIN_FILENO, buf, BUF_LEN);
        if (len == -1) {
          perror("read");
        }

        if (len) {
          buf[len] = '\0';
          printf("read: %s\n", buf);
        }

        if(strncmp(buf, "quit", 4) == 0)
          break;
      }
    }
  }

  if (strncmp(buf, "quit", 4) == 0)
    return 0;
}

