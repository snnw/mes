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

#include "libmes.h"
#include "string.h"
#include "stdlib.h"

void
read_boot ()
{
  eputs ("read_boot 00\n");
#if __M2_PLANET__
  char *prefix = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  char stop = 0;
  char *boot = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  char stop = 0;
#else
  char boot[100];
  char prefix[100];
#endif
  if (getenv ("MES_BOOT") != 0)
    {
      eputs ("read_boot 04\n");
      strcpy (boot, getenv ("MES_BOOT"));
      eputs ("read_boot 05\n");
    }
  else
    {
      eputs ("read_boot 06\n");
      strcpy (
#if __M2_PLANET__  // FIXME: segfault without &
              &
#endif
              boot, "boot-0.scm");
      eputs ("read_boot 07\n");
    }
  eputs ("read_boot 08\n");
  oputs ("boot:"); oputs (
#if __M2_PLANET__
                          &
#endif
                          boot); oputs ("\n");
  eputs ("read_boot 09\n");
  oputs ("prefix:"); oputs (getenv ("MES_PREFIX")); oputs ("\n");
  eputs ("read_boot 10\n");
  if (getenv ("MES_PREFIX"))
    {
      eputs ("read_boot 11\n");
      strcpy (
#if __M2_PLANET__
              &
#endif
              prefix + strlen (
#if __M2_PLANET__
                               &
#endif
                               prefix), "/module");
      eputs ("read_boot 12\n");
      strcpy (
#if __M2_PLANET__
              &
#endif
              prefix + strlen (
#if __M2_PLANET__
                               &
#endif
                               prefix), "/mes/");
      eputs ("read_boot 13\n");
    }
  eputs ("read_boot 14\n");
  oputs ("prefix:"); oputs (
#if __M2_PLANET__
                            &
#endif
                            prefix); oputs ("\n");
  eputs ("read_boot 15\n");
}

int
main (int argc, char **argv)
{
  g_stdout = 1;
  g_stderr = 2;
  eputs ("main 00\n");
  read_boot ();
  return 0;
}
