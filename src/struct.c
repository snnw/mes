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

// CONSTANT STRUCT_TYPE 0
#define STRUCT_TYPE 0
// CONSTANT STRUCT_PRINTER 1
#define STRUCT_PRINTER 1

SCM
make_struct (SCM type, SCM fields, SCM printer)
{
  long size = 2 + length__ (fields);
  SCM v = alloc (size);
  SCM x = make_cell__ (TSTRUCT, size, v);
#if __M2_PLANET__
  SCM vt = vector_entry (type);
  TYPE (v) = TYPE (vt);
  CAR (v) = CAR (vt);
  CDR (v) = CDR (vt);
  SCM vp = vector_entry (printer);
  TYPE (v+1) = TYPE (vp);
  CAR (v+1) = CAR (vp);
  CDR (v+1) = CDR (vp);
#else
  g_cells[v] = g_cells[vector_entry (type)];
  g_cells[v+1] = g_cells[vector_entry (printer)];
#endif
#if __M2_PLANET__
  long i;
  for (i=2; i<size; i=i+1)
#else
  for (long i=2; i<size; i++)
#endif
    {
      SCM e = cell_unspecified;
      if (fields != cell_nil)
        {
          e = CAR (fields);
          fields = CDR (fields);
        }
#if __M2_PLANET__
      //SCM ve = g_cells[vector_entry (e)];
      SCM ve = vector_entry (e);
      TYPE (v+i) = TYPE (ve);
      CAR (v+i) = CAR (ve);
      CDR (v+i) = CDR (ve);
#else
      g_cells[v+i] = g_cells[vector_entry (e)];
#endif
    }
  return x;
}

SCM
struct_length (SCM x)
{
  assert (TYPE (x) == TSTRUCT);
  return MAKE_NUMBER (LENGTH (x));
}

SCM
struct_ref_ (SCM x, long i)
{
  assert (TYPE (x) == TSTRUCT);
  assert (i < LENGTH (x));
  SCM e = STRUCT (x) + i;
  if (TYPE (e) == TREF)
    e = REF (e);
  if (TYPE (e) == TCHAR)
    e = MAKE_CHAR (VALUE (e));
  if (TYPE (e) == TNUMBER)
    e = MAKE_NUMBER (VALUE (e));
  return e;
}

SCM
struct_set_x_ (SCM x, long i, SCM e)
{
  assert (TYPE (x) == TSTRUCT);
  assert (i < LENGTH (x));
  g_cells[STRUCT (x)+i] = g_cells[vector_entry (e)];
  return cell_unspecified;
}

SCM
struct_ref (SCM x, SCM i)
{
  return struct_ref_ (x, VALUE (i));
}

SCM
struct_set_x (SCM x, SCM i, SCM e)
{
  return struct_set_x_ (x, VALUE (i), e);
}
