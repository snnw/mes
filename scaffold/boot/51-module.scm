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

(cond-expand
 (guile)
 (mes
  (define (cons* . rest)
    (if (null? (cdr rest)) (car rest)
        (cons (car rest) (core:apply cons* (cdr rest) (current-module)))))

  (define (apply f h . t)
    (if (null? t) (core:apply f h (current-module))
        (apply f (apply cons* (cons h t)))))

  (define (append . rest)
    (core:display-error "append rest=")
    (core:write-error rest)
    (core:display-error "\n")
    (if (null? rest) '()
        (if (null? (cdr rest)) (car rest)
            (append2 (car rest) (apply append (cdr rest))))))

  (define (string->list s)
    (core:car s))

  (define <cell:string> 10)

  (define (string . lst)
    (core:make-cell <cell:string> lst 0))

  (define (string-append . rest)
    (apply string (apply append (map string->list rest))))

  (define %prefix (getenv "MES_PREFIX"))

  (define (not x) (if x #f #t))
  (define (map1 f lst)
    (if (null? lst) (list)
        (cons (f (car lst)) (map1 f (cdr lst)))))

  (define map map1)

  (define (list->string lst)
    (core:make-cell <cell:string> lst 0))

  (define %moduledir
    (if (not %prefix ) "module/"
        (list->string
         (append (string->list %prefix)
                 (string->list "/module") ; `module/' gets replaced upon install
                 (string->list "/")))))

  (define-macro (load file)
    (list 'begin
          (list 'if (list getenv "MES_DEBUG")
                (list 'begin
                      (list core:display-error ";;; read ")
                      (list core:display-error file)
                      (list core:display-error "\n")))
          (list 'primitive-load file)))

  (define-macro (include-from-path file)
    (list 'load (list string-append %moduledir file)))

  (define (string->symbol s)
    (core:lookup-symbol (core:car s)))

  (define (symbol->list s)
    (core:car s))

  (define <cell:string> 10)

  (define (string . lst)
    (core:make-cell <cell:string> lst 0))

  (define (symbol->string s)
    (apply string (symbol->list s)))

  (define (getcwd) ".")

  (define (display x . rest)
    (if (null? rest) (core:display x)
        (core:display-port x (car rest))))
  ))

(define (memq x lst)
  (if (null? lst) #f
      (if (eq? x (car lst)) lst
          (memq x (cdr lst)))))

(define (string-join lst infix)
  (if (null? (cdr lst)) (car lst)
      (string-append (car lst) infix (string-join (cdr lst) infix))))

(include-from-path "mes/module.mes")
(core:display-error module->file) (core:display-error "\n")
(define %moduledir (string-append (getcwd) "/"))
(mes-use-module (scaffold boot data module))
(mes-use-module (scaffold boot data module))
