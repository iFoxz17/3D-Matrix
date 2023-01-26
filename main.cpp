#include "matrix_3d.h"
#include <vector>

#define NPRINT
#define NEXCEPTION

using namespace std;


void test_matrix_2d_creation() {

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_2D_CREATION BEGIN" << endl;
	cout << "-----------------------------------" << endl;

	matrix_2d<char> gg;

	assert(gg.rows() == 0);
	assert(gg.columns() == 0);
	assert(gg.size() == 0);

	matrix_2d<double> matrix1;
	const matrix_2d<float> matrix2(3, 5);
	matrix_2d<string>* matrix3 = new matrix_2d<string>(4, 4);

	matrix_2d<double> matrix4(4, 4);

	for(typename matrix_2d<string>::size_type i = 0; i < matrix3->rows(); ++i)
		for(typename matrix_2d<string>::size_type j = 0; j < matrix3->columns(); ++j) {
			(*matrix3)(i, j) = "_____";
			matrix4(i, j) = i + j + 0.1;
		}

	matrix_2d<int> conv(matrix4);

	#ifndef NPRINT
	cout << endl << matrix4 << endl << conv << endl;	
	#endif

	matrix_2d<string> clone = *matrix3;
	assert(clone == *matrix3);

	(*matrix3)(0, 1) = "Fuma_";
	(*matrix3)(1, 1) = "Maro_";
	(*matrix3)(1, 3) = "Vime_";
	(*matrix3)(1, 2) = "Kenz_";
	(*matrix3)(1, 3) = "Margh";
	(*matrix3)(3, 2) = "Marti";

	assert(!(clone == *matrix3));

	#ifndef NPRINT
	cout << *matrix3 << endl;
	#endif

	assert(matrix1.rows() == 0);
	assert(matrix2.rows() == 3);
	assert(matrix2.columns() == 5);
	assert(matrix3->size() == 16);

	assert(!(matrix1 == matrix4));
	matrix1 = matrix4;
	assert(matrix1 == matrix4);

	delete matrix3;

	
	#ifndef NEXCEPTION
	try {
		matrix_2d<vector<long double>> err(100000000, 100000000);
	}
	catch(bad_alloc &exc) {
		cout << "bad_alloc caught on matrix_2d<T>(int, int)" << endl;
	}

	try {
		matrix_2d<short> err(1000000000, 100000000);
		matrix_2d<long double> cl(err);
	}
	catch(bad_alloc &exc) {
		cout << "bad_alloc caught on matrix_2d<T>(matrix_2d<U>&)" << endl;
	}
	#endif
	

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_2D_CREATION END" << endl;
	cout << "-----------------------------------" << endl << endl;
}

void test_matrix_2d_access() {

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_2D_ACCESS BEGIN" << endl;
	cout << "-----------------------------------" << endl;

	matrix_2d<float> matrix(3, 5);

	matrix(0, 2) = 1.5f;
	matrix(2, 4) = 1;
	matrix(0, 0) = 3.8f;

	matrix_2d<string> matrix1(2, 7);

	matrix1(1, 5) = "tempo";
	matrix1(0, 3) = "Perdi";
	matrix1(1, 6) = "Caso";
	matrix1(0, 5) = "testa";

	float f = matrix(0, 0);
	string s("tempo");

	const matrix_2d<string> matrix2(matrix1);
	const string a = matrix2(0, 4);
	
	matrix_2d<float>::iterator start = matrix.begin(); 
	auto end = matrix.end();
	int i = 0;

	start[1] = 5.56f;

	while(start != end) {
		assert(*start == matrix(i / matrix.columns(), i % matrix.columns()));

		#ifndef NPRINT
		cout << *start << " ";
		#endif 

		++start;
		++i;
	}

	assert(*(--start) == 1);

	auto start2 = matrix2.begin(); 
	auto end2 = matrix2.end();
	i = 0;

	//start2[3] = "ERRORE"; errore

	while(start2 != end2) {
		assert(*start2 == matrix1(i / matrix1.columns(), i % matrix1.columns()));

		#ifndef NPRINT
		cout << *start2 << " ";
		#endif 

		++start2;
		++i;
	}

	#ifndef NPRINT
	cout << endl;
	#endif 


	assert(matrix(0, 2) == 1.5f);
	assert(matrix(2, 4) == 1.0f);
	assert(f == matrix(0, 0));

	assert(matrix1(1, 5) == "tempo");
	assert(matrix1(1, 5) == s);
	assert(matrix1(0, 3) == "Perdi");
	assert(matrix1(0, 3) != "perdi");

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_2D_ACCESS END" << endl;
	cout << "-----------------------------------" << endl << endl;
}

