#include "railgun.h"
#include <stdarg.h>
#include <string.h>

railgun_args*
_wrap_args(const char *fmt, ...)
{
  int argc;
  char c;
  va_list ap;
  railgun_data_dir dir;
  railgun_args* args;
  railgun_data* argv;

  args = (railgun_args*)malloc(sizeof(railgun_args));
  args->fmt = fmt;
  argc = strlen(fmt);
  if (strchr(fmt, '|') != NULL) {
    argc = strlen(fmt) - 1;
  }
  args->argc = argc;
  argv = (railgun_data*)malloc(sizeof(railgun_data) * argc);
  args->argv = argv;
  dir = RG_DIR_DOWNLOAD;

  va_start(ap, fmt);
  while ((c = *fmt++)) {
    if (c == '|') {
      dir = RG_DIR_READBACK;
      c = *fmt++;
    }
    switch (c) {
    case 'i':
      argv->type = RG_TYPE_INT_P;
      argv->dir = dir;
      argv->d.ip = va_arg(ap, int*);
      argv->n = va_arg(ap, int);
      break;
    default:
      break;
    }
    argv++;
  }

  return args;
}