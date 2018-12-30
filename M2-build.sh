#! /bin/sh

# GNU Mes --- Maxwell Equations of Software
# Copyright © 2018 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

rm -f\
   lib/x86-mes/crt1.o\
   lib/x86-mes-gcc/libc.o\
   src/x86-mes-gcc-mes\
   lib/x86-mes/crt1.o\
   lib/x86-mes/libc.o

echo M2-configure
VERSION=wip-m2

[ -d ../nyacc/module ] || exit 1

# Avoid the need to create and use ./pre-inst-env
GUILE_LOAD_PATH=module:../nyacc/module:$GUILE_LOAD_PATH
export GUILE_LOAD_PATH
MES_PREFIX=${MES_PREFIX-mes}
export MES_PREFIX
PREFIX=.
export PREFIX
MODULEDIR=module/
export MODULEDIR

CC=${CC-i686-unknown-linux-gnu-gcc}
export CC

unset C_INCLUDE_PATH
unset LIBRARY_PATH

cp mes/module/mes/boot-0.scm.in mes/module/mes/boot-0.scm

echo Mes configured for building with M2-Planet

# Verify that M2-Planet'ized Mes C library subset continues to build with GCC...
$CC\
    --std=gnu99\
    -c\
    -g\
    -O0\
    -nostdinc\
    -nostdlib\
    -fno-builtin\
    -I include\
    lib/linux/x86-mes-gcc/crt1.c\
    -o lib/x86-mes-gcc/crt1.o

$CC\
    --std=gnu99\
    -c\
    -g\
    -O0\
    -nostdinc\
    -nostdlib\
    -fno-builtin\
    -fno-stack-protector\
    -Wno-discarded-qualifiers\
    -Wno-int-to-pointer-cast\
    -Wno-pointer-to-int-cast\
    -Wno-pointer-sign\
    -Wno-int-conversion\
    -Wno-incompatible-pointer-types\
    -I lib\
    -I include\
    lib/libc.c\
    -o lib/x86-mes-gcc/libc.o

# ...and that it continues to support GCC-built mes.
$CC\
    --std=gnu99\
    -g\
    -O0\
    -nostdinc\
    -nostdlib\
    -fno-builtin\
    -fno-stack-protector\
    -Wno-discarded-qualifiers\
    -Wno-int-to-pointer-cast\
    -Wno-pointer-to-int-cast\
    -Wno-pointer-sign\
    -Wno-int-conversion\
    -Wno-incompatible-pointer-types\
    -I .\
    -I lib\
    -I include\
    -D MODULEDIR=\"$MODULEDIR/\"\
    -D PREFIX=\"$PREFIX\"\
    -D VERSION=\"$VERSION\"\
    src/mes.c\
    lib/x86-mes-gcc/crt1.o\
    lib/x86-mes-gcc/libc.o\
    -o src/x86-mes-gcc-mes

# We start the M2-Planet transition of Mes by using the MesCC-built Mes C library...
MES_ARENA=100000000 src/x86-mes-gcc-mes\
     -e main\
     scripts/mescc.scm.in\
    -v\
    -c\
    lib/linux/x86-mes/crt1.c\
    -o lib/x86-mes/crt1.o

# ... and simultaneously verify that libc.c continues to build with MesCC.
MES_ARENA=100000000 MES_STACK=500000 src/x86-mes-gcc-mes\
     -e main\
     scripts/mescc.scm.in\
    -v\
    -c\
    -I lib\
    -I include\
    lib/libc.c\
    -o lib/x86-mes/libc.o

# We skip the src/mes.c build as it takes ~5min.

files="
scaffold/main
scaffold/hello
scaffold/argv
scaffold/micro-mes
scaffold/tiny-mes
scaffold/cons-mes
scaffold/memset
scaffold/milli-mes
scaffold/read-boot

lib/tests/assert/50-assert
lib/tests/mes/30-oputs
lib/tests/mes/50-itoa
lib/tests/posix/50-getenv
lib/tests/stdlib/50-malloc
lib/tests/string/30-strlen
lib/tests/string/50-strcmp
lib/tests/string/50-strcpy
lib/tests/string/50-strncmp

scaffold/bug
scaffold/bug2
scaffold/bug3
scaffold/bug4
src/mes
"

broken="
scaffold/argv
scaffold/memset
scaffold/milli-mes
scaffold/read-boot

lib/tests/stdlib/50-malloc
lib/tests/string/50-strcmp
lib/tests/string/50-strcpy
lib/tests/string/50-strncmp

scaffold/bug
scaffold/bug2
scaffold/bug3
scaffold/bug4

src/mes
"

for i in $files; do
    sh M2-compile.sh $i
done

echo M2-check
set +ex
expect=$(echo $broken | wc -w)
pass=0
fail=0
total=0
for t in $files; do
    sh M2-test.sh $t &> $t.log
    r=$?
    total=$((total+1))
    if [ $r = 0 ]; then
        echo $t: [OK]
        pass=$((pass+1))
    else
        echo $t: [FAIL]
        fail=$((fail+1))
    fi
done

[ $expect != 0 ] && echo "expect: $expect"
[ $fail != 0 ] && echo "failed: $fail"
[ $fail -lt $expect ] && echo "solved: $(($expect - $fail))"
echo "passed: $pass"
echo "total:  $total"
if [ $fail != 0 -a $fail -gt $expect ]; then
    echo FAILED: $fail/$total
    exit 1
elif [ $fail != 0 ]; then
    echo PASS: $pass/$total
else
    echo PASS: $total
fi
