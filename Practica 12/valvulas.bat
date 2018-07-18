(reset)
(clear)

(deftemplate valvula
(slot nombre)
(slot TI (default 0))
(slot TE (default 0))
(slot presion (default 0))
(slot estado (default cerrada)(allowed-values abierta cerrada))
)

(deffacts iniciales
(valvula (nombre Entrada)(TI 101)(TE 35)(presion 1))
(valvula (nombre Salida)(TI 101)(TE 155)(presion 5))
(valvula (nombre Pasillo1)(TI 99)(TE 37)(estado cerrada))
)

(deffunction equilibrado (?t ?p)
(while (> ?t 35)
(bind ?t (- ?t 1))
(bind ?p (+ ?p 1))
(printout t "Temperatura actual: " ?t " grados" crlf)
(printout t "Presion actual: " ?p " bares" crlf)
)
return ?p
)

(deffunction decremento (?ti ?te)
(while (> ?te ?ti)
(bind ?te (- ?te ?ti))
(printout t "La temperatura exterior ha descendido a " ?te " grados" crlf)
)
return ?te
)

(defrule R1
?v <- (valvula (nombre ?nom)(presion ?p)(estado abierta))
(test (eq ?p 5))
=>
(modify ?v (presion 0)(estado cerrada))
(printout t "La valvula " ?nom " se ha cerrado" crlf)
)

(defrule R2
?v <- (valvula (nombre ?nom)(presion ?p)(estado cerrada)(TI ?tem))
(test (> ?tem 35))
=>
(bind ?p (equilibrado ?tem ?p))
(bind ?tem 35)
(modify ?v (estado abierta)(presion ?p)(TI 35))
(printout t "La valvula " ?nom " ha equilibrado sus valores de presion " ?p
" y temperatura " ?tem crlf)
)

(defrule R3
?v1 <- (valvula (nombre ?nom1)(TI ?ti1)(TE ?te1)(estado ?est1))
?v2 <- (valvula (nombre ?nom2)(TI ?ti2)(TE ?te2)(estado ?est2))
(test (< ?ti2 ?te2))
=>
(modify ?v1 (estado abierta))
(modify ?v2 (estado abierta))
(bind ?te2 (decremento ?ti2 ?te2))
(printout t "La temperatura de " ?nom2 " se ha estabilizado en " ?te2 " grados"
crlf)
)

(reset)
