#include "scene.h"

Scene::Scene(sf::RenderWindow& window)
:
    render_window_(window),
    scene_view_(window.getDefaultView()),
    scene_bounds_(0.f, 0.f, scene_view_.getSize().x, 5000.f),
    spawn_position_
    (
        scene_view_.getSize().x / 2.f,
        scene_bounds_.height - scene_view_.getSize().y
    ),
    player_(nullptr)
{
    scroll_velocity_ = -100.f;
    LoadTextures_();
    BuildScene_();
    scene_view_.setCenter(spawn_position_);
}

void Scene::LoadTextures_()
{
    textures_holder_.Load_(Textures::Eagle, "share/Eagle.png");
    textures_holder_.Load_(Textures::Raptor, "share/Raptor.png");
    textures_holder_.Load_(Textures::Desert, "share/Desert.png");
}

void Scene::BuildScene_()
{
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SequenceTree::UniqueSequence layer(new SequenceTree());
        scene_layers_[i] = layer.get();
        sequences_root_.attachChild(std::move(layer));
    }

    sf::Texture& texture = textures_holder_.Get_(Textures::Desert);
    sf::IntRect textureRect(scene_bounds_);
    texture.setRepeated(true);

    std::unique_ptr<Element> backgroundSprite(new Element(texture, textureRect));
    backgroundSprite->setPosition(scene_bounds_.left, scene_bounds_.top);
    scene_layers_[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, textures_holder_));
    player_ = leader.get();
    player_->setPosition(spawn_position_);
    player_->set_velocity(0.f, scroll_velocity_);
    scene_layers_[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, textures_holder_));
    leftEscort->setPosition(-80.f, 50.f);
    player_->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, textures_holder_));
    rightEscort->setPosition(80.f, 50.f);
    player_->attachChild(std::move(rightEscort));
}

void Scene::Draw_()
{
    render_window_.setView(scene_view_);
    render_window_.draw(sequences_root_);
}

void Scene::Update_(sf::Time dt)
{
    scene_view_.move(0.f, scroll_velocity_ * dt.asSeconds());
    sf::Vector2f position = player_->getPosition();
    sf::Vector2f velocity = player_->get_velocity();

    std::cout << "\nPosition is: (" << position.x << "," << position.y << ")";
    std::cout << "\nVelocity is: (" << velocity.x << "," << velocity.y << ")";

    if (position.x <= scene_bounds_.left + 150 || position.x >= scene_bounds_.left + scene_bounds_.width - 150)
    {
        velocity.x = -velocity.x;
        player_->set_velocity(velocity);
        player_->updateCurrent(dt);
    }
    sequences_root_.update(dt);
}

Aircraft* Scene::get_player() const
{
    return player_;
}
