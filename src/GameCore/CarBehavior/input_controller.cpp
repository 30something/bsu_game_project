#include "input_controller.h"

void InputController::HandleKeyPressEvent(QKeyEvent* event,
                                          Car* first_car,
                                          Car* second_car) {
  int key = event->key();
  if (first_car->IsAlive()) {
    if (key == Qt::Key_Up) {
      first_car->SetFlagUp(true);
    }
    if (key == Qt::Key_Down) {
      first_car->SetFlagDown(true);
    }
    if (key == Qt::Key_Left) {
      first_car->SetFlagLeft(true);
    }
    if (key == Qt::Key_Right) {
      first_car->SetFlagRight(true);
    }
    if (key == Qt::Key_Control) {
      first_car->SetIsShooting(true);
    }
    if (key == Qt::Key_Shift) {
      first_car->SetIsPuttingMine(true);
    }
  }
  if (second_car != nullptr && second_car->IsAlive()) {
    if (key == Qt::Key_W) {
      second_car->SetFlagUp(true);
    }
    if (key == Qt::Key_S) {
      second_car->SetFlagDown(true);
    }
    if (key == Qt::Key_A) {
      second_car->SetFlagLeft(true);
    }
    if (key == Qt::Key_D) {
      second_car->SetFlagRight(true);
    }
    if (key == Qt::Key_Alt) {
      second_car->SetIsShooting(true);
    }
    if (key == Qt::Key_Space) {
      second_car->SetIsPuttingMine(true);
    }
  }
}

void InputController::HandleKeyReleaseEvent(QKeyEvent* event,
                                            Car* first_car,
                                            Car* second_car) {
  int key = event->key();
  if (first_car->IsAlive()) {
    if (key == Qt::Key_Up) {
      first_car->SetFlagUp(false);
    }
    if (key == Qt::Key_Down) {
      first_car->SetFlagDown(false);
    }
    if (key == Qt::Key_Left) {
      first_car->SetFlagLeft(false);
    }
    if (key == Qt::Key_Right) {
      first_car->SetFlagRight(false);
    }
    if (key == Qt::Key_Control) {
      first_car->SetIsShooting(false);
    }
  }
  if (second_car != nullptr && second_car->IsAlive()) {
    if (key == Qt::Key_W) {
      second_car->SetFlagUp(false);
    }
    if (key == Qt::Key_S) {
      second_car->SetFlagDown(false);
    }
    if (key == Qt::Key_A) {
      second_car->SetFlagLeft(false);
    }
    if (key == Qt::Key_D) {
      second_car->SetFlagRight(false);
    }
    if (key == Qt::Key_Alt) {
      second_car->SetIsShooting(false);
    }
  }
}
