#pragma once

enum class MessageType {
  kPlayersVector,
  kReadyStatus,
  kSignalToStart
};

struct NetworkData {
  QVariant data;
  MessageType type;
};
