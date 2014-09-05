set terminal jpeg size 800,600
set output "comparacion_poda_camion_con_ambas_podas.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 1
set xlabel "Cantidad de productos"
set ylabel "Tiempo en microsegundos"
set title 'Tiempos de ejecución de ambas podas en comparación con sólo la poda de agregar camión'

plot 'tiempos_con_poda_agregar_camion.txt' with lines linewidth 2 title "Sólo poda de agregar camión", \
'tiempos_con_ambas_podas.txt' with lines linewidth 2 title "Ambas podas"

set terminal jpeg size 800,600
set output "comparacion_poda_resto_con_ambas_podas.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 1
set xlabel "Cantidad de productos"
set ylabel "Tiempo en microsegundos"
set title 'Tiempos de ejecución de ambas podas en comparación con sólo la poda de resto de productos'

plot 'tiempos_con_poda_resto_productos.txt' with lines linewidth 2 title "Sólo poda de resto de productos", \
'tiempos_con_ambas_podas.txt' with lines linewidth 2 title "Ambas podas"


set terminal jpeg size 800,600
set output "comparacion_tiempos_podas.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 1
set xlabel "Cantidad de productos"
set ylabel "Tiempo en microsegundos"
set title 'Comparación de tiempos de ejecución'

plot 'tiempos_sin_podas.txt' with lines linewidth 2 title "Sin podas" , \
'tiempos_con_poda_resto_productos.txt' with lines linewidth 2 title "Con poda del resto de los productos", \
'tiempos_con_poda_agregar_camion.txt' with lines linewidth 2 title "Con poda de agregar camión"


set terminal jpeg size 800,600
set output "complejidad.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 1
set ytics 1
set xlabel "Cantidad de productos"
set ylabel ""
set title 'Comprobación de complejidad teórica para algoritmo sin podas'
# log (n * n!) = log(n) + log(n!) = por aprox. Stirling = log(n) + n*log(n) - n
plot 'tiempos_sin_podas.txt' using 1:(log($2) / ((1 + $1)*log($1) - $1)) with lines linewidth 2 title "log(tiempo) / ((x + 1)log(x) - x)"


set terminal jpeg size 800,600
set output "complejidad_con_poda_camion.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 1
set ytics 1
set xlabel "Cantidad de productos"
set ylabel ""
set title 'Comprobación de complejidad teórica para algoritmo con la poda de agregar camión'

plot 'tiempos_con_poda_agregar_camion.txt' using 1:(log($2) / ((1 + $1)*log($1) - $1)) with lines linewidth 2 title "log(tiempo) / ((x + 1)log(x) - x)"



set terminal jpeg size 800,600
set output "complejidad_con_ambas_podas.jpg"
#set xrange [0:200]
set yrange [0:]
set xtics 1
set ytics 1
set xlabel "Cantidad de productos"
set ylabel ""
set title 'Comprobación de complejidad teórica para algoritmo con ambas podas'

plot 'tiempos_con_ambas_podas.txt' using 1:(log($2) / ((1 + $1)*log($1) - $1)) with lines linewidth 2 title "log(tiempo) / ((x + 1)log(x) - x)"
