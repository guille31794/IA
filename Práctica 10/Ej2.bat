(deffacts inicio
  (soltero Jose)
  (soltera Maria)
)

(defrule casamiento
  (comprometidos ?x ?y)
  ?dir1 <-  (soltero ?x)
  ?dir2 <- (soltera ?y)
  => (assert (casados ?x ?y))
  (retract ?dir1)
  (retract ?dir2)
  )

  (reset)
  (assert (comprometidos Jose Maria))

  (facts)
  (run)
