#pragma once


#include <cmath>
#include <limits>

#include "../pbrt.h"


namespace pbrt
{

	inline Float Lerp(Float t, Float v1, Float v2) { return (1 - t) * v1 + t * v2;}

	template <typename T>
	inline bool isNaN(const T x)
	{
		return std::isnan(x);
	}

	template <>
	inline bool isNaN(const int x) {
		return false;
	}


	template<typename T>
	class Point2;

	template<typename T>
	class Point3;

	template<typename T>
	inline Point2<T> Lerp(Float t, Point2<T> v1, Point2<T> v2)
	{
		return (1 - t) * v1 + t * v2;
	}


	template <typename T>
	Point3<T> Lerp(Float t, const Point3<T> &p0, const Point3<T> &p1) {
		return (1 - t) * p0 + t * p1;
	}


	template <typename T>
	class Vector2
	{
	public:
		// Vector2 Public Data
		T x = T();
		T y = T();

		Vector2() {}

		Vector2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }

		explicit Vector2(const Point2<T> &p)
			:x(p.x), y(p.y)
		{
			DCHECK(!HasNaNs());
		}
		explicit Vector2(const Point3<T> &p)
			:x(p.x), y(p.y)
		{
			DCHECK(!HasNaNs());
		}

#ifndef NDEBUG
		// The default versions of these are fine for release builds; for debug
		// we define them so that we can add the Assert checks.
		Vector2(const Vector2<T> &v) {
			DCHECK(!v.HasNaNs());
			x = v.x;
			y = v.y;
		}
		Vector2<T> &operator=(const Vector2<T> &v) {
			DCHECK(!v.HasNaNs());
			x = v.x;
			y = v.y;
			return *this;
		}
#endif  // !NDEBUG

		bool HasNaNs() const { return isNaN(x) || isNaN(y); }


		Vector2<T> operator+ (const Vector2<T> &v) const
		{
			DCHECK(!v.HasNaNs());
			return Vector2<T>(x + v.x, y + v.y);
		}

		Vector2<T> &operator+=(const Vector2<T> &v) {
			DCHECK(!v.HasNaNs());
			x += v.x;
			y += v.y;
			return *this;
		}
		Vector2<T> operator-(const Vector2<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Vector2(x - v.x, y - v.y);
		}

		Vector2<T> &operator-=(const Vector2<T> &v) {
			DCHECK(!v.HasNaNs());
			x -= v.x;
			y -= v.y;
			return *this;
		}
		bool operator==(const Vector2<T> &v) const { return x == v.x && y == v.y; }
		bool operator!=(const Vector2<T> &v) const { return x != v.x || y != v.y; }
		//template <typename U>
		//Vector2<T> operator*(U f) const {
		//	return Vector2<T>(f * x, f * y);
		//}

		//template <typename U>
		//Vector2<T> &operator*=(U f) {
		//	DCHECK(!isNaN(f));
		//	x *= f;
		//	y *= f;
		//	return *this;
		//}

		Vector2<T> &operator* (T v) const {
			DCHECK(!isNaN(v));
			return Vector2<T>(x * v, y * v);
		}

		Vector2<T> &operator*= (T v) const {
			DCHECK(!isNaN(v));
			x *= v;
			y *= v;
			return *this;
		}

		Vector2<T> &operator/ (T v) const {
			DCHECK(!isNaN(v));
			DCHECK(v != 0);
			T inv = 1 / v;
			return Vector2<T>(x * inv, y * inv);
		}

		Vector2<T> &operator/= (T v) const {
			DCHECK(!isNaN(v));
			DCHECK(v != 0);
			T inv = 1 / v;
			x *= inv;
			y *= inv;
			return *this;
		}

		Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
		T operator[](int i) const {
			DCHECK(i >= 0 && i <= 1);
			if (i == 0) return x;
			return y;
		}

		T &operator[](int i) {
			DCHECK(i >= 0 && i <= 1);
			if (i == 0) return x;
			return y;
		}

