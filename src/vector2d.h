#pragma once

#include <math.h>

class Vector2D {
private:
	float m_x;
	float m_y;
public:
	Vector2D();
	Vector2D(float x, float y);

	Vector2D operator+=(const Vector2D& v2);
	Vector2D operator-=(const Vector2D& v2);
	Vector2D operator*=(float scalar);
	Vector2D operator*(float scalar);
	Vector2D operator/=(float scalar);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float length() const;
	void normalize();
};
