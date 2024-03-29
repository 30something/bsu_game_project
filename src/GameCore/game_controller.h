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
#include "src/helpers/cars_data.h"
#include "src/GameCore/Behaviors/first_player_behavior.h"
#include "src/GameCore/Behaviors/second_player_behavior.h"
#include "src/GameCore/Behaviors/bot_behavior.h"
#include "src/GameCore/Behaviors/network_player_behavior.h"
#include "input_controller.h"
#include "src/helpers/wrapper_template.h"
#include "src/helpers/cars_colors.h"
#include "src/helpers/parameters_for_sounds.h"
#include "src/GameCore/GameObjects/animation.h"
#include "src/Network/network_controller.h"
#include "src/helpers/client_car_data_sender.h"

class GameController : public QObject {
  Q_OBJECT

 public:
  explicit GameController(GameMode* game_mode, InputController*);
  ~GameController() override;

  void Tick(int time_millis);

  std::vector<WrapperBase<GameObject>*> GetGameObjects() const;
  std::vector<Vec2f> GetPlayersCarPositions() const;
  std::vector<EngineParameters> GetParametersForEngineSound() const;
  std::vector<DriftParameters> GetParametersForDriftSound() const;
  std::vector<BrakeParameters> GetParametersForBrakeSound() const;
  std::vector<ShootingParameters> GetParametersForShootingSound() const;
  EffectParameters GetParametersForMineExplosionSound() const;
  EffectParameters GetParametersForCarExplosionSound();
  double GetDistance(uint32_t i, uint32_t j) const;
  bool BonusIsApplied() const;
  bool BonusOfPlayersIsApplied() const;

  bool IsGameFinished() const;
  std::vector<CarAchievements> GetCarsData() const;

  void UpdateAnimations();

 private:
  void AddCar(Vec2f position,
              double angle,
              Behavior* behavior,
              CarsColors car_color);
  void SetUpCars(const InputController* input_controller);
  void SetUpCarsNetwork(const InputController* input_controller);
  void SetUpBots();
  void SetUpCarsAchievements();
  void SetNoBonusIsApplied();
  void ProceedCollisionsWithCars();
  void ProceedCollisionsWithFinish();
  void ProceedFinishGame();
  void RecalculateDeviations();

  void UpdateVolumeParameters(std::vector<double>* volume_parameters);
  void ChangingParameterForBonusSound(uint32_t i);
  void ChangingParametersForExplosionSound(uint32_t i);

  void UpdateOrderPositions();
  void UpdateCarsInfoAndCollisions(int time_millis);
  void UpdateCarAchievements(uint32_t index, const Car& car);
  void EnableWeapons();
  static void CollideCars(Car* car_1, Car* car_2);
  std::set<CarsColors> SetBotsColors() const;
  bool SwapOrderPositions(uint32_t first_car, uint32_t second_car);

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
  std::vector<Animation> animations_;
  QTimer weapons_timer_;
  NetworkController* network_controller_;
  ClientCarDataSender* client_car_data_sender_ = nullptr;
  int32_t next_position_to_finish_ = 1;

  bool bonus_is_applied_ = false;
  std::vector<bool> exploded_cars_;
  std::vector<double> volume_parameters_;
};
