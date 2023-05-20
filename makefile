# Explication $(patsubst pattern,replacement,text) remplace pattern par replacement dans text
# $@ nom de la cible (potagibus.exe dans le premier cas)
# $^ liste des dépendances (obj/potagibus_fct.o obj/potagibus_main.o etc dans le premier cas)
# $< première dépendance (src/potagibus_fct.c dans le premier cas)

#Macros
FLAG = -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
EXEC = clang $(FLAG)
COMP = clang -c $(FLAG)

SRC = src
OBJ = obj
EXE = exe

COMPONENT = a_star_struct a_star chemin coord list_int list_t matrice pota_file selection simulation station stationtxt traitementP2 utilisateur voiture
COMPONENT_P1 = a_star_struct a_star chemin coord list_int list_t matrice pota_file selection station voiture

# Liste des fichiers objets COMPONENT
COMPONENT_OBJ = $(patsubst %, $(OBJ)/%.o, $(COMPONENT)) # Remplace chaque élément de COMPONENT par obj/element.o
COMPONENT_OBJ_P1 = $(patsubst %, $(OBJ)/%.o, $(COMPONENT_P1)) # Remplace chaque élément de COMPONENT par obj/element.o

#--------

#Executables

simulation.exe: $(COMPONENT_OBJ) $(OBJ)/simulation.o
	$(EXEC) $^ -o $(EXE)/$@

sim_debug.exe: $(COMPONENT_OBJ) $(OBJ)/sim_debug.o 
	$(EXEC) $^ -o $(EXE)/$@

pota_deb.exe: $(COMPONENT_OBJ) $(OBJ)/potagibus_debug.o
	$(EXEC) $^ -o $(EXE)/$@

pota_p1.exe: $(COMPONENT_OBJ_P1) $(OBJ)/potagibus_p1.o
	$(EXEC) $^ -o $(EXE)/$@

#Fichiers objets

$(OBJ)/%.o: $(SRC)/%.c
	$(COMP) $< -o $@

#--------

#Nettoyage

clean_obj:
	rm -f $(OBJ)/*.o

clean_exe:
	rm -f $(EXE)/*.exe

clean: clean_obj clean_exe

#--------

#Création des dossiers

make_obj:
	mkdir -p $(OBJ)

make_exe:
	mkdir -p $(EXE)

essential: make_obj make_exe
