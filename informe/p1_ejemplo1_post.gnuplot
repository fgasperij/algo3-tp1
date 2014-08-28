set terminal jpeg size 800,600
set output "p1_ej1_post.jpg"

set xrange [-1:4]
set yrange [-1:4]

set arrow from 0,0 to 0,1 nohead lc rgb 'black'
set arrow from 0,1 to 0.5,1 nohead lc rgb 'black'
set arrow from 2.5,1 to 3,1 nohead lc rgb 'black'
set arrow from 3,1 to 3,0 nohead lc rgb 'black'

set arrow from 0.5,1 to 0.5,2 nohead lc rgb 'green'
set arrow from 0.5,2 to 1,2 nohead lc rgb 'green'
set arrow from 2,2 to 2.5,2 nohead lc rgb 'green'
set arrow from 2.5,2 to 2.5,1 nohead lc rgb 'green'

set arrow from 1,2 to 1,3 nohead lc rgb 'blue'
set arrow from 1,3 to 2,3 nohead lc rgb 'blue'
set arrow from 2,3 to 2,2 nohead lc rgb 'blue'

plot 0 notitle
