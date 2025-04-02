#include "iconEleveGroup.h"
#include "mainwindow.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

iconEleveGroup::iconEleveGroup(int numero, QString ip, MainWindow* parentWindow) : QGraphicsItemGroup(), numero(numero), IP(ip), mainWindow(parentWindow) {
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void iconEleveGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (mainWindow->parametrageSession && mainWindow->selectionParticipants) {
        auto it = std::find(mainWindow->listeParticipant.begin(), mainWindow->listeParticipant.end(), this);

        if (it == mainWindow->listeParticipant.end()) {
            // Ajouter l'élément s'il n'est pas présent
            mainWindow->listeParticipant.push_back(this);
        } else {
            // Supprimer l'élément s'il est déjà présent
            mainWindow->listeParticipant.erase(it);
        }

        // Afficher/Masquer l'icône check
        if (checkItem) {
            checkItem->setVisible(!checkItem->isVisible());
        }
    }
    else if(!mainWindow->selectionParticipants){ //Il faudra une session en cours.
        if(!mainWindow->parametrageEleve)
        {
            mainWindow->openSettingEleve(this);

            mainWindow->parametrageEleve = true;
            qDebug() << " IP : " << getIP();
        }
        else
        {
            mainWindow->closeSettingEleve(this);

            mainWindow->parametrageEleve = false;
        }
    }
    QGraphicsItemGroup::mouseDoubleClickEvent(event);

    // 🔹 Remplacez l'IP et les ports pour correspondre à votre réseau
    // VoiceChat chat(QHostAddress("192.168.88.150"), 12345, 12346);

}

QVariant iconEleveGroup::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange) {
        QPointF newPos = value.toPointF();
        QRectF sceneBounds = scene() ? scene()->sceneRect() : QRectF();  // Vérifier que la scène existe

        if (sceneBounds.isNull()) {
            return QGraphicsItemGroup::itemChange(change, value);  // Éviter de modifier si la scène n'est pas définie
        }

        // Taille du groupe
        QRectF itemBounds = boundingRect();

        // Vérifier les limites et ajuster la position
        if (newPos.x() < sceneBounds.left()) {
            newPos.setX(sceneBounds.left());
        }
        if (newPos.y() < sceneBounds.top()) {
            newPos.setY(sceneBounds.top());
        }
        if (newPos.x() + itemBounds.width() > sceneBounds.right()) {
            newPos.setX(sceneBounds.right() - itemBounds.width());
        }
        if (newPos.y() + itemBounds.height() > sceneBounds.bottom()) {
            newPos.setY(sceneBounds.bottom() - itemBounds.height());
        }

        // Mettre à jour la position dans la base de données
        QSqlQuery query;
        query.prepare("UPDATE Raspberry SET X = :x, Y = :y WHERE Id_Raspberry = :numPoste");
        query.bindValue(":x", newPos.x());
        query.bindValue(":y", newPos.y());
        query.bindValue(":numPoste", numero);  // Utiliser l'identifiant de la poste
        if (!query.exec()) {
            qDebug() << "Erreur lors de la mise à jour de la position :" << query.lastError();
        }

        return newPos;
    }

    return QGraphicsItemGroup::itemChange(change, value);
}


QRectF iconEleveGroup::boundingRect() const
{
    QRectF rect = childrenBoundingRect();
    return rect;
}

int iconEleveGroup::getId() const{
    return numero;
}

QString iconEleveGroup::getIP()
{
    return IP;
}
