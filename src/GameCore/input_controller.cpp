#include "input_controller.h"

void InputController::HandleKeyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    keys_condition_[KeyID::kFirstUp] = true;
  }
  if (key == Qt::Key_Down) {
    keys_condition_[KeyID::kFirstDown] = true;
  }
  if (key == Qt::Key_Left) {
    keys_condition_[KeyID::kFirstLeft] = true;
  }
  if (key == Qt::Key_Right) {
    keys_condition_[KeyID::kFirstRight] = true;
  }
  if (key == Qt::Key_Control) {
    keys_condition_[KeyID::kFirstShoot] = true;
  }
  if (key == Qt::Key_Shift) {
    keys_condition_[KeyID::kFirstMine] = true;
  }
  if (key == Qt::Key_W) {
    keys_condition_[KeyID::kSecondUp] = true;
  }
  if (key == Qt::Key_S) {
    keys_condition_[KeyID::kSecondDown] = true;
  }
  if (key == Qt::Key_A) {
    keys_condition_[KeyID::kSecondLeft] = true;
  }
  if (key == Qt::Key_D) {
    keys_condition_[KeyID::kSecondRight] = true;
  }
  if (key == Qt::Key_Alt) {
    keys_condition_[KeyID::kSecondShoot] = true;
  }
  if (key == Qt::Key_Space) {
    keys_condition_[KeyID::kSecondMine] = true;
  }
}

void InputController::HandleKeyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_Up) {
    keys_condition_[KeyID::kFirstUp] = false;
  }
  if (key == Qt::Key_Down) {
    keys_condition_[KeyID::kFirstDown] = false;
  }
  if (key == Qt::Key_Left) {
    keys_condition_[KeyID::kFirstLeft] = false;
  }
  if (key == Qt::Key_Right) {
    keys_condition_[KeyID::kFirstRight] = false;
  }
  if (key == Qt::Key_Control) {
    keys_condition_[KeyID::kFirstShoot] = false;
  }
  if (key == Qt::Key_Shift) {
    keys_condition_[KeyID::kFirstMine] = false;
  }
  if (key == Qt::Key_W) {
    keys_condition_[KeyID::kSecondUp] = false;
  }
  if (key == Qt::Key_S) {
    keys_condition_[KeyID::kSecondDown] = false;
  }
  if (key == Qt::Key_A) {
    keys_condition_[KeyID::kSecondLeft] = false;
  }
  if (key == Qt::Key_D) {
    keys_condition_[KeyID::kSecondRight] = false;
  }
  if (key == Qt::Key_Alt) {
    keys_condition_[KeyID::kSecondShoot] = false;
  }
  if (key == Qt::Key_Space) {
    keys_condition_[KeyID::kSecondMine] = false;
  }
}

const std::map<KeyID, bool>& InputController::GetKeysCondition() const {
  return keys_condition_;
}

InputController::InputController() {
  keys_condition_[KeyID::kFirstUp] = false;
  keys_condition_[KeyID::kFirstDown] = false;
  keys_condition_[KeyID::kFirstLeft] = false;
  keys_condition_[KeyID::kFirstRight] = false;
  keys_condition_[KeyID::kFirstShoot] = false;
  keys_condition_[KeyID::kFirstMine] = false;
  keys_condition_[KeyID::kSecondUp] = false;
  keys_condition_[KeyID::kSecondDown] = false;
  keys_condition_[KeyID::kSecondLeft] = false;
  keys_condition_[KeyID::kSecondRight] = false;
  keys_condition_[KeyID::kSecondShoot] = false;
  keys_condition_[KeyID::kSecondMine] = false;
}
