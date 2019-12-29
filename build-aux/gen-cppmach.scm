#! /bin/sh
# -*-scheme-*-
exec ${GUILE-guile} --no-auto-compile -L $(dirname $0) -C $(dirname $0) -e '(mes-snarf)' -s "$0" "$@"
!#

;;; GNU Mes --- Maxwell Equations of Software
;;; Copyright © 2019 Jan (janneke) Nieuwenhuizen <janneke@gnu.org>
;;;
;;; This file is part of GNU Mes.
;;;
;;; GNU Mes is free software; you can redistribute it and/or modify it
;;; under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 3 of the License, or (at
;;; your option) any later version.
;;;
;;; GNU Mes is distributed in the hope that it will be useful, but
;;; WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;;; GNU General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with GNU Mes.  If not, see <http://www.gnu.org/licenses/>.


;; Usage:
;; GUILE_LOAD_PATH=~/src/nyacc/module MES_ARENA=2000000 MES_MAX_ARENA=$MES_ARENA ./pre-inst-env mes build-aux/gen-cppmach.scm

(cond-expand
 (mes
  (mes-use-module (mes misc))
  (warn 'boo)
  (mes-use-module (mes pretty-print))
  (mes-use-module (nyacc lang c99 cppmach)))
 (guile
  (use-modules (mes pretty-print))
  (module-define! (resolve-module '(nyacc lalr)) 'pretty-print pretty-print)
  (use-modules (nyacc lang c99 cppmach))))

(define (reverse-string-append lst)
  (apply string-append (reverse lst)))

(define (call-with-output-file file-name proc)
  (let ((port (open-output-file file-name)))
    (if (= port -1)
        (error 'cannot-open file-name)
        (proc port))))

(define (string-every-pred-start-end pred s start end)
  (cond ((= start end) #t)
        ((> start end) (throw 'value-out-of-range "string-every" s start end))
        (else (and (string-every-pred-start-end pred s (1+ start) end)
                   (pred (string-ref s start))))))

(define (string-every pred s . rest)
  (let ((start (if (null? rest) 0
                   (car rest)))
        (end (if (or (null? rest) (null? (cdr rest))) (string-length s)
                 (cadr rest)))
        (pred (if (char? pred) (lambda (c) (eq? c pred)) pred)))
    (string-every-pred-start-end pred s start end)))


(define (vector-fold proc init vec1 . rest)
  (if (null? rest)
      (let ((len (vector-length vec1)))
        (let loop ((i 0) (result init))
          (if (= i len) result
              (loop (1+ i) (proc i result (vector-ref vec1 i))))))
      (error "VECTOR-FOLD-2-NOT-SUPPORTED")))

(define F_OK 0)

(define (rename-file old new)
  (system* "mv" old new)) ;; FIXME: rename is in libc+gnu.

(define (move-if-changed src-file dst-file . rest)
  (rename-file src-file dst-file))

(gen-cpp-files ".")