void test_matrix_2d_methods() {

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_2D_METHODS BEGIN" << endl;
	cout << "-----------------------------------" << endl;

	matrix_2d<double> matrix(4, 6);

	int k = 0;

	for(int i=0; i < matrix.rows(); ++i)
		for(int j=0; j < matrix.columns(); ++j)
			matrix(i, j) = k++ + 0.4;

	matrix_2d<int> conv(matrix);
	matrix_2d<int> submatrix(2, 3);

	for(int i=0; i < submatrix.rows(); ++i)
		for(int j=0; j < submatrix.columns(); ++j)
			submatrix(i, j) = conv(i, j);

	matrix_2d<int>* extracted = conv.slice(0, submatrix.rows() - 1,
										   0, submatrix.columns() - 1);

	matrix_2d<double>* extracted1 = matrix.slice(2, 3, 1, 5);

	assert((*extracted1)(0, 0) == 13.4);
	assert((*extracted1)(1, 4) == 23.4);
	assert((*extracted1)(1, 2) == 21.4);


	#ifndef NPRINT
	cout << "Extracted1" << endl << extracted1 << endl;
	#endif

	#ifndef NPRINT
	cout << "conv" << endl << conv << endl << "extracted" << endl << extracted << endl;
	#endif

	assert(*extracted == submatrix);
	assert(submatrix == *extracted);
	assert((*extracted).equals(submatrix, [] (int a, int b) {return a == b;}));
	assert(submatrix.equals(*extracted, [] (int a, int b) {return a == b;}));

	//(*extracted)(0, 0) = -1;

	assert(!(*extracted != submatrix));
	assert(!(submatrix != *extracted));

	struct add2 {
		double adder = 2.5;
		double operator() (int a) const {return a + adder;}
	};

	add2 func;

	matrix_2d<double>* trasformed = transform<double>(submatrix, [] (int a) -> double {return a + 2.5;});

	#ifndef NPRINT
	cout << "trasformed" << endl << trasformed << endl;
	#endif

	submatrix.fill(conv.begin(), conv.end());

	for(int i=0; i < submatrix.rows(); ++i)
		for(int j=0; j < submatrix.columns(); ++j)
			assert(submatrix(i, j) == i * submatrix.columns() + j);

	#ifndef NPRINT
	cout << "conv" << endl << conv << endl;
	#endif

	matrix.fill(extracted->begin(), extracted->end());

	assert(matrix(0, 0) == 0);
	assert(matrix(1, 0) == 6.4);
	assert(matrix(0, 3) == 6);

	#ifndef NPRINT
	cout << "matrix" << endl << matrix << endl;
	#endif

	matrix.fill(conv.begin(), conv.end());

	assert(matrix(0, 0) == 0);

	#ifndef NPRINT
	cout << "matrix" << endl << matrix << endl;
	#endif

	delete trasformed;
	delete extracted;
	delete extracted1;

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_2D_METHODS END" << endl;
	cout << "-----------------------------------" << endl << endl;
}

