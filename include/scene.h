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
        Aircraft* get_mPlayerAircraft() const;

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
        sf::RenderWindow&   mWindow;
        sf::View            mSceneView;
        TextureHolder       mTextures;
        SceneNode           mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;
        sf::FloatRect mSceneBounds;
        sf::Vector2f mSpawnPosition;
        float mScrollSpeed;
        Aircraft* mPlayerAircraft;
};

#endif // SCENE_H
