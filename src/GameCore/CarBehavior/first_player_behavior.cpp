#include "first_player_behavior.h"

void FirstPlayerBehavior::HandleTick(GameObject*) {}

void FirstPlayerBehavior::HandleKeyPressEvent(GameObject* object,
                                              QKeyEvent* event) {
  Car* car = dynamic_cast<Car*>(object);
  int key = event->key();
  if (car->IsAlive()) {
    if (key == Qt::Key_Up) {
      car->SetFlagUp(true);
    }
    if (key == Qt::Key_Down) {
      car->SetFlagDown(true);
    }
    if (key == Qt::Key_Left) {
      car->SetFlagLeft(true);
    }
    if (key == Qt::Key_Right) {
      car->SetFlagRight(true);
    }
    if (key == Qt::Key_Control) {
      car->SetIsShooting(true);
    }
    if (key == Qt::Key_Shift) {
      car->SetIsPuttingMine(true);
    }
  }
}

void FirstPlayerBehavior::HandleKeyReleaseEvent(GameObject* object,
                                                QKeyEvent* event) {
  Car* car = dynamic_cast<Car*>(object);
  int key = event->key();
  if (key == Qt::Key_Up) {
    car->SetFlagUp(false);
  }
  if (key == Qt::Key_Down) {
    car->SetFlagDown(false);
  }
  if (key == Qt::Key_Left) {
    car->SetFlagLeft(false);
  }
  if (key == Qt::Key_Right) {
    car->SetFlagRight(false);
  }
  if (key == Qt::Key_Control) {
    car->SetIsShooting(false);
  }
}
