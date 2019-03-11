/* -*-comment-start: "//";comment-end:""-*-
 * GNU Mes --- Maxwell Equations of Software
 * Copyright © 2016,2017,2018,2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
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

#include <mes/lib.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>

/*#define LONG_MIN (-(~0UL>>1)-1)*/

typedef struct
{
  long quot;
  long rem;
} ldiv_t;

void __mesabi_div0(void)
{
  eputs(" ***MES C LIB*** divide by zero numerator=");
  eputs("\n");
  assert(0);
}

/* Compare gcc: __udivdi3 */
unsigned long __mesabi_uldiv(unsigned long a, unsigned long b, unsigned long* remainder)
{
  unsigned long tmp;
  if (!remainder)
    remainder = &tmp;
  *remainder = 0;
  if (b == 1)
    return a;
  else if (b == 0)
    __mesabi_div0();
  else
    {
      unsigned long x;
      for (x = 0; a >= b; a -= b)
        ++x;
      *remainder = a;
      return x;
    }
}

/* Note: Rounds towards zero.
   Maintainer: Be careful to satisfy quot * b + rem == a.
               That means that rem can be negative. */
ldiv_t ldiv(long a, long b)
{
  ldiv_t result;
  int negate_result = (a < 0) ^ (b < 0);
  assert(b != LONG_MIN);
  if (a != LONG_MIN)
    {
      int negative_a = (a < 0);
      if (negative_a)
        a = -a;
      if (b < 0)
        b = -b;
      result.quot = __mesabi_uldiv(a, b, &result.rem);
      if (negate_result)
        result.quot = -result.quot;
      if (negative_a)
        result.rem = -result.rem;
      return result;
    }
  else
    {
      result.rem = 0;
      if (b < 0)
        b = -b;
      if (b == 1)
        {
          result.quot = a;
          /* Since result.quot is already negative, don't negate it again. */
          negate_result = !negate_result;
        }
      else if (b == 0)
        __mesabi_div0();
      else
        {
          long x;
          for (x = 0; a <= -b; a += b)
            ++x;
          result.rem = a; /* negative */
          result.quot = x;
        }
      if (negate_result)
        result.quot = -result.quot;
      return result;
    }
}

#if __GNUC__ && !SYSTEM_LIBC
// /gnu/store/7sfr3vhxq7l4mai8m0fr1cd8w9xcj9dh-binutils-2.31.1/bin/ld: hash.o: in function `hash_cstring':
// hash.c:(.text+0x56): undefined reference to `__aeabi_idivmod'
// /gnu/store/7sfr3vhxq7l4mai8m0fr1cd8w9xcj9dh-binutils-2.31.1/bin/ld: math.o: in function `divide':
// math.c:(.text+0x516): undefined reference to `__aeabi_idiv'
// /gnu/store/7sfr3vhxq7l4mai8m0fr1cd8w9xcj9dh-binutils-2.31.1/bin/ld: math.o: in function `modulo':
// math.c:(.text+0x5d2): undefined reference to `__aeabi_idivmod'
// /gnu/store/7sfr3vhxq7l4mai8m0fr1cd8w9xcj9dh-binutils-2.31.1/bin/ld: gcc-lib/libc.a(ntoab.o): in function `ntoab':
// ntoab.c:(.text+0x54): undefined reference to `__aeabi_uidivmod'
// /gnu/store/7sfr3vhxq7l4mai8m0fr1cd8w9xcj9dh-binutils-2.31.1/bin/ld: ntoab.c:(.text+0x62): undefined reference to `__aeabi_uidiv'
/* Result: r0: quotient; r1: remainder */
long
__aeabi_idivmod (long a, long b)
{
  ldiv_t result = ldiv(a, b);
  register long rem_result asm("r1");
  rem_result = result.rem;
  return result.quot;
}

long
__aeabi_idiv (long a, long b)
{
  ldiv_t result = ldiv(a, b);
  return result.quot;
}

typedef struct
{
  unsigned long quot;
  unsigned long rem;
} uidiv_t;

/* Result: r0: quotient; r1: remainder */
unsigned long
__aeabi_uidivmod (unsigned long a, unsigned long b)
{
  unsigned long quot;
  unsigned long rem;
  register unsigned long rem_result asm("r1");
  quot = __mesabi_uldiv (a, b, &rem);
  rem_result = rem;
  return quot;
}

unsigned long
__aeabi_uidiv (unsigned long a, unsigned long b)
{
  return __mesabi_uldiv (a, b, 0);
}
#endif // __GNUC__ && !SYSTEM_LIBC
