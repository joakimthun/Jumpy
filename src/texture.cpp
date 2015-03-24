#include "texture.h"

Texture::Texture(ErrorHandler* error_handler, SDL_Renderer* renderer, int x, int y) : Object(error_handler, renderer)
{
	m_texture = nullptr;
	m_font = nullptr;
	m_width = 0;
	m_height = 0;
	m_x = x;
	m_y = y;
	m_offset_x = 0;
	m_offset_y = 0;
};

Texture::~Texture()
{
	if(m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_width = 0;
		m_height = 0;
	}
};

void Texture::render()
{
	SDL_Rect render_rect = { m_x, m_y, m_width, m_height };

	SDL_RenderCopyEx(m_renderer, m_texture, 0, &render_rect, 0, 0, SDL_FLIP_NONE);
}

void Texture::render(int x, int y)
{
	SDL_Rect render_rect = { x, y, m_width, m_height };

	SDL_RenderCopyEx(m_renderer, m_texture, 0, &render_rect, 0, 0, SDL_FLIP_NONE);
}

void Texture::renderWithOffset()
{
	int x = m_x + m_offset_x;
	int y = m_y + m_offset_y;

	SDL_Rect render_rect = { x, y, m_width, m_height };

	SDL_RenderCopyEx(m_renderer, m_texture, 0, &render_rect, 0, 0, SDL_FLIP_NONE);
}

void Texture::render(SDL_Rect* render_rect, SDL_Rect* clip)
{
	SDL_RenderCopy(m_renderer, m_texture, clip, render_rect);
}

void Texture::update(float delta_time) {}

bool Texture::loadPngFromFile(std::string path)
{
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if(!loaded_surface)
	{
		m_error_handler->displayError("Could not load surface from file.");
	}
	else
	{
		m_texture = SDL_CreateTextureFromSurface(m_renderer, loaded_surface);
		if(!m_texture)
		{
			m_error_handler->displayError("Could not create texture from surface.");
		}
		else
		{
			m_width = loaded_surface->w;
			m_height = loaded_surface->h;
		}

		SDL_FreeSurface(loaded_surface);
	}

	return m_texture != nullptr;
}

bool Texture::loadTtfFromFile(std::string path, int size, std::string text)
{
	m_font = TTF_OpenFont(path.c_str(), size);
	if(!m_font)
	{
		m_error_handler->displayError("Failed to load font!");
	}
	else
	{
		SDL_Color text_color = { 255, 0, 0, 255 };

		return setText(text, text_color);
	}

	return m_texture != nullptr;
}

bool Texture::setText(std::string text, SDL_Color color)
{
	if(m_texture)
		SDL_DestroyTexture(m_texture);

	SDL_Surface* text_surface = TTF_RenderText_Solid(m_font, text.c_str(), color);
	if(text_surface)
	{
		m_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
		if(!m_texture)
		{
			m_error_handler->displayError("Unable to create texture from rendered text!");
		}
		else
		{
			m_width = text_surface->w;
			m_height = text_surface->h;
		}

		SDL_FreeSurface(text_surface);
	}
	else
	{
		m_error_handler->displayError("Unable to render text surface!");
	}

	return m_texture != nullptr;
}

int Texture::getWidth()
{
	return m_width;
}

int Texture::getHeight()
{
	return m_height;
}

void Texture::setX(int x)
{
	m_x = x;
}
void Texture::setY(int y)
{
	m_y = y;
}

int Texture::getOffsetX()
{
	return m_offset_x;
}

int Texture::getOffsetY()
{
	return m_offset_y;
}

void Texture::setOffsetX(int x)
{
	m_offset_x = x;
}

void Texture::setOffsetY(int y)
{
	m_offset_y = y;
}






