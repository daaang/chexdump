#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "hexprint.h"

#define USAGE_TEXT \
  "Usage: %s [-n length] [-s skip] [file ...]\n", argv[0]

/* These are allocated in unistd. */
extern char *optarg;
extern int optind;

/**
 * Read file object
 *
 * the_file - pointer to the FILE object (should be mode "rb")
 * length   - how many bytes to read from the file
 * offset   - where to start in the file
 *
 * This reads the FILE pointer you give it and outputs to stdout.
 */
int read_file_obj (FILE*    the_file,
                   long int length,
                   long int offset);

/**
 * Read one file
 *
 * path_to_file - string path to the file we want to read
 * length       - how many bytes to read from the file
 * offset       - where to start in the file
 *
 * This is just like reading a file object except that it opens the file
 * first and then closes it after. Rather than taking in an object, it
 * takes in a path to the file you want to read.
 */
int read_one_file (char*    path_to_file,
                   long int length,
                   long int offset);

/**
 * Read multiple files
 *
 * argc     - integer count of items in argv
 * argv     - array (size argc) of strings; the first will be ignored
 * start_i  - where to start in the array of strings
 * length   - how many bytes to read from the file
 * offset   - where to start in the file
 *
 * This takes in a file count as well as an array (sized to that count)
 * of file path strings. It outputs the filename of each before running
 * read_one_file on them.
 *
 */
int read_multiple_files (int      argc,
                         char*    argv[ ],
                         int      start_i,
                         long int length,
                         long int offset);

int main (int argc, char* argv[ ])
{
  int       option, arg_count;
  long int  length, offset;

  /* By default, our offset and length are set to zero. For the offset,
   * this sets us at the start of the file. For the length, this is a
   * meaningless value that I'll take to mean infinity instead.
   */
  offset = 0;
  length = 0;

  while ((option = getopt(argc, argv, "hn:s:")) != -1)
  {
    switch (option)
    {
      case 'h':
        /* Print help text and exit */
        printf(USAGE_TEXT);
        return 0;

        /* This is for any options that just get loaded right into
         * integer variables. Never write anything twice!
         */
#define OPT_ATOI(CHAR, VAR) \
      case CHAR:            \
        VAR = atoi(optarg); \
        break

        /* These options are just integers. */
        OPT_ATOI('n', length);
        OPT_ATOI('s', offset);

        /* Cleaning up after myself. */
#undef OPT_ATOI

      default:
        /* Print an error. */
        fprintf(stderr, "%s: invalid option -- '%c'\n",
                argv[0], option);

        /* Print the usage text and error out. */
        fprintf(stderr, USAGE_TEXT);
        return 1;
    }
  }

  /* Now that we're done with getopt, we can get the count of nonoption
   * arguments.
   */
  arg_count = argc - optind;

  if (arg_count < 1)
    /* We have no arguments. Read from stdin. */
    return read_file_obj(stdin, length, offset);

  if (arg_count > 1)
    /* We have more than one argument. Read multiple files. */
    return read_multiple_files(argc, argv, optind, length, offset);

  /* Otherwise, we have exactly one argument. Read that one file. */
  return read_one_file(argv[optind], length, offset);
}

int read_file_obj (FILE*    the_file,
                   long int length,
                   long int offset)
{
  /* Just initializing these here. You'll see what they're about. */
  unsigned char bytes [BYTES_PER_LINE];
  size_t        linelen, bytesize;
  unsigned int  bytes_read, i;

  /* The dummy string is to avoid initializing the same block of bytes
   * over and over and over and etc.
   */
  char          dummy_string [2*(BYTES_PER_LINE + 1)];

  /* One byte per, uh, byte. */
  bytesize    = 1;

  /* We'll start at the offset. */
  bytes_read  = offset;

  if (offset != 0)
  {
    /* If we were given an offset greater than zero, we may have to read
     * an extra line at the beginning. We'll start by skipping to
     * wherever we're to begin in the file.
     */
    fseek(the_file, offset, SEEK_SET);

    /* Figure out whether we'll need to read a weird line. */
    i = offset % BYTES_PER_LINE;

    if (i != 0)
    {
      /* Read into the array, but only into the end of the array. */
      linelen = fread(bytes + i,
                      bytesize,
                      BYTES_PER_LINE - i,
                      the_file);

      if (length != 0 && length < linelen)
      {
        /* If we've already read too much, rewind. */
        fseek(the_file, length - linelen, SEEK_CUR);

        /* Set the linelen to something more appropriate. */
        linelen = length;
      }

      /* Print this piece of the line. */
      print_line(stdout, offset, bytes, linelen + i, dummy_string);

      /* Add to our byte count. */
      bytes_read += linelen;
    }
  }

  if (length == 0)
  {
    /* If there's no length, we can just read to the end. */
    while (!feof(the_file))
    {
#define READ_FULL_LINE(LENGTH)                                      \
      /* Read up to sixteen bytes. */                               \
      linelen = fread(bytes, bytesize, LENGTH, the_file);   \
                                                                    \
      /* Print this line. */                                        \
      print_line(stdout, bytes_read, bytes, linelen, dummy_string); \
                                                                    \
      /* Keep track of how many bytes we've read so far. */         \
      bytes_read += linelen

      /* Do the above stuff for real now. */
      READ_FULL_LINE(BYTES_PER_LINE);
    }
  }

  else
  {
    /* Otherwise, we were given a length. Add the offset to get a
     * stopping point.
     */
    length += offset;

    /* Repurpose the offset to point to the value bytes_read will be
     * when it's time to read our last line.
     */
    offset = (length / BYTES_PER_LINE) * BYTES_PER_LINE;

    /* Last, we'll set our length to the length of the final line. */
    length -= offset;

    while (bytes_read < offset && !feof(the_file))
    {
      /* Same as with no length limit, since we know we won't reach it
       * this time around.
       */
      READ_FULL_LINE(BYTES_PER_LINE);
    }

    if (length > 0 && !feof(the_file))
    {
      /* This is the last line. Instead of reading as much as possible,
       * read only up to our length max.
       */
      READ_FULL_LINE(length);

      /* (cleaning up) */
#undef READ_FULL_LINE
    }
  }

  /* Lastly, print the total. */
  printf("%08x\n", bytes_read);

  return 0;
}

int read_one_file (char*    path_to_file,
                   long int length,
                   long int offset)
{
  int   result;
  FILE  *the_file;

  if (strcmp(path_to_file, "-") == 0)
    /* The hyphen just means we read from stdin. */
    return read_file_obj(stdin, length, offset);

  /* Open the file. */
  the_file = fopen(path_to_file, "rb");

  /* Dump it. */
  result = read_file_obj(the_file, length, offset);

  /* Close it. */
  fclose(the_file);

  return result;
}

int read_multiple_files (int      argc,
                         char*    argv[ ],
                         int      start_i,
                         long int length,
                         long int offset)
{
  int i, result;

  i = start_i;

  /* Print the first filename, then the file. */
  printf("%s:\n", argv[i]);
  result = read_one_file(argv[i], length, offset);

  /* We also test for a nonzero result in each iteration. This way we
   * can immediately exit if needed.
   */
  for (i += 1; i < argc && result == 0; ++i)
  {
    /* Do the same with the rest of the files, but also add an extra
     * newline between them.
     */
    printf("\n%s:\n", argv[i]);
    result = read_one_file(argv[i], length, offset);
  }

  return result;
}

/* Cleaning up after myself is all. */
#undef USAGE_TEXT
