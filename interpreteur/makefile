# Nom du programme final
TARGET = bin/prog.exe

# Compilateur
CC = g++

# Options de compilation
CFLAGS = -Wall -Wextra -pedantic -std=c++11

# Répertoire des sources
SRCDIR = src

# Fichiers sources
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Répertoire des objets
OBJDIR = obj

# Fichiers objets
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Règle de compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction du programme final
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Règle par défaut
all: $(TARGET)

# Règle de nettoyage
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
