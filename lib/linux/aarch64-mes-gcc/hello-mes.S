/*
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
 * Copyright © 2021 Sanne Wouda
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

/** Commentary: */

/* Using gdb, esp. GUD in GNU Emacs is recommended
M-x gdb-display-disassembly-buffer
M-x gdb-display-io-buffer
set disassemble-next-line on
break _start
run
info registers
si
p/x $r0
RET
...
*/

/** Code: */

SYS_exit 	= 93		/* Linux syscalls.  */
SYS_write 	= 64
stdout		= 1		/* File discriptor */
	.globl _start		/* Magic linker symbol: --entry-address.  */

	.text			/* Program text. */
_start:
	mov	x8, SYS_write	/* System call function: write, in x8.  */
	mov	x0, stdout	/* 1st parameter: file descriptor, in x0. */
	adr x1, hello	/* 2nd parameter: address, in x1. */
here:
	mov	x2, bye-hello	/* 3rd parameter: byte count x2. */
	svc 0		/* Call system.  */

	mov	x8,SYS_exit	/* System call function: exit, in x8.  */
	mov	x0,0		/* 1st parameter: exit status, in x0. */
	svc	0		/* Call system.  */
	wfi 			/* Should not be reached.  */

hello:	.ascii	"Hello, GNU Mes!\n"
bye:
