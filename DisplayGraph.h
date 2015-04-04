//file:DisplayGraph.h
#include<vector>


//tampilan graf dilakukan dengan bantuan shell, gnome-open, dan graphviz dot.

void displayGraph(std::vector<std::vector<float> > Graph);

void displayGraph(std::vector<std::vector<float> > Graph, std::vector<int> circuit);
