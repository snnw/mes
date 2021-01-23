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
#ifndef __MES_LINUX_AARCH64_SYSCALL_H
#define __MES_LINUX_AARCH64_SYSCALL_H 1

#define AT_FDCWD -100

// libmes
#define SYS_lseek  62

// libc
#define SYS_brk       214
#define SYS_clock_gettime 113
#define SYS_clone 220
#define SYS_dup       23
#define SYS_dup3      24
#define SYS_execve  221
#define SYS_faccessat 48
#define SYS_fchmodat   53

// libc+tcc

#endif // __MES_LINUX_AARCH64_SYSCALL_H
