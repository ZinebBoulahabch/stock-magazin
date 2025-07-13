#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QTabWidget>
#include <QProgressBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QFont>
#include <QStyle>
#include <QGuiApplication>
#include <QScreen>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;

// Classes de base (copiées de stock.cpp)
class Produit {
    protected:
       string nom;
       int quantite;
       int code;
    
    public:
       Produit(){};
       
       Produit(string nom , int quantite , int code)
       :nom(nom) , quantite(quantite) , code(code)
       {}

       virtual ~Produit() {}

       string getNom () const { return nom; }
       int getQuantite () const { return quantite; }
       int getCode () const { return code; }
       
       void setNom(const string& n) { nom = n; }
       void setQuantite(int q) { quantite = q; }
       void setCode(int c) { code = c; }

       virtual string toString() const {
         stringstream ss;
         ss << "Nom: " << nom << ", Quantite: " << quantite << " , Code: " << code ;
         return ss.str();
       }
       
       virtual string getTypeProduit() const = 0; 
       virtual string getDetailsSpecifiques() const = 0;
};

class ProduitElectro : public Produit {
    private:
       int garantie;
       int voltage;
    
    public:
       ProduitElectro(){};
       ProduitElectro(string nom , int quantite , int code , int garantie , int voltage)
       : Produit(nom , quantite , code) , garantie(garantie) , voltage(voltage)
       {}

       int getGarantie() const { return garantie; }
       int getVoltage() const { return voltage; }
       void setGarantie(int g) { garantie = g; }
       void setVoltage(int v) { voltage = v; }

       string toString () const override {
        stringstream ss;
        ss << Produit::toString() << ", Garantie: " << garantie << " ans, Voltage: " << voltage << "V";
        return ss.str(); 
       }

       string getTypeProduit() const override { return "Electro"; }
       
       string getDetailsSpecifiques() const override {
           return "Garantie: " + to_string(garantie) + " ans, Voltage: " + to_string(voltage) + "V";
       }
};

class ProduitLaitier : public Produit{
    private:
       string dateLimite;
       double temperatureConservation;
    
    public:
       ProduitLaitier(){};
       ProduitLaitier(string nom , int quantite , int code , string dateLimite , float temperatureConservation)
       :Produit(nom , quantite , code) , dateLimite(dateLimite) , temperatureConservation(temperatureConservation)
       {}

       string getDateLimite() const { return dateLimite; }
       double getTemperatureConservation() const { return temperatureConservation; }
       void setDateLimite(const string& d) { dateLimite = d; }
       void setTemperatureConservation(double t) { temperatureConservation = t; }

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << ", Date Limite: " << dateLimite << " , Température: " << temperatureConservation << "°C";
        return ss.str();
       }

       string getTypeProduit() const override { return "Laitier"; }
       
       string getDetailsSpecifiques() const override {
           return "Date limite: " + dateLimite + ", Température: " + to_string(temperatureConservation) + "°C";
       }
};

class ProduitMobilier : public Produit {
    private:
       double volume;
       double poids;
    
    public:
        ProduitMobilier(){};
        ProduitMobilier(string nom , int quantite , int code , double volume , double poids)
       : Produit(nom , quantite , code) , volume(volume) , poids(poids)
       {}

       double getVolume() const { return volume; }
       double getPoids() const { return poids; }
       void setVolume(double v) { volume = v; }
       void setPoids(double p) { poids = p; }

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << " , Volume: " << volume << "m³ , Poids: " << poids << "kg";
        return ss.str();
       }

       string getTypeProduit() const override { return "Mobilier"; }
       
       string getDetailsSpecifiques() const override {
           return "Volume: " + to_string(volume) + "m³, Poids: " + to_string(poids) + "kg";
       }
};

class ProduitTextile : public Produit {
    private:
       double taille;
       string couleur;
    
    public:
        ProduitTextile(){};
        ProduitTextile(string nom , int quantite , int code , double taille , string couleur)
       : Produit(nom , quantite , code) , taille(taille) , couleur(couleur)
       {}

