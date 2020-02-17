  
file1= gomez_p1
target= gomez_p1
OBJECTS= $(file1).o 
CFLAGS= -std=c++14 -g

all: $(OBJECTS)
	g++ $(CFLAGS) $(OBJECTS) -o $(target)


$(file1).o: $(file1).h $(file1).cpp
	g++ -c $(CFLAGS) $(file1).cpp

clean:
	rm -rf *.o
	rm $(target)
run: all
	./$(target)
memcheck: all
	valgrind ./$(target) -v --leak-check=full

winclean:
	del *.o
	del $(target).exe