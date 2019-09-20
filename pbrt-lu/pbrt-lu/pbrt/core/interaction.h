#pragma once

#include "geometry.h"
#include "medium.h"

namespace pbrt
{
	struct Interaction
	{
		Point3f p;
		Float time;
		Vector3f pError;   //p点的保守误差界
		Vector3f wo;       //出射射线
		Normal3f n;        //法线
		MediumInterface mediumInterface;

		Interaction() : time(0) {}

		Interaction(const Point3f &p, const Normal3f &n, const Vector3f &pError,
			const Vector3f &wo, Float time,
			const MediumInterface &mediumInterface)
			: p(p),
			time(time),
			pError(pError),
			wo(Normalize(wo)),
			n(n),
			mediumInterface(mediumInterface)
		{

		}

		Interaction(const Point3f &p, const Normal3f &n, const Vector3f &pError,
			const Vector3f &wo, Float time)
			: p(p),
			time(time),
			pError(pError),
			wo(Normalize(wo)),
			n(n)
		{

		}

		bool IsSurfaceInteraction() const { return n != Normal3f(); }

	};

	class Shape;

	class SurfaceInteraction : public Interaction 
	{
	public:
		// SurfaceInteraction Public Data
		Point2f uv;
		Vector3f dpdu, dpdv;
		Normal3f dndu, dndv;
		const Shape *shape = nullptr;

		struct {
			Normal3f n;
			Vector3f dpdu, dpdv;
			Normal3f dndu, dndv;
		} shading;

		int faceIndex = 0;


		SurfaceInteraction() {}

		SurfaceInteraction(const Point3f &p, const Vector3f &pError,
			const Point2f &uv, const Vector3f &wo,
			const Vector3f &dpdu, const Vector3f &dpdv,
			const Normal3f &dndu, const Normal3f &dndv, Float time,
			const Shape *sh,
			int faceIndex = 0);
	};

}
