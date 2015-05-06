Color Hexdump
=============

I got tired of hexdump being not in color. Now it's in color.

Installation
------------

Check out [the install documentation][install].

Screen shot?
------------

Here's what it looks like:

    chexdump pdfa.pdf | more -f

![chexdump pdfa.pdf][pdfa]

This is a PDF where some binary data showed up. For comparison, the
output from `hexdump -C` for the same bytes looks like this:

    00000180  37 2f 52 6f 6f 74 20 31  36 20 30 20 52 2f 49 6e  |7/Root 16 0 R/In|
    00000190  66 6f 20 31 34 20 30 20  52 2f 49 44 5b 3c 31 34  |fo 14 0 R/ID[<14|
    000001a0  33 36 35 35 34 38 45 41  31 37 31 31 38 46 39 42  |365548EA17118F9B|
    000001b0  33 34 32 32 44 46 31 33  36 33 42 32 45 42 3e 3c  |3422DF1363B2EB><|
    000001c0  38 34 37 41 35 42 33 42  30 38 36 43 34 33 33 44  |847A5B3B086C433D|
    000001d0  38 37 35 31 36 45 45 42  38 34 36 38 45 37 34 45  |87516EEB8468E74E|
    000001e0  3e 5d 2f 50 72 65 76 20  34 33 35 38 35 34 37 3e  |>]/Prev 4358547>|
    000001f0  3e 0d 73 74 61 72 74 78  72 65 66 0d 30 0d 25 25  |>.startxref.0.%%|
    00000200  45 4f 46 0d 20 20 20 20  20 20 20 20 20 20 20 20  |EOF.            |
    00000210  20 20 20 20 20 20 20 0d  32 36 20 30 20 6f 62 6a  |       .26 0 obj|
    00000220  0d 3c 3c 2f 46 69 6c 74  65 72 2f 46 6c 61 74 65  |.<</Filter/Flate|
    00000230  44 65 63 6f 64 65 2f 49  20 31 33 33 2f 4c 65 6e  |Decode/I 133/Len|
    00000240  67 74 68 20 31 30 37 2f  4f 20 31 31 37 2f 53 20  |gth 107/O 117/S |
    00000250  36 39 3e 3e 73 74 72 65  61 6d 0d 0a 68 de 62 60  |69>>stream..h.b`|
    00000260  60 60 66 60 60 aa 06 92  ac 91 a7 18 c4 18 10 40  |``f``..........@|
    00000270  0c 28 c6 cc c0 c2 c0 71  10 c8 61 e2 9b 59 12 fa  |.(.....q..a..Y..|
    00000280  af 61 12 90 f5 54 2f 80  29 03 04 e1 a2 48 9a 38  |.a...T/.)....H.8|
    00000290  a1 98 81 41 99 41 98 41  fa 00 90 e1 c6 c0 f2 80  |...A.A.A........|
    000002a0  81 cf ee 4d 83 20 03 03  7f b7 ec 03 a8 3a a7 c0  |...M. .......:..|
    000002b0  2c 20 cd 08 c4 4a 40 cc  c7 e0 d4 60 07 e5 4f 01  |, ...J@....`..O.|
    000002c0  08 30 00 db 70 14 39 0d  65 6e 64 73 74 72 65 61  |.0..p.9.endstrea|
    000002d0  6d 0d 65 6e 64 6f 62 6a  0d 31 36 20 30 20 6f 62  |m.endobj.16 0 ob|
    000002e0  6a 0d 3c 3c 2f 4d 65 74  61 64 61 74 61 20 31 31  |j.<</Metadata 11|
    000002f0  20 30 20 52 2f 4f 75 74  6c 69 6e 65 73 20 39 20  | 0 R/Outlines 9 |
    00000300  30 20 52 2f 4f 75 74 70  75 74 49 6e 74 65 6e 74  |0 R/OutputIntent|
    00000310  73 20 31 32 20 30 20 52  2f 50 61 67 65 73 20 31  |s 12 0 R/Pages 1|
    00000320  30 20 30 20 52 2f 54 79  70 65 2f 43 61 74 61 6c  |0 0 R/Type/Catal|
    00000330  6f 67 3e 3e 0d 65 6e 64  6f 62 6a 0d 31 37 20 30  |og>>.endobj.17 0|
    00000340  20 6f 62 6a 0d 3c 3c 2f  43 6f 6e 74 65 6e 74 73  | obj.<</Contents|
    00000350  20 31 39 20 30 20 52 2f  43 72 6f 70 42 6f 78 5b  | 19 0 R/CropBox[|
    00000360  30 2e 30 20 30 2e 30 20  33 39 36 2e 30 20 36 31  |0.0 0.0 396.0 61|
    00000370  32 2e 30 5d 2f 4d 65 64  69 61 42 6f 78 5b 30 2e  |2.0]/MediaBox[0.|
    00000380  30 20 30 2e 30 20 33 39  36 2e 30 20 36 31 32 2e  |0 0.0 396.0 612.|
    00000390  30 5d 2f 50 61 72 65 6e  74 20 31 30 20 30 20 52  |0]/Parent 10 0 R|
    000003a0  2f 52 65 73 6f 75 72 63  65 73 3c 3c 2f 43 6f 6c  |/Resources<</Col|
    000003b0  6f 72 53 70 61 63 65 3c  3c 2f 44 65 66 61 75 6c  |orSpace<</Defaul|

You can also set skip (-s) and length (-n) just like in regular hexdump
if you want just pieces of files.

more -f
-------

Less and more don't naturally handle all the colors very well so if
you're piping to those, you'll want `less -R` and `more -f`.

Why is this in C instead of [your favorite language]
----------------------------------------------------

The most important answer here is that I like C.

But if it makes you feel better, I ran some benchmarking on really big
files, and this C version is about ten times faster than the first draft
I mocked up in Python.

Also I mean it's just code and not very much of it. I wrote a lot of
comments. Take a look; you can probably figure it out if you need to.

To do
-----

1.  I guess I could make it possible for you to configure your own
    colors if you don't like my totally awesome choices for some reason.

2.  If I can come up with a reason for `~/.config/chexdump` to exist, I
    guess I'll make that happen.

[pdfa]:     doc/pdfa.png
[install]:  INSTALL.md
