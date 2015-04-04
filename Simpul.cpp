#include "Simpul.h"
#include <cmath>
#include <limits>
#include <string>
#include <algorithm>
#include <iostream>

namespace TSP_BnB{
	Simpul::Simpul():Parent(this){
		root=true;
		i=0;
		//sisanya default
	}
	Simpul::Simpul(FILE * f):Parent(this){
		root=true;
		int count = 0;
		i=0;
		path.push_back(i);

		float buffloat;
		vector<float> vec;
		while (fscanf(f,"%f",&buffloat)!=EOF){
			count++;
			vec.push_back(buffloat);
		}
		n = std::sqrt(count);
		R.resize(n);
		for (int i=0;i<n;i++)
			R[i].resize(n);
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				R[i][j]=vec[i*n+j];

		computeA();
		computeCost();
	}

	//membuat simpul anak
	Simpul::Simpul(const Simpul& R, int j):Parent(&R) {
		root=false;
		this->R=Parent->getA();
		n=Parent->getn();
		i = j;
		path=Parent->path;
		path.push_back(i);
		setRRowInf(Parent->geti());
		setRColInf(j);
		this->R[j][Parent->geti()]=std::numeric_limits<float>::infinity();		
		computeA();
		computeCost();
	}

	//dtor
	Simpul::~Simpul(){

	}

	//menghitung matriks bobot tereduksi
	void Simpul::computeA(){
		A=R;
		r=0;
		for (int i=0;i<n;i++)
		setARowReduced(i);
		for (int i=0;i<n;i++)
		setAColReduced(i);
	}
	void Simpul::computeCost(){
		if (isRoot())
			c = r;
		else /*parent!=this*/ {
			c=Parent->getc()+Parent->getA()[Parent->geti()][i]+r;
		}
 
	}

	Simpul Simpul::S(int j){
		return Simpul(*this,j);
	}

	//untuk perbandingan
	bool Simpul::operator==(const Simpul& rhs) const{
		return R == rhs.R;
	}

	//untuk priority queue
	bool Simpul::operator<(const Simpul& rhs) const{
		return getc()>rhs.getc();
	}

	int Simpul::geti() const{
		return i;
	}
	float Simpul::getr() const{
		return r;
	}
	float Simpul::getc() const{
		return c;
	}
	vector<vector<float> > Simpul::getR() const{
		return R;
	}
	vector<vector<float> > Simpul::getA() const{
		return A;
	}

	int Simpul::getn() const{
		return n;
	}
	list<int> Simpul::getPath() const{
		return path;
	}

	//predikat
	bool Simpul::isRoot() const{
		return root;
	}
	bool Simpul::isSolusi() const{
		for (int i=0;i<n;i++)
			if (std::find(path.begin(),path.end(),i)==path.end()) return false;
		for (int i=0;i<A.size();i++)
		for (int j=0;j<A[i].size();j++)
			if (A[i][j]<std::numeric_limits<float>::infinity()) return false;
		return true;
	}

	//method pembantu
	void Simpul::setRColInf(int col){
		for (int i=0;i<R.size();i++)
			R[i][col]=std::numeric_limits<float>::infinity();
	}
	void Simpul::setRRowInf(int row){
		for (int j=0;j<R[row].size();j++)
			R[row][j]=std::numeric_limits<float>::infinity();

	}
	void Simpul::setAColReduced(int col){
		//mencari minimum
		float min=std::numeric_limits<float>::infinity();
		for (int i=0;i<A.size();i++)
			if (A[i][col]<min)
				min=A[i][col];
		if (min!=0 && min<std::numeric_limits<float>::infinity()){
			r+=min;
			for (int i=0;i<A.size();i++)
				if (A[i][col]!=0)A[i][col]-=min;
		}
	}
	void Simpul::setARowReduced(int row){
		//mencari minimum
		float min=std::numeric_limits<float>::infinity();
		for (int i=0;i<A[row].size();i++)
			if (A[row][i]<min)
				min=A[row][i];
		if (min!=0 && min<std::numeric_limits<float>::infinity()){
			r+=min;
			for (int i=0;i<A.size();i++)
				if (A[row][i]!=0)A[row][i]-=min;
		}
	}

}
