/*
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

SYS_exit 	= 1		/* Linux syscalls.  */
SYS_write 	= 4
stdout		= 1		/* File discriptor */
	.globl _start		/* Magic linker symbol: --entry-address.  */

	.text			/* Program text. */
_start:
	mov	r7, $SYS_write	/* System call function: write, in r7.  */
	mov	r0, $stdout	/* 1st parameter: file descriptor, in r0. */
	add	r1, pc, $(hello - here - 4) /* 2nd parameter: address, in r1. */
here:
	mov	r2, $(bye-hello)	/* 3rd parameter: byte count r2. */
	swi     0		/* Call system.  */

	mov	r7,$SYS_exit	/* System call function: exit, in r7.  */
	mov	r0,$0		/* 1st parameter: exit status, in r0. */
	swi	0		/* Call system.  */
	wfi 			/* Should not be reached.  */

hello:	.ascii	"Hello, GNU Mes!\n"
bye:
