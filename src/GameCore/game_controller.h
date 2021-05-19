#pragma once

#include <set>
#include <utility>
#include <vector>

#include <QKeyEvent>
#include <QTextStream>
#include <QFile>
#include <QPoint>
#include <QObject>

#include "src/GameCore/GameObjects/car.h"
#include "game_map.h"
#include "weapon_handler.h"
#include "src/helpers/json_map_parser.h"
#include "src/helpers/car_achievements.h"
#include "src/GameCore/Behaviors/first_player_behavior.h"
#include "src/GameCore/Behaviors/second_player_behavior.h"
#include "src/GameCore/Behaviors/bot_behavior.h"
#include "src/GameCore/Behaviors/network_player_behavior.h"
#include "input_controller.h"
#include "src/helpers/wrapper_template.h"
#include "src/helpers/cars_colors.h"
#include "src/Network/network_controller.h"
#include "src/helpers/client_car_data_sender.h"

class GameController : public QObject {
  Q_OBJECT

 public:
  explicit GameController(GameMode* game_mode, InputController*);
  ~GameController() override = default;

  void Tick(int time_millis);

  std::vector<WrapperBase<GameObject>*> GetGameObjects() const;
  std::vector<Vec2f> GetPlayersCarPositions() const;

  bool IsGameFinished() const;
  std::vector<CarAchievements> GetCarsData() const;

 private:
  void AddCar(Vec2f position,
              double angle,
              Behavior* behavior,
              CarsColors car_color);
  void SetUpCars(const InputController* input_controller);
  void SetUpCarsNetwork(const InputController* input_controller);
  void SetUpBots();
  void SetUpCarsAchievements();
  void ProceedCollisionsWithCars();
  void ProceedCollisionsWithFinish();
  void ProceedFinishGame();
  void RecalculateDeviations();
  void UpdateCarsInfoAndCollisions(int time_millis);
  void EnableWeapons();
  static void CollideCars(Car* car_1, Car* car_2);
  std::set<CarsColors> SetBotsColors() const;

  static constexpr double kVelocityDecrease = 0.5;
  static constexpr double kDeviationDecrease = 0.5;
  static constexpr double kHPDecrease = 0.005;
  static constexpr double kMillisWeaponsEnable = 10000;
  static constexpr size_t kMillisPerCarTimeUpdate = 5;

  Map map_;
  Line finish_line_;
  std::vector<Car> cars_;
  std::vector<CarAchievements> car_achievements_;
  std::set<uint32_t> remaining_cars_;
  std::set<uint32_t> remaining_players_;
  GameMode* game_mode_ = nullptr;
  WeaponHandler weapon_handler_;
  std::vector<WrapperBase<GameObject>*> game_objects_;
  QTimer weapons_timer_;
  NetworkController* network_controller_;
  int32_t next_position_to_finish_ = 1;
};
