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

        int ID = 0;
        int IDEleve=0;
        QString IP;
        int numQCM = 1;

        QGraphicsPixmapItem *checkItem = nullptr;
        QGraphicsPixmapItem *micro = nullptr;
        QGraphicsPixmapItem *sound = nullptr;
        QGraphicsTextItem *textItem = nullptr;

    public:
        iconEleveGroup(int ID, QString ip, QGraphicsTextItem* text, MainWindow* parentWindow);

        //Setteur
        void setCheckItem(QGraphicsPixmapItem *item) { checkItem = item; }
        void setMicro(QGraphicsPixmapItem *item) { micro = item; }
        void setSound(QGraphicsPixmapItem *item) { sound = item; }
        void setIDELeve(int ID) { IDEleve=ID; }
        void setTextItem(const QString newText) {textItem->setPlainText(newText);};
        void setNom(QString newNom) {nom = newNom;};
        void setNumQCM(int num) {numQCM = num;};

        //Getteur
        QGraphicsTextItem* getTextItem() const {return textItem;};
        QGraphicsPixmapItem* getCheckItem() { return checkItem; }
        QGraphicsPixmapItem* getMicro() { return micro; }
        QGraphicsPixmapItem* getSound() { return sound; }
        int getID() const {return ID;};
        QString getIP() const {return IP;};
        QString getNom() const {return nom;};
        int getIDEleve() const {return IDEleve;};
        int getNumQCM() const {return numQCM;};

    signals:
        void doubleClicked();
};

#endif // ICONELEVEGROUP_H
