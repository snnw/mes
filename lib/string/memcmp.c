/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2017,2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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
memcmp (void const *s1, void const *s2, size_t size)
{
  if (!size)
    return 0;
  char *a = s1;
  char *b = s2;
#if __M2_PLANET__
  while (a[0] == b[0] && size > 0)
    {
      size = size - 1;
      a = a + 1;
      b = b + 1;
    }
  return a[0] - b[0];
#else
  while (*a == *b && --size)
    {
      a++;
      b++;
    }
  return *a - *b;
#endif
}