void test_matrix_3d_null() {

	matrix_3d<double> empty(0, 0, 0);

	matrix_3d<double> emptyClone = empty;

	matrix_3d<int> transEmptyClone = empty;

	assert(empty == emptyClone);
	assert(!(empty != emptyClone));
	assert(emptyClone.columns() == 0);
	assert(emptyClone.rows() == 0);

	assert(emptyClone.equals(empty, [] (double a, double b) -> bool {return false;}));

	matrix_3d<int> clone(1, 4, 5);
	clone = transEmptyClone;

	vector<int> v = {1,2,3,4,5,6,7,8,9,11,21,313,4,1,3,113,313,131,31,31};
	clone.fill(v.begin(), v.end());

	assert(clone == transEmptyClone);
	assert(!(clone != transEmptyClone));
	assert(clone.columns() == 0);
	assert(clone.rows() == 0);

	assert(clone.equals(transEmptyClone, [] (int a, int b) -> bool {return false;}));

	//delete &(clone.slice(0, 0, 0, 0, 0, 0));


	matrix_3d<int>* normal = new matrix_3d<int>(3, 5, 2);
	normal->fill(v.begin(), v.end());

	matrix_3d<double>* tra = transform<double>(*normal, [] (int a) -> double {return a * 2.2;});
	
	auto s = tra->begin();
	for(int i = 0; i < v.size(); ++i, ++s) {
		assert(*s == v[i]*2.2);
	}

	delete tra;
	delete normal;

	matrix_3d<double>* tra1 = transform<double>(clone, [] (int a) -> double {return a * 2.2;});

	assert(*tra1 == transEmptyClone);
	assert(!(*tra1 != transEmptyClone));
	assert(tra1->columns() == 0);
	assert(tra1->rows() == 0);

	const matrix_3d<double> c_tra1(*tra1);

	auto a1 = tra1->begin();
	auto a2 = c_tra1.begin();

	auto z1 = tra1->end();
	auto z2 = c_tra1.end();

	assert(a1 == z1);
	assert(a2 == z2);
	assert(++a1 == z1);
	assert(--a2 == z2);
	assert(a1 == ++z1);
	assert(a2 == z2--);

	delete tra1;

	matrix_3d<double> str(5, 5, 0);

	matrix_3d<double> strClone = str;

	matrix_3d<int> transStrClone = str;

	assert(str == strClone);
	assert(!(str != strClone));
	assert(strClone.columns() == 0);
	assert(strClone.rows() == 0);

	assert(strClone.equals(str, [] (double a, double b) -> bool {return false;}));

	matrix_3d<int> strstr(1, 4, 5);
	strstr = transStrClone;

	strstr.fill(v.begin(), v.end());

	assert(strstr == transStrClone);
	assert(!(strstr != transStrClone));
	assert(strstr.columns() == 0);
	assert(strstr.rows() == 0);

	assert(strstr.equals(transStrClone, [] (int a, int b) -> bool {return false;}));

	matrix_3d<string> dfg(3, 5, 0);

	auto w = dfg.begin();
	auto w_end = dfg.end();


	while(w++ != w_end);
	assert(w == w_end);
}

void test_matrix_3d_creation() {

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_3D_CREATION BEGIN" << endl;
	cout << "-----------------------------------" << endl;

	matrix_3d<int> m;

	assert(m.plans() == 0);
	assert(m.rows() == 0);
	assert(m.columns() == 0);
	assert(m.size() == 0);

	matrix_3d<double> matrix(2, 4, 3);

	matrix_3d<float> ma(0, 4, 6);

	matrix(0, 1, 1) = 3.67;
	matrix(0, 2, 2) = 4.12;
	matrix(1, 1, 1) = 1.66;
	matrix(1, 3, 0) = 5.37;

	assert(matrix.plans() == 2);
	assert(matrix.rows() == 4);
	assert(matrix.columns() == 3);
	assert(matrix.size() == 2 * 4 * 3);

	matrix_3d<int> conv(matrix);

	#ifndef NPRINT
	cout << "conv" << endl << conv << endl;
	#endif

	assert(conv(0, 1, 1) == 3);
	assert(conv(0, 2, 2) == 4);
	assert(conv(1, 1, 1) == 1);
	assert(conv(1, 3, 0) == 5);

	matrix_3d<int> clone = conv;
	matrix_3d<int> clone2(clone);
	matrix_2d<int> subclone(clone2[0]);

	assert(clone(0, 1, 1) == 3);
	assert(clone(0, 2, 2) == 4);
	assert(clone(1, 1, 1) == 1);
	assert(clone(1, 3, 0) == 5);
	assert(clone == conv);
	assert(&clone != &conv);

	matrix_3d<int> clone1;
	clone1 = clone;

	assert(clone1(0, 1, 1) == 3);
	assert(clone1(0, 2, 2) == 4);
	assert(clone1(1, 1, 1) == 1);
	assert(clone1(1, 3, 0) == 5);
	assert(clone1 == conv);
	assert(&clone1 != &conv);

	matrix_3d<matrix_3d<int>>* test = new matrix_3d<matrix_3d<int>>(4, 6, 7);
	
	assert((*test)(1, 5, 6).size() == 0);

	matrix_3d<string>* test1 = new matrix_3d<string>[5];

	assert(test1[0].plans() == 0);

	delete[] test1;
	delete test;

	matrix_3d<pair<char, int>>* leak = new matrix_3d<pair<char, int>>(3, 4, 5);
	const matrix_3d<pair<char, int>>* tmp = leak->slice(0, 1, 1, 3, 3, 4); 

	delete tmp;
	delete leak;

	vector<vector<int>> vect;
	vector<int> fill = {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 5, 4, 3, 2, 1};

	for(int i=0; i<10; ++i) {
		vect.push_back(fill);
	}

	matrix_3d<vector<int>> fin(10, 2, 8);

	fin.fill(vect.begin(), vect.end());

	auto iter_vect = fin.begin(); 
	for(int i=0;i<10; ++i)
		assert(*iter_vect == vect[i]);

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_3D_CREATION END" << endl;
	cout << "-----------------------------------" << endl << endl;
}

