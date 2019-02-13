/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

void
_exit ()
{
  asm ("SYS_exit mov____$i8,%r7");
  asm ("!8 mov____0x8(%ebp),%r0");
  asm ("swi____$0");
}

void
_write ()
{
  asm ("SYS_write mov____$i8,%r7");
  asm ("!8 mov____0x8(%ebp),%r0");
  asm ("!12 mov____0x8(%ebp),%r1");
  asm ("!16 mov____0x8(%ebp),%r2");
  asm ("swi____$0");
}
