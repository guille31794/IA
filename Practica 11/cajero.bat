(clear)
(reset)

(deftemplate usuario
(slot DNI)
(slot Pin(type INTEGER)(range 0000 9999))
(slot Cantidad (type INTEGER))
)

(deftemplate tarjeta
(slot Pin(type INTEGER)(range 0000 9999))
(slot DNI)
(slot Intentos (type INTEGER)(range 0 3)(default 3))
(slot Limite (type INTEGER)(range 0 3000)(default 600))
(slot Annio(type INTEGER)(range 2018 2023)(default 2023))
(slot Validada (allowed-values Si No)(default No))
)

(deftemplate cuenta
(slot DNI)
(slot Saldo(type INTEGER))
(slot Estado(allowed-values enPantalla dineroEntregado Inicial SuperaLimite
SinSaldo)(default Inicial))
)

(deffacts iniciales
(tarjeta (DNI 123456)(Pin 1234)(Intentos 3)(Limite 600)(Annio 2020)(Validada No))
(tarjeta (DNI 456456)(Pin 4545)(Intentos 3)(Limite 500)(Annio 2018)(Validada No))
(tarjeta (DNI 000111)(Pin 0011)(Intentos 0)(Limite 500)(Annio 2018)(Validada No))

(cuenta (DNI 1234567)(Saldo 5000))
(cuenta (DNI 456456)(Saldo 33))
(cuenta (DNI 000111)(Saldo 30000))
)

(defglobal ?*Annio* = 2018)

(deffunction decremento (?a)
(- ?a 1)
)

(deffunction diferencia (?a ?b)
(- ?a ?b)
)

(defrule Supera_Intentos
 ?f1 <- (tarjeta (Intentos ?in)(DNI ?dni))
 ?f2 <- (usuario (DNI ?dni))
 ?f3 <- (cuenta (DNI ?dni))
(test (= ?in 0))
=>
(printout t "Intentos agotados, tarjeta bloqueada" crlf)
(retract ?f1)
(retract ?f2)
(retract ?f3)
)

(defrule Pin_Invalido
(usuario (Pin ?pin))
(tarjeta (Pin ?p)(Intentos ?in))
(test (neq ?pin ?p))
=>
(printout t "Error. Pin invalido." crlf)
(decremento ?p)
)

(defrule Valida_Tarjeta
(usuario (Pin ?p)(DNI ?dni))
?f <- (tarjeta (Pin ?pin)(DNI ?dni)(Intentos ?in)(Annio ?an)(Validada No))
(test (> ?in 0))
(test (>= ?an ?*Annio*))
(test (eq ?pin ?p))
=>
(modify ?f (Validada Si))
(printout t "Tarjeta: " ?pin " validada" crlf )
)

(defrule Muestra_Saldo
(tarjeta (Validada Si)(DNI ?dni))
?f <- (cuenta (DNI ?dni)(Saldo ?s)(Estado ?est))
(test (neq ?s 0))
=>
(printout t "Su saldo actual es de: " ?s " euros" crlf)
(modify ?f (Estado enPantalla))
)

(defrule Saldo_NoSuficiente
(tarjeta (Validada Si)(DNI ?dni))
?f2 <- (cuenta (DNI ?dni)(Saldo ?s)(Estado ?est))
?f3 <- (usuario (DNI ?dni))
(test (eq ?s 0))
=>
(printout t "Saldo agotado" crlf)
(modify ?f2 (Estado SinSaldo))
(retract ?f3)
)

(defrule Comprueba_Limite1
?f1 <- (usuario (DNI ?dni)(Cantidad ?eur))
?f2 <- (cuenta (DNI ?dni)(Saldo ?mon)(Estado ?est))
(test(< ?mon ?eur))
=>
(printout t "Saldo insuficiente para realizar la operacion" crlf)
(modify ?f2 (Estado SuperaLimite))
(retract ?f1)
)

(defrule Comprueba_Limite2
(tarjeta (DNI ?dni)(Limite ?lim))
?f1 <- (usuario (DNI ?dni)(Cantidad ?eur))
?f2 <- (cuenta (DNI ?dni)(Estado ?est))
(test(< ?lim ?eur))
=>
(printout t "Limite de retirada superado" crlf)
(modify ?f2 (Estado SuperaLimite))
(retract ?f1)

)

(defrule Entrega_Dinero
?f1 <- (usuario(DNI ?dni)(Cantidad ?eur))
?f2 <- (cuenta (DNI ?dni)(Saldo ?mon)(Estado ?est))
=>
(modify ?f2 (Estado dineroEntregado)(Saldo (diferencia ?mon ?eur)))
(retract ?f1)
(printout t "Su nuevo saldo es de " ?mon " euros")
)

(reset)

(assert (usuario (DNI 123456)(Pin 1234)(Cantidad 300)))
(assert (usuario (DNI 456456)(Pin 1211)(Cantidad 200)))
(assert (usuario (DNI 456456)(Pin 4545)(Cantidad 3000)))
