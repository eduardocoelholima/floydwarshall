#ifndef _MATRIX_CPP_
#define _MATRIX_CPP_
#include <iostream>
#define INF 999999
#define NIL -999999
using namespace std;


class Matrix {
public:
	int n;
	int *data;
		
	size_t index(int x, int y, int z) const {
		return (z + n*y + n*n*x);
	}
	
	Matrix(int _n) {
		n = _n;
		data = new int[(n+1)*n*n];
		zero();
	}
	
	~Matrix() {
		delete [] data;
	}
	
	int read(int x, int y, int z) {
		return data[index(x,y,z)];
	}

	void write(int x, int y, int z, int value) {
		data[index(x,y,z)] = value;
	}

	void zero() {
		for (int k=0;k<=n;k++) {
			for (int i=0;i<n;i++) {
				for (int j=0;j<n;j++) {
					data[index(k,i,j)] = 0;
				}
			}
		}
	}

	void print(string preffix, int offset) {
		string nil = "NIL", inf = "INF";
		for (int k=0;k<=n;k++) {
			cout<<preffix<<k<<""<<endl;
			for (int i=0;i<n;i++) {
				for (int j=0;j<n;j++) {
					int value = read(k,i,j);
					if (value==NIL) cout<<nil<<" ";
					else if (value==INF) cout<<inf<<" ";
					else cout<<value+offset<<" ";
				}
				cout<<endl;
			}
		}
		cout<<endl;
	}
		
};


#endif // !_MATRIX_CPP_