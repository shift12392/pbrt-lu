#include "transform.h"
#include <memory>


namespace pbrt
{
	Matrix4x4::Matrix4x4(Float mat[4][4])
	{
		memcpy(m, mat, 16 * sizeof(Float));
	}

	Matrix4x4::Matrix4x4(Float t00, Float t01, Float t02, Float t03, Float t10,
		Float t11, Float t12, Float t13, Float t20, Float t21,
		Float t22, Float t23, Float t30, Float t31, Float t32,
		Float t33) {
		m[0][0] = t00;
		m[0][1] = t01;
		m[0][2] = t02;
		m[0][3] = t03;
		m[1][0] = t10;
		m[1][1] = t11;
		m[1][2] = t12;
		m[1][3] = t13;
		m[2][0] = t20;
		m[2][1] = t21;
		m[2][2] = t22;
		m[2][3] = t23;
		m[3][0] = t30;
		m[3][1] = t31;
		m[3][2] = t32;
		m[3][3] = t33;
	}

	// 转置
	Matrix4x4 Matrix4x4::Transpose(const Matrix4x4 &m)
	{
		return Matrix4x4(m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0], m.m[0][1],
			m.m[1][1], m.m[2][1], m.m[3][1], m.m[0][2], m.m[1][2],
			m.m[2][2], m.m[3][2], m.m[0][3], m.m[1][3], m.m[2][3],
			m.m[3][3]);
	}


	 

	Point3f Transform::operator()(const Point3f & p) const
	{
		Float x = p.x;
		Float y = p.y;
		Float z = p.z;
		Float xp = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
		Float yp = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
		Float zp = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];

		return Point3f(xp, yp, zp);
	}

	Bounds3f Transform::operator()(const Bounds3f & b) const
	{
		const Transform &M = *this;
		Bounds3f ret(M(Point3f(b.pMin.x, b.pMin.y, b.pMin.z)));
		ret = Union(ret, M(Point3f(b.pMax.x, b.pMin.y, b.pMin.z)));
		ret = Union(ret, M(Point3f(b.pMin.x, b.pMax.y, b.pMin.z)));
		ret = Union(ret, M(Point3f(b.pMin.x, b.pMin.y, b.pMax.z)));
		ret = Union(ret, M(Point3f(b.pMin.x, b.pMax.y, b.pMax.z)));
		ret = Union(ret, M(Point3f(b.pMax.x, b.pMax.y, b.pMin.z)));
		ret = Union(ret, M(Point3f(b.pMax.x, b.pMin.y, b.pMax.z)));
		ret = Union(ret, M(Point3f(b.pMax.x, b.pMax.y, b.pMax.z)));
		return ret;
	}
	bool Transform::SwapsHandedness() const
	{
		//计算左上角3x3矩阵行列式，如果为负，则说明这个转换会变化坐标系手性。
		Float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) -
					m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) +
					m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
		return det < 0;
	}
}


