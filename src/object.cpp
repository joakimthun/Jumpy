#include "object.h"

Object::Object(ErrorHandler* error_handler, SDL_Renderer* renderer)
{
	m_error_handler = error_handler;
	m_renderer = renderer;
}
