#pragma once

#include <SDL/SDL.h>

#include "error_handler.h"

class Object {
protected:
	ErrorHandler* m_error_handler;
	SDL_Renderer* m_renderer;

public:
	Object(ErrorHandler* error_handler, SDL_Renderer* renderer);

	inline virtual ~Object()
	{
		if(m_error_handler)
			delete m_error_handler;

		if(m_renderer)
			SDL_DestroyRenderer(m_renderer);
	}

	virtual void render() = 0;
	virtual void update(float delta_time) = 0;
};
