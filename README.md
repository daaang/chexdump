Color Hexdump
=============

I got tired of hexdump being not in color. Now it's in color.

Screen shot?
------------

Here's what it looks like:

    chexdump pdfa.pdf | more -f

![chexdump pdfa.pdf][pdfa]

This is a PDF where some binary data showed up. In regular hexdump, that
data would have just been a buncha dots over on the right. But now, it's
a buncha colorful letters, wow

more -f
-------

Less and more don't naturally handle all the colors very well so if
you're piping to those, you'll want `less -R` and `more -f`.

To do
-----

1.  It'd be cool if it could take command line arguments to like,
    display only a given byte range of a file, or something. Maybe I'll
    do that next. Probably try and imitate hexdumps `-n` and `-s`
    options.

2.  I guess I could make it possible for you to configure your own
    colors if you don't like my totally awesome choices for some reason.

3.  If I can come up with a reason for `~/.config/chexdump` to exist, I
    guess I'll make that happen.

[pdfa]: doc/pdfa.png
