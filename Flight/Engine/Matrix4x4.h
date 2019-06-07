#pragma once
#include <iostream>
#include "BasicMacros.h"
#include "VectorUtil.h"
#include <cmath>
template<typename TYPE>
class Matrix4x4;

template<class TYPE, int N, int M>
class Matrix {
public:
	TYPE data[N*M];
	Matrix() { PS_DATCLEAR(TYPE, data, N*M); }
	Matrix(const Matrix &p) { PS_DATCOPY(data, p.data, N*M); }
	Matrix(const TYPE v) { PS_INITIALIZE(data, N*M, v); }
	Matrix(const Matrix4x4<TYPE> &p);
	~Matrix() { PS_DATCLEAR(TYPE, data, N*M); }
	void operator=(const Matrix &p) {
		PS_DATCOPY(data, p.data, N*M);
	}
	inline friend std::ostream& operator<<(std::ostream& os, const Matrix &p) {
		int id = 0;
		if (N*M > 0) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M - 1; j++) {
					os << p.data[id] << ", ";
					id++;
				}
				os << p.data[id] << "\n";
				id++;
			}
		}
		return os;
	}


	Matrix operator + (const Matrix &p) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] + p.data[i]; return r; }
	Matrix operator - (const Matrix &p) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] - p.data[i]; return r; }

	
	//template<int K>
	////const Matrix &v, 
	//friend Matrix<TYPE, N, K> operator*(const Matrix<TYPE, M, K> &p) const {
	//	Matrix<TYPE, N, K> r;
	//	r.Clear();
	//	for (int i = 0; i < N; i++)
	//		for (int j = 0; j < K; j++)
	//			for (int k = 0; k < M; k++) 
	//				r[i][j] += (*this)[i][k] * p[k][j]; 
	//			
	//	return r;
	//}
	friend Matrix operator+(const TYPE v, const Matrix &p) {
		return p + v;
	}
	friend Matrix operator-(const TYPE v, const Matrix &p) {
		return p * -1 + v;
	}
	friend Matrix operator*(const TYPE v, const Matrix &p) {
		return p * v;
	}
	
	Matrix operator+ (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] + v; return r; }
	Matrix operator- (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] - v; return r; }
	Matrix operator* (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] * v; return r; }
	Matrix operator/ (const TYPE v) const { Matrix r; for (int i = 0; i < N*M; i++) r.data[i] = data[i] / v; return r; }

	//!@name Assignment operators

	const Matrix& operator += (const Matrix &p) { for (int i = 0; i < N*M; i++) data[i] += p.data[i]; return *this; }
	const Matrix& operator -= (const Matrix &p) { for (int i = 0; i < N*M; i++) data[i] -= p.data[i]; return *this; }

	const Matrix& operator += (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] += v; return *this; }
	const Matrix& operator -= (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] -= v; return *this; }
	const Matrix& operator *= (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] *= v; return *this; }
	const Matrix& operator /= (const TYPE v) { for (int i = 0; i < N*M; i++) data[i] /= v; return *this; }

	bool operator==(const Matrix& p) const { for (int i = 0; i < N*M; i++) if (data[i] != p.data[i]) return false; return true; }
	bool operator!=(const Matrix& p) const { for (int i = 0; i < N*M; i++) if (data[i] != p.data[i]) return true;  return false; }

	TYPE*		operator [] (int i) { return &data[i * M]; }
	const TYPE* operator [] (int i) const { return &data[i * M]; }

	TYPE&       Element(int i) { return data[i]; }
	const TYPE& Element(int i) const { return data[i]; }

	void Clear() {
		PS_DATCLEAR(TYPE, data, N*M);
	}

	Matrix<TYPE, M, N> OriginTranspose() {
		Matrix<TYPE, M, N> r;
		r.Clear();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				r[j][i] = (*this)[i][j];
		return r;
	}
	template<int K>
	friend Matrix<TYPE, N, K> operator*(const Matrix<TYPE, N, M> &v, const Matrix<TYPE, M, K> &p) {
		Matrix<TYPE, N, K> r;
		r.Clear();
		for (int i = 0; i < N; i++)
			for (int j = 0; j < K; j++)
				for (int k = 0; k < M; k++)
					r[i][j] += v[i][k] * p[k][j];

		return r;
	}
};

template<typename TYPE>
class Matrix4x4 : public Matrix<TYPE, 4, 4>
{
public:

