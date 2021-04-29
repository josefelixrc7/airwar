#ifndef SCENE_H
#define SCENE_H

#include <iostream>

#include <SFML/Graphics.hpp>

#include "texture_holder.h"
#include "SceneNode.h"
#include "Aircraft.h"
#include "element.h"

class Scene : private sf::NonCopyable
{
    public:
        explicit Scene(sf::RenderWindow& window);

        void update(sf::Time dt);
        void draw();

    public:
        Aircraft* get_player() const;

    private:
        void loadTextures();
        void buildScene();

    private:
        enum Layer
        {
            Background,
            Air,
            LayerCount
        };

    private:
        sf::RenderWindow&   render_window_;
        sf::View            scene_view_;
        TextureHolder       textures_holder_;
        SceneNode           sequences_root_;
        std::array<SceneNode*, LayerCount> scene_layers_;
        sf::FloatRect scene_bounds_;
        sf::Vector2f spawn_position_;
        float scroll_velocity_;
        Aircraft* player_;
};

#endif // SCENE_H
