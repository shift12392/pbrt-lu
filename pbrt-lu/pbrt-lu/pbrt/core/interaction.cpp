#include "interaction.h"
#include "Shape.h"


namespace pbrt
{
	SurfaceInteraction::SurfaceInteraction(const Point3f & p, const Vector3f & pError, const Point2f & uv, const Vector3f & wo, const Vector3f & dpdu, const Vector3f & dpdv, const Normal3f & dndu, const Normal3f & dndv, Float time, const Shape * sh, int faceIndex)
		:Interaction(p, Normal3f(Normalize(Cross(dpdu, dpdv))),pError,wo,time),
		uv(uv),
		dpdu(dpdu),
		dpdv(dpdv),
		dndu(dndu),
		dndv(dndv),
		shape(shape),
		faceIndex(faceIndex)
	{
		// Initialize shading geometry from true geometry
		shading.n = n;
		shading.dpdu = dpdu;
		shading.dpdv = dpdv;
		shading.dndu = dndu;
		shading.dndv = dndv;

		//Òì»ò
		if (shape != nullptr && shape->reverseOrientation ^ shape->transformSwapsHandedness)
		{
			n *= -1;
			shading.n *= -1;
		}

	}
}


