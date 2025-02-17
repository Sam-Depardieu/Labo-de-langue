#ifndef CUSTOMGRAPHICSITEMGROUP_H
#define CUSTOMGRAPHICSITEMGROUP_H

//#include <QAudioOutput>
//#include <QMediaPlayer>

#include <QObject>
#include <QMainWindow>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QVariant>
#include <QKeyEvent>
#include <QDebug>
#include <QPalette>
#include <QRectF>
#include <QVBoxLayout>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QDate>

class MainWindow;
class VoiceChat;

class CustomGraphicsItemGroup : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
    public:
        CustomGraphicsItemGroup(int numero, QString ip, MainWindow* parentWindow);
        void setCheckItem(QGraphicsPixmapItem *item) { checkItem = item; }
        QGraphicsPixmapItem* getCheckItem() { return checkItem; }

    protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        QRectF boundingRect()const override;
        int getId() const;

    private:
        MainWindow* mainWindow;
        int numero = 0;
        QString IP;
        QGraphicsPixmapItem *checkItem = nullptr;

    signals:
        void doubleClicked();
};

#endif // CUSTOMGRAPHICSITEMGROUP_H
