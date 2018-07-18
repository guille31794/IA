(clear)
(reset)

(deftemplate Productos
(slot id)
(slot nombre)
(slot pasillo)
(slot stock)
(slot precio)
)

(deftemplate Pedidos
(slot id_cliente)
(slot id_producto)
(slot unidades)
)

(deftemplate carro
(slot id_cliente)
(slot pasillo (default 1))
(slot factura (default 0))
(slot num_productos(default 0))
)

(defrule R1_asignarcarro
 ?f <- (nuevo_cliente ?ic)
 (not (carro (id_cliente ?ic)))
=>
(assert (carro (id_cliente ?ic)(pasillo 1)(factura 0)(num_productos 0)))
(retract ?f)
)

(deffunction incremento (?p)
(+ ?p 1)
)

(defrule R2_mover
?c <- (carro (pasillo ?p))
(test (< ?p 12))
=>
(modify ?c (pasillo (incremento ?p)))
)

(defrule R2_moverInicio
?c <- (carro (pasillo ?p))
(test (eq ?p 12))
=>
(modify ?c (pasillo 1))
)

(defrule R3_comprar
?c <- (carro (id_cliente ?ic)(pasillo ?pp)(factura ?fc)(num_productos ?np))
?fp <- (Pedidos (id_cliente ?ic)(id_producto ?ip)(unidades ?u))
?fpr <- (Productos(id ?id)(pasillo ?pp)(stock ?sp)(precio ?pre))
(test (>= ?sp ?u))
=>
(retract ?fp)
(modify ?fpr (stock (- ?sp ?u)))
(modify ?c (factura (+ ?fc (* ?u ?pre)))(num_productos (+ ?np ?u)))
)

(defrule R4_sinStock
?p <- (Pedidos (id_producto ?p)(unidades ?c))
(Productos (id ?p)(stock ?s)(nombre ?n))
(test (< ?s ?c))
=>
(printout t "No queda suficiente stock de " ?n " para satisfacer su compra,
 rogamos, disculpe las molestias")
(retract ?p)
)

(deffacts productos
(Productos (id 1)(nombre leche)(pasillo 3)(stock 45)(precio 1))
(Productos (id 2)(nombre galletas)(pasillo 4)(stock 10)(precio 2.20))
(Productos (id 3)(nombre cafe)(pasillo 5)(stock 2)(precio 2.6))
(Productos (id 4)(nombre arroz)(pasillo 12)(stock 30)(precio 1.98))
)

(assert (nuevo_cliente 33))
(assert (Pedidos (id_cliente 33)(id_producto 1)(unidades 3)))
(assert (Pedidos (id_cliente 33)(id_producto 2)(unidades 30)))
