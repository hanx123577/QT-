#ifndef LEVELSENSE_H
#define LEVELSENSE_H

#include <QMainWindow>
#include<playsence.h>

class LevelSense : public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelSense(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    playsence *psence=NULL;

signals:
void chooseback();
};

#endif // LEVELSENSE_H
