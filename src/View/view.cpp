#include "src/View/view.h"

View::View(QWidget *events_controller, GameController *model,
           GameMode *game_mode) :
        model_(model),
        car_(":resources/images/cars/car_1.png"),
        dead_car_(":resources/images/cars/car_1_dead.png"),
        mine_(":resources/images/other_stuff/mine.png"),
        shot_(":resources/images/other_stuff/shot.png"),
        health_bonus_(":resources/images/other_stuff/hp.png"),
        bullets_ammo_bonus_(":resources/images/other_stuff/ammo.png"),
        mines_bonus_(":resources/images/other_stuff/mines_ammo.png"),
        players_amount_(game_mode->players_amount),
        engine_sound_(new Engine(events_controller)),
        drift_sound_(new Drift(events_controller)),
        brake_sound_(new Brake(events_controller)),
        sounds_of_effects_(new Effects(events_controller)) {
    map_.load(map_data::image_filepaths[game_mode->map_index]);
}

void View::Repaint(QPainter *painter) {
    std::vector<QRect> frames = GetFramesVector(painter);
    painter->scale(kScale, kScale);
    const auto &cars = model_->GetCars();
    const auto &mines = model_->GetMinesCoordinates();
    const auto &bonuses = model_->GetActiveBonuses();
    for (size_t i = 0; i < frames.size(); i++) {
        DrawMap(painter, frames[i], cars[i].GetPosition());
        for (size_t j = 0; j < cars.size(); j++) {
            DrawPicture(
                    painter,
                    frames[i],
                    cars[i].GetPosition(),
                    cars[j].GetPosition(),
                    cars[j].GetAngle(),
                    (cars[j].IsAlive() ? car_ : dead_car_),
                    QPoint(-5, -10));
            if (cars[j].IsShooting()) {
                DrawPicture(
                        painter,
                        frames[i],
                        cars[i].GetPosition(),
                        cars[j].GetPosition(),
                        cars[j].GetAngle(),
                        shot_,
                        QPoint(-2, -20));
            }
        }
        for (const auto &mine : mines) {
            DrawPicture(
                    painter,
                    frames[i],
                    cars[i].GetPosition(),
                    Vec2f(mine.x(), mine.y()),
                    0,
                    mine_,
                    QPoint(-2, -2));
        }
        for (const auto &bonus : bonuses) {
            QPixmap bonus_pixmap;
            switch (bonus.GetType()) {
                case Bonus::BonusType::kHealth: {
                    bonus_pixmap = health_bonus_;
                    break;
                }
                case Bonus::BonusType::kBulletsAmmo: {
                    bonus_pixmap = bullets_ammo_bonus_;
                    break;
                }
                case Bonus::BonusType::kMineAmmo: {
                    bonus_pixmap = mines_bonus_;
                    break;
                }
            }
            DrawPicture(
                    painter,
                    frames[i],
                    cars[i].GetPosition(),
                    Vec2f(bonus.GetPosition().x(), bonus.GetPosition().y()),
                    0,
                    bonus_pixmap,
                    QPoint(-5, -5));
        }
    }
}

std::vector<QRect> View::GetFramesVector(const QPainter *painter) const {
    std::vector<QRect> frames;
    if (players_amount_ == 1) {
        frames.emplace_back(0,
                            0,
                            painter->window().width(),
                            painter->window().height());
    } else {
        frames.emplace_back(0,
                            0,
                            painter->window().width() / 2,
                            painter->window().height());
        frames.emplace_back(painter->window().width() / 2,
                            0,
                            painter->window().width() / 2,
                            painter->window().height());
    }
    return frames;
}

void View::DrawMap(QPainter *painter,
                   const QRect &frame,
                   const Vec2f &pos) {
    painter->drawPixmap(frame.left() / kScale,
                        0,
                        map_,
                        pos.GetX() - frame.width() / 2 / kScale,
                        pos.GetY() - frame.height() / 2 / kScale,
                        frame.width() / kScale,
                        frame.height() / kScale);
}

void View::DrawPicture(QPainter *painter,
                       const QRect &frame,
                       const Vec2f &frame_center,
                       const Vec2f &coords,
                       double angle,
                       const QPixmap &pixmap,
                       const QPoint &offset) const {
    double x = frame.left() / kScale + coords.GetX() - frame_center.GetX()
               + frame.width() / kScale / 2;
    double y = coords.GetY() - frame_center.GetY()
               + frame.height() / kScale / 2;
    if (frame.contains(x * kScale, y * kScale)) {
        painter->save();
        painter->translate(x, y);
        painter->rotate(angle);
        painter->drawPixmap(offset.x(), offset.y(), pixmap);
        painter->restore();
    }
}

void View::PlayEngine(double coefficient, int direction, bool car_is_alive) {
    engine_sound_->Play(coefficient, direction, car_is_alive);
}

void View::PlayDrift(double coefficient) {
    drift_sound_->Play(coefficient);
}

void View::PlayBrake(double coefficient) {
    brake_sound_->Play(coefficient);
}

void View::PlayBonus(bool play_bonus) {
    sounds_of_effects_->PlayBonus(play_bonus);
    model_->SetNoBonusIsApplied();
}

void View::PlayShooting(bool using_gun, bool bullets) {
    sounds_of_effects_->PlayShooting(using_gun, bullets);
}

void View::PlayMine(bool play_mine) {
    sounds_of_effects_->PlayMine(play_mine);
}

void View::PlayCarExplosion(bool play_car_explosion) {
    sounds_of_effects_->PlayCarExplosion(play_car_explosion);
}
