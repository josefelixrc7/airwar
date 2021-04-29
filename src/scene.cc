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
    textures_holder_.Load_(Textures::kEagle, "share/Eagle.png");
    textures_holder_.Load_(Textures::kRaptor, "share/Raptor.png");
    textures_holder_.Load_(Textures::kDesert, "share/Desert.png");
}

void Scene::BuildScene_()
{
	/* Filled the layers */
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SequenceTree::UniqueSequence layer(new SequenceTree());
        scene_layers_[i] = layer.get();
        sequences_root_.AttachChild_(std::move(layer));
    }

    /* Create the background sprite */
    sf::IntRect texture_rect(scene_bounds_);
    textures_holder_.Get_(Textures::kDesert).setRepeated(true);

    std::unique_ptr<Element> background_sprite(new Element(Textures::kDesert, textures_holder_, texture_rect));
    background_sprite->setPosition(scene_bounds_.left, scene_bounds_.top);
    scene_layers_[Background]->AttachChild_(std::move(background_sprite));

    /* Create the sprite player */
    std::unique_ptr<Aircraft> leader(new Aircraft(Textures::kEagle, textures_holder_));
    player_ = leader.get();
    player_->setPosition(spawn_position_);
    player_->set_velocity(0.f, scroll_velocity_);
    scene_layers_[Air]->AttachChild_(std::move(leader));

    std::unique_ptr<Aircraft> left_escort(new Aircraft(Textures::kRaptor, textures_holder_));
    left_escort->setPosition(-80.f, 50.f);
    player_->AttachChild_(std::move(left_escort));

    std::unique_ptr<Aircraft> right_escort(new Aircraft(Textures::kRaptor, textures_holder_));
    right_escort->setPosition(80.f, 50.f);
    player_->AttachChild_(std::move(right_escort));
}

void Scene::Draw_()
{
    render_window_.setView(scene_view_);
    render_window_.draw(sequences_root_);
}

void Scene::Update_(sf::Time delta_time)
{
    scene_view_.move(0.f, scroll_velocity_ * delta_time.asSeconds());
    sf::Vector2f position = player_->getPosition();
    sf::Vector2f velocity = player_->get_velocity();

    std::cout << "\nPosition is: (" << position.x << "," << position.y << ")";
    std::cout << "\nVelocity is: (" << velocity.x << "," << velocity.y << ")";

    if (position.x <= scene_bounds_.left + 150 || position.x >= scene_bounds_.left + scene_bounds_.width - 150)
    {
        velocity.x = -velocity.x;
        player_->set_velocity(velocity);
        player_->UpdateCurrent_(delta_time);
    }
    sequences_root_.Update_(delta_time);
}

Aircraft* Scene::get_player() const
{
    return player_;
}
