#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

using namespace std;

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    clickedParc=false;
    setWindowIcon(QIcon("LogoDet.png"));
    setWindowTitle("Calcul du déterminant d'une Matrice");
    /****************** Textes ******************/
    tailleMatriceLbl = new QLabel("Taille de la matrice : ");


    /****************** Champs à entiers ******************/
    tailleMatrice    = new QSpinBox;
    tailleMatrice->setMinimum(1);


    /****************** Champs de Texte ******************/
    parcourirChamp  = new QLineEdit;
    parcourirChamp->setReadOnly(true);

    /****************** Bouttons ******************/
    parcourirBtn        = new QPushButton("Parcourir");
    parcourirBtn->setFixedWidth(110);
    parcourirBtn->setIcon(QIcon("search3.png"));
    lancerBtn           = new QPushButton("Lancer");
    lancerBtn->setFixedWidth(110);
    lancerBtn->setIcon(QIcon("power115.png"));
    /****************** Tableau ******************/
    tableau     = new QTableView;

    tableauModel    = new QStandardItemModel;
    tableauModel->setRowCount(1);
    tableauModel->setColumnCount(1);

    tableau->setModel(tableauModel);

    /****************** Layouts ******************/
    QHBoxLayout *layoutEditTab = new QHBoxLayout;
    layoutEditTab->addWidget(tailleMatriceLbl);
    layoutEditTab->addWidget(tailleMatrice);

    QHBoxLayout *layoutParcourir = new QHBoxLayout;
    layoutParcourir->addWidget(parcourirChamp);
    layoutParcourir->addWidget(parcourirBtn);
    layoutParcourir->addWidget(lancerBtn);

    QGridLayout *layoutGeneral = new QGridLayout;
    layoutGeneral->addWidget(tableau,0,0,1,10);
    layoutGeneral->addLayout(layoutEditTab,1,0,1,10,Qt::AlignCenter);
    layoutGeneral->addLayout(layoutParcourir,2,0,1,10);

    ui->centralwidget->setLayout(layoutGeneral);


    /****************** Connexions ******************/
    connect(parcourirBtn,SIGNAL(clicked()),this,SLOT(parcourir()));
    connect(lancerBtn,SIGNAL(clicked()),this,SLOT(lancer()));
    connect(tailleMatrice,SIGNAL(valueChanged(int)),this,SLOT(reactionTailleMatrice(int)));

    /*********************** Les Menus ***********************/
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuInfos = menuBar()->addMenu("&?");

    QAction *actionReinitialiser = new QAction("Réinitialiser", this); actionReinitialiser->setIcon(QIcon("file77.png"));
    QAction *actionQuitter = new QAction("Quitter", this); actionQuitter->setIcon(QIcon("door13.png"));
    QAction *actionAPropos = new QAction("À propos", this); actionAPropos->setIcon(QIcon("info2.png"));

    menuFichier->addAction(actionReinitialiser); menuFichier->addSeparator();
    menuFichier->addAction(actionQuitter);

    menuInfos->addAction(actionAPropos);

    connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(actionReinitialiser,SIGNAL(triggered()),this,SLOT(reinitialiser()));
    connect(actionAPropos,SIGNAL(triggered()),this,SLOT(aPropos()));

}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

int FenetrePrincipale::det(std::vector<std::vector<int> > mat)
{
    if(mat.size()==1)
    {
        return mat[0][0];
    }
    else if(mat.size()==2)
    {
        return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0];
    }else if (3<=mat.size())
    {
        std::vector< std::vector<int> > matRetour,matRetour2;
        matRetour=suppLigne(mat,0);
        int resultat=0;

        for(int j=0;j<mat[0].size();j++)
        {
        matRetour2=suppColonne(matRetour,j);
            if(mat[0][j]!=0)
            {
        resultat+=pow(-1,j)*mat[0][j]*det(matRetour2);
            }
        }

    return resultat;
    }
}

std::vector<std::vector<int> > FenetrePrincipale::suppLigne(std::vector<std::vector<int> > mat, int ligne)
{
    std::vector< std::vector<int> > matRetour;
    std::vector<int>  vect,init;
    for(int i=0;i<mat.size();i++)
    {
        if(i!=ligne)
        {
            for(int j=0;j<mat[0].size();j++)
            {
                vect.push_back(mat[i][j]);
            }
            matRetour.push_back(vect);
            vect=init;

        }
    }
    return matRetour;
}

