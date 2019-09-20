#pragma once


#include "geometry.h"


namespace pbrt
{
	class Transform;
	class SurfaceInteraction;

	class Shape
	{
	public:
		const Transform *ObjectToWorld, *WorldToObject;
		const bool reverseOrientation;
		const bool transformSwapsHandedness;         //ObjectToWorld转换，会不会把Shape的坐标系手性给改变了。

		Shape(const Transform *ObjectToWorld, const Transform *WorldToObject,
			bool reverseOrientation);

		virtual ~Shape() {}

		virtual Bounds3f ObjectBound() const = 0;

		virtual Bounds3f WorldBound() const;

		virtual bool Intersect(const Ray &ray, Float *tHit,
			SurfaceInteraction *isect,
			bool testAlphaTexture = true) const = 0;


		virtual bool IntersectP(const Ray &ray,
			bool testAlphaTexture = true) const {
			return Intersect(ray, nullptr, nullptr, testAlphaTexture);
		}


		virtual Float Area() const = 0;

	};
}


