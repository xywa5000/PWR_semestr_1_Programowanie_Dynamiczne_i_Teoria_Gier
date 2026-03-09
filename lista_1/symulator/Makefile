# Flagi i nazwa
CXXFLAGS = -O3 -Wall -std=c++17
HEADERS = $(wildcard *.hpp)

mdp_sim: main.cpp $(HEADERS)
	g++ $(CXXFLAGS) main.cpp -o mdp_sim

clean:
	rm -f mdp_sim

.PHONY: clean