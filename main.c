#include "hexprint.h"

int read_from_stdin(char* dummy_string);

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
      return read_from_stdin(dummy_string);

    case 2:
      return read_one_file(argv[1], dummy_string);

    default:
      return read_multiple_files(argc, argv, dummy_string);
  }
}

int read_from_stdin(char* dummy_string)
{
}

int read_one_file(char* path_to_file,
                  char* dummy_string)
{
  FILE          *the_file;
  unsigned char bytes [BYTES_PER_LINE];
  size_t        bytes_per_line, linelen, bytesize;
  unsigned int  total_size;

  bytesize        = 1;
  bytes_per_line  = BYTES_PER_LINE;
  the_file        = fopen(path_to_file, "rb");
  total_size      = 0;

  while (!feof(the_file))
  {
    linelen = fread(bytes, bytesize, bytes_per_line, the_file);
    print_line(stdout, total_size, bytes, linelen, dummy_string);
    total_size += linelen;
  }

  fclose(the_file);
  printf("%08x\n", total_size);

  return 0;
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
