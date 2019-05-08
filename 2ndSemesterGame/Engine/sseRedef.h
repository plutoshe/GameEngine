#include "VectorUtil.h"
#include "Matrix4x4.h"


#ifdef SSEOP 
	class Matrix4f: Matrix4x4<float> {
		friend Matrix4f operator*(const Matrix4f &v, const Matrix4f &p) {
			__m128 row[4]; 
		    __m128 col[4];
		    for (int i = 0; i < 4; i++) {
		        row[i] = _mm_set_ps(mop1[i][0], mop1[i][1], mop1[i][2], mop1[i][3]);
		        col[i] = _mm_set_ps(mop2[0][i], mop2[1][i], mop2[2][i], mop2[3][i]);
		    }
		    // float result[4]; 
		    for (int i = 0; i < 4; i++)
		        for (int j = 0; j < 4; j++) {
		            __m128 trans = _mm_mul_ps(row[i], col[j]); 
		            _mm_storeu_ps(result, trans);
		            mop4[i][j] = result[0] + result[1] + result[2] + result[3];
		        }
		}
	}
	class Vector3f;
	class Vector3f;
	class Vector4f {
		union {
			struct  
			{
				float x, y, z, w;
			},
			__m128 dat;
		}

		Vector4f() { Clear();  }
		Vector4f(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
		Vector4f(__m128 _dat) { dat = _dat; }
		void operator=(const Vector4f& p) { this->Equal(p); }
		void operator=(const Vector3f &p) { this->Equal(p); }
		void operator=(const Vector2f &p) { this->Equal(p); }
		Vector4f(const Vector4f& p) { this->Equal(p); }
		Vector4f(const Vector3f &p) { this->Equal(p); }
		Vector4f(const Vector2f &p) { this->Equal(p); }
		void Equal(const Vector4f &p) { dat = p.dat; }
		void Equal(const Vector3f &p) { dat = p.dat; }
		void Equal(const Vector2f &p) { dat = p.dat }


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
		Vector4f operator - (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_add_ps(dat, pdat)); }
		Vector4f operator * (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_add_ps(dat, pdat)); }
		Vector4f operator / (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector4f(_mm_add_ps(dat, pdat)); }

		//!@name Assignment operators

		const Vector4f& operator += (const Vector4f &p) { dat = _mm_add_ps(dat, p.dat); return *this + x; }
		const Vector4f& operator -= (const Vector4f &p) { dat = _mm_sub_ps(dat, p.dat); return *this; }
		const Vector4f& operator *= (const Vector4f &p) { dat = _mm_mul_ps(dat, p.dat); return *this; }
		const Vector4f& operator /= (const Vector4f &p) { dat = _mm_div_ps(dat, p.dat); return *this; }
		const Vector4f& operator += (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_add_ps(dat, pdat); return *this; }
		const Vector4f& operator -= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_sub_ps(dat, pdat); return *this; }
		const Vector4f& operator *= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_mul_ps(dat, pdat); return *this; }
		const Vector4f& operator /= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_div_ps(dat, pdat); return *this; }


		bool operator==(const Vector4f& p) const { return (dat == p.dat); }
		bool operator!=(const Vector4f& p) const { return (dat != p.dat); }

		float&		operator [] (int i) { return Element(i); }
		const float& operator [] (int i) const { return Element(i); }

		float&       Element(int i) { return (&x)[i]; }
		const float& Element(int i) const { return (&x)[i]; }

		float*       Data() { return &x; }
		const float* Data() const { return &x; }

		void Clear() { dat = 0; } 
		
		float Length() { return sqrt(x * x + y * y + z * z + w * w); }
	}

	class Vector3f {
		union {
			struct  
			{
				float x, y, z;
			},
			__m128 dat;
		}

		Vector3f() { Clear();  }
		Vector3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z;}
		Vector3f(__m128 _dat) { dat = _dat; }
		void operator=(const Vector2f& p) { this->Equal(p); }
		void operator=(const Vector3f &p) { this->Equal(p); }
		void operator=(const Vector4f &p) { this->Equal(p); }
		Vector3f(const Vector2f& p) { this->Equal(p); }
		Vector3f(const Vector3f &p) { this->Equal(p); }
		Vector3f(const Vector4f &p) { this->Equal(p); }
		void Equal(const Vector2f &p) { dat = p.dat; }
		void Equal(const Vector3f &p) { dat = p.dat; }
		void Equal(const Vector4f &p) { x = p.x; y = p.y; z = p.z; }


		~Vector3f() {}

		inline friend std::ostream& operator<<(std::ostream& os, const Vector3f &p) {
			os << "(" << p.x << "," << p.y << "," << p.z << "," << p.w << ")";
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
		Vector3f operator - (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }
		Vector3f operator * (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }
		Vector3f operator / (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }

		//!@name Assignment operators

		const Vector3f& operator += (const Vector3f &p) { dat = _mm_add_ps(dat, p.dat); return *this + x; }
		const Vector3f& operator -= (const Vector3f &p) { dat = _mm_sub_ps(dat, p.dat); return *this; }
		const Vector3f& operator *= (const Vector3f &p) { dat = _mm_mul_ps(dat, p.dat); return *this; }
		const Vector3f& operator /= (const Vector3f &p) { dat = _mm_div_ps(dat, p.dat); return *this; }
		const Vector3f& operator += (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_add_ps(dat, pdat); return *this; }
		const Vector3f& operator -= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_sub_ps(dat, pdat); return *this; }
		const Vector3f& operator *= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_mul_ps(dat, pdat); return *this; }
		const Vector3f& operator /= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_div_ps(dat, pdat); return *this; }


		bool operator==(const Vector3f& p) const { return (dat == p.dat); }
		bool operator!=(const Vector3f& p) const { return (dat != p.dat); }

		float&		operator [] (int i) { return Element(i); }
		const float& operator [] (int i) const { return Element(i); }

		float&       Element(int i) { return (&x)[i]; }
		const float& Element(int i) const { return (&x)[i]; }

		float*       Data() { return &x; }
		const float* Data() const { return &x; }

		void Clear() { dat = 0; } 
		
		float Length() { return sqrt(x * x + y * y + z * z + w * w); }
	}

	class Vector3f {
		union {
			struct  
			{
				float x, y;
			},
			__m128 dat;
		}

		Vector3f() { Clear();  }
		Vector3f(float _x, float _y) { x = _x; y = _y;}
		Vector3f(__m128 _dat) { dat = _dat; }
		void operator=(const Vector3f& p) { this->Equal(p); }
		void operator=(const Vector3f &p) { this->Equal(p); }
		void operator=(const Vector4f &p) { this->Equal(p); }
		Vector3f(const Vector3f& p) { this->Equal(p); }
		Vector3f(const Vector3f &p) { this->Equal(p); }
		Vector3f(const Vector4f &p) { this->Equal(p); }
		void Equal(const Vector3f &p) { dat = p.dat; }
		void Equal(const Vector3f &p) { x = p.x; y = p.y; }
		void Equal(const Vector4f &p) { x = p.x; y = p.y; }


		~Vector3f() { Clear(); }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector3f &p) {
			os << "(" << p.x << "," << p.y << ")";
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
		Vector3f operator - (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }
		Vector3f operator * (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }
		Vector3f operator / (const float v) const { __m128 pdat = _mm_set_ps(v, v, v, v); return Vector3f(_mm_add_ps(dat, pdat)); }

		//!@name Assignment operators

		const Vector3f& operator += (const Vector3f &p) { dat = _mm_add_ps(dat, p.dat); return *this + x; }
		const Vector3f& operator -= (const Vector3f &p) { dat = _mm_sub_ps(dat, p.dat); return *this; }
		const Vector3f& operator *= (const Vector3f &p) { dat = _mm_mul_ps(dat, p.dat); return *this; }
		const Vector3f& operator /= (const Vector3f &p) { dat = _mm_div_ps(dat, p.dat); return *this; }
		const Vector3f& operator += (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_add_ps(dat, pdat); return *this; }
		const Vector3f& operator -= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_sub_ps(dat, pdat); return *this; }
		const Vector3f& operator *= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_mul_ps(dat, pdat); return *this; }
		const Vector3f& operator /= (const float v) { __m128 pdat = _mm_set_ps(v, v, v, v); dat = _mm_div_ps(dat, pdat); return *this; }


		bool operator==(const Vector3f& p) const { return (dat == p.dat); }
		bool operator!=(const Vector3f& p) const { return (dat != p.dat); }

		float&		operator [] (int i) { return Element(i); }
		const float& operator [] (int i) const { return Element(i); }

		float&       Element(int i) { return (&x)[i]; }
		const float& Element(int i) const { return (&x)[i]; }

		float*       Data() { return &x; }
		const float* Data() const { return &x; }

		void Clear() { dat = 0; } 
		
		float Length() { return sqrt(x * x + y * y + z * z + w * w); }
	}	
#else
	typedef Matrix4x4<float> Matrix4f;
	typedef Vector4D<float> Vector3f;
	typedef Vector2D<float> Vector3f;
	typedef Vector3D<float> Vector3f;
#endif

