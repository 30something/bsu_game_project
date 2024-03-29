#pragma once

#include <map>

#include <QKeyEvent>

enum class KeyID {
  kFirstUp,
  kFirstDown,
  kFirstLeft,
  kFirstRight,
  kFirstShoot,
  kFirstMine,
  kSecondUp,
  kSecondDown,
  kSecondLeft,
  kSecondRight,
  kSecondShoot,
  kSecondMine
};

class InputController {
 public:
  InputController();

  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);
  void ResetAllKeys();
  const std::map<KeyID, bool>& GetKeysCondition() const;

 private:
  std::map<KeyID, bool> keys_condition_;

  void SetKeyConditions(QKeyEvent* event, bool value);
};
