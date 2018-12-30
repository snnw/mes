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

DIFF=${DIFF-diff}
b=$1
set +e
$b.M2-out --help 0> $b.0 1> $b.1 2> $b.2
r=$?
set -e
if [ -f $b.exit ]; then
    e=$(cat $b.exit)
else
    e=0
fi
[ $r = $e ] || exit 1
if [ -f "$b".stdout ]; then
    $DIFF -u "$b".stdout $b.1
fi
if [ -f "$b".stderr ]; then
    $DIFF -u "$b".stderr "$b".2
fi
