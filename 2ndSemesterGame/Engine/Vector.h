#pragma once
#include <memory>
#include "BasicMacros.h"

template<typename TYPE, int N>
class Vector
{
public:
	TYPE data[N];

	Vector() {}
	Vector(const Vector &p) {
		data = p.data;
	}
	const Vector& operator  = (const Vector &p) {
		PS_DATCOPY(data, p.data, N);
		return *this;
	}
	template<int M>
	const Vector(const Vector<TYPE, M> &p) {
		data = p.data;
	}
	template<int M>
	const Vector& operator  = (const Vector<TYPE, M> &p) {
		if (N > M) {
			PS_DATCOPY(data, p.data, M);
			PS_DATCLEAR(TYPE, p + M, N - M);
		}
		else
			PS_DATCOPY(data, p.data, N);
		return *this;
	}

	Vector operator + (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] + p.data[i]; return r; }
	Vector operator - (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] - p.data[i]; return r; }
	Vector operator * (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] * p.data[i]; return r; }
	Vector operator / (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] / p.data[i]; return r; }
	Vector operator + (const TYPE v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] + v; return r; }
	Vector operator - (const TYPE v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] - v; return r; }
	Vector operator * (const TYPE v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] * v; return r; }
	Vector operator / (const TYPE v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] / v; return r; }

	//!@name Assignment operators

	const Vector& operator += (const Vector &p) { for (int i = 0; i < N; ++i) data[i] += p.data[i]; return *this; }
	const Vector& operator -= (const Vector &p) { for (int i = 0; i < N; ++i) data[i] -= p.data[i]; return *this; }
	const Vector& operator *= (const Vector &p) { for (int i = 0; i < N; ++i) data[i] *= p.data[i]; return *this; }
	const Vector& operator /= (const Vector &p) { for (int i = 0; i < N; ++i) data[i] /= p.data[i]; return *this; }
	const Vector& operator += (const TYPE v) { for (int i = 0; i < N; ++i) data[i] += v; return *this; }
	const Vector& operator -= (const TYPE v) { for (int i = 0; i < N; ++i) data[i] -= v; return *this; }
	const Vector& operator *= (const TYPE v) { for (int i = 0; i < N; ++i) data[i] *= v; return *this; }
	const Vector& operator /= (const TYPE v) { for (int i = 0; i < N; ++i) data[i] /= v; return *this; }
};







