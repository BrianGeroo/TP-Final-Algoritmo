# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = sistema_dron

# Todos los archivos .cpp del proyecto
SRCS = main.cpp memoria.cpp operaciones.cpp archivos.cpp visualizaciones.cpp html.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla principal
all: $(TARGET)

# Comando para linkear los archivos objeto y crear el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Comando para compilar cada .cpp en un .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar archivos viejos
clean:
	rm -f $(OBJS) $(TARGET)
