#include "hexprint.h"

#define COLOR_CODE(CODE) "\033[" CODE "m"
const char *COLOR_CODES[] = { COLOR_CODE("0"),      /* Normal */
                              COLOR_CODE("0;34"),   /* Blue */
                              COLOR_CODE("0;33"),   /* Yellow */
                              COLOR_CODE("0;35")};  /* Purple */
#undef COLOR_CODE

void print_line (FILE*          stream,
                 unsigned int   pos,
                 unsigned char* bytes,
                 unsigned char  stop,
                 char*          endstring)
{
  unsigned char i, start, column_stop, endlen, color;

  if (stop < 1)
    return;

  /* We initialize i and endlen to zero. Our color begins at normal.
   * We'll be starting in particular at the file position modulo the
   * number of bytes per line (probably zero). Lastly, we stop at the
   * halfway point along the line to add an extra space.
   */
  i           = 0;
  color       = COLOR_NORMAL;
  endlen      = 0;
  start       = pos % BYTES_PER_LINE;
  column_stop = BYTES_PER_LINE / 2;

  if (column_stop > stop)
    /* If we're actually supposed to stop before the second column, then
     * we should stop writing the first column there as well.
     */
    column_stop = stop;

  /* We begin with our position. */
  fprintf(stream, "%08x  ", pos);

  if (start >= column_stop)
  {
    /* If we don't start until the second half of the line, we only need
     * to print a buncha spaces for this first half.
     */
    for (i; i < column_stop; ++i)
    {
      /* For each byte, print the requisite number of spaces. */
      fputs("   ", stream);
      endstring[endlen++] = ' ';
    }
  }

  else
  {
    /* We are starting in the first column, but we might not be starting
     * at zero. If we are starting at zero, this loop will never run.
     */
    for (i; i < start; ++i)
    {
      /* Print all the spaces corresponding to unreported bytes. */
      fputs("   ", stream);
      endstring[endlen++] = ' ';
    }

    /* We now begin printing actual data for sure. Add a pipe to our end
     * string.
     */
    endstring[endlen++] = '|';

    for (i; i < column_stop; ++i)
      /* Write each byte of data. */
      write_byte(stream, bytes[i], &color, endstring, &endlen);
  }

  /* The first column is done. Print a space. */
  fputs(" ", stream);

  if (i < stop)
  {
    /* We still have data to print. */
    if (i <= start)
    {
      /* Actually, we haven't even started printing data yet. Print
       * however much space we still need, if any.
       */
      for (i; i < start; ++i)
      {
        fputs("   ", stream);
        endstring[endlen++] = ' ';
      }

      /* Finally it's time to start printing data. Add the pipe. */
      endstring[endlen++] = '|';
    }

    for (i; i < stop; ++i)
      /* Write each byte of data. */
      write_byte(stream, bytes[i], &color, endstring, &endlen);
  }

  /* We're done printing actual data; print however many extra sets of
   * three spaces it'll take to align stuff right.
   */
  for (i; i < BYTES_PER_LINE; ++i)
    fputs("   ", stream);
  fputs(" ", stream);

  if (color != COLOR_NORMAL)
  {
    /* If we're currently on some weird color, go back to normal. */
    fputs(COLOR_CODES[COLOR_NORMAL], stream);
    endstring[endlen++] = COLOR_NORMAL;
  }

  for (i = 0; i < endlen; ++i)
  {
    /* Iterate through each character in the end-string. */
    if (endstring[i] < ' ')
      /* If it's a control character, we actually mean for it to be a
       * color change.
       */
      fputs(COLOR_CODES[endstring[i]], stream);

    else
      /* Otherwise, it's just regular ol' ASCII. */
      fputc(endstring[i], stream);
  }

  /* The color is already back to normal, so all that's left is to close
   * the end string with a second pipe. Then write a newline.
   */
  fputs("|\n", stream);
}

void write_byte (FILE*          stream,
                 unsigned char  byte,
                 unsigned char* color,
                 char*          endstring,
                 unsigned char* endlen)
{
  /* By default, let's assume we've been given a visible ASCII byte. The
   * color should be normal, and the pretend byte is the same as the
   * actual byte.
   */
  unsigned char new_color     = COLOR_NORMAL,
                pretend_byte  = byte;

#define SET_CHARS(X, Y, Z)  \
  if (byte X) {             \
    new_color     = Y;      \
    pretend_byte  = byte Z; \
  }

  /* This accounts for every possible non-ASCII byte. */
  SET_CHARS(      < 0x20, COLOR_CONTROL, + 0x40)
  else SET_CHARS(== 0x7f, COLOR_CONTROL, - 0x40)
  else SET_CHARS(>= 0xc0, COLOR_UTFHIGH, - 0x80)
  else SET_CHARS(>= 0x80, COLOR_UTFLOW,  - 0x40)

#undef SET_CHARS

  if (pretend_byte == 0x7f)
    /* There's a chance that this will end up being the non-ASCII DEL
     * character, in which case we want to backup another 0x40.
     */
    pretend_byte -= 0x40;

  if (new_color != *color) {
    /* If our new color is different from the previous color, we'll want
     * to output the new one.
     */
    fputs(COLOR_CODES[new_color], stream);
    endstring[(*endlen)++]  = new_color;

    /* We should also modify the previous color. */
    *color                  = new_color;
  }

  /* Whether or not we needed to print a new color, we definitely need
   * to print the hex code for the byte.
   */
  fprintf(stream, "%02x ", byte);

  /* And our visual string should contain the guaranteed-ASCII pretend
   * byte.
   */
  endstring[(*endlen)++] = pretend_byte;
}
