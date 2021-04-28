#include "scene.h"

Scene::Scene(sf::RenderWindow& window)
:
    mWindow(window),
    mSceneView(window.getDefaultView()),
    mSceneBounds(0.f, 0.f, mSceneView.getSize().x, 5000.f),
    mSpawnPosition
    (
        mSceneView.getSize().x / 2.f,
        mSceneBounds.height - mSceneView.getSize().y
    ),
    mPlayerAircraft(nullptr)
{
    mScrollSpeed = -100.f;
    loadTextures();
    buildScene();
    mSceneView.setCenter(mSpawnPosition);
}

void Scene::loadTextures()
{
    mTextures.Load_(Textures::Eagle, "share/Eagle.png");
    mTextures.Load_(Textures::Raptor, "share/Raptor.png");
    mTextures.Load_(Textures::Desert, "share/Desert.png");
}

void Scene::buildScene()
{
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextures.Get_(Textures::Desert);
    sf::IntRect textureRect(mSceneBounds);
    texture.setRepeated(true);

    std::unique_ptr<Element> backgroundSprite(new Element(texture, textureRect));
    backgroundSprite->setPosition(mSceneBounds.left, mSceneBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->set_velocity(0.f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}

void Scene::draw()
{
    mWindow.setView(mSceneView);
    mWindow.draw(mSceneGraph);
}

void Scene::update(sf::Time dt)
{
    mSceneView.move(0.f, mScrollSpeed * dt.asSeconds());
    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->get_velocity();

    std::cout << "\nPosition is: (" << position.x << "," << position.y << ")";
    std::cout << "\nVelocity is: (" << velocity.x << "," << velocity.y << ")";

    if (position.x <= mSceneBounds.left + 150 || position.x >= mSceneBounds.left + mSceneBounds.width - 150)
    {
        velocity.x = -velocity.x;
        mPlayerAircraft->set_velocity(velocity);
        mPlayerAircraft->updateCurrent(dt);
    }
    mSceneGraph.update(dt);
}

Aircraft* Scene::get_mPlayerAircraft() const
{
    return mPlayerAircraft;
}
