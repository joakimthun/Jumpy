#pragma once

#include <SDL/SDL.h>

#include "object.h"
#include "texture.h"
#include "vector2d.h"
#include "sprite.h"

class Player : public Object {
private:
	Sprite* m_sprite;
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_gravity;

	void addSpriteFrames();

public:
	Player(ErrorHandler* error_handler, SDL_Renderer* renderer, Vector2D position);
	~Player();
	void render();
	void update(float delta_time);
	void handleEvent(SDL_Event& e);
	void jump();
};
