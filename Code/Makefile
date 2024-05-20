# Makefile : Orchestre la compilation
# Auteurs : Daniel Roulin & Joshua Hurlimann
# Version 3

# Definitions de macros
EXEC = projet
TEST = test
PACKAGES = gtkmm-4.0
CXXFLAGS = -g -Wall -std=c++17 `pkg-config --cflags $(PACKAGES)`
CXX = g++
LDLIBS = `pkg-config --libs $(PACKAGES)`
CXXFILES = $(wildcard *.cc)
OFILES   = $(CXXFILES:.cc=.o)
PROJECT_OFILES = $(filter-out $(TEST).o, $(OFILES))
TEST_OFILES = $(filter-out $(EXEC).o, $(OFILES))

# Definition de la premiere regle
$(EXEC): $(PROJECT_OFILES)
	$(CXX) $(CXXFLAGS) $(PROJECT_OFILES) -o $(EXEC) $(LDLIBS)

# Definitions de cibles particulieres
depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ $(EXEC) $(TEST) $(OFILES)

test: $(TEST_OFILES)
	$(CXX) $(CXXFLAGS) $(TEST_OFILES) -o $(TEST) $(LDLIBS)

# Règles de dependances generees automatiquement
# DO NOT DELETE THIS LINE
graphic.o: graphic.cc graphic.h graphic_gui.h
gui.o: gui.cc gui.h simulation.h lifeform.h shape.h graphic.h \
 constantes.h graphic_gui.h
lifeform.o: lifeform.cc lifeform.h shape.h graphic.h constantes.h \
 message.h
message.o: message.cc message.h
projet.o: projet.cc simulation.h lifeform.h shape.h graphic.h \
 constantes.h gui.h
shape.o: shape.cc shape.h graphic.h
simulation.o: simulation.cc simulation.h lifeform.h shape.h graphic.h \
 constantes.h message.h
