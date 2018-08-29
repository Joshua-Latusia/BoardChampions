#pragma once

class Vec3fl
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};


	Vec3fl();
	Vec3fl(const Vec3fl &other);
	Vec3fl(float x, float y, float z);

	float& operator [](int);
};

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();


	Vec2f( float x, float y);
	Vec2f(const Vec2f &other);
	float& operator [](int);
};