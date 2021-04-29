#ifndef SCENE_H
#define SCENE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "texture_holder.h"
#include "sequence_tree.h"
#include "aircraft.h"
#include "element.h"

class Scene : private sf::NonCopyable
{
    public:
        explicit Scene(sf::RenderWindow& window);

        void Update_(sf::Time dt);
        void Draw_();

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

        sf::RenderWindow& render_window_;
        sf::View scene_view_;
        TextureHolder textures_holder_;
        SequenceTree sequences_root_;
        std::array<SequenceTree*, kLayerCount> scene_layers_;
        sf::FloatRect scene_bounds_;
        sf::Vector2f spawn_position_;
        sf::Vector2f scroll_velocity_;
        Aircraft* player_;
};

#endif // SCENE_H