	// copy
	Matrix4x4() {}
	Matrix4x4(const Vector4D<TYPE> &p) {
		for (int i = 0; i < 4; i++) (*this)[i][i] = p[i];
	}
	Matrix4x4(const Matrix4x4 &p) {
		PS_DATCOPY(this->data, p.data, 16);
	}
	Matrix4x4(const Matrix<TYPE, 4, 4> &p) {
		PS_DATCOPY(this->data, p.data, 16);
	}
	using Matrix<TYPE, 4, 4>::operator=;
	void operator=(const Vector4D<TYPE> &p) {
		(*this).Clear();
		for (int i = 0; i < 4; i++) (*this)[i][i] = p[i];
	}
	void operator=(const Matrix4x4 &p) {
		PS_DATCOPY(this->data, p.data, 16);
	}
	void operator=(const Matrix<TYPE, 4, 4> &p) {
		PS_DATCOPY(this->data, p.data, 16);
	}


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

	using Matrix<TYPE, 4, 4>::operator*;
	// Matrix4x4 operator*(const Matrix4x4 &p) {
	// 	Matrix<TYPE, 4, 4> a = (Matrix<TYPE, 4, 4>)(*this);
	// 	Matrix<TYPE, 4, 4> b = (Matrix<TYPE, 4, 4>)(p);
	// 	*this = a * b;
	// 	return *this;
	// }
	friend Vector4D<TYPE> operator *(const Matrix4x4& v, const Vector4D<TYPE> &p) {
		Vector4D<TYPE> r;
		r.Clear();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 1; j++)
				for (int k = 0; k < 4; k++) 
					r[i] += v[i][k] * p[k];
			
