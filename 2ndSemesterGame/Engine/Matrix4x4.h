#pragma once
#include <iostream>

#define PS_DATCOPY(dst, src, n) \
	{ for (int i = 0; i < (n); i++) (dest)[i] = (source)[i]; }

#define PS_DATCONVERT(TYPE, dst, src, n) \
	{ for (int i = 0; i < (n); i++) (dst)[i] = type((src)[i]); }

#define PS_INITIALIZE(dst, n, value) \
	{ for (int i = 0; i < (n); i++) (dst)[i] = value; }

#define PS_DATCLEAR(TYPE, dst, n) memset(dst, 0, (n)*sizeof(TYPE))



template<typename TYPE, int N, int M> 
class Matrix {
public:
	TYPE data[N*M];
	Matrix() { PS_DATCLEAR(TYPE, data, N*M); }
	Matrix(const Matrix &p) { PS_DATCOPY(data, p.data, N*M); }
	Matrix(const TYPE v) { PS_INITIALIZE(dst, N*M, value) }
	~Matrix() { PS_DATCLEAR(TYPE, data, N*M); }

	inline friend std::ostream& operator<<(std::ostream& os, const Matrix &p) {
		id = 0;
		if (N*M > 0) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M - 1; j++) {
					os << data[id] << ", ";
					id++;
				}
				os << data[id] << "\n";
				id++;
			}
		}
		return os;
	}


	Matrix operator + (const Matrix &p) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] + p.data[i]; return r; }
	Matrix operator - (const Matrix &p) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] + p.data[i]; return r; }
	Matrix<typename TYPE, int N, int K> operator * (const Matrix<typename TYPE, int M, int K> &p) const {
		Matrix<typename TYPE, int N, int K> r;
		r.Clear();
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < K; j++) 
				for (int k = 0; k < M; k++)
					r[i][j] += data[i][j] * p.data[j][k];
		return r;
	}
	
	Matrix operator + (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] + v; return r; }
	Matrix operator - (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] - v; return r; }
	Matrix operator * (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] * v; return r; }
	Matrix operator / (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] / v; return r; }

	//!@name Assignment operators

	const Matrix& operator += (const Matrix &p) { for (int i = 0; i < N*M; i++) data[i] += p.data[i]; return *this; }
	const Matrix& operator -= (const Matrix &p) { for (int i = 0; i < N*M; i++) data[i] -= p.data[i]; return *this; }
	
	const Matrix& operator += (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] += v; return *this; }
	const Matrix& operator -= (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] -= v; return *this; }
	const Matrix& operator *= (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] *= v; return *this; }
	const Matrix& operator /= (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] /= v; return *this; }

	bool operator==(const Matrix& p) const { for (int i = 0; i < N*M; i++) if (data[i] != p.data[i]) return false; return true; }
	bool operator!=(const Matrix& p) const { for (int i = 0; i < N*M; i++) if (data[i] != p.data[i]) return true;  return false; }

	TYPE*		operator [] (int i)		  { return &data[i * M]; }
	const TYPE* operator [] (int i) const { return &data[i * M]; }

	TYPE&       Element(int i)		 { return data[i]; }
	const TYPE& Element(int i) const { return data[i]; }

	void Clear() {
		PS_DATCLEAR(TYPE, data, N*M);
	}

	Matrix<typename TYPE, int M, int N> OriginTranspose() {
		Matrix<typename TYPE, int M, int N> r;
		r.Clear();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				r[j][i] = (*this)[i][j];
		return r;
	}

};



template<typename TYPE>
class Matrix4x4: public class Matrix<TYPE, 4, 4>
{
public:
	
	// copy
	Matrix4x4(const Vector4D<TYPE> p) { for (int i = 0; i < 4; i++) (*this)[i][i] = p[i]; }
	Matrix4x4(
		TYPE M11, TYPE M12, TYPE M13, TYPE M14,
		TYPE M21, TYPE M22, TYPE M23, TYPE M24,
		TYPE M31, TYPE M32, TYPE M33, TYPE M34,
		TYPE M41, TYPE M42, TYPE M43, TYPE M44) {
		(*this)[0][0] = M11; (*this)[0][1] = M12; (*this)[0][2] = M13; (*this)[0][3] = M14;
		(*this)[1][0] = M21; (*this)[1][1] = M22; (*this)[1][2] = M23; (*this)[1][3] = M24;
		(*this)[2][0] = M31; (*this)[2][1] = M32; (*this)[2][2] = M33; (*this)[2][3] = M34;
		(*this)[3][0] = M41; (*this)[3][1] = M42; (*this)[3][2] = M43; (*this)[3][3] = M44;
	}

	Vector4D<TYPE> operator *(const Vector4D<TYPE> &p) {
		Vector4D<TYPE> r;
		r.Clear();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				r[i] += (*this)[i][j] * p[j];
	}

