(deftemplate persona
  (slot nombre)
  (slot cabello (allowed-values rubio moreno castagno blanco negro))
  (slot ojos (allowed-values negros verdes azules))
)

(assert (persona (nombre Claudia)(cabello rubio)(ojos azules)))
(assert (persona(nombre Elena)(cabello blanco)(ojos negros)))
(assert(persona(nombre Juan)(cabello moreno)(ojos verdes)))
(assert (persona(nombre Jorge)(cabello castagno)(ojos negros)))
(assert (persona(nombre Pascual)(cabello moreno)(ojos negros)))

(defrule persona-no-moreno
(persona (nombre ?nombre)
          (cabello ~moreno))
=>
(printout t ?nombre " no tiene el cabello moreno" crlf))

(defrule persona-morena-o-castagno
(persona (nombre ?nombre)
(cabello castagno | moreno))
=>
(printout t ?nombre " tiene el cabello oscuro" crlf))
