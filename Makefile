#############################################################################
# Fichier Makefile
# UE MAP401 - DLST - UGA - 2017/2018
#############################################################################
# utilisation des variables internes $< $@ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = gcc

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = Contour bezier2test


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique :
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image_pbm.o : image_pbm.c image_pbm.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

bezier2test.o : bezier2test.c shapeTools.h shapeSimplification.h geometrie2D.h TTVpoint.h TTVcontour.h
	$(CC) -c $(COMPILOPTS) $<

Contour.o : Contour.c shapeTools.h image_pbm.h geometrie2D.h TTVpoint.h TTVcontour.h shapeSimplification.h
	$(CC) -c $(COMPILOPTS) $<

TTVpoint.o : geometrie2D.h

shapeSimplification.o : geometrie2D.h TTVcontour.h TTVpoint.h

########################################################
# regles explicites de creation des executables

Contour : Contour.o image_pbm.o shapeTools.o geometrie2D.o TTVpoint.o TTVcontour.o shapeSimplification.o
	$(CC) $^ $(LDOPTS) -o $@

bezier2test : bezier2test.o geometrie2D.o TTVpoint.o TTVcontour.o shapeSimplification.o
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o

bclean :
	rm -f ../../Bezier/*.eps
