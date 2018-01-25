(define display core:display)
(define write core:write)

;; unmemoize removes formal caching...but only one level
(define (foo doit bar)
  (define baz
    (lambda (doit)
      (display "   baz:doit=")
      (write doit)
      (display "   baz:bar=")
      (write bar)
      (display "\n")
      (doit bar)))
  (display "foo doit=")
  (write doit)
  (display "\n")
  (display " bar=")
  (write bar)
  (display "\n")
  (display "  baz=")
  (write baz)
  (display "\n")
  (baz doit))

(foo display 1)
(display "foo=")
(write foo)
(display "\n")
(foo exit 0)
(exit 1)
