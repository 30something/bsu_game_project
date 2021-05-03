#pragma once

enum class MessageType {
  kPlayersVector,
  kReadyStatus
};

struct NetworkData {
  QVariant data;
  MessageType type;
};
