#include "game.h"


Game::Game() :
	render_window_(sf::VideoMode(1080, 720), "SFML Application"),
	mWorld(render_window_)
{
	player_velocity_.x = 300.f;
	player_velocity_.y = 300.f;
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
				HandlePlayerInput_(event.key.code, true);
			break;
			case sf::Event::KeyReleased:
				HandlePlayerInput_(event.key.code, false);
			break;
			case sf::Event::Closed:
				render_window_.close();
			break;
		}
	}
}

void Game::Update_(sf::Time deltaTime)
{
    mWorld.update(time_per_frame_);

	sf::Vector2f movement(0.f, 0.f);
	if(is_moving_up_)
		movement.y -= player_velocity_.y;
	if(is_moving_down_)
		movement.y += player_velocity_.y;
	if(is_moving_left_)
		movement.x -= player_velocity_.x;
	if(is_moving_right_)
		movement.x += player_velocity_.x;
	mWorld.get_player()->move(movement * deltaTime.asSeconds());
}

void Game::Render_()
{
    render_window_.clear();
    mWorld.draw();
    render_window_.setView(render_window_.getDefaultView());
    render_window_.display();
}

void Game::HandlePlayerInput_(sf::Keyboard::Key key, bool is_pressed)
{
	if (key == sf::Keyboard::W)
		is_moving_up_ = is_pressed;
	else if (key == sf::Keyboard::S)
		is_moving_down_ = is_pressed;
	else if (key == sf::Keyboard::A)
		is_moving_left_ = is_pressed;
	else if (key == sf::Keyboard::D)
		is_moving_right_ = is_pressed;
}
