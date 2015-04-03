#include "Simpul.h"
#include <iostream>
#include <cstdio>
#include <queue>
#include <string>
#include <limits>
#include <unistd.h>
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
	Simpul Sim(stdin);
	Simpul Solusi;
	float mincost ;

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
			for (int i=0;i<CS.getn();i++)
				pq.push(Simpul(CS,i));
		}
	}

	std::cout<<"Solusi: ";
	printList(Solusi.getPath(),std::cout);
	std::cout<<std::endl;
	std::cout<<"cost: " << Solusi.getc() << std::endl;
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
			for (int i=0;i<CS.getn();i++)
				pq.push(Simpul(CS,i));
		}
	}

	std::cout<<"Solusi: ";
	printList(Solusi.getPath(),std::cout);
	std::cout<<std::endl;
	std::cout<<"cost: " << Solusi.getc() << std::endl;



	return 0;
	
}
