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
#include <stdlib.h>
#include <stdbool.h>

//function prototype
void parse (char *, char **, const char *);

int main()
{
  pid_t pid;
  int cstatus;
  pid_t c;

  int BUFSIZE = 1024;
  char line[BUFSIZE];
  char * commandv[1024] = {NULL}; //1024 possible separate commands
  char * argv[64] = {NULL}; //max arguments is 64
  static char * commandDelim = ";\n";
  static char * subDelim = " \n\t";
  bool quitTrigger = 0;

  // display the prompt
  while (1)
  {
    if (quitTrigger)
      exit(0); //quit program
    printf("Prompt>");
    fflush(stdout);
    if (fgets(line, BUFSIZE, stdin) == NULL) //uses existing line buffer as memory store
    {
      perror("The following error occurred");
    }
    else //valid entry, now parse the arguments
    {
      parse(line,commandv,commandDelim);
      //the line now is separated by individual commands between semicolons, continue processing each one

      //decipher individual arguments on the line
      size_t count = 0;
      while (commandv[count] != NULL)
      {
        parse(commandv[count],argv,subDelim);
        if (argv[0] == NULL)
        {
          ++count;
          memset(argv,0,sizeof(char *) * 64);
          continue;
        }
        if (strcmp(argv[0],"quit") == 0)
        {
          ++count;
          quitTrigger = 1; //indicates the program should quit
          continue;
        }
        pid = fork();
        if (pid == 0) //inside child process
        {
          execvp(argv[0],argv);
          fprintf(stderr,"Exec failed on command %s.\n",argv[0]);
          exit(1);
        }
        else //inside parent process
        {
          c = wait(&cstatus); //wait for child to complete
          printf("PID %d exited with status %d\n", (int) c, cstatus);
        }
        ++count;
        //clear argv vector to ensure it doesn't affect next read
        memset(argv,0,sizeof(char *) * 64);
      }
    }
  }
}

void parse(char * line, char ** separator, const char * delim)
{
  char * token = strtok(line, delim);  //token is a pointer to a character sequence terminated in '\0'
  while (token != NULL)
  {
    *separator++ = token;
    token = strtok(NULL, delim);
  }
  *separator = (char *)'\0';                 /* mark the end of argument list  */
}