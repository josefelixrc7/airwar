#ifndef SCENE_H
#define SCENE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "resource_holder.h"
#include "sequence_tree.h"
#include "aircraft.h"
#include "element.h"

class Scene : private sf::NonCopyable
{
    public:
        explicit Scene(sf::RenderWindow& window);

        void Update_(sf::Time delta_time);
        void Draw_();
		void HandlePlayerInput_(sf::Keyboard::Key key, bool is_pressed);

        Aircraft* get_player() const;

	protected:
        enum Layer
        {
            kBackground,
            kAir,
            kLayerCount
        };

        void LoadTextures_();
        void BuildScene_();
		void FillLayers_();
		void CreateElements_();
		void CreateCharacters_();

    private:
    	struct
    	{
    		bool is_moving_up_, is_moving_down_, is_moving_left_, is_moving_right_;
			sf::Vector2f player_velocity_;
    	} player_settings_;

        sf::RenderWindow& render_window_;
        sf::View scene_view_;
        ResourceHolder<sf::Texture, ResourcesID::Elements> textures_elements_;
        ResourceHolder<sf::Texture, ResourcesID::Characters> textures_characters_;
        SequenceTree sequences_root_;
        std::array<SequenceTree*, kLayerCount> scene_layers_;
        sf::FloatRect scene_bounds_;
        sf::Vector2f spawn_position_;
        sf::Vector2f scroll_velocity_;
        Aircraft* player_;
};

#endif // SCENE_H
