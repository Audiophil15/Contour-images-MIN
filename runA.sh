#!/bin/bash
for fichier in 'Asterix3' 'lettre-L-cursive' 'Picasso-ColombesDeLaPaix'
do
for i in '0' '0.5' '1' '2' '4' '8' '16'
do
time ./Contour ../../PBM/$fichier.pbm ../../Contour/C-$fichier.contour ../../EPS/E-$fichier.eps F ../../Segments/S-$fichier-$i.eps F ../../Bezier/B-2-$fichier-$i.eps F ../../Bezier/B-3-$fichier-$i.eps F $i
done
done
