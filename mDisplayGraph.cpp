#include "DisplayGraph.h"
#include <vector>
#include <list>
#include <limits>

using namespace std;

int main(){
	vector<vector<float> > G(3,(vector<float>(3)));
	int k=0;
	for (int i=0;i<3;i++)
	for (int j=0;j<3;j++)
		G[i][j]=i==j?numeric_limits<float>::infinity():++k;

	displayGraph(G);

	vector<int> circ;
	for (int i=0;i<3;i++)
		circ.push_back(i);
	circ.push_back(0);

	displayGraph(G,circ);
}
