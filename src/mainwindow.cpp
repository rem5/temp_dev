#include "mainwindow.h"

#include "qatemconnection.h"
#include "qatemmixeffect.h"
#include "qatemdownstreamkey.h"

#include <unistd.h>
#include <QInputDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QObject(parent)
{

    m_atemConnection = new QAtemConnection(this);

    connectToAtem();
    connect(m_atemConnection, SIGNAL(connected()),
            this, SLOT(onAtemConnected()));



}

MainWindow::~MainWindow()
{

}

void MainWindow::connectToAtem()
{

    QString address = "192.168.0.10";
    cout << "CONNECTING TO...\n";
    //usleep(1000000);    
    if(!address.isEmpty())
    {
        m_atemConnection->connectToSwitcher(QHostAddress(address));      
    }
}

void MainWindow::onAtemConnected()
{
    quint8 count = 0;
    
    cout << "CONNECTED\n";

    foreach(const QAtem::InputInfo &info, m_atemConnection->inputInfos())
    {
        if(info.externalType != 0 /*Internal source*/)
        {
            ++count;
        }
    }



    /* 
     * initialization
     * with chroma key
     */

    // UpstreamKeyType => 0: Luma, 1: Chroma, 2: Pattern, 3: DVE
    // keysource: 3010 => MediaPlayer1, 3020 => MediaPlayer2

    QString s0 = "INIT";// TEMP TO FIX IT   
    QString s1 = "SHOW_PC";// TEMP TO FIX IT 

    qCritical() << "ARGUMENT SITUATION : " << m_situation;  
    
    QAtemMixEffect *me = m_atemConnection->mixEffect(0);    
    if(!me)
    {
        qCritical() << "No M/E found!";
        return;
    }     
       
     
    if(m_situation == s1){
      qCritical() << "SHOW_PC ..."; 

      m_atemConnection->mixEffect(0)->changeProgramInput(1);
      m_atemConnection->mixEffect(0)->changePreviewInput(2);            

    
    }else if(m_situation == s0){
      qCritical() << "INIT ..."; 
      
      m_atemConnection->mixEffect(0)->changeProgramInput(1);
      m_atemConnection->mixEffect(0)->changePreviewInput(2);

      
    }else{
      qCritical() << "Unknowned situation parameter.";
    }
    
    emit actionsFinished();
    
    //QCoreApplication::quit();


}


void MainWindow::changeProgramInput(int input)
{
    QAtemMixEffect *me = m_atemConnection->mixEffect(0);

    if(me)
    {
        me->changeProgramInput(input);
    }
    else
    {
        qCritical() << "No M/E found!";
    }
}

void MainWindow::changePreviewInput(int input)
{
    QAtemMixEffect *me = m_atemConnection->mixEffect(0);

    if(me)
    {
        me->changePreviewInput(input);
    }
    else
    {
        qCritical() << "No M/E found!";
    }
}



void MainWindow::toogleDsk1Tie()
{
    m_atemConnection->downstreamKey(0)->setTie(!m_atemConnection->downstreamKey(0)->tie());
}

void MainWindow::toogleDsk1OnAir()
{
    m_atemConnection->downstreamKey(0)->setOnAir(!m_atemConnection->downstreamKey(0)->onAir());
}

void MainWindow::doDsk1Auto()
{
    m_atemConnection->downstreamKey(0)->doAuto();
}

void MainWindow::toogleDsk2Tie()
{
    m_atemConnection->downstreamKey(1)->setTie(!m_atemConnection->downstreamKey(1)->tie());
}

void MainWindow::toogleDsk2OnAir()
{
    m_atemConnection->downstreamKey(1)->setOnAir(!m_atemConnection->downstreamKey(1)->onAir());
}

void MainWindow::doDsk2Auto()
{
    m_atemConnection->downstreamKey(1)->doAuto();
}

void MainWindow::changeKeysTransition(int btn, bool state)
{
    if(btn == 0)
    {
        m_atemConnection->mixEffect(0)->setBackgroundOnNextTransition(state);
    }
    else
    {
        m_atemConnection->mixEffect(0)->setUpstreamKeyOnNextTransition(btn - 1, state);
    }
}

void MainWindow::changeKeyOnAir(int index, bool state)
{
    m_atemConnection->mixEffect(0)->setUpstreamKeyOnAir(index, state);
}

void MainWindow::setAddress(QString address)
{
    m_address = address;
}

void MainWindow::setSituation(QString situation)
{
    m_situation = situation;
}


