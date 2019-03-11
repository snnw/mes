/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

/** Commentary:
    Inspired by implementation in GNU C Library:
    Initialization code run first thing by the ELF startup code.  For i386/Hurd.
    Copyright (C) 1995-2016 Free Software Foundation, Inc.
 */

#include <gnu/hurd.h>
#include <gnu/syscall.h>

#include <mach/mach-init.h>
#include <mach/mach_types.h>
#include <mach/message.h>
#include <mach/port.h>

struct hurd_startup_data _hurd_startup_data;
mach_port_t _hurd_dtable[_HURD_DTABLE_MAX];
int _hurd_dtable_size;

void __mach_init (void);

void
_hurd_start ()
{
  mach_port_t bootstrap;
  __mach_init ();
  __task_get_special_port (__mach_task_self (), TASK_BOOTSTRAP_PORT,
                           &bootstrap);
  __exec_startup_get_data (bootstrap, &_hurd_startup_data);
  _hurd_dtable_size = _hurd_startup_data.dtablesize;
  for (int i = 0; i < _hurd_dtable_size; i++)
    _hurd_dtable[i] = _hurd_startup_data.dtable[i];
}
