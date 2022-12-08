PHP_ARG_ENABLE([skeleton],
  [whether to enable skeleton support],
  [AS_HELP_STRING([--enable-skeleton],
    [Enable skeleton support])],
  [yes])

if test "$PHP_skeleton" != "no"; then
  AC_DEFINE(HAVE_skeleton, 1, [ Have skeleton support ])
  PHP_NEW_EXTENSION(skeleton, skeleton.c, $ext_shared)
fi
