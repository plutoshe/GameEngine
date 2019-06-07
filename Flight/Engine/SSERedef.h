#pragma once

//#define SSEOP
#include "VectorUtil.h"
#include "Matrix4x4.h"


#ifdef SSEOP 
	#include <emmintrin.h>
	class Vector2f;
	class Vector3f;
	class Vector4f: public Vector4D<float> {
	public:
		Vector4f() { Clear();  }
		Vector4f(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
		Vector4f(__m128 _dat) { dat = _dat; }

		void Equal(const Vector4f &p) { dat = p.dat; }
		void operator=(const Vector4f& p) { this->Equal(p); }
		Vector4f(const Vector4f& p) { this->Equal(p); }

		void Equal(const Vector3f &p);
		void Equal(const Vector2f &p);
		void operator=(const Vector3f &p);
		void operator=(const Vector2f &p);
		Vector4f(const Vector3f &p);
		Vector4f(const Vector2f &p);
		
		~Vector4f() { Clear(); }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector4f &p) {
			os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
			return os;
		}

		friend Vector4f operator +(const float v, const Vector4f &p) {
			return p + v;
		}
		friend Vector4f operator -(const float v, const Vector4f &p) {
			return p * -1 + v;
		}
		friend Vector4f operator *(const float v, const Vector4f &p) {
			return p * v;
		}

		Vector4f operator + (const Vector4f &p) const { return Vector4f(_mm_add_ps(dat, p.dat)); }
		Vector4f operator - (const Vector4f &p) const { return Vector4f(_mm_sub_ps(dat, p.dat)); }
		Vector4f operator * (const Vector4f &p) const { return Vector4f(_mm_mul_ps(dat, p.dat)); }
		Vector4f operator / (const Vector4f &p) const { return Vector4f(_mm_div_ps(dat, p.dat)); }
		Vector4f operator + (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_add_ps(dat, pdat)); }
		Vector4f operator - (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_sub_ps(dat, pdat)); }
		Vector4f operator * (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_mul_ps(dat, pdat)); }
		Vector4f operator / (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_div_ps(dat, pdat)); }

		//!@name Assignment operators

		const Vector4f& operator += (const Vector4f &p) { dat = _mm_add_ps(dat, p.dat); return *this; }
		const Vector4f& operator -= (const Vector4f &p) { dat = _mm_sub_ps(dat, p.dat); return *this; }
		const Vector4f& operator *= (const Vector4f &p) { dat = _mm_mul_ps(dat, p.dat); return *this; }
		const Vector4f& operator /= (const Vector4f &p) { dat = _mm_div_ps(dat, p.dat); return *this; }
		const Vector4f& operator += (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_add_ps(dat, pdat); return *this; }
		const Vector4f& operator -= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_sub_ps(dat, pdat); return *this; }
		const Vector4f& operator *= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_mul_ps(dat, pdat); return *this; }
		const Vector4f& operator /= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_div_ps(dat, pdat); return *this; }


		bool operator==(const Vector4f& p) const { return (x == p.x) && (y == p.y) && (z == p.z) && (w == p.w); }
		bool operator!=(const Vector4f& p) const { return (x != p.x) || (y != p.y) || (z != p.z) || (w != p.w); }

		float&		operator [] (int i) { return Element(i); }
		const float& operator [] (int i) const { return Element(i); }

		float&       Element(int i) { return (&x)[i]; }
		const float& Element(int i) const { return (&x)[i]; }

		float*       Data() { return &x; }
		const float* Data() const { return &x; }

		void Clear() { x = y = z = w = 0; }
		
		float Length() { return sqrt(x * x + y * y + z * z + w * w); }
		Vector4f Dot(const Vector4f& p) const {
			return Vector4f(_mm_mul_ps(dat,p.dat));
		}
	};

	class Vector3f: public Vector3D<float> {
	public:

		Vector3f() { Clear();  }
		Vector3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z;}
		Vector3f(__m128 _dat) { dat = _dat; }
		void Vector3f::Equal(const Vector3f &p) { dat = p.dat; }
		void Vector3f::operator=(const Vector3f &p) { this->Equal(p); }
		Vector3f::Vector3f(const Vector3f &p) { this->Equal(p); }

		void operator=(const Vector2f& p);
		void operator=(const Vector4f &p);
		Vector3f(const Vector2f& p);
		Vector3f(const Vector4f &p);
		void Equal(const Vector2f &p);
		void Equal(const Vector4f &p);

		~Vector3f() {}

		inline friend std::ostream& operator<<(std::ostream& os, const Vector3f &p) {
			os << "(" << p.x << "," << p.y << "," << p.z << ")";
			return os;
		}

		friend Vector3f operator +(const float v, const Vector3f &p) {
			return p + v;
		}
		friend Vector3f operator -(const float v, const Vector3f &p) {
			return p * -1 + v;
		}
		friend Vector3f operator *(const float v, const Vector3f &p) {
			return p * v;
		}

		Vector3f operator + (const Vector3f &p) const { return Vector3f(_mm_add_ps(dat, p.dat)); }
		Vector3f operator - (const Vector3f &p) const { return Vector3f(_mm_sub_ps(dat, p.dat)); }
		Vector3f operator * (const Vector3f &p) const { return Vector3f(_mm_mul_ps(dat, p.dat)); }
		Vector3f operator / (const Vector3f &p) const { return Vector3f(_mm_div_ps(dat, p.dat)); }
		Vector3f operator + (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }
		Vector3f operator - (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_sub_ps(dat, pdat)); }
		Vector3f operator * (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_mul_ps(dat, pdat)); }
		Vector3f operator / (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_div_ps(dat, pdat)); }

		//!@name Assignment operators

		const Vector3f& operator += (const Vector3f &p) { dat = _mm_add_ps(dat, p.dat); return *this; }
		const Vector3f& operator -= (const Vector3f &p) { dat = _mm_sub_ps(dat, p.dat); return *this; }
		const Vector3f& operator *= (const Vector3f &p) { dat = _mm_mul_ps(dat, p.dat); return *this; }
		const Vector3f& operator /= (const Vector3f &p) { dat = _mm_div_ps(dat, p.dat); return *this; }
		const Vector3f& operator += (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_add_ps(dat, pdat); return *this; }
		const Vector3f& operator -= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_sub_ps(dat, pdat); return *this; }
		const Vector3f& operator *= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_mul_ps(dat, pdat); return *this; }
		const Vector3f& operator /= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_div_ps(dat, pdat); return *this; }


		bool operator==(const Vector3f& p) const { return (x == p.x) && (y == p.y) && (z == p.z); }
		bool operator!=(const Vector3f& p) const { return (x != p.x) || (y != p.y) || (z != p.z); }

		float&		operator [] (int i) { return Element(i); }
		const float& operator [] (int i) const { return Element(i); }

		float&       Element(int i) { return (&x)[i]; }
		const float& Element(int i) const { return (&x)[i]; }

		float*       Data() { return &x; }
		const float* Data() const { return &x; }

		void Clear() { x = y = z = 0; }
		
		float Length() { return sqrt(x * x + y * y + z * z); }

		Vector3f Dot(const Vector3f& p) const {
			return Vector3f(_mm_mul_ps(dat, p.dat));
		}
	};

	class Vector2f : public Vector2D<float> {
	public:

		Vector2f() { Clear(); }
		Vector2f(float _x, float _y) { x = _x; y = _y; }
		Vector2f(__m128 _dat) { dat = _dat; }
		void Vector2f::Equal(const Vector2f &p) { dat = p.dat; }
		void Vector2f::operator=(const Vector2f& p) { this->Equal(p); }
		Vector2f::Vector2f(const Vector2f& p) { this->Equal(p); }

		void operator=(const Vector3f &p);
		void operator=(const Vector4f &p);
		Vector2f(const Vector3f &p);
		Vector2f(const Vector4f &p);
		void Equal(const Vector3f &p);
		void Equal(const Vector4f &p);
		

		~Vector2f() { Clear(); }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector2f &p) {
			os << "(" << p.x << "," << p.y << ")";
			return os;
		}

		friend Vector2f operator +(const float v, const Vector2f &p) {
			return p + v;
		}
		friend Vector2f operator -(const float v, const Vector2f &p) {
			return p * -1 + v;
		}
		friend Vector2f operator *(const float v, const Vector2f &p) {
			return p * v;
		}

		Vector2f operator + (const Vector2f &p) const { return Vector2f(_mm_add_ps(dat, p.dat)); }
		Vector2f operator - (const Vector2f &p) const { return Vector2f(_mm_sub_ps(dat, p.dat)); }
		Vector2f operator * (const Vector2f &p) const { return Vector2f(_mm_mul_ps(dat, p.dat)); }
		Vector2f operator / (const Vector2f &p) const { return Vector2f(_mm_div_ps(dat, p.dat)); }
		Vector2f operator + (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector2f(_mm_add_ps(dat, pdat)); }
		Vector2f operator - (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector2f(_mm_sub_ps(dat, pdat)); }
		Vector2f operator * (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector2f(_mm_mul_ps(dat, pdat)); }
		Vector2f operator / (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector2f(_mm_div_ps(dat, pdat)); }

		//!@name Assignment operators

		const Vector2f& operator += (const Vector2f &p) { dat = _mm_add_ps(dat, p.dat); return *this; }
		const Vector2f& operator -= (const Vector2f &p) { dat = _mm_sub_ps(dat, p.dat); return *this; }
		const Vector2f& operator *= (const Vector2f &p) { dat = _mm_mul_ps(dat, p.dat); return *this; }
		const Vector2f& operator /= (const Vector2f &p) { dat = _mm_div_ps(dat, p.dat); return *this; }
		const Vector2f& operator += (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_add_ps(dat, pdat); return *this; }
		const Vector2f& operator -= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_sub_ps(dat, pdat); return *this; }
		const Vector2f& operator *= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_mul_ps(dat, pdat); return *this; }
		const Vector2f& operator /= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_div_ps(dat, pdat); return *this; }


		bool operator==(const Vector2f& p) const { return (x == p.x) && (y == p.y); }
		bool operator!=(const Vector2f& p) const { return (x != p.x) || (y != p.y); }

		float&		operator [] (int i) { return Element(i); }
		const float& operator [] (int i) const { return Element(i); }

		float&       Element(int i) { return (&x)[i]; }
		const float& Element(int i) const { return (&x)[i]; }

		float*       Data() { return &x; }
		const float* Data() const { return &x; }

		void Clear() { x = y = 0; }

		float Length() { return sqrt(x * x + y * y); }
		Vector2f Dot(const Vector2f& p) const {
			return Vector2f(_mm_mul_ps(dat, p.dat));
		}
	};

	class Matrix4f : public Matrix4x4<float> {
	public:
		Matrix4f(
			float M11, float M12, float M13, float M14,
			float M21, float M22, float M23, float M24,
			float M31, float M32, float M33, float M34,
			float M41, float M42, float M43, float M44) {
			(*this)[0][0] = M11; (*this)[0][1] = M12; (*this)[0][2] = M13; (*this)[0][3] = M14;
			(*this)[1][0] = M21; (*this)[1][1] = M22; (*this)[1][2] = M23; (*this)[1][3] = M24;
			(*this)[2][0] = M31; (*this)[2][1] = M32; (*this)[2][2] = M33; (*this)[2][3] = M34;
			(*this)[3][0] = M41; (*this)[3][1] = M42; (*this)[3][2] = M43; (*this)[3][3] = M44;
		}
		Matrix4f() {  }
		//Matrix4x4<float>::Clear();
		Matrix4f(const Matrix4x4 &p) {
			PS_DATCOPY(this->data, p.data, 16);
		}
		Matrix4f(const Matrix4f &p) {
			PS_DATCOPY(this->data, p.data, 16);
		}
		using Matrix4x4<float>::operator=;

		void operator=(const Matrix4x4 &p) {
			PS_DATCOPY(this->data, p.data, 16);
		}
		void operator=(const Matrix4f &p) {
			PS_DATCOPY(this->data, p.data, 16);
		}
		friend Matrix4f operator*(const Matrix4f &mop1, const Matrix4f &mop2) {
			__m128 row[4];
			__m128 col[4];
			for (int i = 0; i < 4; i++) {
				row[i] = _mm_set_ps(mop1[i][0], mop1[i][1], mop1[i][2], mop1[i][3]);
				col[i] = _mm_set_ps(mop2[0][i], mop2[1][i], mop2[2][i], mop2[3][i]);
			}
			Matrix4f r;
			float result[4];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					__m128 trans = _mm_mul_ps(row[i], col[j]);
					_mm_storeu_ps(result, trans);
					r[i][j] = result[0] + result[1] + result[2] + result[3];
				}
			return r;
		}

		friend Vector4f operator *(const Matrix4f& v, const Vector4f &p) {
			Vector4f r;
			r.Clear();
			__m128 mp1[4];
			__m128 mp2 = _mm_set_ps(p[0], p[1], p[2], p[3]);

			for (int i = 0; i < 4; i++) {
				mp1[i] = _mm_set_ps(v[i][0], v[i][1], v[i][2], v[i][3]);
			}

			float result[4];
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 1; j++) {
					/*for (int k = 0; k < 4; k++)
						r[i] += v[i][k] * p[k];*/
					__m128 trans = _mm_mul_ps(mp1[i], mp2);
					_mm_storeu_ps(result, trans);
					r[i] = result[0] + result[1] + result[2] + result[3];
				}

			return r;
		}

		friend Vector4f operator *(const Vector4f &p, const Matrix4f& v) {
			Vector4f r;
			r.Clear();
			__m128 mp2[4];
			__m128 mp1 = _mm_set_ps(p[0], p[1], p[2], p[3]);

			for (int i = 0; i < 4; i++) {
				mp2[i] = _mm_set_ps(v[0][i], v[1][i], v[2][i], v[3][i]);
			}
			
			float result[4];
			for (int i = 0; i < 1; i++)
				for (int j = 0; j < 4; j++) {
				/*	for (int k = 0; k < 4; k++) {
						r[j] += p[k] * v[k][j];
					}*/
					__m128 trans = _mm_mul_ps(mp1, mp2[j]);
					_mm_storeu_ps(result, trans);
					r[j] = result[0] + result[1] + result[2] + result[3];
				}

			return r;
		}

		static Matrix4f GetTranslationMatrix(const Vector4f &move) {
			return Matrix4x4<float>::GetTranslationMatrix(move);
		}

		static Matrix4f GetRotationXMatrix(float angle) {
			return Matrix4x4<float>::GetRotationXMatrix(angle);
		}

		static Matrix4f GetRotationYMatrix(float angle) {
			return Matrix4x4<float>::GetRotationYMatrix(angle);
		}

		static Matrix4f GetRotationZMatrix(float angle) {
			return Matrix4x4<float>::GetRotationZMatrix(angle);
		}

		static Matrix4f GetRotationMatrix(Vector3f angles) {
			return Matrix4x4<float>::GetRotationMatrix(angles);
		}

		static Matrix4f GetRotationMatrix(float angleX, float angleY, float angleZ) {
			return Matrix4x4<float>::GetRotationMatrix(angleX, angleY, angleZ);
		}

		Matrix4f Inversion() {
			return Matrix4x4<float>::Inversion();
		}

	};
		
#else
	typedef Vector2D<float> Vector2f;
	typedef Vector3D<float> Vector3f;
	typedef Vector4D<float> Vector4f;

	typedef Matrix4x4<float> Matrix4f;
#endif
	

