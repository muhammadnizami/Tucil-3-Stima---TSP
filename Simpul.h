#include <vector>
#include <list>
using std::vector;
using std::list;

#include <cstdio>

namespace TSP_BnB{

	class Simpul {
		public:
		//ctor
		Simpul();
		//membuat dari input matriks dengan delimiter spasi hingga eof
		Simpul(FILE * f);

		//membuat simpul anak
		Simpul(const Simpul& R, int j);

		//dtor
		~Simpul();

		//menghitung matriks bobot tereduksi
		void computeA();
		void computeCost();

		Simpul S(int j);

		//untuk perbandingan
		bool operator==(const Simpul& rhs) const;

		//untuk priority queue
		bool operator<(const Simpul& rhs) const;
		
		//getter
		int geti() const;
		float getr() const;
		float getc() const;
		int getn() const;
		list<int> getPath() const;
		vector<vector<float> > getR() const;
		vector<vector<float> > getA() const;

		//predikat
		bool isRoot() const;
		bool isSolusi() const;

		private:
		const Simpul* Parent;
		vector<vector<float> > R;
		vector<vector<float> > A;
		int n;	//banyaknya baris, serta banyaknya kolom
			//banyaknya simpul pada graf

		float r;
		int i;
		float c;

		list<int> path;

		//method pembantu
		void setRColInf(int col);
		void setRRowInf(int row);
		void setAColReduced(int col);
		void setARowReduced(int row);
	};
}
