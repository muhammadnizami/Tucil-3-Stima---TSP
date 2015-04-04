#include <sstream>
#include <limits>
#include <string>
#include <cstdlib>
#include <utility>
#include <set>
#include "DisplayGraph.h"
#include <iostream>

using namespace std;

void displayGraph(vector<vector<float> > Graph){
	displayGraph(Graph,vector<int>());
}

void displayGraph(std::vector<std::vector<float> > Graph, vector<int> circuit){

	set<pair<int,int> > circuitedges;
	for (int i=1;i<circuit.size();i++)
		circuitedges.insert(pair<int,int>(circuit[i-1],circuit[i]));
	
	ostringstream dot_cmd_ss;
	dot_cmd_ss<<"digraph G {"<<endl;
	for (int i=0;i<Graph.size();i++)
		dot_cmd_ss<<i<<";"<<endl;
	for (int i=0;i<Graph.size();i++)
	for (int j=0;j<Graph[i].size();j++)
		if (Graph[i][j]<std::numeric_limits<float>::infinity()){
			dot_cmd_ss<<i<<"->"<<j<<" [label=\\\""<<Graph[i][j]<<(circuitedges.find(pair<int,int>(i,j))!=circuitedges.end()?"\\\" fontcolor=\\\"red\\\"] [color=\\\"red\\\"];":"\\\"];")<<endl;
		}

	dot_cmd_ss<<"}"<<endl;

	string dot_cmd(dot_cmd_ss.str());

	string makeimage = string("echo ") + "\"" + dot_cmd + "\""
				+ "| dot -Tpng > graph.png";
	
	if(system(makeimage.c_str())!=0)cerr<<"cannot make image: maybe graphviz is not installed."<<endl;

	if(system("gnome-open graph.png")!=0)cerr<<"cannot open image: maybe gnome-open is not installed."<<endl;
}
