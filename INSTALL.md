Installation
============

Inside the package base directory:

    ./configure
    make
    make install

It's just regular ol' autoconf, so go nuts if you want to go nuts. If
you don't already know what options that gives you, go ahead and type

    ./configure --help

Gentoo (portage)
----------------

There's an ebuild file in my own [custom overlay][funtoo] under
`sys-apps/chexdump`. It's technically for funtoo (not gentoo), but it's
the same exact thing in this case, so feel free to use it.

If you clone my overlay and add this to your `/etc/portage/make.conf`:

    PORTDIR_OVERLAY="/path/to/wherever/you/cloned/it"

then all you have to do is type

    emerge chexdump

And you'll be all set. If you don't want to have to keep track of the
overlay manually, maybe look into layman? Or something.

Things that are not portage
---------------------------

I don't remember how other package managers work, so either build your
own thing (maybe share it??) or just settle for `make install`.

[funtoo]: https://github.com/daaang/matts-funtoo-overlay