       double getTaille() const { return taille; }
       string getCouleur() const { return couleur; }
       void setTaille(double t) { taille = t; }
       void setCouleur(const string& c) { couleur = c; }

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << " , Taille: " << taille << " , Couleur: " << couleur;
        return ss.str();
       }

       string getTypeProduit() const override { return "Textile"; }
       
       string getDetailsSpecifiques() const override {
           return "Taille: " + to_string(taille) + ", Couleur: " + couleur;
       }
};

class ProduitEnfant : public Produit {
    private:
       int ageLimite;
       string typeJoue;
    
    public:
        ProduitEnfant() {};
        ProduitEnfant(string nom , int quantite , int code , int ageLimite , string typeJoue)
       : Produit(nom , quantite , code) , ageLimite(ageLimite) , typeJoue(typeJoue)
       {}

       int getAgeLimite() const { return ageLimite; }
       string getTypeJoue() const { return typeJoue; }
       void setAgeLimite(int a) { ageLimite = a; }
       void setTypeJoue(const string& t) { typeJoue = t; }

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << " , Age limite " << ageLimite << " ans , Type: " << typeJoue;
        return ss.str();
       }

       string getTypeProduit() const override { return "Enfant"; }
       
       string getDetailsSpecifiques() const override {
           return "Âge limite: " + to_string(ageLimite) + " ans, Type: " + typeJoue;
       }
};

class Stock {
    private:
       vector <shared_ptr<Produit>> produits;
    
    public:
       Stock(){};

       bool codeExiste(int code) const {
           for (const auto& produit : produits) {
               if (produit->getCode() == code) {
                   return true;
               }
           }
           return false;
       }

       void ajouterProduit(shared_ptr<Produit> p) {
         if (p == nullptr) {
             return;
         }
         
         if (codeExiste(p->getCode())) {
             return;
         }
         
         produits.push_back(p);
       }

       void supprimerProduit(int code) {
         for(auto it = produits.begin() ; it != produits.end() ;){
             if((*it)->getCode() == code) {
                 it = produits.erase(it);
             }
             else {
                 ++it;
             }
         }
       }

       shared_ptr<Produit> rechercherProduit(int code) {
        for (auto& produit : produits) {
            if(produit->getCode() == code) {
                return produit;
            }
        }
        return nullptr;
       } 

       void trierProduits() {
        sort(produits.begin(), produits.end(), [](const shared_ptr<Produit>& a, const shared_ptr<Produit>& b) {
            return a->getQuantite() < b->getQuantite();
        });
       }   

       void sauvegarderDonnees(const string& nomFichier) {
          ofstream fichier(nomFichier);
          if(!fichier) {
            return;
          }

          fichier << "=== STOCK MAGAZIN - SAUVEGARDE ===\n";
          fichier << "Nombre de produits: " << produits.size() << "\n\n";
          
          for(const auto& produit : produits) {
            fichier << "Type: " << produit->getTypeProduit() << "\n";
            fichier << produit->toString() << "\n";
            fichier << "------------------------\n";
          }

          fichier.close();
       } 

       void reinitialiser() {
        produits.clear();
       }

       void chargerDonneesTest() {
           // Produits Electro
           ajouterProduit(make_shared<ProduitElectro>("Television Samsung", 15, 1001, 2, 220));
           ajouterProduit(make_shared<ProduitElectro>("Refrigerateur LG", 8, 1002, 3, 220));
           ajouterProduit(make_shared<ProduitElectro>("Machine a laver", 12, 1003, 2, 220));
           
           // Produits Laitiers
           ajouterProduit(make_shared<ProduitLaitier>("Lait frais", 50, 2001, "2024-02-15", 4.0));
           ajouterProduit(make_shared<ProduitLaitier>("Yaourt nature", 30, 2002, "2024-02-10", 4.0));
           ajouterProduit(make_shared<ProduitLaitier>("Fromage blanc", 25, 2003, "2024-02-12", 4.0));
           
           // Produits Mobilier
           ajouterProduit(make_shared<ProduitMobilier>("Table de salle a manger", 5, 3001, 1.2, 25.5));
           ajouterProduit(make_shared<ProduitMobilier>("Chaise de bureau", 20, 3002, 0.8, 8.0));
           ajouterProduit(make_shared<ProduitMobilier>("Lit double", 3, 3003, 2.0, 45.0));
           
           // Produits Textiles
           ajouterProduit(make_shared<ProduitTextile>("T-shirt coton", 100, 4001, 42.0, "Bleu"));
           ajouterProduit(make_shared<ProduitTextile>("Jean slim", 75, 4002, 32.0, "Noir"));
           ajouterProduit(make_shared<ProduitTextile>("Pull hiver", 45, 4003, 44.0, "Gris"));
           
           // Produits Enfants
           ajouterProduit(make_shared<ProduitEnfant>("Puzzle 100 pieces", 30, 5001, 6, "Educatif"));
           ajouterProduit(make_shared<ProduitEnfant>("Voiture telecommandee", 15, 5002, 8, "Jouet"));
           ajouterProduit(make_shared<ProduitEnfant>("Poupee Barbie", 25, 5003, 3, "Poupee"));
       }

