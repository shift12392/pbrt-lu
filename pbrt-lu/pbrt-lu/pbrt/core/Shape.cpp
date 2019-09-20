#include "Shape.h"
#include "transform.h"

namespace pbrt
{

	Shape::Shape(const Transform * ObjectToWorld, const Transform * WorldToObject, bool reverseOrientation)
		: ObjectToWorld(ObjectToWorld),
		WorldToObject(WorldToObject),
		reverseOrientation(reverseOrientation),
		transformSwapsHandedness(ObjectToWorld->SwapsHandedness())
	{
	}
	Bounds3f Shape::WorldBound() const
	{
		return (*ObjectToWorld)(ObjectBound());
	}
}
