#include <QApplication>
#include <QtGui>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "fenetreprincipale.h"



int main(int argc,char *argv[])
{
     QApplication app(argc,argv);

    FenetrePrincipale fenetre;
    fenetre.show();

return app.exec();
}

