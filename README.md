# multiphaseLB
Resoluci\'on de flujo multif\'asico usando el m\'etodo de lattice-Boltzmann


# Por hacer

1. Revisar la b\'usqueda de fileSearch, para poder emplear correctamente el valor de retorno (status) de estas funciones

2. Intercambiar s\'olo velocidades necesarias en syncPdfField, no toda la distribuci\'on

3. Incorporar los nodos ghosts sobre la frontera. De esta manera, no ser\'ia necesaria una sincronizaci\'on despu\'es de la actualizaci\'on de las condiciones de borde

4. non-blocking sinc