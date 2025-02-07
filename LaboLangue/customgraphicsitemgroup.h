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

class MainWindow;

class CustomGraphicsItemGroup : public QObject, public QGraphicsItemGroup {
    Q_OBJECT
    public:
        CustomGraphicsItemGroup(int numero, QString ip, MainWindow* parentWindow);

    protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
        QRectF boundingRect()const override;
        int getId() const;

    private:
        MainWindow* mainWindow;
        int numero = 0;
        QString IP;

    signals:
        void doubleClicked();
};

#endif // CUSTOMGRAPHICSITEMGROUP_H
