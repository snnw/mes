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

int
_start ()
{
  asm ("mov____$i8,%r0 !0");
  asm ("mov____%r0,0x32 &__stdin");

  asm ("mov____$i8,%r0 !1");
  asm ("mov____%r0,0x32 &__stdout");

  asm ("mov____$i8,%r0 !2");
  asm ("mov____%r0,0x32 &__stderr");

  asm ("mov____%r11,%r0");
  asm ("add____$i8,%r0 !4");

  asm ("movzbl_(%r0),%r0");
  asm ("add____$i8,%r0 !3");

  asm ("shl____$i8,%r0 !0x02");
  asm ("add____%r11,%r0");
  asm ("mov____%r0,0x32 &environ");
  asm ("push___%r0");

  asm ("mov____%r11,%r0");
  asm ("add____$i8,%r0 !8");
  asm ("push___%r0");

  asm ("mov____%r11,%r0");
  asm ("add____$i8,%r0 !4");
  asm ("movzbl_(%r0),%r0");
  asm ("push___%r0");

  main ();

  //asm ("mov____%r0,%r0");
  asm ("mov____$i8,%r7 SYS_exit");
  asm ("swi____$0");
  asm ("hlt");
}
