#! /bin/sh

# GNU Mes --- Maxwell Equations of Software
# Copyright © 2017,2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
#
# This file is part of GNU Mes.
#
# GNU Mes is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or (at
# your option) any later version.
#
# GNU Mes is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Mes.  If not, see <http://www.gnu.org/licenses/>.

set -ex

# Basename of C program to M2-Planet'ize and build
mes=${1-src/mes}
shift ||:

CC=${CC-i686-unknown-linux-gnu-gcc}
HEX2=${HEX2-hex2}
M1=${M1-M1}
M2_PLANET=${M2_PLANET-M2-Planet}

MES_PREFIX=${MES_PREFIX-mes}
PREFIX=.
MODULEDIR=mes/module
VERSION=wip-m2

CRT1=lib/x86-mes/crt1.o
X86_M1=../m2-planet/test/common_x86/x86_defs.M1
X86_ELF=../m2-planet/test/common_x86/ELF-i386.hex2

rm -f $mes.M2
rm -f $mes.S
rm -f $mes.o
rm -f $mes.M2-out

$CC -E \
    -U __GNUC__\
    -D const=\
    -D enum=\
    -D functionn_t=FUNCTION\
    -D gid_t=int\
    -D intptr_t=int\
    -D off_t=int\
    -D pid_t=int\
    -D ssize_t=int\
    -D size_t=int\
    -D type_t=int\
    -D uid_t=int\
    -D long=int\
    -D FILE=int\
    -D SCM=int\
    -D __MESC__\
    -D __i386__\
    -D __M2_PLANET__\
    -D MODULEDIR=\"$MODULEDIR/\"\
    -D PREFIX=\"$PREFIX\"\
    -D VERSION=\"$VERSION\"\
    -I .\
    -I lib\
    -I src\
    -I include\
    $mes.c\
    | grep -v double\
    | grep -v float\
    | grep -v typedef\
    | grep -v '\.\.\.'\
    | sed \
          -e 's,[*] *argv[][]],**argv,g'\
          -e 's,[*] *env[][]],**env,g'\
          -e 's,^extern ,#extern,g'\
          -e 's,int atexit,#int atexit,g'\
          -e 's,(char[*])\([-&a-z]\),\1,g'\
          -e 's,(void[*])\([-&a-z]\),\1,g'\
          -e 's,(int)\([-&a-z]\),\1,g'\
          -e 's/, (int)/, /g'\
          -e 's,^void [*] bsearch,#void * bsearch,g'\
          -e 's,^int vfprint,#int vfprint,g'\
          -e 's,^int vprint,#int vprint,g'\
          -e 's,^int vsprint,#int vsprint,g'\
          -e 's,^int vsnprint,#int vsnprint,g'\
          -e 's,^int vsscanf,#int vsscanf,g'\
          -e 's,void qsort,#void qsort,g'\
          -e 's,int int,int,g'\
          -e 's,intptr_t,int,g'\
          -e 's,ssize_t,int,g'\
          -e 's,size_t,unsigned,g'\
          -e 's,clockid_t,int,g'\
          -e 's,gid_t,int,g'\
          -e 's,mode_t,int,g'\
          -e 's,pid_t,int,g'\
          -e 's,off_t,int,g'\
          -e 's,time_t,unsigned,g'\
          -e 's,uid_t,int,g'\
          -e 's,unsigned int,unsigned,g'\
          -e 's,unsigned short,unsigned /*FIXME: short*/,g'\
          -e 's,[]][.],]->,g'\
          -e 's,ts[.],ts->,g'\
          -e 's,time[.],time->,g'\
          -e 's,/" ",/,g'\
          -e "s,'[\\]0',0,g"\
          -e "s,'[\\]a',7,g"\
          -e "s,'[\\]b',8,g"\
          -e "s,'[\\]0',0,g"\
    > $mes.M2

if [ "$V" = 2 ]; then
    cat $mes.M2
fi

$M2_PLANET\
    -f $mes.M2 \
    -o $mes.S

test -s $mes.S || exit 101

$M1\
      --LittleEndian\
      --Architecture 1\
      -f lib/x86-mes/x86.M1\
      -f $X86_M1\
      -f $mes.S\
      -o $mes.o

sed -i\
    -e s,GLOBAL_,,\
    -e s,FUNCTION_,,\
  $mes.o

LIBC=lib/x86-mes/libc.o
$HEX2\
      --LittleEndian\
      --Architecture 1\
      --BaseAddress 0x1000000\
      -f $X86_ELF\
      -f $CRT1\
      -f $LIBC\
      -f $mes.o\
      --exec_enable\
      -o $mes.M2-out
