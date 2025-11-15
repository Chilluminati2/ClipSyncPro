// src/gui/SnippetDelegate.cpp
#include "SnippetDelegate.h"
#include "core/Snippet.h" // Our data model
#include <QPainter>
#include <QApplication>

void SnippetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();

    // Get the Snippet data stored in the model item
    Snippet snippet = index.data(Qt::UserRole).value<Snippet>();

    // --- Drawing the Background ---
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    } else if (option.state & QStyle::State_MouseOver) {
        painter->fillRect(option.rect, option.palette.dark());
    }

    // --- Drawing the Content ---
    QRect contentRect = option.rect.adjusted(10, 5, -10, -5); // Add some padding

    if (snippet.type == Snippet::Text) {
        // If it's a color, draw a color swatch
        if (snippet.previewColor.isValid()) {
            QRect colorRect(contentRect.left(), contentRect.top() + (contentRect.height() - 20) / 2, 20, 20);
            painter->fillRect(colorRect, snippet.previewColor);
            painter->drawRect(colorRect); // Add a border
            contentRect.setLeft(colorRect.right() + 10);
        }

        // Draw the display text
        painter->setPen(option.palette.windowText().color());
        painter->drawText(contentRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, snippet.displayText);

    } else if (snippet.type == Snippet::Image) {
        QImage image = snippet.data.value<QImage>();
        if (!image.isNull()) {
            // Calculate thumbnail size
            QSize thumbnailSize(64, 64);
            QImage thumbnail = image.scaled(thumbnailSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            
            QRect imageRect(contentRect.left(), contentRect.top() + (contentRect.height() - thumbnail.height()) / 2, thumbnail.width(), thumbnail.height());
            painter->drawImage(imageRect, thumbnail);

            // Draw the text next to the image
            QRect textRect = contentRect;
            textRect.setLeft(imageRect.right() + 10);
            painter->setPen(option.palette.windowText().color());
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, snippet.displayText);
        }
    }

    painter->restore();
}

QSize SnippetDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Snippet snippet = index.data(Qt::UserRole).value<Snippet>();
    if (snippet.type == Snippet::Image) {
        return QSize(200, 74); // Taller hint for image items
    }
    // Default size for text items
    return QSize(200, 50);
}