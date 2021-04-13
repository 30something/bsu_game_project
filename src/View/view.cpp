#include "src/View/view.h"

View::View(GameController* model, GameMode* game_mode) :
    model_(model),
    players_amount_(game_mode->players_amount) {
  PreparePixmaps(game_mode);
}

void View::PreparePixmaps(const GameMode* game_mode) {
  QPixmap car(":resources/images/cars/car_1.png");
  QPixmap dead_car(":resources/images/cars/car_1_dead.png");
  QPixmap shooting_car(":resources/images/cars/car_1_shoot.png");
  QPixmap mine(":resources/images/other_stuff/mine.png");
  QPixmap health_bonus(":resources/images/other_stuff/hp.png");
  QPixmap bullets_ammo_bonus(":resources/images/other_stuff/ammo.png");
  QPixmap mines_bonus(":resources/images/other_stuff/mines_ammo.png");
  QPixmap map(map_data::image_filepaths[game_mode->map_index]);

  pixmaps_["car"] = car;
  pixmaps_["dead_car"] = dead_car;
  pixmaps_["mine"] = mine;
  pixmaps_["shooting_car"] = shooting_car;
  pixmaps_["bonus_health"] = health_bonus;
  pixmaps_["bonus_bullets_ammo"] = bullets_ammo_bonus;
  pixmaps_["bonus_mine_ammo"] = mines_bonus;
  pixmaps_["map"] = map;

  offsets_["car"] = QPoint(-5, -10);
  offsets_["dead_car"] = QPoint(-5, -10);
  offsets_["shooting_car"] = QPoint(-5, -16);
  offsets_["mine"] = QPoint(-2, -2);
  offsets_["bonus_health"] = QPoint(-5, -5);
  offsets_["bonus_bullets_ammo"] = QPoint(-5, -5);
  offsets_["bonus_mine_ammo"] = QPoint(-5, -5);
  offsets_["map"] = QPoint(0, 0);
}

void View::Repaint(QPainter* painter) {
  std::vector<QRect> frames = GetFramesVector(painter);
  painter->scale(kScale, kScale);
  const auto& cars = model_->GetCars();
  const auto& mines = model_->GetMines();
  const auto& bonuses = model_->GetBonuses();

  for (size_t i = 0; i < frames.size(); i++) {
    DrawMap(painter, frames[i], cars[i]->GetPosition());
    DrawGameObjects(painter, frames[i], cars[i]->GetPosition(), cars);
    DrawGameObjects(painter, frames[i], cars[i]->GetPosition(), mines);
    DrawGameObjects(painter, frames[i], cars[i]->GetPosition(), bonuses);
  }
}

std::vector<QRect> View::GetFramesVector(const QPainter* painter) const {
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

void View::DrawMap(QPainter* painter,
                   const QRect& frame,
                   const Vec2f& pos) {
  painter->drawPixmap(frame.left() / kScale,
                      0,
                      pixmaps_["map"],
                      pos.GetX() - frame.width() / 2 / kScale,
                      pos.GetY() - frame.height() / 2 / kScale,
                      frame.width() / kScale,
                      frame.height() / kScale);
}

void View::DrawGameObjects(QPainter* painter,
                           const QRect& frame,
                           const Vec2f& frame_center,
                           const std::vector<const GameObject*>& game_objects) {
  for (const auto& object : game_objects) {
    double x = frame.left() / kScale + object->GetPosition().GetX()
        - frame_center.GetX()
        + frame.width() / kScale / 2;
    double y = object->GetPosition().GetY() - frame_center.GetY()
        + frame.height() / kScale / 2;
    if (frame.contains(x * kScale, y * kScale)) {
      painter->save();
      painter->translate(x, y);
      painter->rotate(object->GetAngle());
      pixmaps_[object->GetPixmapId()];
      painter->drawPixmap(offsets_[object->GetPixmapId()].x(),
                          offsets_[object->GetPixmapId()].y(),
                          pixmaps_[object->GetPixmapId()]);
      painter->restore();
    }
  }
}
