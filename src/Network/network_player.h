#pragma once

#include <QString>
#include <QTcpSocket>
#include <QPixmap>

class NetworkPlayer {
 public:
  NetworkPlayer();
  const QString& GetNickname() const;
  void SetNickname(const QString& nickname);
  QTcpSocket* Socket();
  bool IsReady() const;
  void SetIsReady(bool is_ready);

 private:
  QString nickname_;
  QTcpSocket socket_;
  bool is_ready_ = false;
};
