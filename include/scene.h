#ifndef SCENE_H
#define SCENE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "texture_holder.h"
#include "sequence_tree.h"
#include "Aircraft.h"
#include "element.h"

class Scene : private sf::NonCopyable
{
    public:
        explicit Scene(sf::RenderWindow& window);

        void Update_(sf::Time dt);
        void Draw_();

        Aircraft* get_player() const;

    private:
        enum Layer
        {
            Background,
            Air,
            LayerCount
        };

        void LoadTextures_();
        void BuildScene_();


        sf::RenderWindow& render_window_;
        sf::View scene_view_;
        TextureHolder textures_holder_;
        SequenceTree sequences_root_;
        std::array<SequenceTree*, LayerCount> scene_layers_;
        sf::FloatRect scene_bounds_;
        sf::Vector2f spawn_position_;
        float scroll_velocity_;
        Aircraft* player_;
};

#endif // SCENE_H
