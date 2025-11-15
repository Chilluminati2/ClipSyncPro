// src/gui/SnippetDelegate.h
#ifndef SNIPPETDELEGATE_H
#define SNIPPETDELEGATE_H

#include <QStyledItemDelegate>

class SnippetDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    // The paint function is where we do all our custom drawing
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    
    // sizeHint tells the view how tall each item should be
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // SNIPPETDELEGATE_H