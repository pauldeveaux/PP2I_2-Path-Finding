CC=clang
CFLAGS=-std=c99 -Wall -Wextra -pedantic -fdiagnostics-color=always
CFLAGS+=-O0 -g3 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
CFLAGS+= `pkg-config --cflags gtk+-3.0`
LDFLAGS+= -fsanitize=address
LDFLAGS+= `pkg-config --libs gtk+-3.0`


ALL_EXECUTABLES=parser_csv_test calculate_distance_test dijkstra_test astar_test queue_test time_distance_calcul_test degree_of_station_test astar_perf search_button_test france_map_test program
ALL_O= parser_csv.o station.o car.o dijkstra.o astar.o station_node_priority_queue.o search_button.o france_map.o option_display.o options_user.o graphics.o simulation.o

all: $(ALL_EXECUTABLES)

create_o: $(ALL_O)

# ---- Lancement du programm ----
program: src/graphics/graphics.o src/station.o src/utils/parser_csv.o src/astar.o src/station_node_priority_queue.o
	$(MAKE) station.o parser_csv.o astar.o station_node_priority_queue.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
# -----------


# --- .o ---
parser_csv.o: src/utils/parser_csv.c src/utils/parser_csv.h
	${CC} $(CFLAGS) -c $< -o src/utils/$@

station.o : src/station.c src/station.h
	$(CC) $(CFLAGS) -c $< -o src/$@

car.o : src/car.c src/car.h
	$(CC) $(CFLAGS) -c $< -o src/$@

dijkstra.o: src/dijkstra.c src/station.o
	$(CC) $(CFLAGS) -c $< -o src/$@

search_button.o : src/graphics/search_button.c src/station.o
	$(CC) $(CFLAGS) -c $< -o src/graphics/$@

france_map.o : src/graphics/france_map.c src/station.o
	$(CC) $(CFLAGS) -c $< -o src/graphics/$@

option_display.o : src/graphics/option_display.c src/station.o
	$(CC) $(CFLAGS) -c $< -o src/graphics/$@

options_user.o : src/graphics/options_user.c src/station.o
	$(CC) $(CFLAGS) -c $< -o src/graphics/$@

graphics.o : src/graphics/graphics.c src/station.o src/utils/parser_csv.o 
	$(CC) $(CFLAGS) -c $< -o src/graphics/$@

astar.o : src/astar.c src/station_node_priority_queue.o
	$(CC) $(CFLAGS) -c $< -o src/$@

station_node_priority_queue.o : src/station_node_priority_queue.c src/station.o
	$(CC) $(CFLAGS) -c $< -o src/$@

simulation.o : src/simulation.c
	$(CC) $(CFLAGS) -c $< -o src/$@
#   -----------------

# --- Tests ---
parser_csv_test: $(parser_csv.o) src/test/csv_loading_test.c src/utils/parser_csv.o
	$(MAKE) parser_csv.o
	${CC} $(CFLAGS) -o $@ $<

calculate_distance_test:  src/test/calculate_distance.c src/station.o
	$(MAKE) station.o
	${CC} $(CFLAGS) -o $@ $<

dijkstra_test: src/test/dijkstra_test.c src/dijkstra.o src/station.o src/utils/parser_csv.o
	$(MAKE) station.o parser_csv.o dijkstra.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

astar_test: src/test/astar_test.c src/astar.o src/station.o src/utils/parser_csv.o src/station_node_priority_queue.o
	$(MAKE) station.o parser_csv.o astar.o station_node_priority_queue.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

queue_test: src/test/queue_test.c src/station_node_priority_queue.o src/station.o 
	$(MAKE) station_node_priority_queue.o station.o 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

#  --- Performances tests ---

time_distance_calcul_test: src/test/performances/time_distance_calcul.c src/station.o src/utils/parser_csv.o
	$(MAKE) station.o parser_csv.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

degree_of_station_test: src/test/performances/degree_of_station.c src/station.o src/utils/parser_csv.o
	$(MAKE) station.o parser_csv.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

astar_perf : src/test/performances/astar_perf.c src/astar.o src/station.o src/utils/parser_csv.o src/station_node_priority_queue.o
	$(MAKE) station.o parser_csv.o astar.o station_node_priority_queue.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

#  -----------------

#  --- Graphics Tests ---
search_button_test: src/test/search_button_test.c src/graphics/search_button.o src/station.o src/utils/parser_csv.o
	$(MAKE) search_button.o parser_csv.o station.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

france_map_test: src/test/france_map_test.c src/graphics/france_map.o src/station.o src/utils/parser_csv.o
	$(MAKE) france_map.o parser_csv.o station.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

option_display_test: src/test/option_display_test.c src/graphics/option_display.o src/station.o src/utils/parser_csv.o
	$(MAKE) option_display.o parser_csv.o station.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

options_user_test: src/test/options_user_test.c src/graphics/options_user.o src/station.o src/utils/parser_csv.o
	$(MAKE) options_user.o parser_csv.o station.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

graphics_test: src/graphics/graphics.o src/station.o src/utils/parser_csv.o src/astar.o src/station_node_priority_queue.o
	$(MAKE) station.o parser_csv.o astar.o station_node_priority_queue.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

#   -------

simulation_test: src/test/simulation_test.c src/simulation.o src/astar.o src/station.o src/utils/parser_csv.o src/station_node_priority_queue.o
	$(MAKE) station.o parser_csv.o astar.o simulation.o station_node_priority_queue.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@


clean:
	find . -name '*.o' -type f -delete
	@echo "Tout les fichiers .o ont été supprimés"
	rm -f $(ALL_EXECUTABLES)
	@echo "Tout les fichiers exécutables ont été supprimés"

.SILENT: clean test