std::vector<std::vector<int> > FenetrePrincipale::suppColonne(std::vector<std::vector<int> > mat, int colonne)
{
    std::vector< std::vector<int> > matRetour;
     std::vector<int>  vect,init;
    for(int i=0;i<mat.size();i++)
    {
            for(int j=0;j<mat[0].size();j++)
            {
                if(j!=colonne){
                vect.push_back(mat[i][j]);
                }
            }
            matRetour.push_back(vect);
            vect=init;
    }
    return matRetour;
}



void FenetrePrincipale::parcourir()
{
    clickedParc=true;
    QString fichier=QFileDialog::getOpenFileName(this, "Recherche de la matrice",QString(),"Text (*.txt)");
    parcourirChamp->setText(fichier);

    vector<int> vect,init;
    int j(0),k(0);
    QString mot("");
    QString caract("");
    QString ligne("");

    /***** Lecture de la matrice depuis le fichier *****/
    QFile *matriceTxt=new QFile(fichier);
    if (!matriceTxt->open(QIODevice::ReadOnly | QIODevice::Text))
           return;

    while (!matriceTxt->atEnd())
    {
        ligne = matriceTxt->readLine();
       // nombreDeLignes->setValue(ligne.size());
        for(int i=0;i<ligne.size();i++)
        {

            while(ligne[i] != ' ' && i<ligne.size() )
            {
               mot.push_back(ligne[i]);
               i++;
            }

            if(mot != "")
            {
            vect.push_back(mot.toInt());
            tableauModel->setItem(j,k,new QStandardItem(mot));
            k++;
            }
            mot="";

        }

        matrice.push_back(vect);
        vect=init;
         j++; k=0;

    }
    tableauModel->setRowCount(matrice.size());
    tableauModel->setColumnCount(matrice.size());
    tailleMatrice->setValue(tableauModel->rowCount());

}

void FenetrePrincipale::lancer()
{

    if(!clickedParc)
    {
    bool nestPasRempli=false;
         vector<int> vect,init;
         vector< vector<int> >     matriceI;
         QStandardItem  *item=new QStandardItem;
        for(int i=0;i<tableauModel->rowCount() && !nestPasRempli;i++)
        {
            for(int j=0;j<tableauModel->columnCount()&& !nestPasRempli;j++)
            {
                if(tableauModel->item(i,j)==0){nestPasRempli=true;}
            }

        }

        if(!nestPasRempli)
        {
        for(int i=0;i<tableauModel->rowCount();i++)
        {
            for(int j=0;j<tableauModel->columnCount();j++)
            {
                vect.push_back(tableauModel->item(i,j)->text().toInt());
            }
            matriceI.push_back(vect);
            vect=init;
        }
        matrice=matriceI;
        }
        else
        {
            QMessageBox::critical(this,"ERRUER","ERREUR : La matrice n'est pas correctement remplie");
        }
    }
    /*********************** Calcul *************************/


    /*********************** Affichage du Résultat ******************************/
QWidget *resultatDeterminant = new QWidget;
resultatDeterminant->setFixedSize(500,200);
resultatDeterminant->setVisible(true);
QString detString("Le déterminant est égal à : <strong>");

detString+=QString::number(det(matrice));
detString+="</strong>";
QLabel *detLbl = new QLabel(detString);

QGridLayout *layG   = new QGridLayout;
layG->addWidget(detLbl,0,0,1,2,Qt::AlignCenter);
resultatDeterminant->setLayout(layG);
}

void FenetrePrincipale::reactionTailleMatrice(int i)
{
    tableauModel->setRowCount(i);
    tableauModel->setColumnCount(i);
}

void FenetrePrincipale::reinitialiser()
{
    tableauModel->setRowCount(0);
    tableauModel->setColumnCount(0);
    tableauModel->setRowCount(1);
    tableauModel->setColumnCount(1);

    vector<vector <int> > mat;
    matrice=mat;
    tailleMatrice->setValue(0);
    parcourirChamp->setText("");
}

void FenetrePrincipale::aPropos()
{
    QString inf("<br>Cette application a été créer par l'étudiant <strong>Mehdi BOUZiDi</strong>, en master R.O <br>");
    inf+="<br>Option : <strong>METHODES ET MODELES POUR L'INGENIERIE ET LA RECHERCHE </strong>.<br> ";
    inf+="<br>Date : <strong> 05/10/2015</strong> <br>";

    QWidget *infos = new QWidget;
infos->setWindowTitle("À propos");
infos->setWindowIcon(QIcon("info2.png"));
infos->setFixedSize(500,300);
 QLabel *auteur = new QLabel(inf);
 QVBoxLayout *layoutInfo =new QVBoxLayout;
 layoutInfo->addWidget(auteur);
 infos->setLayout(layoutInfo);
 infos->setHidden(false);
}
