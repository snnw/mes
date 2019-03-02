/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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
#ifndef __MES_GRP_H
#define __MES_GRP_H 1

#if SYSTEM_LIBC
#undef __MES_GRP_H
#include_next <pwd.h>
#else // ! SYSTEM_LIBC

#include <sys/types.h>

struct group
{
  char *gr_name;
  gid_t gr_gid;
  char **gr_mem;
};

struct group *getgrent (void);
void endgrent (void);
void setgrent (void);
struct group *getgrgid (gid_t gid);
struct group *getgrnam (char const *name);

#endif // ! SYSTEM_LIBC

#endif // __MES_GRP_H
