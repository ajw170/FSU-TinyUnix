/* Andrew J Wood
 * Operating Systems
 * January 12, 2019
 *
 * Creates a "tiny" Unix shell simulation.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

//function prototype
void parse (char *, char **);

int main()
{
  pid_t pid;
  int cstatus;
  pid_t c;

  int BUFSIZE = 1024;
  char line[BUFSIZE];
  char *argv[64]; //max arguments is 64

  // display the prompt
  while (1)
  {
    printf("Prompt>");
    fflush(stdout);
    if (fgets(line, BUFSIZE, stdin) == NULL)
    {
      printf("There was a problem with the input.");
    }
    else //valid entry, now parse the arguments
    {
      parse(line,argv);
      pid = fork();
      if (pid == 0) //inside child process
      {
        execvp(argv[0],argv);
        fprintf(stderr,"Sorry, but the execution failed.\n");
      }
      else //inside parent process
      {
        c = wait(&cstatus); //wait for child to complete
        printf("PID %d exited with status %d\n", (long) c, cstatus);
      }
    }
  }
}

void parse(char * line, char ** argv)
{
  static char * delimiter = " \n\t";
  char * token = strtok(line, delimiter);  //token is a pointer to a character sequence terminated in '\0'
  while (token != NULL)
  {
    *argv++ = token;
    token = strtok(NULL, delimiter);
  }
  *argv = (char *)'\0';                 /* mark the end of argument list  */
}