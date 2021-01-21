/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 * Copyright © 2019,2020 Danny Milosavljevic <dannym@scratchpost.org>
 * Copyright © 2021 Sanne Wouda
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

#include "mes/lib-mini.h"

#define SYS_exit   "93"
#define SYS_write  "64"

// *INDENT-OFF*
void
_exit (int code)
{
  asm (
       "mov    x8, "SYS_exit"\n\t"
       "mov    x0, %0\n\t"
       "svc    0\n\t"
       : // no outputs "=" (r)
       : "r" (code)
       : "x0", "x8"
       );
  // not reached
  _exit (0);
}

ssize_t
_write (int filedes, void const *buffer, size_t size)
{
  long r;
  asm (
       "mov    x8, "SYS_write"\n\t"
       "mov    x0, %1\n\t"
       "mov    x1, %2\n\t"
       "mov    x2, %3\n\t"
       "svc    0\n\t"
       "mov    %0, x0\n\t"
       : "=r" (r)
       : "r" (filedes), "r" (buffer), "r" (size)
       : "x0", "x1", "x2", "x8"
       );
  return r;
}
// *INDENT-ON*
