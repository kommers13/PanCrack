#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>
#include <graph.h>

class Signals : public QObject
{
    Q_OBJECT
public:
    explicit Signals(QObject *parent = nullptr);

signals:
    QString output_command(const QString& input);
    QString get_command(const QString& input);
};

#endif // SIGNALS_H
