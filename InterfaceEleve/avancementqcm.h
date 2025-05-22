#ifndef AVANCEMENTQCM_H
#define AVANCEMENTQCM_H

#include <QStyledItemDelegate>
#include <QPainter>

class AvancementQCM : public QStyledItemDelegate {
public:
    AvancementQCM(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override {
        return QSize(100, 30);
    }
};

#endif // AVANCEMENTQCM_H
