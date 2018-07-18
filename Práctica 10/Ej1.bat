(clear)
(reset)
(deftemplate persona
	(multislot nombre)
	(slot dni (type INTEGER))
	(slot profesion (default estudiante))
  (slot nacionalidad (allowed-values Es Fr Po Al In It))
)

(deftemplate intelectual_europeo
	(multislot nombre)
	(slot dni)
	(slot idioma)
	(slot nacionalidad)
)

(list-deftemplates)

(deffacts iniciales
	(persona (nombre Mario Cantero Casino)
						(dni 122333)
						(profesion escritor)
						(nacionalidad Es))
	(persona (nombre Juana Bodega Gallego)
						(dni 3334444))
	(ciudad Gertrudis Cadiz)
	(ciudad Filoberto Sevilla)
)

(facts)

(reset)
(facts)

(assert (ciudad Juana Cadiz))
(assert (persona (nombre Alicia Mata Rueda) (dni 1234)))
(assert (intelectual_europeo (nombre Victor Hugo) (idioma frances)))

(assert (persona (nombre Mateo Duran Barbera) (dni 333221)))

(facts)
(retract 1)
(facts)
(retract 3 5)
(facts)
(retract *)
(facts)

(reset)

(reset)
(modify 1 (nombre Maria Cantero Cansino) (profesion escritora))
(facts)

(duplicate 2 (nombre Maria Bodega Gallego) (dni 11))

(facts)

(defrule R1_gaditanos
	(ciudad ?x Cadiz) => (assert (comunidad ?x Andalucia))
)

(agenda)

(defrule R2_sevillanos
	(ciudad ?x Sevilla) => (assert (comunidad Andalucia))
)

(reset)
(agenda)

(run 1)
(facts)
(run 1)
(facts)

(defrule R3_escritores
	(persona (nombre ?x ?y ?z)(profesion escritor) (nacionalidad Es)) => (assert
	(intelectual_europeo (nombre ?x ?y ?z) (nacionalidad española)
	(idioma español)))
)

(agenda)
(run 1)
(facts)
