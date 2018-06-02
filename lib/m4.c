/* -*-comment-start: "//";comment-end:""-*-
 * Mes --- Maxwell Equations of Software
 * Copyright © 2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

int
abort (int x)
{
  eputs ("abort stub\n");
  return 0;
}

int
atof (int x)
{
  eputs ("atof stub\n");
  return 0;
}

int
atol (char const *s)
{
  return atoi (s);
}

int
bcmp (void const *s1, void const *s2, size_t size)
{
  return memcmp (s1, s2, size);
}

void
bcopy (void const *src, void *dest, size_t n)
{
  return memmove (dest, src, n);
}

int
bzero (void *block, size_t size)
{
  return memset (block, 0, size);
}

int
fileno (FILE *stream)
{
  return (int)stream;
}

int
fpurge (FILE *stream)
{
  eputs ("fpurge stub\n");
  return 0;
}

size_t
freadahead (FILE *fp)
{
  eputs ("freadahead stub\n");
  return 0;
}

int
index (char const *s, int c)
{
  return strchr (s, c);
}

int
isalnum (int c)
{
  return isdigit (c) || isalpha (c);
}

int
isalpha (int c)
{
  return islower (c) || isupper (c);
}

int
iscntrl (int c)
{
  return c >= 0 && c < 32;
}

int
isprint (int c)
{
  return c >= 32 && c < 127;
}

int
ispunct (int c)
{
  return isprint (c) && !isspace (c) && !isalnum (c);
}

char *
mktemp (char *template)
{
  char *p = strchr (template, '\0');
  int q = (int)template;
  *--p = ((unsigned char)(q >> 4)) % 26 + 'a';
  *--p = ((unsigned char)(q >> 8)) % 26 + 'a';
  *--p = ((unsigned char)(q >> 12)) % 26 + 'a';
  *--p = ((unsigned char)(q >> 16)) % 26 + 'a';
  *--p = ((unsigned char)(q >> 20)) % 26 + 'a';
  *--p = ((unsigned char)(q >> 24)) % 26 + 'a';
  return template;
}

int
pclose (int x)
{
  eputs ("pclose stub\n");
  return 0;
}

int
popen (int x)
{
  eputs ("popen stub\n");
  return 0;
}

int
rindex (char const *s, int c)
{
  return strrchr (s, c);
}

int
rewind (int x)
{
  eputs ("rewind stub\n");
  return 0;
}

int
setbuf (int x)
{
  eputs ("setbuf stub\n");
  return 0;
}

int
signal (int x)
{
  eputs ("signal stub\n");
  return 0;
}

int
sys_errlist (int x)
{
  eputs ("sys_errlist stub\n");
  return 0;
}

int
sys_nerr (int x)
{
  eputs ("sys_nerr stub\n");
  return 0;
}

int
system (int x)
{
  eputs ("system stub\n");
  return 0;
}