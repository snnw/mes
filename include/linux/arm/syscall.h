/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 * Copyright © 2019 Danny Milosavljevic <dannym@scratchpost.org>
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
#ifndef __MES_LINUX_ARM_SYSCALL_H
#define __MES_LINUX_ARM_SYSCALL_H 1

// libc
#define SYS_fork    0x900002
#define SYS_read    0x900003
#define SYS_open    0x900005
//#define SYS_waitpid
#define SYS_wait4   0x900072
#define SYS_execve  0x90000b
#define SYS_chmod   0x90000f
#define SYS_access  0x900021
#define SYS_brk     0x90002d
#define SYS_ioctl   0x900036
#define SYS_fsync   0x900076

// libc+tcc
#define SYS_close  0x900006
#define SYS_time   0x90000d
#define SYS_lseek  0x900013
#define SYS_unlink 0x90000a
#define SYS_rmdir  0x900028
#define SYS_gettimeofday 0x90004e
#define SYS_stat   0x90006a
#define SYS_getcwd 0x9000b7

// libc+gnu
#define SYS_chdir     0x90000c
#define SYS_link      0x900009
#define SYS_getpid    0x900014
#define SYS_getuid    0x900018
#define SYS_kill      0x900025
#define SYS_rename    0x900026
#define SYS_mkdir     0x900027
#define SYS_dup       0x900029
#define SYS_pipe      0x90002a
#define SYS_getgid    0x90002f
#define SYS_rt_sigaction 0x9000ae
#define SYS_rt_sigreturn 0x9000ad
#define SYS_fcntl     0x900037
#define SYS_dup2      0x90003f
#define SYS_getrusage 0x90004d
#define SYS_lstat     0x90006b
#define SYS_setitimer 0x900068
#define SYS_fstat     0x90006c
#define SYS_nanosleep 0x9000a2
#define SYS_getdents  0x90008d
#define SYS_clock_gettime 0x900107

// bash
#define SYS_setuid    0x900017
#define SYS_setgid    0x90002e
#define SYS_geteuid   0x900031
#define SYS_getegid   0x900032
#define SYS_getppid   0x900040

// make+WITH_GLIBC
#define SYS_rt_sigprocmask 0x9000af

// tar
#define SYS_symlink   0x900053
#define SYS_readlink  0x900055
#define SYS_mknod     0x90000e

#endif // __MES_LINUX_ARM_SYSCALL_H
