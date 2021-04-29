#include "game.h"


Game::Game() :
	render_window_(sf::VideoMode(1080, 720), "SFML Application"),
	scene_world_(render_window_)
{
	time_per_frame_ = sf::seconds(1.f / 60.f);
}

void Game::Run_()
{
	sf::Clock clock;
	sf::Time time_since_last_update = sf::Time::Zero;
	while (render_window_.isOpen())
	{
		ProcessEvents_();
		time_since_last_update += clock.restart();
		while(time_since_last_update > time_per_frame_)
		{
			time_since_last_update -= time_per_frame_;
			ProcessEvents_();
			Update_(time_per_frame_);
		}
		Render_();
	}
}

void Game::ProcessEvents_()
{
	sf::Event event;
	while (render_window_.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				scene_world_.HandlePlayerInput_(event.key.code, true);
			break;
			case sf::Event::KeyReleased:
				scene_world_.HandlePlayerInput_(event.key.code, false);
			break;
			case sf::Event::Closed:
				render_window_.close();
			break;
		}
	}
}

void Game::Update_(sf::Time deltaTime)
{
    scene_world_.Update_(time_per_frame_);
}

void Game::Render_()
{
    render_window_.clear();
    scene_world_.Draw_();
    render_window_.setView(render_window_.getDefaultView());
    render_window_.display();
}
