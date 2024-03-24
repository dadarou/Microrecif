# Definitions de macros

EXEC     = test
# CXXFILES = test.cc ../Code/project.cc ../Code/simulation.cc ../Code/lifeform.cc ../Code/message.cc ../Code/shape.cc
CXXFILES = test.cc ../Code/shape.cc
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

# Regles de dependances generees automatiquement
# DO NOT DELETE THIS LINE
test.o: test.cc ../Code/shape.cc ../Code/shape.h
shape.o: ../Code/shape.cc ../Code/shape.h
