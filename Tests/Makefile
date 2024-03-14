FILE     = test.cc
EXEC     = $(basename $(FILE))
CXXFILES = test.cc ../Code/project.cc ../Code/simulation.cc ../Code/lifeform.cc ../Code/message.cc ../Code/shape.cc
CXX      = g++
CXXFLAGS = -g -Wall -std=c++11

$(EXEC): $(FILE)
	$(CXX) $(FILE) -o $(EXEC)

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ $(EXEC)

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

# DO NOT DELETE THIS LINE
test.o: test.cc ../Code/shape.cc ../Code/shape.h
project.o: ../Code/project.cc ../Code/project.h ../Code/simulation.h
simulation.o: ../Code/simulation.cc ../Code/simulation.h \
 ../Code/message.h ../Code/lifeform.h ../Code/shape.h
lifeform.o: ../Code/lifeform.cc ../Code/lifeform.h ../Code/shape.h
message.o: ../Code/message.cc ../Code/message.h
shape.o: ../Code/shape.cc ../Code/shape.h