		inline Float LengthSquared() const { return x * x + y * y; }
		inline Float Length() const { return std::sqrt(LengthSquared()); }

	};


	template<typename T>
	class Normal3;

	template <typename T>
	class Vector3
	{
	public:
		// Vector2 Public Data
		T x = T();
		T y = T();
		T z = T();


		// Vector3 Public Methods
		T operator[](int i) const {
			DCHECK(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}
		T &operator[](int i) {
			DCHECK(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}
		Vector3() { x = y = z = 0; }
		Vector3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
		bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
		explicit Vector3(const Point3<T> &p)
			:x(p.x), y(p.y), z(p.z)
		{

		}
#ifndef NDEBUG
		// The default versions of these are fine for release builds; for debug
		// we define them so that we can add the Assert checks.
		Vector3(const Vector3<T> &v) {
			DCHECK(!v.HasNaNs());
			x = v.x;
			y = v.y;
			z = v.z;
		}

		Vector3<T> &operator=(const Vector3<T> &v) {
			DCHECK(!v.HasNaNs());
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}
#endif  // !NDEBUG
		Vector3<T> operator+(const Vector3<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Vector3(x + v.x, y + v.y, z + v.z);
		}
		Vector3<T> &operator+=(const Vector3<T> &v) {
			DCHECK(!v.HasNaNs());
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Vector3<T> operator-(const Vector3<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Vector3(x - v.x, y - v.y, z - v.z);
		}
		Vector3<T> &operator-=(const Vector3<T> &v) {
			DCHECK(!v.HasNaNs());
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		bool operator==(const Vector3<T> &v) const {
			return x == v.x && y == v.y && z == v.z;
		}
		bool operator!=(const Vector3<T> &v) const {
			return x != v.x || y != v.y || z != v.z;
		}
		Vector3<T> operator*(T s) const {
			DCHECK(!isNaN(s));
			return Vector3<T>(s * x, s * y, s * z);
		}
		Vector3<T> &operator*=(T s) {
			DCHECK(!isNaN(s));
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		Vector3<T> operator/(T f) const {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);
			T inv = 1 / f;
			return Vector3<T>(x * inv, y * inv, z * inv);
		}

		Vector3<T> &operator/=(T f) {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);
			T inv = 1 / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}
		Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
		Float LengthSquared() const { return x * x + y * y + z * z; }
		Float Length() const { return std::sqrt(LengthSquared()); }
		explicit Vector3(const Normal3<T> &n)
			: x(n.x), y(n.y), z(n.z)
		{
			DCHECK(!n.HasNaNs());
		}
	};



	typedef Vector2<Float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector3<Float> Vector3f;
	typedef Vector3<int> Vector3i;


	template <typename T>
	class Point2
	{
	public:
		// Vector2 Public Data
		T x = T();
		T y = T();


		// Point2 Public Methods
		explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) { DCHECK(!HasNaNs()); }
		Point2() { x = y = 0; }
		Point2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }

		template <typename U>
		explicit Point2(const Point2<U> &p) {
			x = (T)p.x;
			y = (T)p.y;
			DCHECK(!HasNaNs());
		}

		template <typename U>
		explicit Point2(const Vector2<U> &p) {
			x = (T)p.x;
			y = (T)p.y;
			DCHECK(!HasNaNs());
		}

		template <typename U>
		explicit operator Vector2<U>() const {
			return Vector2<U>(x, y);
		}

#ifndef NDEBUG
		Point2(const Point2<T> &p) {
			DCHECK(!p.HasNaNs());
			x = p.x;
			y = p.y;
		}

		Point2<T> &operator=(const Point2<T> &p) {
			DCHECK(!p.HasNaNs());
			x = p.x;
			y = p.y;
			return *this;
		}
#endif  // !NDEBUG
		Point2<T> operator+(const Vector2<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Point2<T>(x + v.x, y + v.y);
		}

		Point2<T> &operator+=(const Vector2<T> &v) {
			DCHECK(!v.HasNaNs());
			x += v.x;
			y += v.y;
			return *this;
		}
		Vector2<T> operator-(const Point2<T> &p) const {
			DCHECK(!p.HasNaNs());
			return Vector2<T>(x - p.x, y - p.y);
		}

		Point2<T> operator-(const Vector2<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Point2<T>(x - v.x, y - v.y);
		}
		Point2<T> operator-() const { return Point2<T>(-x, -y); }
		Point2<T> &operator-=(const Vector2<T> &v) {
			DCHECK(!v.HasNaNs());
			x -= v.x;
			y -= v.y;
			return *this;
		}
		Point2<T> &operator+=(const Point2<T> &p) {
			DCHECK(!p.HasNaNs());
			x += p.x;
			y += p.y;
			return *this;
		}
		Point2<T> operator+(const Point2<T> &p) const {
			DCHECK(!p.HasNaNs());
			return Point2<T>(x + p.x, y + p.y);
		}

		Point2<T> &operator* (T v) const {
			DCHECK(!isNaN(v));
			return Point2<T>(x * v, y * v);
		}

		Point2<T> &operator*= (T v) const {
			DCHECK(!isNaN(v));
			x *= v;
			y *= v;
			return *this;
		}

		Point2<T> operator/(T f) const {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);

			T inv = 1 / f;
			return Point2<T>(inv * x, inv * y);
		}

		Point2<T> &operator/=(T f) {
			DCHECK(f != 0);
			T inv = 1 / f;
			x *= inv;
			y *= inv;
			return *this;
		}
		T operator[](int i) const {
			DCHECK(i >= 0 && i <= 1);
			if (i == 0) return x;
			return y;
		}

		T &operator[](int i) {
			DCHECK(i >= 0 && i <= 1);
			if (i == 0) return x;
			return y;
		}
		bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }
		bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }
		bool HasNaNs() const { return isNaN(x) || isNaN(y); }
	};


	template <typename T>
	class Point3
	{
	public:
		// Vector2 Public Data
		T x = T();
		T y = T();
		T z = T();

		// Point3 Public Methods
		Point3() { x = y = z = 0; }
		Point3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
		template <typename U>
		explicit Point3(const Point3<U> &p)
			: x((T)p.x), y((T)p.y), z((T)p.z) {
			DCHECK(!HasNaNs());
		}
		template <typename U>
		explicit operator Vector3<U>() const {
			return Vector3<U>(x, y, z);
		}
#ifndef NDEBUG
		Point3(const Point3<T> &p) {
			DCHECK(!p.HasNaNs());
			x = p.x;
			y = p.y;
			z = p.z;
		}

		Point3<T> &operator=(const Point3<T> &p) {
			DCHECK(!p.HasNaNs());
			x = p.x;
			y = p.y;
			z = p.z;
			return *this;
		}
#endif  // !NDEBUG
		Point3<T> operator+(const Vector3<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Point3<T>(x + v.x, y + v.y, z + v.z);
		}
		Point3<T> &operator+=(const Vector3<T> &v) {
			DCHECK(!v.HasNaNs());
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}
		Vector3<T> operator-(const Point3<T> &p) const {
			DCHECK(!p.HasNaNs());
			return Vector3<T>(x - p.x, y - p.y, z - p.z);
		}
		Point3<T> operator-(const Vector3<T> &v) const {
			DCHECK(!v.HasNaNs());
			return Point3<T>(x - v.x, y - v.y, z - v.z);
		}
		Point3<T> &operator-=(const Vector3<T> &v) {
			DCHECK(!v.HasNaNs());
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}
		Point3<T> &operator+=(const Point3<T> &p) {
			DCHECK(!p.HasNaNs());
			x += p.x;
			y += p.y;
			z += p.z;
			return *this;
		}
		Point3<T> operator+(const Point3<T> &p) const {
			DCHECK(!p.HasNaNs());
			return Point3<T>(x + p.x, y + p.y, z + p.z);
		}
		Point3<T> operator*(T s) const {
			DCHECK(!isNaN(s));
			return Point3<T>(s * x, s * y, s * z);
		}
		Point3<T> &operator*=(T s) {
			DCHECK(!isNaN(s));
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		Point3<T> operator/(T f) const {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);
			T inv = 1 / f;
			return Point3<T>(x * inv, y * inv, z * inv);
		}

		Point3<T> &operator/=(T f) {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);
			T inv = 1 / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}
		T operator[](int i) const {
			DCHECK(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		T &operator[](int i) {
			DCHECK(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}
		bool operator==(const Point3<T> &p) const {
			return x == p.x && y == p.y && z == p.z;
		}
		bool operator!=(const Point3<T> &p) const {
			return x != p.x || y != p.y || z != p.z;
		}
		bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
		Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }
	};


	typedef Point2<Float> Point2f;
	typedef Point2<int> Point2i;
	typedef Point3<Float> Point3f;
	typedef Point3<int> Point3i;


	// Normal Declarations
	// 必须规范化
	template <typename T>
	class Normal3 {
	public:
		// Normal3 Public Methods
		Normal3() { x = y = z = 0; }
		Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { DCHECK(!HasNaNs()); }
		Normal3<T> operator-() const { return Normal3(-x, -y, -z); }
		Normal3<T> operator+(const Normal3<T> &n) const {
			DCHECK(!n.HasNaNs());
			return Normal3<T>(x + n.x, y + n.y, z + n.z);
		}

		Normal3<T> &operator+=(const Normal3<T> &n) {
			DCHECK(!n.HasNaNs());
			x += n.x;
			y += n.y;
			z += n.z;
			return *this;
		}
		Normal3<T> operator-(const Normal3<T> &n) const {
			DCHECK(!n.HasNaNs());
			return Normal3<T>(x - n.x, y - n.y, z - n.z);
		}

		Normal3<T> &operator-=(const Normal3<T> &n) {
			DCHECK(!n.HasNaNs());
			x -= n.x;
			y -= n.y;
			z -= n.z;
			return *this;
		}
		bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

		Normal3<T> operator*(T s) const {
			DCHECK(!isNaN(s));
			return Normal3<T>(s * x, s * y, s * z);
		}
		Normal3<T> &operator*=(T s) {
			DCHECK(!isNaN(s));
			x *= s;
			y *= s;
			z *= s;
			return *this;
		}
		Normal3<T> operator/(T f) const {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);
			T inv = 1 / f;
			return Normal3<T>(x * inv, y * inv, z * inv);
		}

		Normal3<T> &operator/=(T f) {
			DCHECK(!isNaN(f));
			DCHECK(f != 0);
			T inv = 1 / f;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		Float LengthSquared() const { return x * x + y * y + z * z; }
		Float Length() const { return std::sqrt(LengthSquared()); }

#ifndef NDEBUG
		Normal3<T>(const Normal3<T> &n) {
			DCHECK(!n.HasNaNs());
			x = n.x;
			y = n.y;
			z = n.z;
		}

		Normal3<T> &operator=(const Normal3<T> &n) {
			DCHECK(!n.HasNaNs());
			x = n.x;
			y = n.y;
			z = n.z;
			return *this;
		}
#endif  // !NDEBUG
		explicit Normal3<T>(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {
			DCHECK(!v.HasNaNs());
		}
		bool operator==(const Normal3<T> &n) const {
			return x == n.x && y == n.y && z == n.z;
		}
		bool operator!=(const Normal3<T> &n) const {
			return x != n.x || y != n.y || z != n.z;
		}

		T operator[](int i) const {
			DCHECK(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		T &operator[](int i) {
			DCHECK(i >= 0 && i <= 2);
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		// Normal3 Public Data
		T x, y, z;
	};

	typedef Normal3<Float> Normal3f;



	// Bounds Declarations
	template <typename T>
	class Bounds2
	{
	public:
		// Bounds2 Public Data
		Point2<T> pMin, pMax;


		Bounds2()
		{
			T minNum = std::numeric_limits<T>::lowest();
#undef max
			T maxNum = std::numeric_limits<T>::max();
			pMin = Point2<T>(maxNum, maxNum);
			pMax = Point2<T>(minNum, minNum);
		}

#undef min
		explicit Bounds2(const Point2<T> &p) : pMin(p), pMax(p) {}
		Bounds2(const Point2<T> &p1, const Point2<T> &p2) {
			pMin = Point2<T>(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
			pMax = Point2<T>(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
		}

		//求对角线
		Vector2<T> Diagonal() const { return pMax - pMin; }
		T Area() const
		{
			Vector2<T> d = pMax - pMin;
			return (d.x * d.y);
		}

		//长和宽比较，长是否为最长的
		int MaximumExtent() const {
			Vector2<T> diag = Diagonal();
			if (diag.x > diag.y)
				return 0;
			else
				return 1;
		}

		inline const Point2<T> &operator[](int i) const {
			DCHECK(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}
		inline Point2<T> &operator[](int i) {
			DCHECK(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}
		bool operator==(const Bounds2<T> &b) const {
			return b.pMin == pMin && b.pMax == pMax;
		}
		bool operator!=(const Bounds2<T> &b) const {
			return b.pMin != pMin || b.pMax != pMax;
		}

		Point2<T> Lerp(const Point2f &t) const
		{
			return Point2<T>(pbrt::Lerp(t.x, pMin.x, pMax.x), pbrt::Lerp(t.y, pMin.y, pMax.y));
		}


	};

}
