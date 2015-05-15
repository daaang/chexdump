# I made this with 2.69 in mind.
AC_PREREQ([2.69])

# Package string.
AC_INIT([chexdump], [1.2.1])

# Foreign gets rid of annoying README etc. requirements. They're
# annoying because I already have README.md; I'm not adding one with no
# extension. That's asenine.
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Here's a file in the src directory.
AC_CONFIG_SRCDIR([src/main.c])

# Calling this config.h makes for annoying tab completion.
AC_CONFIG_HEADERS([localconf.h])

# I'll be creating these as well as localconf.h.
AC_CONFIG_FILES([Makefile src/Makefile])

# Without this, autoconf would be required for anyone trying to run
# make. Which kinda defeats the purpose?
AM_MAINTAINER_MODE([disable])

# All I need is CC.
AC_PROG_CC

# Checks for header files.
AC_CHECK_HEADERS([string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Wrap it up!
AC_OUTPUT