       const vector<shared_ptr<Produit>>& getProduits() const {
           return produits;
       }

       int getNombreProduits() const {
           return produits.size();
       }

       map<string, int> getStatistiques() const {
           map<string, int> stats;
           for(const auto& produit : produits) {
               stats[produit->getTypeProduit()]++;
           }
           return stats;
       }
};

// Interface graphique
class StockGUI : public QMainWindow {
    Q_OBJECT

private:
    Stock stock;
    QTableWidget* tableProduits;
    QTextEdit* textDetails;
    QComboBox* comboType;
    QLineEdit* editCode;
    QLineEdit* editNom;
    QSpinBox* spinQuantite;
    QSpinBox* spinGarantie;
    QSpinBox* spinVoltage;
    QLineEdit* editDateLimite;
    QDoubleSpinBox* spinTemperature;
    QDoubleSpinBox* spinVolume;
    QDoubleSpinBox* spinPoids;
    QDoubleSpinBox* spinTaille;
    QLineEdit* editCouleur;
    QSpinBox* spinAgeLimite;
    QLineEdit* editTypeJoue;
    QStatusBar* statusBar;

public:
    StockGUI(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("🏪 Système de Gestion des Stocks");
        setMinimumSize(1200, 800);
        
        // Centrer la fenêtre
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
        
        setupUI();
        chargerDonneesTest();
        actualiserTableau();
    }

private slots:
    void ajouterProduit() {
        if (comboType->currentText().isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un type de produit.");
            return;
        }

        int code = editCode->text().toInt();
        if (code <= 0) {
            QMessageBox::warning(this, "Erreur", "Le code doit être un nombre positif.");
            return;
        }

        if (stock.codeExiste(code)) {
            QMessageBox::warning(this, "Erreur", "Un produit avec ce code existe déjà.");
            return;
        }

        string nom = editNom->text().toStdString();
        if (nom.empty()) {
            QMessageBox::warning(this, "Erreur", "Le nom ne peut pas être vide.");
            return;
        }

        int quantite = spinQuantite->value();
        if (quantite <= 0) {
            QMessageBox::warning(this, "Erreur", "La quantité doit être positive.");
            return;
        }

        shared_ptr<Produit> nouveauProduit = nullptr;
        string type = comboType->currentText().toStdString();

        if (type == "Electro") {
            int garantie = spinGarantie->value();
            int voltage = spinVoltage->value();
            nouveauProduit = make_shared<ProduitElectro>(nom, quantite, code, garantie, voltage);
        }
        else if (type == "Laitier") {
            string dateLimite = editDateLimite->text().toStdString();
            double temperature = spinTemperature->value();
            nouveauProduit = make_shared<ProduitLaitier>(nom, quantite, code, dateLimite, temperature);
        }
        else if (type == "Mobilier") {
            double volume = spinVolume->value();
            double poids = spinPoids->value();
            nouveauProduit = make_shared<ProduitMobilier>(nom, quantite, code, volume, poids);
        }
        else if (type == "Textile") {
            double taille = spinTaille->value();
            string couleur = editCouleur->text().toStdString();
            nouveauProduit = make_shared<ProduitTextile>(nom, quantite, code, taille, couleur);
        }
        else if (type == "Enfant") {
            int ageLimite = spinAgeLimite->value();
            string typeJoue = editTypeJoue->text().toStdString();
            nouveauProduit = make_shared<ProduitEnfant>(nom, quantite, code, ageLimite, typeJoue);
        }

        if (nouveauProduit) {
            stock.ajouterProduit(nouveauProduit);
            actualiserTableau();
            viderFormulaire();
            statusBar->showMessage("Produit ajouté avec succès!", 3000);
        }
    }

