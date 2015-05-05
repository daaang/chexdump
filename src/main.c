#include <stdio.h>
#include <string.h>
#include "hexprint.h"

/**
 * Read file object
 *
 * the_file - pointer to the FILE object (should be mode "rb")
 *
 * This reads the FILE pointer you give it and outputs to stdout.
 */
int read_file_obj(FILE* the_file);

/**
 * Read one file
 *
 * path_to_file - string path to the file we want to read
 *
 * This is just like reading a file object except that it opens the file
 * first and then closes it after. Rather than taking in an object, it
 * takes in a path to the file you want to read.
 */
int read_one_file(char* path_to_file);

/**
 * Read multiple files
 *
 * argc - integer count of items in argv
 * argv - array (size argc) of strings; the first will be ignored
 *
 * This takes in a file count as well as an array (sized to that count)
 * of file path strings. It outputs the filename of each before running
 * read_one_file on them.
 *
 * Well, actually, it ignores the first argument. Since these are just
 * from int main, and the first argument's just gonna be something like
 * `./chexdump` or whatever, who cares.
 */
int read_multiple_files(int argc, char* argv[ ]);

int main (int argc, char* argv[ ])
{
  switch (argc)
  {
    case 1:
      /* If there's a single argument, that means there are actually no
       * arguments, so we must be reading from stdin.
       */
      return read_file_obj(stdin);

    case 2:
      /* If there are two arguments, there's actually only one, so we
       * read that file.
       */
      return read_one_file(argv[1]);

    default:
      /* If there are more arguments, we read each file. */
      return read_multiple_files(argc, argv);
  }
}

int read_file_obj (FILE* the_file)
{
  /* Just initializing these here. You'll see what they're about. */
  unsigned char bytes [BYTES_PER_LINE];
  size_t        linelen, bytesize;
  unsigned int  bytes_read;

  /* The dummy string is to avoid initializing the same block of bytes
   * over and over and over and etc.
   */
  char          dummy_string [2*(BYTES_PER_LINE + 1)];

  /* One byte per, uh, byte. */
  bytesize    = 1;

  /* So far, we have read zero (0) bytes. */
  bytes_read  = 0;

  while (!feof(the_file))
  {
    /* Read up to sixteen bytes. */
    linelen     = fread(bytes, bytesize, BYTES_PER_LINE, the_file);

    /* Print this line. */
    print_line(stdout, bytes_read, bytes, linelen, dummy_string);

    /* Keep track of how many bytes we've read so far. */
    bytes_read += linelen;
  }

  /* Lastly, print the total. */
  printf("%08x\n", bytes_read);

  return 0;
}

int read_one_file(char* path_to_file)
{
  int   result;
  FILE  *the_file;

  if (strcmp(path_to_file, "-") == 0)
    /* The hyphen just means we read from stdin. */
    return read_file_obj(stdin);

  /* Open the file. */
  the_file = fopen(path_to_file, "rb");

  /* Dump it. */
  result = read_file_obj(the_file);

  /* Close it. */
  fclose(the_file);

  return result;
}

int read_multiple_files(int   argc,
                        char* argv[ ])
{
  int i, result;

  /* Print the first filename, then the file. */
  printf("%s:\n", argv[1]);
  result = read_one_file(argv[1]);

  /* We also test for a nonzero result in each iteration. This way we
   * can immediately exit if needed.
   */
  for (i = 2; i < argc && result == 0; ++i)
  {
    /* Do the same with the rest of the files, but also add an extra
     * newline between them.
     */
    printf("\n%s:\n", argv[i]);
    result = read_one_file(argv[i]);
  }

  return result;
}
