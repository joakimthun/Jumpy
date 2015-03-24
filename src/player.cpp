#include "player.h"

Player::Player(ErrorHandler* error_handler, SDL_Renderer* renderer, Vector2D position) : Object(error_handler, renderer)
{
	m_position = position;
	m_velocity = Vector2D(0, 0);
	m_gravity = Vector2D(0, 500);

	m_sprite = new Sprite("../assets/img/player_run.png", error_handler, renderer, 90);
	addSpriteFrames();
}

Player::~Player()
{
	if(m_sprite)
		delete m_sprite;
}

void Player::render()
{
	m_sprite->render(m_position);
}

void Player::update(float delta_time)
{
	m_position += (m_velocity * delta_time);
	m_velocity += (m_gravity * delta_time);

	if(m_position.getY() >= 563)
	{
		m_position.setY(563);
		m_velocity.setY(0);
	}

	m_sprite->update(delta_time);
}

void Player::jump()
{
	m_velocity += Vector2D(0, -500);
}

void Player::handleEvent(SDL_Event& e)
{
	int speed = 200;

	//A key was pushed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	{
	    switch( e.key.keysym.sym )
	    {
	        case SDLK_UP: jump(); break;
	        case SDLK_DOWN: m_velocity.setY(speed); break;
	        case SDLK_LEFT: m_velocity.setX(-speed); break;
	        case SDLK_RIGHT: m_velocity.setX(speed); break;
	    }
	}
	//A key was released
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		//Adjust the velocity
		switch( e.key.keysym.sym )
		{
			//case SDLK_UP: m_velocity.setY(0); break;
			case SDLK_DOWN: m_velocity.setY(0); break;
			case SDLK_LEFT: m_velocity.setX(0); break;
			case SDLK_RIGHT: m_velocity.setX(0); break;
		}
	}
}

void Player::addSpriteFrames()
{
	m_sprite->registerFrame(2, 2, 243, 328);
	m_sprite->registerFrame(2, 332, 243, 328);
	m_sprite->registerFrame(2, 662, 243, 328);
	m_sprite->registerFrame(2, 992, 243, 328);
	m_sprite->registerFrame(2, 1322, 243, 328);
	m_sprite->registerFrame(2, 1652, 243, 328);
}
