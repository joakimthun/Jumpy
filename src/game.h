#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>
#include <math.h>

#include "object.h"
#include "error_handler.h"
#include "texture.h"
#include "parallax_background.h"
#include "player.h"
#include "vector2d.h"
#include "timer.h"

class Game {

private:
	bool m_running;
	int m_screen_width;
	int m_screen_height;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	std::vector<Object*> m_objects;
	ErrorHandler* m_error_handler;
	Uint32 m_last_frame_time;

public:
	Game();
	~Game();
	void start();
	void stop();
	void exit();
	void update();
	bool init();
	bool createScene();
};