void test_matrix_3d_access() {
	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_3D_ACCESS BEGIN" << endl;
	cout << "-----------------------------------" << endl;

	matrix_3d<double> matrix(2, 4, 3);

	int cont = 0;

	for(int k=0; k < matrix.plans(); ++k)
		for(int i=0; i < matrix.rows(); ++i)
			for(int j=0; j < matrix.columns(); ++j)
				matrix(k, i, j) = 0.4 + cont++; 

	auto iter = matrix.begin();
	auto end = matrix.end();

	#ifndef NPRINT
	cout << matrix << endl;
	for(; iter != end; ++iter)
		cout << *iter << " ";
	
	cout << endl;
	#endif


	iter = matrix.begin();

	matrix_3d<double>::const_iterator c_iter(iter);

	for(int k=0; k < matrix.plans(); ++k)
		for(int i=0; i < matrix.rows(); ++i)
			for(int j=0; j < matrix.columns(); ++j) {
				assert(&(matrix(k, i, j)) == &(*iter));
				*iter -= 12.4;
				assert(matrix(k, i, j) == *iter);
				assert(*c_iter == *iter);
				*iter += 12.4;
				++iter;
				++c_iter;
			}

	assert(iter == matrix.end());
	assert(c_iter == iter); 
	--iter;

	c_iter = iter;

	for(int k=matrix.plans() - 1; k >= 0; --k)
		for(int i=matrix.rows() - 1; i >= 0; --i)
			for(int j=matrix.columns() - 1; j >= 0; --j) {
				assert(&(matrix(k, i, j)) == &(*iter));
				assert(&(*c_iter) == &(*iter));
				--iter;
				--c_iter;
			}

	assert(iter == matrix.begin());
	assert(c_iter == matrix.begin()); 


	const matrix_3d<int>* conv_p = new matrix_3d<int>(matrix);
	const matrix_3d<int>& conv = *conv_p;
	cont = 0;

	for(int k=0; k < matrix.plans(); ++k)
		for(int i=0; i < matrix.rows(); ++i)
			for(int j=0; j < matrix.columns(); ++j) {
				assert(abs(matrix(k, i, j) - cont - 0.4) < 10e-8);
				assert(conv(k, i, j) == cont++);
			}

	//conv(0, 0, 0) = 23; Error

	matrix_3d<int> clone(conv);
	for(int k=0; k < clone.plans(); ++k)
		for(int i=0; i < clone.rows(); ++i)
			for(int j=0; j < clone.columns(); ++j)
				clone(k, i, j) += 2;

	const matrix_3d<int> cloneClone(clone);

	const matrix_3d<int> tmp(clone);
	
	auto const_iter = cloneClone.begin();
	const_iter = clone.begin();
	tmp.begin() = const_iter;
	auto f = tmp.begin();
	f = clone.end();

	f--;

	matrix_3d<int>::const_iterator abc(const_iter);
	matrix_3d<int>::const_iterator abcd(clone.begin());

	abc == const_iter;
	abc == clone.end();
	abc != const_iter;
	abc != clone.end();

	auto o = clone.begin();

	o == const_iter;
	o == clone.end();
	o != const_iter;
	o != clone.end();

	auto a1 = clone.begin();
	auto z1 = clone.end();

	while(a1++ != z1);

	for(int i=0;i<5;++i) {
		a1++;
		z1++;
	}

	assert(a1++ == z1);

	a1 = clone.begin();
	z1 = clone.end();

	int g = 30;

	while(a1 != z1-- && g-- > 0);

	for(int i=0;i<5;++i) {
		--a1;
		z1--;
	}

	assert(a1-- == z1);

	struct diff {
		int x = 2;

		bool operator()(int& param1, int& param2) const {
			return (param1 - param2) == x;
		}
	};

	matrix_3d<diff*> complex(1, 2, 2);

	diff vv1, vv2, vv3;

	complex(0, 0, 0) = &(vv1);
	complex(0, 0, 1) = &(vv2);
	complex(0, 1, 0) = &(vv3);

	complex(0, 0, 0)->x = 1;
	complex(0, 0, 1)->x = 2;
	complex(0, 1, 0)->x = 3;

	auto d1 = complex.begin();

	for(int i=0; i<3; ++i) {
		assert((*d1)->x == i + 1);
		++d1;
	}
	

	diff d;

	assert(clone != conv);
	assert(clone == matrix_3d<int>(clone));

	assert(clone.equals<diff>(conv, d));

	const matrix_3d<int> const_clone = clone;

	//const_clone[2](0, 0) = 11; Error

	for(matrix_3d<int>::size_type z=0; z < clone.plans(); ++z) {
		assert(const_clone[z].equals<diff>(conv[z], d));
		for(int i=0; i < clone.rows(); ++i)
			for(int j=0; j < clone.columns(); ++j)
				assert(clone(z, i, j) == conv(z, i, j) + 2);
	}

	#ifndef NPRINT
	cout << "clone" << endl << clone << endl;
	#endif

	delete conv_p;



	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_3D_ACCESS END" << endl;
	cout << "-----------------------------------" << endl << endl;
}

