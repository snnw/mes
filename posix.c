/* -*-comment-start: "//";comment-end:""-*-
 * Mes --- Maxwell Equations of Software
 * Copyright © 2016 Jan Nieuwenhuizen <janneke@gnu.org>
 *
 * This file is part of Mes.
 *
 * Mes is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * Mes is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Mes.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fcntl.h>

char const*
string_to_cstring (scm *s)
{
  static char buf[1024];
  char *p = buf;
  s = s->string;
  while (s != &scm_nil)
    {
      *p++ = s->car->value;
      s = s->cdr;
    }
  *p = 0;
  return buf;
}

scm *
open_input_file (scm *file_name)
{
  return make_number (open (string_to_cstring (file_name), O_RDONLY));
}

scm *
current_input_port ()
{
  return make_number (fileno (g_stdin));
}

scm *
set_current_input_port (scm *port)
{
  g_stdin = fdopen (port->value, "r");
}
