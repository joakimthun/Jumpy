#include "game.h"

Game::Game()
{
	m_running = false;
	m_screen_width = 1920;
	m_screen_height = 1080;
	m_window = nullptr;
	m_renderer = nullptr;
	m_error_handler = new ErrorHandler;
	m_last_frame_time = 0;
}

Game::~Game()
{
	if(m_window)
		SDL_DestroyWindow(m_window);

	//TODO: Clean up objects
}

void Game::start()
{
	m_running = true;

	if( !createScene() )
	{
		printf( "Failed to load media!\n" );
	}
	else
	{
		SDL_Event e;
		auto playerPosition = Vector2D(473, 563);
		auto player = new Player(m_error_handler, m_renderer, playerPosition);

		Timer timer;
		SDL_Color text_color = { 255, 0, 0, 255 };
		std::string text = "FPS: ";
		std::stringstream text_stream;
		Texture* text_texture = new Texture(m_error_handler, m_renderer, 10, 0);
		text_texture->loadTtfFromFile("../assets/font/Capsmall.ttf", 40, text);
		int frame_count = 0;
		timer.start();

		m_last_frame_time = timer.getTicks();
		while(m_running)
		{
			//Handle events in the event queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT )
				{
					m_running = false;
				}

				player->handleEvent(e);
			}

			//Calculate fps and delta time
			Uint32 ticks = timer.getTicks();
			float delta_time = ((ticks - m_last_frame_time) / 1000.f);
			m_last_frame_time = ticks;

			float avg_fps = frame_count / (ticks / 1000.f);
			if( avg_fps > 2000000 )
			{
				// The first couple of frames the elapsed time count is tiny and will spike the fps.
				avg_fps = 0;
			}

			//Clear the screen
			SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(m_renderer);

			for(auto object : m_objects)
			{
				object->update(delta_time);
				object->render();
			}

			player->update(delta_time);
			player->render();

			text_stream.str("");
			text_stream << text << round(avg_fps);
			text_texture->setText(text_stream.str(), text_color);
			text_texture->render();

			//Update screen
			SDL_RenderPresent(m_renderer);
			frame_count++;
		}

		timer.stop();
		if(text_texture)
			delete text_texture;
	}

	//Free resources and close SDL
	exit();
}

void Game::stop()
{
	m_running = false;

}

void Game::exit()
{
	IMG_Quit();
	SDL_Quit();
}

void Game::update()
{

}

bool Game::init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		m_error_handler->displayError("SDL could not be initialized.");
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
		{
			m_error_handler->displayError("Warning: Linear texture filtering not enabled!");
		}

		m_window = SDL_CreateWindow("Jumpy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screen_width, m_screen_height, SDL_WINDOW_SHOWN);
		if(!m_window)
		{
			m_error_handler->displayError("Window could not be created!");
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(!m_renderer)
			{
				m_error_handler->displayError("Renderer could not be created!");
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if(!( IMG_Init( imgFlags ) & imgFlags))
				{
					m_error_handler->displayError("SDL_image could not initialize!");
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					m_error_handler->displayError("SDL_ttf could not initialize!");
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::createScene()
{
	bool success = true;

	auto background = new ParallaxBackground(m_error_handler, m_renderer);
	background->addLayer("../assets/img/layer0.png");
	background->addLayer("../assets/img/layer1.png");
	background->addLayer("../assets/img/layer2.png");
	background->addLayer("../assets/img/layer4.png");

	m_objects.push_back(background);

	return success;
}
