// src/core/Snippet.h
#ifndef SNIPPET_H
#define SNIPPET_H

#include <QDateTime>
#include <QVariant>
#include <QIcon>

// This class represents a single item in our clipboard history.
class Snippet {
public:
    enum Type {
        Text,
        Image,
        // We can add more types like 'File' later
    };

    // The data itself (can be a QString for text, or a QImage for images)
    QVariant data;

    // The type of snippet
    Type type;
    
    // When it was copied
    QDateTime timestamp;
    
    // The text that will be shown in the list view
    QString displayText;

    // An icon to represent the type (e.g., text icon, image icon, link icon)
    QIcon displayIcon;

    // A small preview swatch (e.g., for colors)
    QColor previewColor;
};

#endif // SNIPPET_H