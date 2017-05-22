#pragma once

namespace ExtCSGO
{
	class vec3;
}

namespace ExtCSGO::Maths
{
	void ClampAngles(vec3& v);
	void VectorNormalize(vec3& vec);
	void VectorAngles(vec3& forward, vec3& angles);
	vec3 ConvertAngles(const float &Sensitivity, const vec3 &AimAngle, const vec3 &ViewAngle);
	float GetFov(const vec3& viewAngle, const vec3& aimAngle);
}