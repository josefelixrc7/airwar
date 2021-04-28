#include "World.h"

World::World(sf::RenderWindow& window)
:
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 5000.f),
    mSpawnPosition
    (
        mWorldView.getSize().x / 2.f,
        mWorldBounds.height - mWorldView.getSize().y
    ),
    mPlayerAircraft(nullptr)
{
    mScrollSpeed = -100.f;
    loadTextures();
    buildScene();
    mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
    mTextures.load(Textures::Eagle, "share/Eagle.png");
    mTextures.load(Textures::Raptor, "share/Raptor.png");
    mTextures.load(Textures::Desert, "share/Desert.png");
}

void World::buildScene()
{
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(0.f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    std::cout << "\nPosition is: (" << position.x << "," << position.y << ")";
    std::cout << "\nVelocity is: (" << velocity.x << "," << velocity.y << ")";

    if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150)
    {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
        mPlayerAircraft->updateCurrent(dt);
    }
    mSceneGraph.update(dt);
}

Aircraft* World::get_mPlayerAircraft() const
{
    return mPlayerAircraft;
}
