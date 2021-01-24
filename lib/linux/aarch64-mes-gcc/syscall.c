/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2018,2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 * Copyright © 2020 Sanne Wouda
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

#include <errno.h>

// *INDENT-OFF*
long
__sys_call1 (long sys_call, long one)
{
  long r;
  asm (
       "mov    x8, %1\n\t"
       "mov    x0, %2\n\t"
       "svc    0\n\t"
       "mov    %0, x0\n\t"
       : "=r" (r)
       : "r" (sys_call), "r" (one)
       : "x0", "x8"
       );
  return r;
}

long
__sys_call2 (long sys_call, long one, long two)
{
  long r;
  asm (
       "mov    x8, %1\n\t"
       "mov    x0, %2\n\t"
       "mov    x1, %3\n\t"
       "svc    0\n\t"
       "mov    %0, x0\n\t"
       : "=r" (r)
       : "r" (sys_call), "r" (one), "r" (two)
       : "x0", "x1", "x8"
       );
  return r;
}

long
__sys_call3 (long sys_call, long one, long two, long three)
{
  long r;
  asm (
       "mov    x8, %1\n\t"
       "mov    x0, %2\n\t"
       "mov    x1, %3\n\t"
       "mov    x2, %4\n\t"
       "svc    0\n\t"
       "mov    %0, x0\n\t"
       : "=r" (r)
       : "r" (sys_call), "r" (one), "r" (two), "r" (three)
       : "x0", "x1", "x2", "x8"
       );
  return r;
}

long
__sys_call4 (long sys_call, long one, long two, long three, long four)
{
  long r;
  asm (
       "mov    x8, %1\n\t"
       "mov    x0, %2\n\t"
       "mov    x1, %3\n\t"
       "mov    x2, %4\n\t"
       "mov    x3, %5\n\t"
       "svc    0\n\t"
       "mov    %0, x0\n\t"
       : "=r" (r)
       : "r" (sys_call), "r" (one), "r" (two), "r" (three), "r" (four)
       : "x0", "x1", "x2", "x3", "x8"
       );
  return r;
}

long
__sys_call5 (long sys_call, long one, long two, long three, long four, long five)
{
  long r;
  asm (
       "mov    x8, %1\n\t"
       "mov    x0, %2\n\t"
       "mov    x1, %3\n\t"
       "mov    x2, %4\n\t"
       "mov    x3, %5\n\t"
       "mov    x4, %6\n\t"
       "svc    0\n\t"
       "mov    %0, x0\n\t"
       : "=r" (r)
       : "r" (sys_call), "r" (one), "r" (two), "r" (three), "r" (four), "r" (five)
       : "x0", "x1", "x2", "x3", "x4", "x8"
       );
  return r;
}

// *INDENT-ON*

long
_sys_call1 (long sys_call, long one)
{
  long r = __sys_call1 (sys_call, one);
  if (r < 0)
    {
      errno = -r;
      r = -1;
    }
  else
    errno = 0;
  return r;
}

long
_sys_call2 (long sys_call, long one, long two)
{
  long r = __sys_call2 (sys_call, one, two);
  if (r < 0)
    {
      errno = -r;
      r = -1;
    }
  else
    errno = 0;
  return r;
}

long
_sys_call3 (long sys_call, long one, long two, long three)
{
  long r = __sys_call3 (sys_call, one, two, three);
  if (r < 0)
    {
      errno = -r;
      r = -1;
    }
  else
    errno = 0;
  return r;
}

long
_sys_call4 (long sys_call, long one, long two, long three, long four)
{
  long r = __sys_call4 (sys_call, one, two, three, four);
  if (r < 0)
    {
      errno = -r;
      r = -1;
    }
  else
    errno = 0;
  return r;
}

long
_sys_call5 (long sys_call, long one, long two, long three, long four, long five)
{
  long r = __sys_call5 (sys_call, one, two, three, four, five);
  if (r < 0)
    {
      errno = -r;
      r = -1;
    }
  else
    errno = 0;
  return r;
}
