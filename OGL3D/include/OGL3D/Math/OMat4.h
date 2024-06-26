#pragma once
#include <memory>
#include <OGL3D/Math/OVec4.h>
#include <OGL3D/Math/OVec3.h>
#include <OGL3D/OPrerequisites.h>
#include <math.h>
#include <string.h>


class OMat4
{
public:
	OMat4()
	{
		setIdentity();
	}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setTranslation(const OVec3& translation)
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

	void setScale(const OVec3& scale)
	{
		mat[0][0] = (f32)scale.x;
		mat[1][1] = (f32)scale.y;
		mat[2][2] = (f32)scale.z;
	}

	void setRotationX(float x)
	{
		mat[1][1] = (f32)cos(x);
		mat[1][2] = (f32)sin(x);
		mat[2][1] = (f32)-sin(x);
		mat[2][2] = (f32)cos(x);
	}

	void setRotationY(float y)
	{
		mat[0][0] = (f32)cos(y);
		mat[0][2] = (f32)-sin(y);
		mat[2][0] = (f32)sin(y);
		mat[2][2] = (f32)cos(y);
	}

	void setRotationZ(float z)
	{
		mat[0][0] = (f32)cos(z);
		mat[0][1] = (f32)sin(z);
		mat[1][0] = (f32)-sin(z);
		mat[1][1] = (f32)cos(z);
	}
	float getDeterminant()
	{
		OVec4 minor, v1, v2, v3;
		float det;

		v1 = OVec4(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
		v2 = OVec4(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
		v3 = OVec4(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
			this->mat[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		OMat4 out;
		OVec4 v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->mat[j][0]);
					vec[a].y = (this->mat[j][1]);
					vec[a].z = (this->mat[j][2]);
					vec[a].w = (this->mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.mat[0][i] = (f32)pow(-1.0f, i) * v.x / det;
			out.mat[1][i] = (f32)pow(-1.0f, i) * v.y / det;
			out.mat[2][i] = (f32)pow(-1.0f, i) * v.z / det;
			out.mat[3][i] = (f32)pow(-1.0f, i) * v.w / det;
		}

		this->setMatrix(out);
	}
	void operator *=(const OMat4& matrix)
	{
		OMat4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
			}
		}
		setMatrix(out);
	}

	void setMatrix(const OMat4& matrix)
	{
		::memcpy(mat, matrix.mat, sizeof(float) * 16);
	}

	OVec3 getTranslation()
	{
		return OVec3(mat[3][0], mat[3][1], mat[3][2]);
	}

	OVec3 getRightwardDirection()
	{
		return OVec3(mat[0][0], mat[0][1], mat[0][2]);
	}
	OVec3 getUpDirection()
	{
		return OVec3(mat[1][0], mat[1][1], mat[1][2]);
	}
	OVec3 getForwardDirection()
	{
		return OVec3(mat[2][0], mat[2][1], mat[2][2]);
	}



	void setOrthoLH(f32 width, f32 height, f32 nearPlane, f32 farPlane)
	{
		setIdentity();
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		setIdentity();
		float yscale = 1.0f / (f32)tan(fov / 2.0f);
		float xscale = yscale / aspect;
		mat[0][0] = xscale;
		mat[1][1] = yscale;
		mat[2][2] = zfar / (zfar - znear);
		mat[2][3] = 1.0f;
		mat[3][2] = (-znear * zfar) / (zfar - znear);
		mat[3][3] = 0.0f;
	}

public:
	float mat[4][4] = {};
};