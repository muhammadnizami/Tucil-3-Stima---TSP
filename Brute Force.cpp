#include <queue>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <limits>
using namespace std;

class Problem{
	public:
	friend std::ostream& operator<<(std::ostream& o, const Problem& rhs);

	Problem(FILE * f);

	vector<vector<float> > getTab(){return Tab;};
	int getn(){return n;};

	float cost(vector<int> sirkuit);

	private:
	vector<vector<float> > Tab;
	int n;
};

std::ostream& operator<<(std::ostream& o, const Problem& rhs);

vector<int> firstCircuit(int n);
bool nextCircuit(vector<int>& circ);

int main(){
	Problem P(stdin);
	cout<<P;
	vector<int> mincirc;
	float mincost = std::numeric_limits<float>::infinity();
	bool cont = true;
	for (vector<int> circ = firstCircuit(P.getn()); cont; cont=nextCircuit(circ)){
		if (P.cost(circ)<mincost){
			mincost=P.cost(circ);
			mincirc=circ;
		}
	}

	cout<<"path:";
	for (int i=0;i<mincirc.size();i++)
		cout<<"\t"<<mincirc[i];
	cout<<endl<<"cost: "<<P.cost(mincirc)<<endl;
	return 0;
}

vector<int> firstCircuit(int n){
	vector<int> retval;
	for (int i=0;i<n;i++)
		retval.push_back(i);
	retval.push_back(0);
	return retval;
		
}
bool nextCircuit(vector<int>& circ){
	if(circ.size()>1)
		return std::next_permutation(circ.begin()+1,circ.end()-1);
	else return false;
}

Problem::Problem(FILE * f){
	int count = 0;
	float buffloat;
	vector<float> vec;
	while (fscanf(f,"%f",&buffloat)!=EOF){
		count++;
		vec.push_back(buffloat);
	}
	n = std::sqrt(count);
	Tab.resize(n);
	for (int i=0;i<n;i++)
		Tab[i].resize(n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			Tab[i][j]=vec[i*n+j];

}

float Problem::cost(vector<int> sirkuit){
	float sum = 0;
	for (int i=1;i<sirkuit.size();i++){
		sum+=Tab[sirkuit[i-1]][sirkuit[i]];
	}
	return sum;
}

std::ostream& operator<<(std::ostream& o, const Problem& rhs){
	for (int i=0;i<rhs.n;i++){
		for (int j=0;j<rhs.n;j++)
			o<<rhs.Tab[i][j]<<"\t";
		o<<endl;
	}
}
