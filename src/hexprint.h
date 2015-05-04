#ifndef HEXPRINT_H
#define HEXPRINT_H

#include <stdio.h>
#include <string.h>

/* This is kinda an enum. */
#define COLOR_NORMAL  0
#define COLOR_CONTROL 1
#define COLOR_UTFLOW  2
#define COLOR_UTFHIGH 3

/* Sixteen bytes per line. */
#define BYTES_PER_LINE 0x10

/**
 * Print line
 *
 * Prints a row of hex bytes to the output stream.
 *
 * stream     - the output stream
 * pos        - the byte position in the input stream
 * bytes      - the size-16 array of bytes
 * stop       - integer [1,16] for where to stop printing
 * endstring  - char array of size at least 2 * (BYTES_PER_LINE + 1)
 */
void print_line (FILE*          stream,
                 unsigned int   pos,
                 unsigned char* bytes,
                 unsigned char  stop,
                 char*          endstring);

/**
 * Write byte
 *
 * Write a single byte to output and store an ASCII version of it in a
 * given string.
 *
 * stream     - the output stream
 * byte       - the actual byte
 * color      - the current output color
 * endstring  - char array of size at least 2 * (BYTES_PER_LINE + 1)
 * endlen     - current length of endstring
 */
void write_byte (FILE*          stream,
                 unsigned char  byte,
                 unsigned char* color,
                 char*          endstring,
                 unsigned char* endlen);

#endif /* HEXPRINT_H */
