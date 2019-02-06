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

#include "libmes-mini.h"

int main (int argc, char *argv[], char *envp[]);

void /* must not return */
_start ()
{
/*

sp+1    argv
sp   -> argc

environ = &argv[argc + 1]

*/


  /* stdin = 0 */

  asm ("mov____$i8,%r0 !0");
  asm ("mov____%r0,0x32 &__stdin");

  /* stdout = 1 */

  asm ("mov____$i8,%r0 !1");
  asm ("mov____%r0,0x32 &__stdout");

  /* stderr = 2 */

  asm ("mov____$i8,%r0 !2");
  asm ("mov____%r0,0x32 &__stderr");

  /* Add "environ" to main's arguments */

  asm ("ldr___%r0,(%sp,#$i8) !0"); /* "argc" */
  asm ("ldr___%r1,(%sp,#$i8) !4"); /* "argv" */
  asm ("add___%r2,%r0,%r1,lsl#4"); /* "environ": argv + argc */
  asm ("add___%r2,$i8 !4"); /* "environ": argv + argc + 1 */

  asm ("push___%r2");
  asm ("push___%r1");
  asm ("push___%r0");

  main ();

  //asm ("mov____%r0,%r0");
  asm ("mov____$i8,%r7 SYS_exit");
  asm ("swi____$0");
  asm ("hlt");
}