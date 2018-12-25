/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

char *p = "01234567890";
struct scm
{
  int type;
  int car;
  int cdr;
};
struct scm *g_cells;

#define struct_size 12
#define TYPE(x) ((x*struct_size)+g_cells)->type

int
main (int argc, char **argv)
{
  g_cells = &p;
  TYPE (0) = 1;      // This works, but expands to unreadable .M2 code

#if __M2_PLANET__
  g_cells[0]->type = 0;
#else
  g_cells[0].type = 0;
#endif

  return 0;
}
