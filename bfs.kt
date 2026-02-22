fun BFS(g: Grafo, inicio: Int, ultimo: Int): List<Int> { // presenta el recorrido BFS del grafo g desde el nodo inicio
    val visitado = mutableListOf<Int>()
    val cola = ArrayDeque<Int>()
    cola.add(inicio)
    visitado.add(inicio)
    while (cola.isNotEmpty()) {
        val nodo = cola.removeFirst()
        getVecinos(g,nodo)?.forEach { vecino ->
            if (vecino !in visitado) {
                visitado.add(vecino)
                cola.add(vecino)
                if(ultimo == vecino){
                    //Encontramos el camino que llega hasta nuestro candidato
                    return visitado
                }
            }
        }
    }
    return visitado
}