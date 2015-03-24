#include "parallax_background.h"

ParallaxBackground::ParallaxBackground(ErrorHandler* error_handler, SDL_Renderer* renderer) : Object(error_handler, renderer)
{
	m_x = 0;
	m_y = 0;
}

ParallaxBackground::~ParallaxBackground()
{
	//TODO: Clean up layers
}

void ParallaxBackground::render()
{
	for(auto layer : m_layers)
	{
		layer->renderWithOffset();
		layer->render(layer->getOffsetX() + layer->getWidth(), 0);
	}
}

void ParallaxBackground::update(float delta_time)
{
	for(size_t i = 0; i < m_layers.size(); i++)
	{
		auto layer = m_layers[i];
		if(layer->getOffsetX() < -layer->getWidth())
			layer->setOffsetX(0);

		layer->setOffsetX(layer->getOffsetX() - i);
	}
}

void ParallaxBackground::addLayer(std::string path)
{
	auto layer = new Texture(m_error_handler, m_renderer, m_x, m_y);
	if(!layer->loadPngFromFile(path))
	{
		m_error_handler->displayError("Could not add layer");
		delete layer;
	}
	else
	{
		m_layers.push_back(layer);
	}
}
