set terminal jpeg size 800,600
set output "p1_ej1_pre.jpg"

set xrange [0:5]
set yrange [0:4]

set arrow from 1,0 to 1,1 nohead lc rgb 'black'
set arrow from 1,1 to 4,1 nohead lc rgb 'black'
set arrow from 4,1 to 4,0 nohead lc rgb 'black'

set arrow from 1.5,0 to 1.5,2 nohead lc rgb 'green'
set arrow from 1.5,2 to 3.5,2 nohead lc rgb 'green'
set arrow from 3.5,2 to 3.5,0 nohead lc rgb 'green'

set arrow from 2,0 to 2,3 nohead lc rgb 'blue'
set arrow from 2,3 to 3,3 nohead lc rgb 'blue'
set arrow from 3,3 to 3,0 nohead lc rgb 'blue'

plot -1 notitle
