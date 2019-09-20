#pragma once


#include "../core/Shape.h"


namespace pbrt
{
	class Sphere : public Shape
	{
	public:
		const Float radius;
		const Float zMin, zMax;
		const Float thetaMin, thetaMax, phiMax;


		Sphere(const Transform *ObjectToWorld, const Transform *WorldToObject,
			bool reverseOrientation, Float radius, Float zMin, Float zMax,
			Float phiMax)
			: Shape(ObjectToWorld, WorldToObject, reverseOrientation),
				radius(radius),
				zMin(Clamp(fminf(zMin, zMax), -radius, radius)),
				zMax(Clamp(fmaxf(zMin, zMax), -radius, radius)),
				thetaMin(std::acos(Clamp(fminf(zMin, zMax) / radius, -1.0f, 1.0f))),
				thetaMax(std::acos(Clamp(fmaxf(zMin, zMax) / radius, -1.0f, 1.0f))),
				phiMax(Radians(Clamp(phiMax, 0.0f, 360.0f))) 
		{
		}


		virtual Bounds3f ObjectBound() const
		{
			return Bounds3f(Point3f(-radius, -radius, zMin), Point3f(radius, radius, zMax));
		}
	};
}
