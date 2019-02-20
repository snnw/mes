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

#include <setjmp.h>

void
longjmp (jmp_buf env, int val)
{
  val = val == 0 ? 1 : val;
  ///asm ("!0x0c mov____0x8(%ebp),%eax"); // val
  asm ("!0x08 mov____0x8(%ebp),%ebp"); // env*

  asm ("!0x4 mov____0x8(%ebp),%ebx");  // env.__pc
  asm ("!0x8 mov____0x8(%ebp),%esp");  // env.__sp
  asm ("!0x0 mov____0x8(%ebp),%ebp");  // env.__bp
  asm ("jmp____*%r1");
  // not reached
  exit (42);
}

int
setjmp (__jmp_buf *env)
{
  long *p = (long*)&env;
  env[0].__bp = p[-2];
  env[0].__pc = p[-1];
  env[0].__sp = (long)&env;
  return 0;
}