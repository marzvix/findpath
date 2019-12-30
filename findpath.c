/* ---------------------- findpath.c --------------------- */
/*
 *  A function to find where a file is located.
 */


#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <io.h>
#include <dir.h>


static char path[65];

char *findpath(char *fname)
{
  char *pp, *pathenv;

  /* ---- see if the file is in the current directory ---- */
  if (access(fname, 0) == 0)    {
    getcwd(path, 64);
    if (path[strlen(path) - 1] != '\\')
      strcat(path, "\\");
    return path;
  }
  /* -------- search the path for the file --------------- */
  if ((pathenv = getenv("PATH")) != NULL)    {
    while(*pathenv)    {
      pp = path;
      memset(path, '\0', sizeof path);
      while (*pathenv && *pathenv != ';')
  	*pp++ = *pathenv++;
      if (*pathenv)
  	pathenv++;
      if (*(pp - 1) != '\\')
  	*pp++ = '\\';
      strcpy(pp, fname);
      if (access(path, 0) == 0)	{
	*pp = '\0';
	return path;
      }
    }
  }
  /* --- check the directory where the program was run --- */
  strcpy(path, *__argv);
  pp = strrchr(path, '\\') + 1;
  strcpy(pp, fname);
  if (access(path, 0) == 0)    {
    *pp = '\0';
    return path;
  }
  return NULL;
}

#ifdef DEMOPATH

void main(int argc, char *argv[])
{
  char *fp;

  if (argc > 1)    {
    fp = findpath(argv[1]);
    printf("\nThe path is %s",
	   fp ? fp : "nowhere to be found");
  }
}
#endif