	friend Vector4D<TYPE> operator *(const Matrix& v, const Vector4D<TYPE> &p) {
		Vector4D<TYPE> r;
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++) 
				r[k] += p[j] * (*this)[j][k];
	}

	void Scale(TYPE v) {
		*this *= v;
		return *this;
	}

	void Transpose() {
		*this = *this.OriginTranspose();
	}

	void Translation(Vector4D<TYPE> p) {
		
	}

	void SetRotationX(TYPE angle) { SetRotationY((TYPE) ::sin(angle), (TYPE) ::cos(angle)); }

	void SetRotationX(TYPE sinAngle, TYPE cosAngle)
	{
		(*this)[0][0] = TYPE(1); (*this)[0][1] = TYPE(0);   (*this)[0][2] = TYPE(0);  (*this)[0][3] = TYPE(0);
		(*this)[1][0] = TYPE(0); (*this)[1][1] = cosAngle;  (*this)[1][2] = sinAngle; (*this)[1][3] = TYPE(0);
		(*this)[2][0] = TYPE(0); (*this)[2][1] = -sinAngle; (*this)[2][2] = cosAngle; (*this)[2][3] = TYPE(0);
		(*this)[3][0] = TYPE(0); (*this)[3][1] = TYPE(0);   (*this)[3][2] = TYPE(0);  (*this)[3][3] = TYPE(1);
	}

	void SetRotationY(TYPE angle) { SetRotationY((TYPE) ::sin(angle), (TYPE) ::cos(angle)); }

	void SetRotationY(TYPE sinAngle, TYPE cosAngle)
	{
		(*this)[0][0] = cosAngle; (*this)[0][1] = TYPE(0); (*this)[0][2] = -sinAngle; (*this)[0][3] = TYPE(0);
		(*this)[1][0] = TYPE(0);  (*this)[1][1] = TYPE(1); (*this)[1][2] = TYPE(0);   (*this)[1][3] = TYPE(0);
		(*this)[2][0] = sinAngle; (*this)[2][1] = TYPE(0); (*this)[2][2] = cosAngle;  (*this)[2][3] = TYPE(0);
		(*this)[3][0] = TYPE(0);  (*this)[3][1] = TYPE(0); (*this)[3][2] = TYPE(0);   (*this)[3][3] = TYPE(1);
	}

	void SetRotationZ(TYPE angle) { SetRotationZ((TYPE) ::sin(angle), (TYPE) ::cos(angle)); }

	void SetRotationZ(TYPE sinAngle, TYPE cosAngle)
	{
		(*this)[0][0] = cosAngle;  (*this)[0][1] = sinAngle; (*this)[0][2] = TYPE(0); (*this)[0][3] = TYPE(0);
		(*this)[1][0] = -sinAngle; (*this)[1][1] = cosAngle; (*this)[1][2] = TYPE(0); (*this)[1][3] = TYPE(0);
		(*this)[2][0] = TYPE(0);   (*this)[2][1] = TYPE(0);  (*this)[2][2] = TYPE(1); (*this)[2][3] = TYPE(0);
		(*this)[3][0] = TYPE(0);   (*this)[3][1] = TYPE(0);  (*this)[3][2] = TYPE(0); (*this)[3][3] = TYPE(1);
	}

	void SetTrans(const Vector3D<TYPE> &move) { 
		(*this)[0][0] = TYPE(1); (*this)[0][1] = TYPE(0); (*this)[0][2] = TYPE(0); (*this)[0][3] = TYPE(move.x);
		(*this)[1][0] = TYPE(0); (*this)[1][1] = TYPE(1); (*this)[1][2] = TYPE(0); (*this)[1][3] = TYPE(move.y);
		(*this)[2][0] = TYPE(0); (*this)[2][1] = TYPE(0); (*this)[2][2] = TYPE(1); (*this)[2][3] = TYPE(move.z);
		(*this)[3][0] = TYPE(0); (*this)[3][1] = TYPE(0); (*this)[3][2] = TYPE(0); (*this)[3][3] = TYPE(1);
	}

	void AddTrans(const Vector3D<TYPE> &move) { 
		 (*this)[0][3] += move.x; (*this)[1][3] += move.y; (*this)[2][3] += move.z; 
	}

	void SetScale(const TYPE &scale) { SetScale(scale, scale, scale); }

	void SetScale(const TYPE &scaleX, const TYPE &scaleY, const TYPE &scaleZ, TYPE scaleW = 1)
	{
		Clear();
		(*this)[0][0] = scaleX;
		(*this)[1][1] = scaleY;
		(*this)[2][2] = scaleZ;
		(*this)[3][3] = scaleW;
	}

	void Matrix4x4::Invert(Matrix4x4 & out)
	{

	}

};

