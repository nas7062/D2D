#pragma once
class Math
{
public:
	static const float PI;

	static float ToRadian(float degree);
	static float ToDegree(float radian);

	static int Random(int r1, int r2);
	static float Random(float r1, float r2);

	template<typename T>
	static T Clamp(T value, T min, T max)
	{
		value = value > max ? max : value;
		value = value < min ? min : value;

		return value;
	}
	template<typename T> static T Lerp(T value1, T value2, T t)
	{
		return value1 + (value2 - value1) * t;
	}

	static double Length(Vector2 pos1, Vector2 pos2)
	{
		double length = sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) +
			(pos1.y - pos2.y)*(pos1.y - pos2.y));
		return length;

	}

};

