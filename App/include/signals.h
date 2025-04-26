#ifndef SIGNALS_H
#define SIGNALS_H

#include <QObject>

class Signals : public QObject
{
    Q_OBJECT
public:
    explicit Signals(QObject *parent = nullptr);

signals:
    void output_command(const QString& command, QObject* answer_field);
};

#endif // SIGNALS_H