    void supprimerProduit() {
        int row = tableProduits->currentRow();
        if (row >= 0) {
            int code = tableProduits->item(row, 0)->text().toInt();
            stock.supprimerProduit(code);
            actualiserTableau();
            statusBar->showMessage("Produit supprimé avec succès!", 3000);
        } else {
            QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un produit à supprimer.");
        }
    }

    void rechercherProduit() {
        int code = editCode->text().toInt();
        auto produit = stock.rechercherProduit(code);
        if (produit) {
            textDetails->setText(QString::fromStdString(produit->toString()));
            statusBar->showMessage("Produit trouvé!", 3000);
        } else {
            textDetails->setText("Produit non trouvé.");
            statusBar->showMessage("Produit non trouvé.", 3000);
        }
    }

    void trierProduits() {
        stock.trierProduits();
        actualiserTableau();
        statusBar->showMessage("Produits triés par quantité!", 3000);
    }

    void sauvegarderDonnees() {
        QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder les données", "", "Fichiers texte (*.txt)");
        if (!fileName.isEmpty()) {
            stock.sauvegarderDonnees(fileName.toStdString());
            statusBar->showMessage("Données sauvegardées avec succès!", 3000);
        }
    }

    void reinitialiserDonnees() {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", 
            "Êtes-vous sûr de vouloir réinitialiser toutes les données?", 
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            stock.reinitialiser();
            actualiserTableau();
            statusBar->showMessage("Données réinitialisées!", 3000);
        }
    }

    void rechargerDonneesTest() {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", 
            "Voulez-vous recharger les données de test?", 
            QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            stock.reinitialiser();
            stock.chargerDonneesTest();
            actualiserTableau();
            statusBar->showMessage("Données de test rechargées!", 3000);
        }
    }

    void afficherStatistiques() {
        auto stats = stock.getStatistiques();
        QString statsText = "=== STATISTIQUES ===\n";
        statsText += "Total des produits: " + QString::number(stock.getNombreProduits()) + "\n\n";
        
        for (const auto& stat : stats) {
            statsText += QString::fromStdString(stat.first) + ": " + QString::number(stat.second) + "\n";
        }
        
        textDetails->setText(statsText);
        statusBar->showMessage("Statistiques affichées!", 3000);
    }

    void selectionnerProduit(int row, int column) {
        if (row >= 0 && row < tableProduits->rowCount()) {
            auto produit = stock.getProduits()[row];
            textDetails->setText(QString::fromStdString(produit->toString() + "\n\n" + produit->getDetailsSpecifiques()));
        }
    }

    void changerTypeProduit() {
        string type = comboType->currentText().toStdString();
        
        // Masquer tous les champs spécifiques
        spinGarantie->setVisible(false);
        spinVoltage->setVisible(false);
        editDateLimite->setVisible(false);
        spinTemperature->setVisible(false);
        spinVolume->setVisible(false);
        spinPoids->setVisible(false);
        spinTaille->setVisible(false);
        editCouleur->setVisible(false);
        spinAgeLimite->setVisible(false);
        editTypeJoue->setVisible(false);
        
        // Afficher les champs appropriés
        if (type == "Electro") {
            spinGarantie->setVisible(true);
            spinVoltage->setVisible(true);
        }
        else if (type == "Laitier") {
            editDateLimite->setVisible(true);
            spinTemperature->setVisible(true);
        }
        else if (type == "Mobilier") {
            spinVolume->setVisible(true);
            spinPoids->setVisible(true);
        }
        else if (type == "Textile") {
            spinTaille->setVisible(true);
            editCouleur->setVisible(true);
        }
        else if (type == "Enfant") {
            spinAgeLimite->setVisible(true);
            editTypeJoue->setVisible(true);
        }
    }

