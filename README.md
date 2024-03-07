# foodWeb
C++: Takes in text list of species, list of connections. Returns trophic levels of each species. Final project for CS-211 Data Struct. & Algorithms
This application uses a breadth-first search algorithm and uses an adjacency list to represent a directed graph of species from lower to higher trophic levels

Instructions for use:
1) create a list of organisms without repeats "organisms.txt" in same folder
2) create a list of connections representing relationship between organisms ("connections.txt")
Ex: if bacteria are eaten by insects and insects are eaten by amphibians, the list looks like:
bacteria insects\n
insects amphibians
3) compile foodWeb.cpp - ensure executable has organisms.txt and connections.txt in same folder for execution
4) run the executable. the output will be displayed in the commandline. 
the output consists of a list of organisms and list of organisms and their calculated trophic levels
