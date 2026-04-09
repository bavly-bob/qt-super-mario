#pragma once

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <QPointF>

class Player : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT

 public:
  Player(QGraphicsItem* parent = nullptr);

 public slots:
  void updateState();

 protected:
  void keyPressEvent(QKeyEvent* event) override;

 private:
  int velocityY;
  bool onGround;
  QPointF spawnPos;
};
