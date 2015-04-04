//file:MainBnB.cpp
#include "Simpul.h"
#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <limits>
#include <unistd.h>
#include <ctime>
#include "DisplayGraph.h"
using namespace TSP_BnB;
using std::vector;

template<class T>
void printMatrix(vector<vector<T> > M, std::ostream& o){
	for (int i=0; i<M.size();i++){
		for (int j=0; j<M[i].size();j++){
			o<<M[i][j]<<"\t";
		}
		o<<std::endl;
	}
}

void printList(std::list<int> path, std::ostream& o){
	for (std::list<int>::iterator it = path.begin();it!=path.end();it++){
		o << (*it)<<  "\t";
	}
}

int main(){
	int numSimp = 0;

	Simpul Sim(stdin);
	numSimp++;
	Simpul Solusi;
	float mincost ;	
	clock_t startTime,finTime;
	startTime=clock(); //mulai

	std::priority_queue<Simpul> pq;
	pq.push(Sim);
	//hingga ditemukan solusi sementara
	while (!pq.empty()){
		Simpul CS = pq.top();
		pq.pop();
		if (CS.isSolusi()){
			Solusi = CS;
			mincost = CS.getc();
			break;
		} else {
			if(CS.getc()<std::numeric_limits<float>::infinity())
			for (int i=0;i<CS.getn();i++){
				numSimp++;
				pq.push(Simpul(CS,i));
			}
		}
	}

	//setelah ditemukan solusi sementara
	//ada bounding
	//dihabiskan
	while (!pq.empty()){
		Simpul CS = pq.top();
		pq.pop();
		if (CS.isSolusi()){
			if (CS.getc() < mincost){
				Solusi = CS;
				mincost = CS.getc();
			}
		} else if /*bound*/ (CS.getc()<=mincost) {
			if(CS.getc()<std::numeric_limits<float>::infinity())
			for (int i=0;i<CS.getn();i++){
				numSimp++;
				pq.push(Simpul(CS,i));
			}
		}
	}
	
	finTime=clock();//selesai

	std::cout<<"Solusi: ";
	printList(Solusi.getPath(),std::cout);
	std::cout<<std::endl;
	std::cout<<"cost: " << Solusi.getc() << std::endl;
	printf("\nBnB finished. time = %f \n", ((double) (finTime-startTime))/CLOCKS_PER_SEC);
	std::cout<<"Banyaknya simpul: " << numSimp <<std::endl;

	std::list<int> li = Solusi.getPath();
	std::vector<int> vi;        
	copy(li.begin(),li.end(),back_inserter(vi));
	displayGraph(Sim.getR(),vi);
	return 0;
	
}
