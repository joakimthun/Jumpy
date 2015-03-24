#pragma once

#include <SDL/SDL.h>
#include <vector>
#include <string>

#include "object.h"
#include "sprite_frame.h"
#include "texture.h"
#include "timer.h"
#include "vector2d.h"

class Sprite : public Object {
private:
	Texture* m_sprite_sheet;
	std::vector<SpriteFrame*> m_frames;
	Timer* m_timer;
	int m_current_frame;
	int m_num_frames;
	Uint32 m_frame_time;
	Uint32 m_last_frame;

public:
	Sprite(std::string path, ErrorHandler* error_handler, SDL_Renderer* renderer, Uint32 frame_time);
	~Sprite();
	void registerFrame(int x, int y, int width, int height);
	void render();
	void render(Vector2D position);
	void update(float delta_time);
};
