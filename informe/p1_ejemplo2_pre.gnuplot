set terminal jpeg size 800,600
set output "p1_ej2_pre.jpg"

set xrange [-1:3]
set yrange [-1:4]

set arrow from 0,0 to 0,3 nohead lc rgb 'blue'
set arrow from 0,3 to 1,3 nohead lc rgb 'blue'
set arrow from 1,3 to 1,0 nohead lc rgb 'blue'

set arrow from 1,0 to 1,2 nohead lc rgb 'black'
set arrow from 1,2 to 2,2 nohead lc rgb 'black'
set arrow from 2,2 to 2,0 nohead lc rgb 'black'

plot 0 notitle