private:
    void setupUI() {
        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
        
        // Barre d'outils
        QToolBar* toolbar = addToolBar("Outils");
        toolbar->addAction("➕ Ajouter", this, &StockGUI::ajouterProduit);
        toolbar->addAction("🗑️ Supprimer", this, &StockGUI::supprimerProduit);
        toolbar->addAction("🔍 Rechercher", this, &StockGUI::rechercherProduit);
        toolbar->addAction("📊 Statistiques", this, &StockGUI::afficherStatistiques);
        toolbar->addAction("📈 Trier", this, &StockGUI::trierProduits);
        toolbar->addAction("💾 Sauvegarder", this, &StockGUI::sauvegarderDonnees);
        toolbar->addAction("🔄 Réinitialiser", this, &StockGUI::reinitialiserDonnees);
        toolbar->addAction("🔄 Recharger Test", this, &StockGUI::rechargerDonneesTest);
        
        // Zone principale
        QHBoxLayout* contentLayout = new QHBoxLayout();
        
        // Panneau gauche - Formulaire
        QGroupBox* groupFormulaire = new QGroupBox("📝 Ajouter un Produit");
        QGridLayout* formLayout = new QGridLayout(groupFormulaire);
        
        // Champs de base
        formLayout->addWidget(new QLabel("Type:"), 0, 0);
        comboType = new QComboBox();
        comboType->addItems({"Electro", "Laitier", "Mobilier", "Textile", "Enfant"});
        formLayout->addWidget(comboType, 0, 1);
        connect(comboType, QOverload<const QString &>::of(&QComboBox::currentTextChanged), 
                this, &StockGUI::changerTypeProduit);
        
        formLayout->addWidget(new QLabel("Code:"), 1, 0);
        editCode = new QLineEdit();
        formLayout->addWidget(editCode, 1, 1);
        
        formLayout->addWidget(new QLabel("Nom:"), 2, 0);
        editNom = new QLineEdit();
        formLayout->addWidget(editNom, 2, 1);
        
        formLayout->addWidget(new QLabel("Quantité:"), 3, 0);
        spinQuantite = new QSpinBox();
        spinQuantite->setRange(1, 9999);
        formLayout->addWidget(spinQuantite, 3, 1);
        
        // Champs spécifiques Electro
        formLayout->addWidget(new QLabel("Garantie (ans):"), 4, 0);
        spinGarantie = new QSpinBox();
        spinGarantie->setRange(1, 10);
        spinGarantie->setVisible(false);
        formLayout->addWidget(spinGarantie, 4, 1);
        
        formLayout->addWidget(new QLabel("Voltage (V):"), 5, 0);
        spinVoltage = new QSpinBox();
        spinVoltage->setRange(110, 380);
        spinVoltage->setValue(220);
        spinVoltage->setVisible(false);
        formLayout->addWidget(spinVoltage, 5, 1);
        
        // Champs spécifiques Laitier
        formLayout->addWidget(new QLabel("Date limite:"), 6, 0);
        editDateLimite = new QLineEdit();
        editDateLimite->setPlaceholderText("YYYY-MM-DD");
        editDateLimite->setVisible(false);
        formLayout->addWidget(editDateLimite, 6, 1);
        
        formLayout->addWidget(new QLabel("Température (°C):"), 7, 0);
        spinTemperature = new QDoubleSpinBox();
        spinTemperature->setRange(-10, 20);
        spinTemperature->setValue(4);
        spinTemperature->setVisible(false);
        formLayout->addWidget(spinTemperature, 7, 1);
        
        // Champs spécifiques Mobilier
        formLayout->addWidget(new QLabel("Volume (m³):"), 8, 0);
        spinVolume = new QDoubleSpinBox();
        spinVolume->setRange(0.1, 10);
        spinVolume->setDecimals(2);
        spinVolume->setVisible(false);
        formLayout->addWidget(spinVolume, 8, 1);
        
        formLayout->addWidget(new QLabel("Poids (kg):"), 9, 0);
        spinPoids = new QDoubleSpinBox();
        spinPoids->setRange(0.1, 1000);
        spinPoids->setDecimals(1);
        spinPoids->setVisible(false);
        formLayout->addWidget(spinPoids, 9, 1);
        
        // Champs spécifiques Textile
        formLayout->addWidget(new QLabel("Taille:"), 10, 0);
        spinTaille = new QDoubleSpinBox();
        spinTaille->setRange(1, 100);
        spinTaille->setDecimals(1);
        spinTaille->setVisible(false);
        formLayout->addWidget(spinTaille, 10, 1);
        
        formLayout->addWidget(new QLabel("Couleur:"), 11, 0);
        editCouleur = new QLineEdit();
        editCouleur->setVisible(false);
        formLayout->addWidget(editCouleur, 11, 1);
        
        // Champs spécifiques Enfant
        formLayout->addWidget(new QLabel("Âge limite:"), 12, 0);
        spinAgeLimite = new QSpinBox();
        spinAgeLimite->setRange(1, 18);
        spinAgeLimite->setVisible(false);
        formLayout->addWidget(spinAgeLimite, 12, 1);
        
        formLayout->addWidget(new QLabel("Type de jeu:"), 13, 0);
        editTypeJoue = new QLineEdit();
        editTypeJoue->setVisible(false);
        formLayout->addWidget(editTypeJoue, 13, 1);
        
        // Bouton Ajouter
        QPushButton* btnAjouter = new QPushButton("➕ Ajouter Produit");
        btnAjouter->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 10px; font-weight: bold; }");
        connect(btnAjouter, &QPushButton::clicked, this, &StockGUI::ajouterProduit);
        formLayout->addWidget(btnAjouter, 14, 0, 1, 2);
        
        // Panneau central - Tableau
        QGroupBox* groupTableau = new QGroupBox("📋 Liste des Produits");
        QVBoxLayout* tableLayout = new QVBoxLayout(groupTableau);
        
        tableProduits = new QTableWidget();
        tableProduits->setColumnCount(5);
        tableProduits->setHorizontalHeaderLabels({"Code", "Nom", "Quantité", "Type", "Détails"});
        tableProduits->horizontalHeader()->setStretchLastSection(true);
        tableProduits->setSelectionBehavior(QAbstractItemView::SelectRows);
        connect(tableProduits, &QTableWidget::cellClicked, this, &StockGUI::selectionnerProduit);
        tableLayout->addWidget(tableProduits);
        
        // Panneau droit - Détails
        QGroupBox* groupDetails = new QGroupBox("📄 Détails du Produit");
        QVBoxLayout* detailsLayout = new QVBoxLayout(groupDetails);
        
        textDetails = new QTextEdit();
        textDetails->setReadOnly(true);
        detailsLayout->addWidget(textDetails);
        
        // Assemblage
        contentLayout->addWidget(groupFormulaire, 1);
        contentLayout->addWidget(groupTableau, 2);
        contentLayout->addWidget(groupDetails, 1);
        
        mainLayout->addLayout(contentLayout);
        
        // Barre de statut
        statusBar = new QStatusBar();
        setStatusBar(statusBar);
        statusBar->showMessage("Prêt");
        
        // Initialiser les champs spécifiques
        changerTypeProduit();
    }

    void actualiserTableau() {
        tableProduits->setRowCount(0);
        const auto& produits = stock.getProduits();
        
        for (const auto& produit : produits) {
            int row = tableProduits->rowCount();
            tableProduits->insertRow(row);
            
            tableProduits->setItem(row, 0, new QTableWidgetItem(QString::number(produit->getCode())));
            tableProduits->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(produit->getNom())));
            tableProduits->setItem(row, 2, new QTableWidgetItem(QString::number(produit->getQuantite())));
            tableProduits->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(produit->getTypeProduit())));
            tableProduits->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(produit->getDetailsSpecifiques())));
        }
        
        statusBar->showMessage(QString("Total: %1 produits").arg(stock.getNombreProduits()));
    }

    void viderFormulaire() {
        editCode->clear();
        editNom->clear();
        spinQuantite->setValue(1);
        spinGarantie->setValue(1);
        spinVoltage->setValue(220);
        editDateLimite->clear();
        spinTemperature->setValue(4);
        spinVolume->setValue(1.0);
        spinPoids->setValue(10.0);
        spinTaille->setValue(42);
        editCouleur->clear();
        spinAgeLimite->setValue(6);
        editTypeJoue->clear();
    }

    void chargerDonneesTest() {
        stock.chargerDonneesTest();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Style moderne
    app.setStyle("Fusion");
    
    StockGUI window;
    window.show();
    
    return app.exec();
}

#include "stock_gui.moc" 