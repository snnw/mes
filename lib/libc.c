/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 *
 * This file is part of GNU Mes.
 *
 * GNU Mes is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * GNU Mes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Mes.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/ioctl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <libmes.h>
#include <stdio.h>

#include <libmes.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include <libc-mini.c>
#include <libmes.c>

#if __GNU__
#include <hurd/libc.c>
#elif __linux__
#include <linux/libc.c>
#else
#error both __GNU__ and _linux__ are undefined, choose one
#endif

void _env ();

#if __M2_PLANET__
int
MAX(int a, int b)
{
  if (a > b)
    return a;
  return b;
}
#else
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#if __M2_PLANET__
int __mes_debug; // = -1;
#endif

int
__mes_debug ()
{
#if !__M2_PLANET__
  static int __mes_debug = -1;
#endif
  if (__mes_debug == -1)
    {
      char *p = getenv ("MES_DEBUG");
      __mes_debug = 0;
      if (p)
        __mes_debug = MAX (atoi (p), 1);
    }
  return __mes_debug;
}


#if !___GNU__
#include <assert/assert.c>
#include <stdlib/malloc.c>
#include <string/memcpy.c>
#endif

#include <stdio/getchar.c>
#include <stdio/putchar.c>
#include <stdio/fputc.c>
#include <stdio/fputs.c>
#include <stdio/putc.c>
#include <stdio/getc.c>
#include <stdio/fgetc.c>
#include <stdio/ungetc.c>

#include <string/memchr.c>
#include <string/memcmp.c>
#include <string/memset.c>
#include <string/strcmp.c>
#include <string/strcpy.c>
#include <string/strncmp.c>

#include <stdlib/free.c>
#include <stdlib/realloc.c>

#include <posix/getenv.c>
#include <posix/isatty.c>
#include <posix/setenv.c>
#include <posix/wait.c>
#include <posix/execv.c>
