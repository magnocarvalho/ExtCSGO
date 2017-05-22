#include "Maths\Math.h"
#include "Maths\Vector.h"
#include <math.h>

#define DEG2RAD( x  )  ( (float)(x) * (float)(3.14159265358979323846f / 180.f) )
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / 3.14159265358979323846f) )

namespace ExtCSGO::Maths
{
	static void SinCos(float radians, float * sine, float * cosine)
	{
		*sine = (float)sin(radians);
		*cosine = (float)cos(radians);
	}

	void ClampAngles(vec3& v)
	{
		if (v.x > 89.0f && v.x <= 180.0f)
			v.x = 89.0f;

		if (v.x > 180.0f)
			v.x = v.x - 360.0f;

		if (v.x < -89.0f)
			v.x = -89.0f;

		v.y = fmodf(v.y + 180, 360) - 180;

		v.z = 0;
	}

	void VectorNormalize(vec3& vec)
	{
		float iradius = 1.f / (sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z) + 1.192092896e-07f);
		vec.x *= iradius;
		vec.y *= iradius;
		vec.z *= iradius;
	}

	void VectorAngles(vec3 & forward, vec3 & angles)
	{
		float tmp, yaw, pitch;


		if (forward.y == 0.f && forward.x == 0.f)
		{
			yaw = 0;
			if (forward.z > 0)pitch = 270;
			else pitch = 90.f;
		}
		else
		{
			yaw = (float)(atan2(forward.y, forward.x) * 180.f / 3.14159265358979323846f);
			if (yaw < 0)yaw += 360.f;

			tmp = (float)sqrt(forward.x * forward.x + forward.y * forward.y);
			pitch = (float)(atan2(-forward.z, tmp) * 180.f / 3.14159265358979323846f);
			if (pitch < 0)pitch += 360.f;
		}
		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0.f;
	}

	static void AngleVectors(const vec3 & angles, vec3 * forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);


		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	vec3 ConvertAngles(
		const float& Sensitivity,
		const vec3 &AimAngle,
		const vec3 &ViewAngle)
	{
		vec3 AnglePixels = (ViewAngle - AimAngle);
		ClampAngles(AnglePixels);

		AnglePixels.x = ((AnglePixels.x / Sensitivity) / -0.022f);
		AnglePixels.y = ((AnglePixels.y / Sensitivity) / 0.022f);

		return vec3(AnglePixels.y, AnglePixels.x, 0.f);
	}

	float GetFov(const vec3& viewAngle, const vec3& aimAngle)
	{
		vec3 ang, aim;

		AngleVectors(viewAngle, &aim);
		AngleVectors(aimAngle, &ang);

		return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
	}
}