#pragma once

#include <QVariant>

#include "src/helpers/vec2f.h"


enum class MessageType {
  kPlayersVector,
  kReadyStatus,
  kSignalToStart,
  kPlayersCarData
};

struct NetworkData {
  QVariant data;
  MessageType type;
};

struct PlayerCarData {
  Vec2f position;
  Vec2f angle;
  double hp;
  bool flag_up;
  bool flag_down;
  bool flag_left;
  bool flag_right;
  bool flag_shoot;
  bool flag_mine;
  bool is_updated;
};
