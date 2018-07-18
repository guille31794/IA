
(clear)
(reset)

(deftemplate cuestionario
  (slot precio (type INTEGER)(default 13000)(range 12000 15000))
  (slot maletero(type SYMBOL)(allowed-values Grande Mediano Pequeño)
  (default Grande))
  (slot potencia(type INTEGER)(default 80)(range 60 150))
  (slot ABS (type SYMBOL)(allowed-values  Si No)(default Si))
  (slot consumo (type FLOAT)(default 8.0))
)

(deftemplate coches
  (slot modelo(type SYMBOL))
  (slot precio (type INTEGER)(default 13000)(range 12000 15000))
  (slot maletero(type SYMBOL)(allowed-symbols Grande Mediano Pequeño)
  (default Grande))
  (slot potencia(type INTEGER)(default 80)(range 60 150))
  (slot ABS (type SYMBOL)(allowed-symbols  Si No)(default Si))
  (slot consumo (type FLOAT)(default 8.0))
)

(deffacts iniciales
  (coches (modelo Modelo1)(precio 12000)(maletero Pequeño)(potencia 65)
  (ABS No)(consumo 4.7))
  (coches (modelo Modelo2)(precio 12500)(maletero Pequeño)(potencia 80)
  (ABS Si)(consumo 4.9))
  (coches (modelo Modelo3)(precio 13000)(maletero Mediano)(potencia 100)
  (ABS Si)(consumo 7.8))
  (coches (modelo Modelo4)(precio 14000)(maletero Grande)(potencia 125)
  (ABS Si)(consumo 6.0))
  (coches (modelo Modelo5)(precio 15000)(maletero Pequeño)(potencia 147)
  (ABS Si)(consumo 8.5))
  (iniciar)
)

(reset)

(defrule iniciaPreguntas
   ?i <- (iniciar) =>
  (printout t "Cuestionario de eleccion de vehiculo:" crlf)
  (printout t "¿Prepuesto máximo en euros?:" crlf)
  (bind ?precio (read))
  (printout t "¿Tamaño del maletero?(Pequeño, Mediano o Grande):" crlf)
  (bind ?maletero (read))
  (printout t "¿Potencia maxima en CV?:" crlf)
  (bind ?potencia (read))
  (printout t "¿Quiere ABS? (Si o No):" crlf)
  (bind ?ABS(read))
  (printout t "¿Consumo maximo a los 100 Km en L? (incluir primer decimal):" crlf)
  (bind ?consumo (read))
  (assert(cuestionario(precio ?precio)(maletero ?maletero)(potencia ?potencia)
  (ABS ?ABS)(consumo ?consumo)))
  (retract ?i)
)

(defrule eligeCoche
?cu <- (cuestionario (precio ?pre1)(maletero ?m)(potencia ?po1)(ABS ?a)(consumo ?c1))
?co <- (coches (modelo ?mo)(precio ?pre2)(maletero ?m)(potencia ?po2)(ABS ?a)(consumo ?c2))
(test (<= ?pre2 ?pre1))
(test (<= ?c1 ?c2))
(test (>= ?po1 ?po2))
=>
(printout t "Su modelo recomendado es: " ?mo crlf)
(retract ?cu)
)
