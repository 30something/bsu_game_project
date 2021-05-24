#include "cars_data.h"

CarsData::CarsData(std::vector<CarAchievements> new_cars_data)
    : cars_data(std::move(new_cars_data)) {
}

size_t CarsData::GetVelocity(int index) const {
  double current_velocity = cars_data[index].current_showed_velocity;
  return current_velocity < kMinVisibleVelocity ?
         0 : static_cast<size_t>(current_velocity);
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

size_t CarsData::GetElapsedTime(int index) const {
  return cars_data[index].elapsed_millis_time;
}

size_t CarsData::GetFinishPosition(int index) const {
  return cars_data[index].finish_position;
}

size_t CarsData::GetCurrentOrderPosition(int index) const {
  return cars_data[index].current_order_position;
}

size_t CarsData::GetNumber(int index) const {
  return cars_data[index].car_number;
}

double CarsData::GetHP(int index) const {
  return std::max(cars_data[index].hit_points_, 0.);
}

