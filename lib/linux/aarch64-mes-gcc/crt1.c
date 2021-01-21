/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2017,2018,2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

#include <mes/lib-mini.h>
//int main (int argc, char *argv[], char *envp[]);

/* Note: GCC automatically emits a preamble in order to set up the frame pointer:
"push {fp}"
"add fp, sp, 0"
 */
// *INDENT-OFF*
void
_start ()
{
  asm (
       "mov    %0,0\n"
       : "=r" (__stdin)
       : //no inputs ""
       );

  asm (
       "mov    %0,1\n\t"
       : "=r" (__stdout)
       : //no inputs ""
       );

  asm (
       "mov    %0,2\n\t"
       : "=r" (__stderr)
       : //no inputs ""
       );

  /* environ = argv + argc + 1 */
  asm (
       "ldr     x0,[sp]\n\t" /* x0 = argc */
       "mov     x1,sp\n\t" /* x1 = &argc */
       "add     x1,x1,#8\n\t" /* x1 = &argv[0] */
       "add     x2,x0,#1\n\t" /* x2 = x0 + 1 */
       "lsl     x2,x2,#3\n\t" /* x2 = (x0 + 1) << 3 */
       "add     x2,x2,x1\n\t" /* x2 = ((x0 + 1) << 3) + x1 */
       "stp     x2,xzr,[sp,#-16]!\n\t" /* envp */
       "stp     x0,x1,[sp,#-16]!\n\t" /* argv, argc */
       "mov     %0,x2\n\t"
       : "=r" (environ)
       : //no inputs ""
       );
  asm (
       "ldr     x0,[sp]\n\t" /* argc */
       "ldr     x1,[sp, #8]\n\t" /* argv */
       "ldr     x2,[sp, #16]\n\t" /* envp */
       "bl      main\n\t"
       "mov     x8, #93\n\t"
       "svc     #0\n\t"
       );
}
