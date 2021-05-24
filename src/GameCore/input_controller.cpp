#include "input_controller.h"

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

void InputController::HandleKeyPressEvent(QKeyEvent* event) {
    SetKeyConditions(event, true);
}

void InputController::HandleKeyReleaseEvent(QKeyEvent* event) {
    SetKeyConditions(event, false);
}

void InputController::ResetAllKeys() {
    for (auto& condition : keys_condition_) {
        condition.second = false;
    }
}

const std::map<KeyID, bool>& InputController::GetKeysCondition() const {
    return keys_condition_;
}

void InputController::SetKeyConditions(QKeyEvent* event, bool value) {
    int key = event->key();
    if (key == Qt::Key_Up) {
        keys_condition_[KeyID::kFirstUp] = value;
    }
    if (key == Qt::Key_Down) {
        keys_condition_[KeyID::kFirstDown] = value;
    }
    if (key == Qt::Key_Left) {
        keys_condition_[KeyID::kFirstLeft] = value;
    }
    if (key == Qt::Key_Right) {
        keys_condition_[KeyID::kFirstRight] = value;
    }
    if (key == Qt::Key_O) {
        keys_condition_[KeyID::kFirstShoot] = value;
    }
    if (key == Qt::Key_P) {
        keys_condition_[KeyID::kFirstMine] = value;
    }
    if (key == Qt::Key_W) {
        keys_condition_[KeyID::kSecondUp] = value;
    }
    if (key == Qt::Key_S) {
        keys_condition_[KeyID::kSecondDown] = value;
    }
    if (key == Qt::Key_A) {
        keys_condition_[KeyID::kSecondLeft] = value;
    }
    if (key == Qt::Key_D) {
        keys_condition_[KeyID::kSecondRight] = value;
    }
    if (key == Qt::Key_C) {
        keys_condition_[KeyID::kSecondShoot] = value;
    }
    if (key == Qt::Key_V) {
        keys_condition_[KeyID::kSecondMine] = value;
    }
}


