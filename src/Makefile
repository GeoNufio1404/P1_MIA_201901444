# Definir los archivos objeto y los archivos de inclusión
OBJECTS := main.o
INCLUDES := ../include/*.cpp

# Regla para compilar el ejecutable
ejecutable : $(OBJECTS)
	g++ -o $@ $^ -I $(INCLUDES)
	rm -f *.o

# Regla para compilar los archivos objeto
%.o: %.cpp
	g++ -o $@ -c $< -I $(INCLUDES)