//
//
//friend Vector operator + (TYPE v, const Vector &p) { return   p + v; }	//!< Addition with a constant
//friend Vector operator - (TYPE v, const Vector &p) { return -(p - v); }	//!< Subtraction from a constant
//friend Vector operator * (TYPE v, const Vector &p) { return   p * v; }	//!< Multiplication with a constant
//
//public:
//
//	TYPE data[N];
//
//	//!@name Constructors
//	Vector() {}
//	Vector(const Vector &p) { CY_MEMCOPY(TYPE, data, p.data, N); }
//	explicit Vector(const TYPE *p) { CY_MEMCOPY(TYPE, data, p, N); }
//	explicit Vector(TYPE v) { for (int i = 0; i < N; ++i) data[i] = v; }
//	template <typename T> explicit Vector(const Vector<T, N> &p) { CY_MEMCONVERT(TYPE, data, p.data, N); }
//	template <int M> explicit Vector(const Vector<TYPE, M> &p)
//	{
//		if (N <= M) { CY_MEMCOPY(TYPE, data, p.data, N); }
//		else { CY_MEMCOPY(TYPE, data, p.data, M); CY_MEMCLEAR(TYPE, data, N - M); }
//	}
//	template <typename T, int M> explicit Vector(const Vector<T, M> &p)
//	{
//		if (N <= M) { CY_MEMCONVERT(TYPE, data, p.data, N); }
//		else { CY_MEMCONVERT(TYPE, data, p.data, M); CY_MEMCLEAR(TYPE, data, N - M); }
//	}
//	explicit Vector(const Vector2<TYPE> &p);
//	explicit Vector(const Vector3<TYPE> &p);
//	explicit Vector(const Vector4<TYPE> &p);
//	template <typename T> explicit Vector(const Vector2<T> &p);
//	template <typename T> explicit Vector(const Vector3<T> &p);
//	template <typename T> explicit Vector(const Vector4<T> &p);
//	template <typename P> explicit Vector(const P &p) { for (int i = 0; i < N; ++i) data[i] = (TYPE)p[i]; }
//
//	//!@name Set & Get value methods
//	void Zero() { CY_MEMCLEAR(TYPE, data, N); }					//!< Sets the coordinates as zero
//	void Get(TYPE *p) const { CY_MEMCOPY(TYPE, p, data, N); }				//!< Puts the coordinate values into the array
//	void Set(const TYPE *p) { CY_MEMCOPY(TYPE, data, p, N); }				//!< Sets the coordinates using the values in the given array
//	void Set(TYPE v) { for (int i = 0; i < N; ++i) data[i] = v; }	//!< Sets all coordinates using the given value
//	template <int M> void CopyData(TYPE *p) { if (M <= N) { CY_MEMCOPY(TYPE, p, data, M); } else { CY_MEMCOPY(TYPE, p, data, N); CY_MEMCLEAR(TYPE, p + N, M - N); } }
//	template <typename T, int M> void ConvertData(T *p) { if (M <= N) { CY_MEMCONVERT(T, p, data, M); } else { CY_MEMCONVERT(T, p, data, N); CY_MEMCLEAR(T, p + N, M - N); } }
//
//	//!@name General methods
//	TYPE  LengthSquared() const { Vector p = operator*(*this); return p.Sum(); }	//!< Returns the square of the length. Effectively, this is the dot product of the vector with itself.
//	TYPE  Length() const { return (TYPE)cySqrt(LengthSquared()); }		//!< Returns the length of the vector.
//	void  Normalize() { *this /= Length(); }							//!< Normalizes the vector, such that its length becomes 1.
//	Vector GetNormalized() const { return *this / Length(); }					//!< Returns a normalized copy of the vector.
//	TYPE  Sum() const { TYPE v = data[0]; for (int i = 1; i < N; ++i) v += data[i]; return v; }		//!< Returns the sum of its components
//	bool  IsZero() const { for (int i = 0; i < N; ++i) if (data[i] != TYPE(0)) return false; return true; }	//!< Returns true if all components are exactly zero
//	TYPE  Min() const { TYPE m = data[0]; for (int i = 1; i < N; ++i) if (m > data[i]) m = data[i]; return m; }
//	TYPE  Max() const { TYPE m = data[0]; for (int i = 1; i < N; ++i) if (m < data[i]) m = data[i]; return m; }
//	int   MinID() const { TYPE m = data[0]; int ix = 0; for (int i = 1; i < N; ++i) if (m > data[i]) { m = data[i]; ix = i; } return m; }
//	int   MaxID() const { TYPE m = data[0]; int ix = 0; for (int i = 1; i < N; ++i) if (m < data[i]) { m = data[i]; ix = i; } return m; }
//
//	//!@name Limit methods
//	void Clamp(TYPE minValue, TYPE maxValue) { ClampMin(minValue); ClampMax(maxValue); }
//	void ClampMin(TYPE v) { for (int i = 0; i < N; ++i) data[i] = (data[i] < v) ? v : data[i]; }
//	void ClampMax(TYPE v) { for (int i = 0; i < N; ++i) data[i] = (data[i] > v) ? v : data[i]; }
//	void Abs() { for (int i = 0; i < N; i++) data[i] = cyAbs(data[i]); }	//!< Converts all negative components to positive values
//
//	//!@name Unary operators
//	Vector operator - () const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = -data[i]; return r; }
//
//	//!@name Binary operators
//	Vector operator + (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] + p.data[i]; return r; }
//	Vector operator - (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] - p.data[i]; return r; }
//	Vector operator * (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] * p.data[i]; return r; }
//	Vector operator / (const Vector &p) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] / p.data[i]; return r; }
//	Vector operator + (const TYPE   v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] + v; return r; }
//	Vector operator - (const TYPE   v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] - v; return r; }
//	Vector operator * (const TYPE   v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] * v; return r; }
//	Vector operator / (const TYPE   v) const { Vector r; for (int i = 0; i < N; ++i) r.data[i] = data[i] / v; return r; }
//
//	//!@name Assignment operators
//	const Vector& operator  = (const Vector &p) { CY_MEMCOPY(TYPE, data, p.data, N); return *this; }
//	const Vector& operator += (const Vector &p) { for (int i = 0; i < N; ++i) data[i] += p.data[i]; return *this; }
//	const Vector& operator -= (const Vector &p) { for (int i = 0; i < N; ++i) data[i] -= p.data[i]; return *this; }
//	const Vector& operator *= (const Vector &p) { for (int i = 0; i < N; ++i) data[i] *= p.data[i]; return *this; }
//	const Vector& operator /= (const Vector &p) { for (int i = 0; i < N; ++i) data[i] /= p.data[i]; return *this; }
//	const Vector& operator += (const TYPE   v) { for (int i = 0; i < N; ++i) data[i] += v; return *this; }
//	const Vector& operator -= (const TYPE   v) { for (int i = 0; i < N; ++i) data[i] -= v; return *this; }
//	const Vector& operator *= (const TYPE   v) { for (int i = 0; i < N; ++i) data[i] *= v; return *this; }
//	const Vector& operator /= (const TYPE   v) { for (int i = 0; i < N; ++i) data[i] /= v; return *this; }
//
//	//!@name Test operators
//	bool operator == (const Vector& p) const { for (int i = 0; i < N; ++i) if (data[i] != p.data[i]) return false; return true; }
//	bool operator != (const Vector& p) const { for (int i = 0; i < N; ++i) if (data[i] != p.data[i]) return true; return false; }
//
//	//!@name Access operators
//	TYPE& operator [] (int i) { return data[i]; }
//	TYPE  operator [] (int i) const { return data[i]; }
//
//	//!@name Dot product
//	TYPE Dot(const Vector &p) const { Vector r = operator*(p); return r.Sum(); }	//!< Dot product
//	TYPE operator % (const Vector &p) const { return Dot(p); }