void test_matrix_3d_methods() {
	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_3D_METHODS BEGIN" << endl;
	cout << "-----------------------------------" << endl;

	int k = 0;

	matrix_3d<double> source(5, 3, 2);
	for(int z=0; z < source.plans(); ++z)
		for(int i=0; i < source.rows(); ++i)
			for(int j=0; j < source.columns(); ++j)
				source(z, i, j) = k++ + 0.23;

	#ifndef NPRINT
	cout << "source" << endl << source << endl;
	#endif

	matrix_3d<int>* trasformed = transform<int>(source, 
		[] (double a) -> int {return static_cast<int>(a) + 29;}); 

	#ifndef NPRINT
	cout << "trasformed" << endl << trasformed << endl;
	#endif

	k = 29;

	for(int z=0; z < trasformed->plans(); ++z)
		for(int i=0; i < trasformed->rows(); ++i)
			for(int j=0; j < trasformed->columns(); ++j)
				assert((*trasformed)(z, i, j) == k++);

	delete trasformed;


	pair<char, int> p[50];
	for(int i=0; i < 50; ++i)
		p[i] = pair<char, int>(static_cast<char>(i + 60), i);


	matrix_3d<pair<char, int>> matrix(6, 4, 2);

	matrix.fill(p, p+50);
	k = 0;

	for(int z=0; z < matrix.plans(); ++z) {
		for(int i=0; i < matrix.rows(); ++i) {
			for(int j=0; j < matrix.columns(); ++j) {
				
				#ifndef NPRINT
				cout << matrix(z, i, j).first << matrix(z, i, j).second << " ";
				#endif

				assert(matrix(z, i, j).first == static_cast<char>(k + 60));
				assert(matrix(z, i, j).second == static_cast<char>(k++));
			}
			#ifndef NPRINT
			cout << endl;
			#endif
		}
		#ifndef NPRINT
		cout << endl;
		#endif
	}

	struct f {

		float adder = 3.76f;

		pair<int, float>* operator()(int p) const {
			pair<int, float> *p1 = new pair<int, float>;
			p1->first = p;
			p1->second = p + adder;
			return p1;
		}
	};

	f myF;

	matrix_3d<int> startMatrix(2, 4, 5);

	int y = 0;

	for(int z=0; z < startMatrix.plans(); ++z) 
		for(int i=0; i < startMatrix.rows(); ++i) 
			for(int j=0; j < startMatrix.columns(); ++j) 
				startMatrix(z, i, j) = y++;

	matrix_3d<pair<int, float>*>* clone = transform<pair<int, float>*>(startMatrix, myF);

	y = 0;

	for(int z=0; z < clone->plans(); ++z) {
		for(int i=0; i < clone->rows(); ++i) {
			for(int j=0; j < clone->columns(); ++j) {
				
				#ifndef NPRINT
				cout << (*clone)(z, i, j)->first << "," << (*clone)(z, i, j)->second << " ";
				#endif

				assert((*clone)(z, i, j)->first == y);
				assert((*clone)(z, i, j)->second == y + myF.adder);
				++y;
				
			}
			#ifndef NPRINT
			cout << endl;
			#endif
		}
		#ifndef NPRINT
		cout << endl;
		#endif
	}

	auto start = clone->begin();
	auto end = clone->end();

	--end;

	while(end != start) {
		delete *end;
		--end;
	}

	delete *end;

	delete clone;
	
	matrix_3d<pair<char, int>>* submatrix = matrix.slice(0, 4, 1, 1, 0, 1);

	for(int z=0; z < submatrix->plans(); ++z) {
		for(int i=0; i < submatrix->rows(); ++i) {
			for(int j=0; j < submatrix->columns(); ++j) {
				#ifndef NPRINT
				cout << (*submatrix)(z, i, j).first << (*submatrix)(z, i, j).second << " ";
				#endif
				assert((*submatrix)(z, i, j) == matrix(z, i + 1, j));
			}
			#ifndef NPRINT
			cout << endl;
			#endif
		}
		#ifndef NPRINT
		cout << endl;
		#endif
	}
	

	delete submatrix;


	std::vector<double> v;
	for(int i=0; i < 1000; ++i)
		v.push_back(i - 334.5);

	matrix_3d<double> filled(12, 11, 5);
	filled.fill(v.begin(), v.end());

	int kk = 0;

	for(int z=0; z < filled.plans(); ++z)
		for(int i=0; i < filled.rows(); ++i)
			for(int j=0; j < filled.columns(); ++j) {
				assert(filled(z, i, j) == kk++ - 334.5);
			}

	struct myV {
		vector<int> operator() (vector<double> vect) const {
			
			vector<int> cl;

			for(double d : vect)
				cl.push_back(10 + static_cast<int>(d));
			return cl;
		}
	};

	myV func_v;

	matrix_3d<vector<double>> asdf(6, 3, 4);

	vector<double> a;
	for(int i=0; i<100; ++i)
		a.push_back(i + 0.56);

	asdf(0, 0, 0) = a;
	asdf(0, 1, 1) = a;
	asdf(4, 0, 1) = a;

	matrix_3d<vector<int>>* ttrans = transform<vector<int>>(asdf, func_v);

	int h = 10;

	for(int i : (*ttrans)(0, 0, 0))
		assert(i == h++);

	delete ttrans;

	cout << "-----------------------------------" << endl;
	cout << "TEST MATRIX_3D_METHODS END" << endl;
	cout << "-----------------------------------" << endl;
}

int main() {

	test_matrix_2d_creation();

	test_matrix_2d_access();

	test_matrix_2d_methods();

	test_matrix_3d_null();

	test_matrix_3d_creation();

	test_matrix_3d_access();

	test_matrix_3d_methods();

	return 0;
}
