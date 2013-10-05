RM=rm -f
CPPFLAGS=-O3 -g -ggdb -W -Wall -Wextra -pedantic -std=c++11 -stdlib=libc++ -I.
LDFLAGS=-O3 -g -ggdb -stdlib=libc++
LDLIBS=

SRCS=apsp.cpp directed_graph.cpp priority_queue.cpp shortest_path_algorithm.cpp dijkstra_algorithm.cpp bellman_ford_algorithm.cpp johnson_algorithm.o
OBJS=$(subst .cpp,.o,$(SRCS))

all: apsp

apsp: apsp.o directed_graph.o priority_queue.o shortest_path_algorithm.o dijkstra_algorithm.o bellman_ford_algorithm.o johnson_algorithm.o
	clang++ $(LDFLAGS) -o apsp priority_queue.o apsp.o directed_graph.o shortest_path_algorithm.o bellman_ford_algorithm.o dijkstra_algorithm.o johnson_algorithm.o $(LDLIBS)

digraph: apsp.cpp  directed_graph.cpp priority_queue.cpp shortest_path_algorithm.cpp dijkstra_algorithm.cpp bellman_ford_algorithm.cpp johnson_algorithm.cpp
	clang++ $(CPPFLAGS) -c directed_graph.cpp priority_queue.cpp shortest_path_algorithm.cpp dijkstra_algorithm.cpp bellman_ford_algorithm.cpp johnson_algorithm.cpp apsp.cpp 

clean:
	$(RM) $(OBJS)
