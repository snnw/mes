;;; Mes --- Maxwell Equations of Software
;;; Copyright © 2018 Jan Nieuwenhuizen <janneke@gnu.org>
;;;
;;; This file is part of Mes.
;;;
;;; Mes is free software; you can redistribute it and/or modify it
;;; under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 3 of the License, or (at
;;; your option) any later version.
;;;
;;; Mes is distributed in the hope that it will be useful, but
;;; WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with Mes.  If not, see <http://www.gnu.org/licenses/>.

(define display core:display)
(define write core:write)

(define (foo doit bar)
  (display "foo doit=")
  (write doit)
  (display "\n")
  (display " bar=")
  (write bar)
  (display "\n")
  (doit bar))

(foo display 1)
(foo exit 0)

(exit 1)