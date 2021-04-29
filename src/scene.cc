#include "scene.h"

Scene::Scene(sf::RenderWindow& window)
:
    render_window_(window),
    scene_view_(window.getDefaultView()),
    scene_bounds_(0.f, 0.f, 5000.f, scene_view_.getSize().y),
    spawn_position_
    (
        scene_view_.getSize().x / 2.f,
        scene_view_.getSize().y / 2
    ),
    player_(nullptr)
{
    scroll_velocity_.x = 100.f;
    scroll_velocity_.y = 0.f;
    LoadTextures_();
    BuildScene_();
    scene_view_.setCenter(spawn_position_);
}

Aircraft* Scene::get_player() const
{
    return player_;
}

void Scene::Update_(sf::Time delta_time)
{
    scene_view_.move(scroll_velocity_.x * delta_time.asSeconds(), 0.f);
    sf::Vector2f position = player_->getPosition();
    sf::Vector2f velocity = player_->get_velocity();

    std::cout << "\nPosition is: (" << position.x << "," << position.y << ")";
    std::cout << "\nVelocity is: (" << velocity.x << "," << velocity.y << ")";
    std::cout << "\nSceneView xy (" << scene_view_.getSize().x << "," << scene_view_.getSize().y << ")";
    std::cout << "\nSceneBounds width, height (" << scene_bounds_.width << "," << scene_bounds_.height << ")";

    if (position.y <= scene_bounds_.top + 150 || position.y >= scene_bounds_.top + scene_bounds_.height - 150)
    {
        velocity.y = -velocity.y;
        player_->set_velocity(velocity);
        player_->UpdateCurrent_(delta_time);
    }

    sequences_root_.Update_(delta_time);
}

void Scene::Draw_()
{
    render_window_.setView(scene_view_);
    render_window_.draw(sequences_root_);
}

void Scene::LoadTextures_()
{
    textures_holder_.Load_(Textures::kSky, "share/sky.png");
    textures_holder_.Load_(Textures::kMountains1, "share/mountains_1.png");
    textures_holder_.Load_(Textures::kMountains2, "share/mountains_2.png");
    textures_holder_.Load_(Textures::kAircraftEagle, "share/aircraft_eagle.png");
    textures_holder_.Load_(Textures::kRaptorEnemy, "share/raptor_enemy.png");
}

void Scene::BuildScene_()
{
	FillLayers_();
	CreateElements_();
	CreateCharacters_();
}

void Scene::FillLayers_()
{
    for (std::size_t i = 0; i < kLayerCount; ++i)
    {
        SequenceTree::UniqueSequence layer(new SequenceTree());
        scene_layers_[i] = layer.get();
        sequences_root_.AttachChild_(std::move(layer));
    }
}

void Scene::CreateElements_()
{
    sf::IntRect rect_sky(0.f, 0.f, scene_view_.getSize().x, scene_view_.getSize().y);
    sf::IntRect rect_total(scene_bounds_);

    textures_holder_.Get_(Textures::kMountains1).setRepeated(true);
    textures_holder_.Get_(Textures::kMountains2).setRepeated(true);

    std::unique_ptr<Element> sky(new Element(Textures::kSky, textures_holder_, rect_sky));
    sky->setPosition(scene_bounds_.left, scene_bounds_.top);
    sky->set_velocity(scroll_velocity_.x, 0.f);
    scene_layers_[kBackground]->AttachChild_(std::move(sky));

    std::unique_ptr<Element> mountain_1(new Element(Textures::kMountains1, textures_holder_, rect_total));
    mountain_1->setPosition(scene_bounds_.left, scene_bounds_.top);
    mountain_1->set_velocity(-scroll_velocity_.x / 7.f, 0.f);
    scene_layers_[kBackground]->AttachChild_(std::move(mountain_1));

    std::unique_ptr<Element> mountain_2(new Element(Textures::kMountains2, textures_holder_, rect_total));
    mountain_2->setPosition(scene_bounds_.left, scene_bounds_.top);
    mountain_2->set_velocity(-scroll_velocity_.x * 3.f, 0.f);
    scene_layers_[kBackground]->AttachChild_(std::move(mountain_2));
}

void Scene::CreateCharacters_()
{
	// Character 1: Leader
		std::unique_ptr<Aircraft> leader(new Aircraft(Textures::kAircraftEagle, textures_holder_));
		player_ = leader.get();
		player_->setPosition(spawn_position_);
		player_->set_velocity(scroll_velocity_.x, 0.f);
		player_->setOrigin(64.f, 64.f);

		scene_layers_[kAir]->AttachChild_(std::move(leader));

	// Character 2: Left Scort
		std::unique_ptr<Aircraft> left_escort(new Aircraft(Textures::kRaptorEnemy, textures_holder_));
		left_escort->setPosition(-80.f, 50.f);
		player_->AttachChild_(std::move(left_escort));

	// Character 3: Right Scort
		std::unique_ptr<Aircraft> right_escort(new Aircraft(Textures::kRaptorEnemy, textures_holder_));
		right_escort->setPosition(80.f, 50.f);
		player_->AttachChild_(std::move(right_escort));
}
