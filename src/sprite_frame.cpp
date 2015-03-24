#include "sprite_frame.h"

SpriteFrame::SpriteFrame(int x, int y, int width, int height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

void SpriteFrame::setX(int x)
{
	m_x = x;
}

void SpriteFrame::setY(int y)
{
	m_y = y;
}

void SpriteFrame::setWidth(int width)
{
	m_width = width;
}

void SpriteFrame::setHeight(int height)
{
	m_height = height;
}

int SpriteFrame::getX()
{
	return m_x;
}

int SpriteFrame::getY()
{
	return m_y;
}

int SpriteFrame::getWidth()
{
	return m_width;
}

int SpriteFrame::getHeight()
{
	return m_height;
}
