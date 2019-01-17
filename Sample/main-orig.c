#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int gstrange = 30;

int main(int argc, char *argv[]) {
  int rv=0;
  int strange = 100;
  printf("parent\n");
  rv = fork();
  if (rv > 0) {
    // parent
    wait(NULL);
    strange = 20000;
    gstrange = 50;
    printf("My PID (parent) is %d, (strange,gstrange) = ( %d,%d)\n", getpid(), strange, gstrange);
  }
  else if (rv == 0){
    // child
    printf("My PID (child) is %d, (strange,gstrage) = ( %d,%d)\n", getpid(), strange, gstrange);
  }
  return 0;
} /* End of main. */
