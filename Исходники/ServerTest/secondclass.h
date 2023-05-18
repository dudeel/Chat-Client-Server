#ifndef SECONDCLASS_H
#define SECONDCLASS_H

#include <QObject>

class secondClass : public QObject
{
    Q_OBJECT
public:
    explicit secondClass(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SECONDCLASS_H