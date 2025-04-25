#ifndef ICONELEVEGROUP_H
#define ICONELEVEGROUP_H

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
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegularExpression>
#include <QtWebSockets/QWebSocket>

class MainWindow;
class VoiceChat;

class iconEleveGroup : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

    protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        QRectF boundingRect()const override;

    private:
        MainWindow* mainWindow;
        QString nom;
        std::vector<iconEleveGroup*> affiliate = {};
        int numero = 0;
        QString IP;
        QGraphicsPixmapItem *checkItem = nullptr;
        QGraphicsPixmapItem *micro = nullptr;
        QGraphicsPixmapItem *sound = nullptr;

    public:
        iconEleveGroup(int numero, QString ip, MainWindow* parentWindow);
        void setCheckItem(QGraphicsPixmapItem *item) { checkItem = item; }
        void setMicro(QGraphicsPixmapItem *item) { micro = item; }
        void setSound(QGraphicsPixmapItem *item) { sound = item; }

        QGraphicsPixmapItem* getCheckItem() { return checkItem; }
        QGraphicsPixmapItem* getMicro() { return micro; }
        QGraphicsPixmapItem* getSound() { return sound; }
        int getId() const;
        QString getIP();

    signals:
        void doubleClicked();
};

#endif // ICONELEVEGROUP_H
