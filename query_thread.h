#ifndef QUERY_THREAD_H
#define QUERY_THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

class Query_Thread : public QThread
{
    Q_OBJECT
public:
    explicit Query_Thread(QThread *parent = 0);

private:
    void run();

signals:

public slots:
};

#endif // QUERY_THREAD_H
