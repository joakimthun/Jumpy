#pragma once

#include <vector>
#include <string>

#include "object.h"
#include "texture.h"

class ParallaxBackground : public Object {
private:
	int m_x;
	int m_y;
	std::vector<Texture*> m_layers;

public:
	ParallaxBackground(ErrorHandler* error_handler, SDL_Renderer* renderer);
	~ParallaxBackground();
	void render();
	void update(float delta_time);
	void addLayer(std::string path);
};
