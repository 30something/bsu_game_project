#include "second_player_behavior.h"

void SecondPlayerBehavior::HandleTick() {}

void SecondPlayerBehavior::HandleKeyPressEvent(GameObject* object,
                                              QKeyEvent* event) {
  Car* car = dynamic_cast<Car*>(object);
  int key = event->key();
  if (car->IsAlive()) {
    if (key == Qt::Key_W) {
      car->SetFlagUp(true);
    }
    if (key == Qt::Key_S) {
      car->SetFlagDown(true);
    }
    if (key == Qt::Key_A) {
      car->SetFlagLeft(true);
    }
    if (key == Qt::Key_D) {
      car->SetFlagRight(true);
    }
    if (key == Qt::Key_Alt) {
      car->SetIsShooting(true);
    }
    if (key == Qt::Key_Space) {
      car->SetIsPuttingMine(true);
    }
  }
}

void SecondPlayerBehavior::HandleKeyReleaseEvent(GameObject* object,
                                                QKeyEvent* event) {
  Car* car = dynamic_cast<Car*>(object);
  int key = event->key();
  if (key == Qt::Key_W) {
    car->SetFlagUp(false);
  }
  if (key == Qt::Key_S) {
    car->SetFlagDown(false);
  }
  if (key == Qt::Key_A) {
    car->SetFlagLeft(false);
  }
  if (key == Qt::Key_D) {
    car->SetFlagRight(false);
  }
  if (key == Qt::Key_Alt) {
    car->SetIsShooting(false);
  }
}
