#pragma once

class SpriteFrame {
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
public:
	SpriteFrame(int x, int y, int width, int height);
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
};
