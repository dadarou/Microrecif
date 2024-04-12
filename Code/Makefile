# Definitions de macros

EXEC     = projet
PACKAGES = gtkmm-4.0
CXXFLAGS = -g -Wall -std=c++17 `pkg-config --cflags $(PACKAGES)`
CXX      = g++
LDLIBS   = `pkg-config --libs $(PACKAGES)`
CXXFILES = $(wildcard *.cc)
OFILES   = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

$(EXEC): $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o $(EXEC) $(LDLIBS)

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ $(EXEC) $(OFILES)

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
graphic.o: graphic.cc graphic.h
gui.o: gui.cc gui.h simulation.h lifeform.h shape.h constantes.h \
 graphic.h
lifeform.o: lifeform.cc lifeform.h shape.h constantes.h message.h
message.o: message.cc message.h
projet.o: projet.cc simulation.h lifeform.h shape.h constantes.h gui.h
shape.o: shape.cc shape.h graphic.h
simulation.o: simulation.cc simulation.h lifeform.h shape.h constantes.h \
 message.h
