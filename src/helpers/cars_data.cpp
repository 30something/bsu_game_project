#include "cars_data.h"

CarsData::CarsData(uint32_t players_amount) {
  cars_data.resize(players_amount);
}

double CarsData::GetVelocity(int index) const {
  double current_velocity = cars_data[index].current_showed_velocity;
  return current_velocity < kMinVisibleVelocity ? 0 : current_velocity;
}

int32_t CarsData::GetLapsCounter(int index) const {
  return cars_data[index].laps_counter;
}

void CarsData::UpdateCarsData(
    const std::vector<CarAchievements>& new_cars_data) {
  cars_data = new_cars_data;
}
