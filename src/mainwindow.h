#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <iostream>
#include <QMainWindow>
#include <QCoreApplication>

namespace Ui {
class MainWindow;
}

class QAtemConnection;

class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setAddress(QString address);    
    void setSituation(QString situation);        

protected slots:
    void connectToAtem();

    void onAtemConnected();

    void changeProgramInput(int input);
    void changePreviewInput(int input);

    void toogleDsk1Tie();
    void toogleDsk1OnAir();
    void doDsk1Auto();
    void toogleDsk2Tie();
    void toogleDsk2OnAir();
    void doDsk2Auto();

    void changeKeysTransition(int btn, bool state);

    void changeKeyOnAir(int index, bool state);

signals:
	void actionsFinished();

private:
    QAtemConnection *m_atemConnection;
    
    QString m_address;
    QString m_situation;


};

#endif // MAINWINDOW_H
