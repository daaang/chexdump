#include <stdio.h>
#include <string.h>
#include "hexprint.h"

int read_file_obj(FILE* the_file,
                  char* dummy_string);

int read_one_file(char* path_to_file,
                  char* dummy_string);

int read_multiple_files(int   argc,
                        char* argv[ ],
                        char* dummy_string);

int main (int argc, char* argv[ ])
{
  char dummy_string [2*(BYTES_PER_LINE + 1)];

  switch (argc)
  {
    case 1:
      return read_file_obj(stdin, dummy_string);

    case 2:
      return read_one_file(argv[1], dummy_string);

    default:
      return read_multiple_files(argc, argv, dummy_string);
  }
}

int read_file_obj(FILE* the_file,
                  char* dummy_string)
{
  unsigned char bytes [BYTES_PER_LINE];
  size_t        linelen, bytesize;
  unsigned int  bytes_read;

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

int read_one_file(char* path_to_file,
                  char* dummy_string)
{
  int   result;
  FILE  *the_file;

  if (strcmp(path_to_file, "-") == 0)
    /* The hyphen just means we read from stdin. */
    return read_file_obj(stdin, dummy_string);

  /* Open the file. */
  the_file = fopen(path_to_file, "rb");

  /* Dump it. */
  result = read_file_obj(the_file, dummy_string);

  /* Close it. */
  fclose(the_file);

  return result;
}

int read_multiple_files(int   argc,
                        char* argv[ ],
                        char* dummy_string)
{
  int i, result;

  /* Print the first filename, then the file. */
  printf("%s:\n", argv[1]);
  result = read_one_file(argv[1], dummy_string);

  /* We also test for a nonzero result in each iteration. This way we
   * can immediately exit if needed.
   */
  for (i = 2; i < argc && result == 0; ++i)
  {
    /* Do the same with the rest of the files, but also add an extra
     * newline between them.
     */
    printf("\n%s:\n", argv[i]);
    result = read_one_file(argv[i], dummy_string);
  }

  return result;
}
