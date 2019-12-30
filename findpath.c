/* ---------------------- findpath.c --------------------- */
/*
 *  A function to find where a file is located.
 *  Based on code of Extending Turbo C - Al Stevens - pg 116
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __MINGW32__
#include <dos.h>
#include <dir.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include <io.h>

#ifdef __MINGW32__
#define SEP '\\'
#define PATHSEP ';'
#else
#define SEP '/'
#define PATHSEP ':'
#endif

static char path[65];

char *findpath(char *fname)
  {
  char *pp, *pathenv;

  /* ---- see if the file is in the current directory ---- */
  if (access(fname, 0) == 0)    {
    getcwd(path, 65);
    if (path[strlen(path) - 1] != SEP)
      strcat(path, (SEP == '\\') ? "\\" : "/");
    return path;
  }
  /* -------- search the path for the file --------------- */
  if ((pathenv = getenv("PATH")) != NULL)    {
    while(*pathenv)    {
      pp = path;
      memset(path, '\0', sizeof path);
      while (*pathenv && *pathenv != PATHSEP)
  	*pp++ = *pathenv++;
      if (*pathenv)
  	pathenv++;
      if (*(pp - 1) != SEP)
  	*pp++ = SEP;
      strcpy(pp, fname);
      if (access(path, 0) == 0)	{
	*pp = '\0';
	return path;
      }
    }
  }
  /* --- check the directory where the program was run --- */
#ifdef __MINGW32__
  strcpy(path, *__argv);
#else
  getcwd(path, 65);
#endif
  pp = strrchr(path, SEP) + 1;
  strcpy(pp, fname);
  if (access(path, 0) == 0)    {
    *pp = '\0';
    return path;
  }
  return NULL;
}

#ifdef DEMOPATH

int main(int argc, char *argv[])
{
  char *fp;

  if (argc > 1)    {
    fp = findpath(argv[1]);
    printf("\nThe path is %s",
	   fp ? fp : "nowhere to be found");
  }
  return 0;
}

#endif
