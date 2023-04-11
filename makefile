#Macros
exec = clang -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
comp = clang -c -Wall -Wextra -pedantic -O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

#--------
#Executables

potagibus.exe: obj/potagibus_fct.o obj/potagibus_main.o
	$(exec) obj/potagibus_fct.o obj/potagibus_main.o -o exe/potagibus.exe

potagibus_main_debug_a_star.exe: obj/potagibus_fct.o obj/potagibus_main_debug_a_star.o obj/potagibus_a_star.o
	$(exec) obj/potagibus_fct.o obj/potagibus_main_debug_a_star.o obj/potagibus_a_star.o -o exe/potagibus_main_debug_a_star.exe

#Fichiers objets


obj/potagibus_fct.o: src/potagibus_fct.h src/potagibus_fct.c
	$(comp) src/potagibus_fct.c -o obj/potagibus_fct.o
	
obj/potagibus_main.o: src/potagibus_fct.h src/potagibus_main.c
	$(comp) src/potagibus_main.c -o obj/potagibus_main.o

obj/potagibus_main_debug_a_star.o: src/potagibus_fct.h src/potagibus_a_star.h src/potagibus_main_debug_a_star.c
	$(comp) src/potagibus_main_debug_a_star.c -o obj/potagibus_main_debug_a_star.o

obj/potagibus_a_star.o: src/potagibus_fct.h src/potagibus_a_star.h src/potagibus_a_star.c
	$(comp) src/potagibus_a_star.c -o obj/potagibus_a_star.o

#clean
clean:
	@rm -f obj/*.o exe/*
