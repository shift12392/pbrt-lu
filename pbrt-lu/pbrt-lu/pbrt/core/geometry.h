#pragma once


#include <cmath>
#include <limits>
#include <utility>

#include "../pbrt.h"


namespace pbrt
{


#define MachineEpsilon (std::numeric_limits<Float>::epsilon() * 0.5)


	static constexpr Float Pi = 3.14159265358979323846;


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




	inline Float gamma(int n) {
		return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
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
	inline Point3<T> Lerp(Float t, const Point3<T> &p0, const Point3<T> &p1) {
		return (1 - t) * p0 + t * p1;
	}


	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}

	// 度转弧度
	inline Float Radians(Float deg) { return (Pi / 180) * deg; }

	//弧度转度
	inline Float Degrees(Float radians) { return (180 / Pi) * radians; }


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
		explicit Normal3(const Vector3<T>& v) :x(v.x), y(v.y), z(v.z) { DCHECK(!HasNaNs()); }

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

		//返回，点p位置，在框的长宽的比例
		Vector2<T> Offset(const Point2<T> &p) const {
			Vector2<T> o = p - pMin;
			if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
			if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
			return o;
		}


	};

	class Ray
	{
	public:
		Point3f o;
		Vector3f d;
		mutable Float tMax;
		Float time;

		Ray() :tMax(std::numeric_limits<Float>::infinity()), time(0.f) {}
		Ray(const Point3f &o, const Vector3f &d, Float tMax = std::numeric_limits<Float>::infinity(),
			Float time = 0.f)
			: o(o), d(d), tMax(tMax), time(time) {}

		bool HasNaNs() const { return (o.HasNaNs() || d.HasNaNs() || isNaN(tMax)); }

		Point3f operator() (Float t)
		{
			return o + d * t;
		}

	};

	template <typename T>
	class Bounds3 {
	public:

		// Bounds3 Public Data
		Point3<T> pMin, pMax;


		// Bounds3 Public Methods
		Bounds3() {
			T minNum = std::numeric_limits<T>::lowest();
			T maxNum = std::numeric_limits<T>::max();
			pMin = Point3<T>(maxNum, maxNum, maxNum);
			pMax = Point3<T>(minNum, minNum, minNum);
		}
		explicit Bounds3(const Point3<T> &p) : pMin(p), pMax(p) {}
		Bounds3(const Point3<T> &p1, const Point3<T> &p2)
			: pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
				std::min(p1.z, p2.z)),
			pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
				std::max(p1.z, p2.z)) {}

		const Point3<T> &operator[](int i) const
		{
			DCHECK(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}

		Point3<T> &operator[](int i)
		{
			DCHECK(i == 0 || i == 1);
			return (i == 0) ? pMin : pMax;
		}

		bool operator==(const Bounds3<T> &b) const {
			return b.pMin == pMin && b.pMax == pMax;
		}

		bool operator!=(const Bounds3<T> &b) const {
			return b.pMin != pMin || b.pMax != pMax;
		}

	    /* 
		                 6---------------7(pMax) 
                      -  -            -  -
                  -      -         -     -
				2---------------3        -
				-        4- - - ---------5
				-     -         -     -
                - -             -  -    
		        0(pMin)---------1      

		 */

		Point3<T> Corner(int corner) const {
			DCHECK(corner >= 0 && corner < 8);
			return Point3<T>((*this)[(corner & 1)].x,
				(*this)[(corner & 2) ? 1 : 0].y,
				(*this)[(corner & 4) ? 1 : 0].z);
		}

		//对角线
		Vector3<T> Diagonal() const { return pMax - pMin; }

		//表面积
		T SurfaceArea() const {
			Vector3<T> d = Diagonal();
			return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
		}

		//体积
		T Volume() const {
			Vector3<T> d = Diagonal();
			return d.x * d.y * d.z;
		}

		// 返回0，说明长（x）最大；返回1，说明高（y）最大； 返回2，说明宽（z）最大。
		int MaximumExtent() const {
			Vector3<T> d = Diagonal();
			if (d.x > d.y && d.x > d.z)
				return 0;
			else if (d.y > d.z)
				return 1;
			else
				return 2;
		}

		Point3<T> Lerp(const Point3f &t) const {
			return Point3<T>(pbrt::Lerp(t.x, pMin.x, pMax.x),
				pbrt::Lerp(t.y, pMin.y, pMax.y),
				pbrt::Lerp(t.z, pMin.z, pMax.z));
		}
		Vector3<T> Offset(const Point3<T> &p) const {
			Vector3<T> o = p - pMin;
			if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
			if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
			if (pMax.z > pMin.z) o.z /= pMax.z - pMin.z;
			return o;
		}

		//求射线与Box框的两个交点的t值。
		/* x-y平面的情况,射线（o,d）在x-y平面投影，与平面x1,x2的相交的情况。
		  

                       |                |
					   |                |      d
					   |                |t2
				o	   |t1              |
		  -------------|----------------|------------------> x轴
		               |（x1）          |(x2)
		*/
		//射线完全在包围框内，也返回true。
		bool IntersectP(const Ray &ray, Float *hitt0 = nullptr,
			Float *hitt1 = nullptr) const
		{
			Float t0 = 0.0, t1 = ray.tMax;
			for (int i = 0; i < 3; i++)
			{
				// 如果ray.d[i]为0，光线平行于平面，则这个inv为无穷值。
				Float inv = 1 / ray.d[i];

			    // 如果射线原点在平面（比如：x1）内,同时平行平面（比如：x1）,则会出现0/0，根据IEEE 745浮点数标准，这会得到NaN。
				Float tNear = (pMin[i] - ray.o[i]) * inv;   
				Float tFar = (pMax[i] - ray.o[i]) * inv;

				//NaN浮点数参与比较总会返回false。
				if (tFar < tNear)
				{   
					std::swap(tNear, tFar);
				}

				tFar *= 1 + 2 * gamma(3);

				// NaN浮点数参与比较总会返回false。
				t0 = tNear > t0 ? tNear : t0;   
				t1 = tFar < t1 ? tFar : t1;

				if (t0 > t1)
					return false;
					
			}

			if (hitt0) *hitt0 = t0;
			if (hitt1) *hitt1 = t1;

			return true;
		}

	};


	typedef Bounds2<Float> Bounds2f;
	typedef Bounds2<int> Bounds2i;
	typedef Bounds3<Float> Bounds3f;
	typedef Bounds3<int> Bounds3i;






	template <typename T>
	Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2)
	{
		return Point3<T>(fminf(p1.x, p2.x), fminf(p1.y, p2.y),
			fminf(p1.z, p2.z));
	}

	template <typename T>
	Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2) {
		return Point3<T>(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y),
			fmaxf(p1.z, p2.z));
	}

	template <typename T>
	inline Vector3<T> Normalize(const Vector3<T> &v) {
		return v / v.Length();
	}

	template <typename T>
	inline Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2) {
		DCHECK(!v1.HasNaNs() && !v2.HasNaNs());

		//这里强转为double，是为了避免catastrophic cancellation。
		//对于两个接近的浮点小数 a, b，a - b 会比 a + b 造成更大的误差，这称为 catastrophic cancellation。
		double v1x = v1.x, v1y = v1.y, v1z = v1.z;
		double v2x = v2.x, v2y = v2.y, v2z = v2.z;
		return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}


	template <typename T>
	Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p)
	{
		Bounds3<T> ret;
		ret.pMin = Min(b.pMin, p);
		ret.pMax = Max(b.pMax, p);
		return ret;
	}

}



