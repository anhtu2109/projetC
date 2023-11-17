#ourir image PNG
set term png
set output "evolut.png"

#designer
plot "Evol_Pop.txt" using 1:2 with lines title "proies", "Evol_Pop.txt" using 1:3 with lines title "predateurs"
