(reset)
(clear)

(deftemplate aeronaves
(slot id_aeronave)
(slot compania)
(slot origen)
(slot destino)
(slot vActual)
(slot peticion (allowed-values Ninguna Despegue Aterrizaje Emergencia Rumbo))
(slot estado (allowed-values enTierra Ascenso Crucero Descenso)
(default enTierra))
)

(deftemplate aerodromo
(slot id_aerodromo)
(slot ciudad)
(slot radar (allowed-values On Off))
(slot visibilidad)
(slot vViento)
)

(deftemplate piloto
(slot id_piloto)
(slot aeronave)
(slot estado (allowed-values OK SOS Ejecutando Stand-by)(default Stand-by))
)

(deftemplate vuelos
(slot aer_origen)
(slot aer_destino)
(slot distancia)
(slot vDespegue (default 240))
(slot vCrucero (default 700))
)

(defrule Despegar
?f1 <- (aeronaves (id_aeronave ?id_avion)(estado enTierra)(peticion Despegue)
(origen ?id_aeropuerto)(vActual ?v1)(compania ?com)(destino ?des))
?f2 <- (piloto (aeronave ?id_avion)(estado OK))
(aerodromo (id_aerodromo ?id_aeropuerto)(ciudad ?ciudad)(radar On)
(visibilidad ?vis)(vViento ?vel))
(vuelos (aer_origen ?id_aeropuerto)(aer_destino ?des)(vDespegue ?v2))
(test (< ?vel 75))
(test (> ?vis 5))
=>
(modify ?f2 (estado Ejecutando))
(modify ?f1 (estado Ascenso)(peticion Ninguna)(vActual ?v2))
(printout t "La aeronave " ?id_avion " de la comapañia "
?com " va a realizar la accion despegue desde el aerodromo "
?id_aeropuerto " de " ?ciudad " con destino " ?des crlf)
)

(defrule Excepcion
(piloto (estado ~OK)(aeronave ?avion))
?a <- (aeronaves (id_aeronave ?avion)(peticion Despegue)(origen ?ori)(compania ?com)
(destino ?des))
(vuelos (aer_origen ?ori)(aer_destino ?des))
(aerodromo (id_aerodromo ?ori))
=>
(modify ?a (peticion Emergencia))
(printout t "ATENCION El piloto de la aeronave " ?avion " de la compania "
?com " no se encuentra disponible para iniciar el despegue desde el aerodromo "
?ori " con destino " ?des crlf)
)

(deffunction estimacionH (?d ?v)
(div ?d ?v)
)

(deffunction estimacionM (?d ?v)
(bind ?m (mod ?d ?v))
(bind ?aux (* ?m 60))
(div ?aux ?v)
)

(defrule Crucero
(vuelos (vCrucero ?vc)(distancia ?d)(aer_origen ?ori)(aer_destino ?des))
?a <- (aeronaves (estado Ascenso)(vActual ?vel)(id_aeronave ?avion)(origen ?ori)
(destino ?des))
?p <- (piloto (estado ?est)(aeronave ?avion))
=>
(modify ?a (estado Crucero)(vActual ?vc))
(modify ?p (estado Stand-by))
(bind ?h (estimacionH ?d ?vc))
(bind ?m (estimacionM ?d ?vc))
(printout t "Se informa a los pasajeros, que el despegue ha sido correcto y se
estima que el tiempo de vuelo será de " ?h " horas y " ?m " minutos" crlf)
)

(deffacts prueba
(vuelos (vCrucero 800)(distancia 880)(aer_origen XRY)(aer_destino BCN))
(aeronaves (id_aeronave CA123)(estado Ascenso)(vActual 240)(origen XRY)(destino
BCN))
(piloto (id_piloto Kbsa)(estado Ejecutando)(aeronave CA123))
)

(reset)
(run)
