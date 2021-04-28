#ifndef GAME_H
#define GAME_H


#include <string>

#include <SFML/Graphics.hpp>

#include "scene.h"


class Game
{
	public:
		Game();
		void Run_();

	private:
		void ProcessEvents_();
		void Update_(sf::Time deltaTime);
		void Render_();
		void HandlePlayerInput_(sf::Keyboard::Key key, bool is_pressed);

	private:
		sf::RenderWindow render_window_;
		bool is_moving_up_, is_moving_down_, is_moving_left_, is_moving_right_;
		sf::Vector2f player_velocity_;
		sf::Time time_per_frame_;
		Scene mWorld;
};

#endif // GAME_H
