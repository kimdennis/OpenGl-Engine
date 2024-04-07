#pragma once
#include <OGL3D/OPrerequisites.h>


class OVec3
{
public:
	OVec3()
	{
	}
	OVec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z)
	{
	}
	~OVec3()
	{
	}

	OVec3 operator += (const OVec3& vec)
	{
		*this = OVec3(x + vec.x, y + vec.y, z + vec.z);
		return *this;
	}

public:
	f32 x = 0, y = 0, z = 0;
};