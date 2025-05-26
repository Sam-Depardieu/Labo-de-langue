
#include "avancementqcm.h"

AvancementQCM::AvancementQCM(QObject *parent) : QStyledItemDelegate(parent) {}


void AvancementQCM::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    QRect rect = option.rect;

    // Fond gris clair
    painter->setBrush(QColor("#eeeeee"));
    painter->setPen(Qt::NoPen);
    painter->drawRect(rect);

    // Numéro (gauche)
    QString numero = QString::number(index.row() + 1);
    painter->setPen(Qt::black);
    painter->drawText(rect.adjusted(10, 0, -rect.width()/2, 0), Qt::AlignVCenter | Qt::AlignLeft, numero);

    // Rond de statut (droite)
    QColor couleur = index.data(Qt::UserRole + 1).value<QColor>();
    painter->setBrush(couleur);
    painter->setPen(Qt::NoPen);
    QPoint centre(rect.right() - 20, rect.center().y());
    painter->drawEllipse(centre, 8, 8);

    painter->restore();
}
