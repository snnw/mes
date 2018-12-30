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

#include <string.h>

int
strncmp (char const* a, char const* b, size_t size)
{
#if __M2_PLANET__
  if (size == 0)
    return 0;
  //eputs ("strncmp a="); eputs (a); eputs (", b="); eputs (b); eputs ("\n");
  while (a[0] != 0 && b[0] != 0 && a[0] == b[0] && size > 1)
    {
      // eputs ("a[0]:"); eputc (a[0]);
      // eputs (" b[0]:"); eputc (b[0]);
      // eputs ("\n");
      size = size - 1;
      a = a + 1;
      b = b + 1;
    }
  // eputs ("done a[0]="); eputc (a[0]);
  // eputs (" b[0]="); eputc (b[0]);
  // eputs (" returning:"); eputs (itoa (a[0] - b[0])); eputs ("\n");
  return a[0] - b[0];
#else
  if (!size)
    return 0;
  while (*a && *b && *a == *b && --size)
    {
      a++;
      b++;
    }
  return *a - *b;
#endif
}
