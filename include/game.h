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

	private:
		sf::RenderWindow render_window_;
		sf::Time time_per_frame_;
		Scene scene_world_;
};

#endif // GAME_H
