/* Andrew J Wood
 * Operating Systems
 * January 12, 2019
 *
 * Creates a "tiny" Unix shell simulation.
 *
 * Note that the code is self-documenting.
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

int main(int numProgArgs, char * progArgs[])
{
  pid_t pid;
  int cstatus;
  pid_t c;

  int BUFSIZE = 520; //offers a bit more space to cushion 512.
  char line[BUFSIZE];
  char * commandv[520] = {NULL}; //520 possible separate commands, not possible since buf is limited to 520 total chars
  char * argv[64] = {NULL}; //max arguments is 64
  static char * commandDelim = ";\n";
  static char * subDelim = " \n\t";
  bool quitTrigger = 0;
  bool batchMode = 0;
  FILE * filePtr = 0;
  FILE * programMode = stdin; //defaults to stdin, but can be changed to file.

  //determine if the program is running in batch mode or interactive mode
  if (numProgArgs > 2) // incorrect usage; inform user
  {
    printf("Usage: tinysh [batchFile]\n");
    exit(1);
  }
  if (numProgArgs == 2) // entering batch mode, establish file hook.
  {
    filePtr = fopen(progArgs[1],"r");
    if (filePtr == NULL)
      perror("fopen()");
    batchMode = 1;
    programMode = filePtr;
  }

  // display the prompt
  while (1)
  {
    if (quitTrigger)
    {
      fclose(programMode);
      exit(0);
    }
    if (batchMode == 0)
    {
      printf("Prompt>");
      fflush(stdout);
    }
    if (fgets(line, BUFSIZE, programMode) == NULL) //uses existing line buffer as memory store
    {
      if (feof(programMode)) //end of file is encountered
        exit(1);
      else
        perror("The following error occurred");
    }
    else if (strlen(line) > 512) //if the line is longer than 512 characters (including \n in the 512th space)
    {
      char ch = getc(programMode);
      while (ch != '\n' && ch != EOF) //keep iterating until newline or EOF is hit.
      {
        ch = getc(programMode);
      }
      //neline or EOF is hit, continue to next line (or end)
      fprintf(stderr,"The line exceeded 512 characters. Skipping to next line.\n");
    }
    else//valid entry, now parse the arguments
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