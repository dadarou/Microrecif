# Definitions de macros

EXEC     = project
CXXFILES = project.cc simulation.cc lifeform.cc message.cc shape.cc
CXX      = g++
CXXFLAGS = -g -Wall -std=c++11
OFILES   = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

$(EXEC): $(OFILES)
	$(CXX) $(OFILES) -o $(EXEC)

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
	@/bin/rm -f *.o *.x *.cc~ *.h~ $(EXEC)

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
project.o: project.cc simulation.h
simulation.o: simulation.cc simulation.h message.h lifeform.h shape.h
lifeform.o: lifeform.cc lifeform.h shape.h
message.o: message.cc message.h
shape.o: shape.cc shape.h
