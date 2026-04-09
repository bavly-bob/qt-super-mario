#include "player.hpp"

#include <QGraphicsScene>
#include <QMessageBox>
#include <QPixmap>

Player::Player(QGraphicsItem* parent)
    : QObject(),
      QGraphicsPixmapItem(parent),
      velocityY(0),
      onGround(false),
      spawnPos(300, 0) {
  setPixmap(QPixmap("assets/player.png"));
  setPos(spawnPos);

  setFlag(QGraphicsItem::ItemIsFocusable);
  setFocus();
}

void Player::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Left) {
    moveBy(-10, 0);
  }
  if (event->key() == Qt::Key_Right) {
    moveBy(10, 0);
  }
  if (event->key() == Qt::Key_Space && onGround) {
    velocityY = -15;
  }
}

void Player::updateState() {
  velocityY += 1;
  onGround = false;
  moveBy(0, velocityY);

  if (scene() && y() > scene()->sceneRect().bottom()) {
    velocityY = 0;
    setPos(spawnPos);
    QMessageBox::information(nullptr, "Game Over", "You lost!");
    return;
  }

  const QList<QGraphicsItem*> items = collidingItems();
  if (items.isEmpty()) {
    return;
  }

  if (velocityY >= 0) {
    const QRectF playerRect = sceneBoundingRect();
    const QRectF previousRect = playerRect.translated(0, -velocityY);
    const qreal playerHeight = boundingRect().height();
    const qreal previousBottom = previousRect.bottom();
    const qreal currentBottom = playerRect.bottom();

    bool landed = false;
    qreal bestTop = 0;

    for (QGraphicsItem* item : items) {
      const QRectF itemRect = item->sceneBoundingRect();
      if (previousBottom <= itemRect.top() && currentBottom >= itemRect.top()) {
        if (!landed || itemRect.top() < bestTop) {
          bestTop = itemRect.top();
          landed = true;
        }
      }
    }

    if (landed) {
      setY(bestTop - playerHeight);
      velocityY = 0;
      onGround = true;
    }
  }
}
