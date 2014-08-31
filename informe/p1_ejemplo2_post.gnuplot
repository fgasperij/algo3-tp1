set terminal jpeg size 800,600
set output "p1_ej2_post.jpg"

set xrange [0:4]
set yrange [0:4]

set arrow from 1,0 to 1,3 nohead lc rgb 'blue'
set arrow from 1,3 to 2,3 nohead lc rgb 'blue'
set arrow from 2,3 to 2,2 nohead lc rgb 'blue'


set arrow from 2,2 to 3,2 nohead lc rgb 'black'
set arrow from 3,2 to 3,0 nohead lc rgb 'black'

plot -1 notitle
