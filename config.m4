dnl $Id$
dnl config.m4 for extension ohash

PHP_ARG_ENABLE(ohash, whether to enable ohash support,
[  --enable-ohash           Enable ohash support])

if test "$PHP_OHASH" != "no"; then
  PHP_NEW_EXTENSION(ohash, ohash.c, $ext_shared)
fi
