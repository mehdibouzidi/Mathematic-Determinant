#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <vector>
#include <cmath>
#include <iostream>

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();
    int det(std::vector< std::vector<int> >mat);
    std::vector< std::vector<int> > suppLigne(std::vector< std::vector<int> > mat,int ligne);
    std::vector< std::vector<int> > suppColonne(std::vector< std::vector<int> > mat,int colonne);

public slots:
    void parcourir();
    void lancer();
    void reactionTailleMatrice(int i);
    void reinitialiser();
    void aPropos();
private:
    Ui::FenetrePrincipale *ui;
    QLabel              *tailleMatriceLbl;
    QSpinBox            *tailleMatrice;
    QLineEdit           *parcourirChamp;
    QPushButton         *parcourirBtn,*lancerBtn;
    QTableView          *tableau;
    QStandardItemModel  *tableauModel;
    std::vector< std::vector<int> >     matrice;
    bool clickedParc;
   // int resultat,k;
};

#endif // FENETREPRINCIPALE_H
