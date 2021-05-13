#include "cars_data.h"

CarsData::CarsData(const std::vector<CarAchievements>& new_cars_data) {
  cars_data = new_cars_data;
}

double CarsData::GetVelocity(int index) const {
  double current_velocity = cars_data[index].current_showed_velocity;
  return current_velocity < kMinVisibleVelocity ? 0 : current_velocity;
}

int32_t CarsData::GetLapsCounter(int index) const {
  return cars_data[index].laps_counter;
}
size_t CarsData::GetBulletsAmount(int index) const {
  return cars_data[index].bullets_amount_;
}

size_t CarsData::GetMinesAmount(int index) const {
  return cars_data[index].mines_amount_;
}

double CarsData::GetHP(int index) const {
  return std::max(cars_data[index].hit_points_, 0.);
}

size_t CarsData::GetElapsedTime(int index) const {
  return cars_data[index].elapsed_millis_time;
}
