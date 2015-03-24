#include "sprite.h"

//private:
//	Texture m_sprite_sheet;
//	std::vector<SpriteFrame> m_frames;
//	Timer m_timer;
//	int m_current_frame;
//	int m_num_frames;

Sprite::Sprite(std::string path, ErrorHandler* error_handler, SDL_Renderer* renderer, Uint32 frame_time) : Object(error_handler, renderer)
{
	m_sprite_sheet = new Texture(error_handler, renderer, 0, 0);
	if(m_sprite_sheet)
		m_sprite_sheet->loadPngFromFile(path);

	m_timer = new Timer();
	m_current_frame = 0;
	m_num_frames = -1;
	m_frame_time = frame_time;
	m_last_frame = 0;
}

Sprite::~Sprite()
{
	if(m_sprite_sheet)
		delete m_sprite_sheet;

	if(m_timer)
		delete m_timer;

	//TODO: Delete frames
}

void Sprite::registerFrame(int x, int y, int width, int height)
{
	SpriteFrame* frame = new SpriteFrame(x, y, width, height);

	m_frames.push_back(frame);
	m_num_frames++;
}

void Sprite::render() {}

void Sprite::render(Vector2D position)
{
	SDL_Rect render_rect = { (int)position.getX(), (int)position.getY(), m_frames[m_current_frame]->getWidth(), m_frames[m_current_frame]->getHeight() };
	SDL_Rect clip = { m_frames[m_current_frame]->getX(), m_frames[m_current_frame]->getY(), m_frames[m_current_frame]->getWidth(), m_frames[m_current_frame]->getHeight() };
	m_sprite_sheet->render(&render_rect, &clip);
}

void Sprite::update(float delta_time)
{
	Uint32 ticks = m_timer->getTicks();

	if(!m_timer->isStarted())
	{
		m_timer->start();
		m_current_frame = 0;
	}
	else
	{
		Uint32 diff =  ticks - m_last_frame;
		if(diff >= m_frame_time)
		{
			if(m_current_frame >= m_num_frames)
			{
				m_current_frame = 0;
			}
			else
			{
				m_current_frame++;
			}

			m_last_frame = ticks;
		}
	}
}
