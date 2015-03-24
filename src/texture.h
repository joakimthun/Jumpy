#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "object.h"

class Texture : public Object {
private:
	SDL_Texture* m_texture;
	TTF_Font* m_font;
	int m_width;
	int m_height;
	int m_x;
	int m_y;
	int m_offset_x;
	int m_offset_y;

public:
	Texture(ErrorHandler* error_handler, SDL_Renderer* renderer, int x, int y);
	~Texture();
	void render();
	void render(int x, int y);
	void renderWithOffset();
	void render(SDL_Rect* render_rect, SDL_Rect* clip);
	void update(float delta_time);
	bool loadPngFromFile(std::string);
	bool loadTtfFromFile(std::string path, int size, std::string text);
	bool setText(std::string text, SDL_Color color);

	int getWidth();
	int getHeight();

	void setX(int x);
	void setY(int y);

	int getOffsetX();
	int getOffsetY();
	void setOffsetX(int x);
	void setOffsetY(int y);
};
