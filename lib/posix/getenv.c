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

#include <stdlib.h>

char *
getenv (char const* s)
{
  // eputs ("getenv s="); eputs (s); eputs ("\n");
  char **p = environ;
  int length = strlen (s);
  // eputs ("length="); eputs (itoa (length)); eputs ("\n");
#if __M2_PLANET__
  while (p[0] != 0)
    {
      // eputs ("getenv p[0]="); eputs (p[0]); eputs ("\n");
      if (strncmp (s, p[0], length) == 0)
        {
          // eputs ("found!\n");
          char *q = p[0] + length;
          if (q[0] == '=')
            return q + 1;
        }
      // else
      //   eputs ("not found!\n");
      p = p + sizeof (char*);
    }
#else
  while (*p)
    {
      // eputs ("getenv *p="); eputs (*p); eputs ("\n");
      if (!strncmp (s, *p, length) && *(*p + length) == '=')
        return (*p + length + 1);
      p++;
    }
#endif
  return 0;
}
