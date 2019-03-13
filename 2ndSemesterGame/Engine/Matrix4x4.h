#pragma once

# define PS_DATCOPY(dst, src, TYPE, n) \
	{ for (int i = 0; i < (n); i++) (dest)[i] = (source)[i]; }

#define PS_DATCONVERT(type,dest,source,n) \
	{ for ( int i = 0; i < (n); i++ ) (dest)[i] = type((source)[i]); }


template<typename TYPE, int N, int M> 
class Matrix {
public:
	TYPE data[N*M];
	Matrix() {}
	Matrix(const Matrix &p) {
		PS_DATCOPY(dst, )
	}

};



template<typename TYPE>
class Matrix4x4: public class Matrix<TYPE, 4, 4>
{
public:
	
	// copy



	// + - * /

	Matrix4x4();
	~Matrix4x4();
};

