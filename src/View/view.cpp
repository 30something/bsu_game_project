#include "src/helpers/sizes.h"
#include "src/View/view.h"

View::View(QWidget *events_controller, GameMode *game_mode) :
        pixmap_loader_(
                map_data::image_file_paths.maps_file_paths[game_mode->map_index]),
        players_amount_(game_mode->players_amount),
        cars_amount_(
                game_mode->players_amount + game_mode->network_players_amount +
                game_mode->bots_amount),
        game_mode_(game_mode),
        sounds_of_effects_(new Effects(events_controller)) {
    engine_sounds_.reserve(cars_amount_);
    drift_sounds_.reserve(cars_amount_);
    brake_sounds_.reserve(cars_amount_);
    shooting_sounds_.reserve(cars_amount_);

    for (uint32_t i = 0; i < cars_amount_; i++) {
        engine_sounds_.push_back(new Engine(
                events_controller, game_mode_->volume_settings_parameter));
        drift_sounds_.push_back(new Drift(events_controller));
        brake_sounds_.push_back(new Brake(events_controller));
        shooting_sounds_.push_back(new Shooting(events_controller));
    }
}

void View::Repaint(const std::vector<WrapperBase<GameObject> *> &objects,
                   const std::vector<Vec2f> &cars_positions,
                   QPainter *painter) {
    painter->scale(scale_, scale_);
    for (size_t i = 0; i < frames_.size(); i++) {
        Vec2f position = cars_positions[i];
        DrawMap(painter, frames_[i], position);
        DrawObjects(painter, frames_[i], position, objects);
    }
}

void View::UpdateFrames(int width, int height) {
    frames_.clear();
    if (players_amount_ == 1) {
        frames_.emplace_back(0,
                             0,
                             width,
                             height);
    } else {
        frames_.emplace_back(0,
                             0,
                             width / 2,
                             height);
        frames_.emplace_back(width / 2,
                             0,
                             width / 2,
                             height);
    }
}

std::vector<QRect> View::GetFrames() const {
    return frames_;
}

double View::GetScale() const {
    return scale_;
}

void View::CalculateScale(int window_width, int window_height) {
    double screen_diagonal =
            std::hypot(window_width, window_height);
    screen_diagonal *= car_sizes::kPercentageOfCarSizeOnSceeen;
    screen_diagonal /= 100;
    screen_diagonal /= car_sizes::kCarDiagonalInPixels;
    scale_ = screen_diagonal;
}

void View::DrawMap(QPainter *painter,
                   const QRect &frame,
                   const Vec2f &pos) {
    painter->drawPixmap(frame.left() / scale_,
                        0,
                        pixmap_loader_.GetMapPixmap(),
                        pos.GetX() - frame.width() / 2 / scale_,
                        pos.GetY() - frame.height() / 2 / scale_,
                        frame.width() / scale_,
                        frame.height() / scale_);
}

void View::DrawObjects(QPainter *painter,
                       const QRect &frame,
                       const Vec2f &frame_center,
                       const std::vector<WrapperBase<GameObject> *> &objects) {
    for (const auto &object : objects) {
        for (size_t i = 0; i < object->Size(); i++) {
            double x = frame.left() / scale_ + (*object)[i].GetPosition().GetX()
                       - frame_center.GetX()
                       + frame.width() / scale_ / 2;
            double y = (*object)[i].GetPosition().GetY() - frame_center.GetY()
                       + frame.height() / scale_ / 2;
            if (frame.contains(x * scale_, y * scale_)) {
                painter->save();
                painter->translate(x, y);
                painter->rotate((*object)[i].GetAngle());
                QPixmap pixmap = pixmap_loader_.GetPixmap(
                        (*object)[i].GetPixmapId());
                painter->drawPixmap(-(pixmap.width() / 2),
                                    -(pixmap.height() / 2),
                                    pixmap);
                painter->restore();
            }
        }
    }
}

void View::resizeEvent(int width, int height) {
    CalculateScale(width, height);
    UpdateFrames(width, height);
}

void View::PlayEngine(const std::vector<EngineParameters> &engine_parameters,
                      bool pause) {
    for (uint32_t i = 0; i < cars_amount_; i++) {
        engine_sounds_.at(i)->Play(engine_parameters.at(i).speed_parameter,
                                   engine_parameters.at(i).motion_parameter,
                                   engine_parameters.at(i).volume_parameter,
                                   game_mode_->volume_settings_parameter,
                                   pause);
    }

}

void
View::PlayDrift(std::vector<DriftParameters> drift_parameters, bool pause) {
    for (uint32_t i = 0; i < cars_amount_; i++) {
        drift_sounds_.at(i)->Play(drift_parameters.at(i).speed_parameter,
                                  drift_parameters.at(i).enable_drifting,
                                  drift_parameters.at(i).volume_parameter,
                                  game_mode_->volume_settings_parameter,
                                  pause);
    }
}

void
View::PlayBrake(std::vector<BrakeParameters> brake_parameters, bool pause) {
    for (uint32_t i = 0; i < cars_amount_; i++) {
        brake_sounds_.at(i)->Play(brake_parameters.at(i).speed_parameter,
                                  brake_parameters.at(i).volume_parameter,
                                  game_mode_->volume_settings_parameter,
                                  pause);
    }
}

void View::PlayBonus(bool play_bonus) {
    sounds_of_effects_.PlayBonus(play_bonus,
                                 game_mode_->volume_settings_parameter);
}

void View::PlayShooting(std::vector<ShootingParameters> shooting_parameters,
                        bool pause) {
    for (uint32_t i = 0; i < cars_amount_; i++) {
        shooting_sounds_.at(i)->Play(shooting_parameters.at(i).using_gun,
                                     shooting_parameters.at(i).bullets,
                                     shooting_parameters.at(i).enable_weapons,
                                     shooting_parameters.at(i).volume_parameter,
                                     game_mode_->volume_settings_parameter,
                                     pause);
    }
}

void View::PlayMine(EffectParameters explosion_parameters) {
    sounds_of_effects_.PlayMine(explosion_parameters.play,
                                explosion_parameters.volume_parameter,
                                game_mode_->volume_settings_parameter);
}

void View::PlayCarExplosion(EffectParameters explosion_parameters) {
    sounds_of_effects_.PlayCarExplosion(explosion_parameters.play,
                                        explosion_parameters.volume_parameter,
                                        game_mode_->volume_settings_parameter);
}

