#pragma once

#include <QString>
#include <QTcpSocket>
#include <QPixmap>

class NetworkPlayer {
 public:
  explicit NetworkPlayer(QTcpSocket* p_socket);
  size_t GetId() const;
  void SetId(size_t id);
  QTcpSocket* Socket();
  bool IsReady() const;
  void SetIsReady(bool is_ready);

 private:
  size_t id_;
  QTcpSocket* socket_;
  bool is_ready_ = false;
};
