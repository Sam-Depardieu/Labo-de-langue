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
        QString nomGroupe = "";
        int numQCM = 1;

        QGraphicsPixmapItem *checkItem = nullptr;

        //Image des micro / casque
            QGraphicsPixmapItem *microActiver = nullptr;
            QGraphicsPixmapItem *microDesactiver = nullptr;
            QGraphicsPixmapItem *casqueActiver = nullptr;
            QGraphicsPixmapItem *casqueDesactiver = nullptr;


        QGraphicsPixmapItem *sound = nullptr;
        QGraphicsTextItem *textItem = nullptr;

    public:

        iconEleveGroup(int ID, QString ip, QGraphicsTextItem* text, MainWindow* parentWindow);

            //Setteur
            void setCheckItem(QGraphicsPixmapItem *item) { checkItem = item; }

            // Micro et casque
                void setMicroActiver(QGraphicsPixmapItem *item) { microActiver = item; }
                void setMicroDesactiver(QGraphicsPixmapItem *item) { microDesactiver = item; }
                void setCasqueActiver(QGraphicsPixmapItem *item) { casqueActiver = item; }
                void setCasqueDesactiver(QGraphicsPixmapItem *item) { casqueDesactiver = item; }

            void setSound(QGraphicsPixmapItem *item) { sound = item; }
            void setIDELeve(int ID) { IDEleve=ID; }
            void setTextItem(const QString newText) {textItem->setPlainText(newText);};
            void setNom(QString newNom) {nom = newNom;};
            void setNumQCM(int num) {numQCM = num;};
            void setNomGroupe(QString nomG) {nomGroupe = nomG;};

            //Getteur
                QString getNomGroupe() {return nomGroupe;};
                std::vector<iconEleveGroup*> getAffiliate() {return affiliate;};
                QGraphicsTextItem* getTextItem() const {return textItem;};
                QGraphicsPixmapItem* getCheckItem() { return checkItem; }

                // Micro et casque
                    QGraphicsPixmapItem* getMicroActiver() { return microActiver; }
                    QGraphicsPixmapItem* getMicroDesactiver() { return microDesactiver; }
                    QGraphicsPixmapItem* getCasqueActiver() { return casqueActiver; }
                    QGraphicsPixmapItem* getCasqueDesactiver() { return casqueDesactiver; }


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
