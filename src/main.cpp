#include "mainwindow.h"
#include <QCoreApplication>

#include <QDebug>

#include <QCommandLineOption>
#include <QCommandLineParser>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("qatemswitcher_cli");
    QCoreApplication::setApplicationVersion("0.1");    
    

    /*
     * Detect the parameters sent via the CLI
     * -situation
     * SHOW_PC,...
     *
     * call example: ./qatemswitcher -s SHOW_PC
     */
    QCommandLineParser parser;
    parser.setApplicationDescription("Change the status of the ATEM, then quit. Use -platform offscreen to disable X windows.");
    parser.addHelpOption();
    parser.addVersionOption();    
    // An option with multiple names (-a, --address) FIXME
    QCommandLineOption addressOption(QStringList() << "a" << "address",
            QCoreApplication::translate("main", "IP address of the ATEM"), "value");
    parser.addOption(addressOption);    
    // An option with multiple names (-s, --situation)
    QCommandLineOption situationOption(QStringList() << "s" << "situation",
            QCoreApplication::translate("main", "Which situation to set \
            (SHOW_PC, INIT)."), "value");
    parser.addOption(situationOption);
    
    parser.process(a);
    
    QString address = parser.value(addressOption);
    QString situation = parser.value(situationOption);    
    
    MainWindow w;
    
    QObject::connect( &w, SIGNAL(actionsFinished()), &a, SLOT(quit()) );
    
    w.setAddress(address);
    w.setSituation(situation);    


    return a.exec();
}