		return r;
	}

	friend Vector4D<TYPE> operator *(const Vector4D<TYPE> &p, const Matrix4x4& v) {
		Vector4D<TYPE> r;
		r.Clear();
		
		for (int i = 0; i < 1; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++) {
					r[j] += p[k] * v[k][j];
				}
					
		return r;
	}

	void Scale(TYPE v) {
		*this *= v;
		return *this;
	}


	Matrix4x4 Transpose() {
		return this->OriginTranspose();
	}

	static Matrix4x4 GetTranslationMatrix(const Vector4D<TYPE> &move) {
		Matrix4x4 trans;
		trans.SetTrans(move);
		return trans;
	}

	static Matrix4x4 GetRotationXMatrix(TYPE angle) {
		Matrix4x4 rot;
		rot.SetRotationX(angle);
		return rot;
	}

	static Matrix4x4 GetRotationYMatrix(TYPE angle) {
		Matrix4x4 rot;
		rot.SetRotationY(angle);
		return rot;
	}
	
	static Matrix4x4 GetRotationZMatrix(TYPE angle) {
		Matrix4x4 rot;
		rot.SetRotationZ(angle);
		return rot;
	}

	static Matrix4x4 GetRotationMatrix(Vector3D<TYPE> angles) {
		return GetRotationMatrix(angles[0], angles[1], angles[2]);
	}

	static Matrix4x4 GetRotationMatrix(TYPE angleX, TYPE angleY, TYPE angleZ) {
		Matrix4x4 rot;
		rot.SetRotationXYZ(angleX, angleY, angleZ);
		return rot;
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

	void SetTrans(const Vector4D<TYPE> &move) {
		(*this)[0][0] = TYPE(1); (*this)[0][1] = TYPE(0); (*this)[0][2] = TYPE(0); (*this)[0][3] = TYPE(move.x);
		(*this)[1][0] = TYPE(0); (*this)[1][1] = TYPE(1); (*this)[1][2] = TYPE(0); (*this)[1][3] = TYPE(move.y);
		(*this)[2][0] = TYPE(0); (*this)[2][1] = TYPE(0); (*this)[2][2] = TYPE(1); (*this)[2][3] = TYPE(move.z);
		(*this)[3][0] = TYPE(0); (*this)[3][1] = TYPE(0); (*this)[3][2] = TYPE(0); (*this)[3][3] = TYPE(1);
	}

	void SetRotationXYZ(TYPE angleX, TYPE angleY, TYPE angleZ)
	{
		const TYPE sx = (TYPE) ::sin(angleX);
		const TYPE cx = (TYPE) ::cos(angleX);
		const TYPE sy = (TYPE) ::sin(angleY);
		const TYPE cy = (TYPE) ::cos(angleY);
		const TYPE sz = (TYPE) ::sin(angleZ);
		const TYPE cz = (TYPE) ::cos(angleZ);

		(*this)[0][0] = cy * cz;              (*this)[0][1] = cy * sz;                 (*this)[0][2] = -sy;     (*this)[0][3] = TYPE(0);
		(*this)[1][0] = cz * sx*sy - cx * sz; (*this)[1][1] = cx * cz + sx * sy * sz;  (*this)[1][2] = cy * sx; (*this)[1][3] = TYPE(0);
		(*this)[2][0] = cx * cz*sy + sx * sz; (*this)[2][1] = -cz * sx + cx * sy * sz; (*this)[2][2] = cx * cy; (*this)[2][3] = TYPE(0);
		(*this)[3][0] = TYPE(0);              (*this)[3][1] = TYPE(0);                 (*this)[3][2] = TYPE(0); (*this)[3][3] = TYPE(1);
	}

	void AddTrans(const Vector4D<TYPE> &move) {
		(*this)[0][3] += move.x; (*this)[1][3] += move.y; (*this)[2][3] += move.z;
	}

	void SetScale(const TYPE &scale) { SetScale(scale, scale, scale); }

	void SetScale(const TYPE &scaleX, const TYPE &scaleY, const TYPE &scaleZ, TYPE scaleW = 1)
	{
		this->Clear();
		(*this)[0][0] = scaleX;
		(*this)[1][1] = scaleY;
		(*this)[2][2] = scaleZ;
		(*this)[3][3] = scaleW;
	}

	Vector4D<TYPE> GetDiag() {
		Vector4D<TYPE> r;
		r.Clear();
		r[0] = (*this)[0][0];
		r[1] = (*this)[1][1];
		r[2] = (*this)[2][2];
		r[3] = (*this)[3][3];
		return r;
	}


	Matrix4x4 Inversion()
	{
		Matrix4x4 inversion;
		// matrix:
		// 0 1 2 3
		// 4 5 6 7
		// 8 9 10 11
		// 12 13 14 15

		const TYPE data_11_14__10_15 = (*this)[2][3] * (*this)[3][2] - (*this)[2][2] * (*this)[3][3];
		const TYPE data_10_15__11_14 = (*this)[2][2] * (*this)[3][3] - (*this)[2][3] * (*this)[3][2];
		const TYPE data__7_14___6_15 = (*this)[1][3] * (*this)[3][2] - (*this)[1][2] * (*this)[3][3];
		const TYPE data__6_11___7_10 = (*this)[1][2] * (*this)[2][3] - (*this)[1][3] * (*this)[2][2];

		const TYPE data__9_15__11_13 = (*this)[2][1] * (*this)[3][3] - (*this)[2][3] * (*this)[3][1];
		const TYPE data_11_13___9_15 = (*this)[2][3] * (*this)[3][1] - (*this)[2][1] * (*this)[3][3];
		const TYPE data__5_15___7_13 = (*this)[1][1] * (*this)[3][3] - (*this)[1][3] * (*this)[3][1];
		const TYPE data__7__9___5_11 = (*this)[1][3] * (*this)[2][1] - (*this)[1][1] * (*this)[2][3];

		const TYPE data_10_13___9_14 = (*this)[2][2] * (*this)[3][1] - (*this)[2][1] * (*this)[3][2];
		const TYPE data__9_14__10_13 = (*this)[2][1] * (*this)[3][2] - (*this)[2][2] * (*this)[3][1];
		const TYPE data__6_13___5_14 = (*this)[1][2] * (*this)[3][1] - (*this)[1][1] * (*this)[3][2];
		const TYPE data__5_10___6__9 = (*this)[1][1] * (*this)[2][2] - (*this)[1][2] * (*this)[2][1];

		const TYPE data_11_12___8_15 = (*this)[2][3] * (*this)[3][0] - (*this)[2][0] * (*this)[3][3];
		const TYPE data__8_15__11_12 = (*this)[2][0] * (*this)[3][3] - (*this)[2][3] * (*this)[3][0];
		const TYPE data__7_12___4_15 = (*this)[1][3] * (*this)[3][0] - (*this)[1][0] * (*this)[3][3];
		const TYPE data__4_11___7__8 = (*this)[1][0] * (*this)[2][3] - (*this)[1][3] * (*this)[2][0];

		const TYPE data__8_14__10_12 = (*this)[2][0] * (*this)[3][2] - (*this)[2][2] * (*this)[3][0];
		const TYPE data_10_12___8_14 = (*this)[2][2] * (*this)[3][0] - (*this)[2][0] * (*this)[3][2];
		const TYPE data__4_14___6_12 = (*this)[1][0] * (*this)[3][2] - (*this)[1][2] * (*this)[3][0];
		const TYPE data__6__8___4_10 = (*this)[1][2] * (*this)[2][0] - (*this)[1][0] * (*this)[2][2];

		const TYPE data__9_12___8_13 = (*this)[2][1] * (*this)[3][0] - (*this)[2][0] * (*this)[3][1];
		const TYPE data__8_13___9_12 = (*this)[2][0] * (*this)[3][1] - (*this)[2][1] * (*this)[3][0];
		const TYPE data__5_12___4_13 = (*this)[1][1] * (*this)[3][0] - (*this)[1][0] * (*this)[3][1];
		const TYPE data__4__9___5__8 = (*this)[1][0] * (*this)[2][1] - (*this)[1][1] * (*this)[2][0];

		inversion[0][0] = (*this)[1][1] * (-data_11_14__10_15) + (*this)[1][2] * (-data__9_15__11_13) + (*this)[1][3] * (-data_10_13___9_14);
		inversion[0][1] = (*this)[0][1] * (-data_10_15__11_14) + (*this)[0][2] * (-data_11_13___9_15) + (*this)[0][3] * (-data__9_14__10_13);
		inversion[0][2] = (*this)[0][1] * (-data__7_14___6_15) + (*this)[0][2] * (-data__5_15___7_13) + (*this)[0][3] * (-data__6_13___5_14);
		inversion[0][3] = (*this)[0][1] * (-data__6_11___7_10) + (*this)[0][2] * (-data__7__9___5_11) + (*this)[0][3] * (-data__5_10___6__9);

		inversion[1][0] = (*this)[1][0] * (data_11_14__10_15)+(*this)[1][2] * (-data_11_12___8_15) + (*this)[1][3] * (-data__8_14__10_12);
		inversion[1][1] = (*this)[0][0] * (data_10_15__11_14)+(*this)[0][2] * (-data__8_15__11_12) + (*this)[0][3] * (-data_10_12___8_14);
		inversion[1][2] = (*this)[0][0] * (data__7_14___6_15)+(*this)[0][2] * (-data__7_12___4_15) + (*this)[0][3] * (-data__4_14___6_12);
		inversion[1][3] = (*this)[0][0] * (data__6_11___7_10)+(*this)[0][2] * (-data__4_11___7__8) + (*this)[0][3] * (-data__6__8___4_10);

		inversion[2][0] = (*this)[1][0] * (data__9_15__11_13)+(*this)[1][1] * (data_11_12___8_15)+(*this)[1][3] * (-data__9_12___8_13);
		inversion[2][1] = (*this)[0][0] * (data_11_13___9_15)+(*this)[0][1] * (data__8_15__11_12)+(*this)[0][3] * (-data__8_13___9_12);
		inversion[2][2] = (*this)[0][0] * (data__5_15___7_13)+(*this)[0][1] * (data__7_12___4_15)+(*this)[0][3] * (-data__5_12___4_13);
		inversion[2][3] = (*this)[0][0] * (data__7__9___5_11)+(*this)[0][1] * (data__4_11___7__8)+(*this)[0][3] * (-data__4__9___5__8);

		inversion[3][0] = (*this)[1][0] * (data_10_13___9_14)+(*this)[1][1] * (data__8_14__10_12)+(*this)[1][2] * (data__9_12___8_13);
		inversion[3][1] = (*this)[0][0] * (data__9_14__10_13)+(*this)[0][1] * (data_10_12___8_14)+(*this)[0][2] * (data__8_13___9_12);
		inversion[3][2] = (*this)[0][0] * (data__6_13___5_14)+(*this)[0][1] * (data__4_14___6_12)+(*this)[0][2] * (data__5_12___4_13);
		inversion[3][3] = (*this)[0][0] * (data__5_10___6__9)+(*this)[0][1] * (data__6__8___4_10)+(*this)[0][2] * (data__4__9___5__8);

		const TYPE det = (*this)[0][0] * inversion[0][0] + (*this)[0][1] * inversion[1][0] + (*this)[0][2] * inversion[2][0] + (*this)[0][3] * inversion[3][0];
		return inversion / det;
	}
	

};


template<typename TYPE, int N, int M>
Matrix<TYPE, N, M>::Matrix(const Matrix4x4<TYPE> &p) {
	if (N == 4 && M == 4)
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				(*this)[i][j] = p[i][j];
}
