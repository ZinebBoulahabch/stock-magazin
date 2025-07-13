#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>

using namespace std;

// Fonction utilitaire pour nettoyer le buffer d'entrée
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Fonction pour valider un entier positif
bool validerEntierPositif(int& valeur, const string& message) {
    cout << message;
    if (!(cin >> valeur) || valeur <= 0) {
        cout << "Erreur: Veuillez entrer un nombre entier positif.\n";
        clearInputBuffer();
        return false;
    }
    return true;
}

// Fonction pour valider un double positif
bool validerDoublePositif(double& valeur, const string& message) {
    cout << message;
    if (!(cin >> valeur) || valeur <= 0) {
        cout << "Erreur: Veuillez entrer un nombre positif.\n";
        clearInputBuffer();
        return false;
    }
    return true;
}

// Fonction pour valider une chaîne non vide
bool validerChaine(string& valeur, const string& message) {
    cout << message;
    cin >> valeur;
    if (valeur.empty()) {
        cout << "Erreur: La chaîne ne peut pas être vide.\n";
        return false;
    }
    return true;
}

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

       string getNom () const {
        return nom;
       }

       int getQuantite () const {
        return quantite;
       }

       int getCode () const {
        return code;
       }

       virtual bool saisir() {
            int tempCode, tempQuantite;
            string tempNom;
            
            if (!validerEntierPositif(tempCode, "Produit Code: ")) return false;
            if (!validerChaine(tempNom, "Nom du produit: ")) return false;
            if (!validerEntierPositif(tempQuantite, "Quantite disponible: ")) return false;
            
            code = tempCode;
            nom = tempNom;
            quantite = tempQuantite;
            return true;
       }

       virtual void afficher() const {
            cout << "Produit Code: " << code << endl;
            cout << "Nom du produit: " << nom << endl;
            cout << "Quantite disponible: " <<  quantite << endl;
       }

       virtual bool operator == (const Produit& other) const {
            return (getCode() == other.getCode() && 
                    getNom() == other.getNom() &&
                    getQuantite() == other.getQuantite()
            );
       }

       bool operator < (const Produit& other) const {
        return quantite < other.quantite;
       }

       virtual string toString() const {
         stringstream ss;
         ss << "Nom: " << nom << ", Quantite: " << quantite << " , Code: " << code ;
         return ss.str();
       }
       
       virtual string getTypeProduit() const = 0; 
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

       int getVoltage () const {
        return voltage;
       }

       bool saisir() override {
         if (!Produit::saisir()) return false;
         
         int tempGarantie, tempVoltage;
         if (!validerEntierPositif(tempGarantie, "Garantie(ans): ")) return false;
         if (!validerEntierPositif(tempVoltage, "Voltage(V): ")) return false;
         
         garantie = tempGarantie;
         voltage = tempVoltage;
         return true;
       }

       void afficher() const override {
        Produit::afficher();
        cout << "Garantie: "<< garantie << " ans"<< endl;
        cout << "Voltage: " << voltage << " V" << endl;
       }

       bool operator == (const Produit& other) const override{
          const ProduitElectro* otherElectro =  dynamic_cast<const ProduitElectro*>(&other);  ;
          if(otherElectro) {
            return Produit::operator==(other) && garantie == otherElectro->garantie 
            && voltage == otherElectro->voltage;
          }
          return false;
       }

       string toString () const override{
        stringstream ss;
        ss << Produit::toString() << ", Garantie: " << garantie << " ans, Voltage: " << voltage << "V";
        return ss.str(); 
       }

      string getTypeProduit() const override {
                return "Electro";
            }};

class ProduitLaitier : public Produit{
    private:
       string dateLimite;
       double  temperatureConservation;
    
    public:
       ProduitLaitier(){};
       ProduitLaitier(string nom , int quantite , int code , string dateLimite , float temperatureConservation)
       :Produit(nom , quantite , code) , dateLimite(dateLimite) , temperatureConservation(temperatureConservation)
       {}

       bool saisir() override{
         if (!Produit::saisir()) return false;
         
         string tempDate;
         double tempTemp;
         if (!validerChaine(tempDate, "Date Limite de consommation: ")) return false;
         if (!validerDoublePositif(tempTemp, "température de conservation: ")) return false;
         
         dateLimite = tempDate;
         temperatureConservation = tempTemp;
         return true;
       }

       void afficher() const override {
         Produit::afficher();
         cout << "Date Limite de consommation: " << dateLimite << endl;
         cout << "Température de conservation: " << temperatureConservation << endl;
       }

       bool operator == (const Produit& p) const override{
          const ProduitLaitier* otherLaitier = dynamic_cast <const ProduitLaitier*>(&p);
          if(otherLaitier) {
            return nom == otherLaitier->nom && quantite == otherLaitier->quantite 
            && code == otherLaitier->code &&  dateLimite == otherLaitier->dateLimite 
            && temperatureConservation == otherLaitier->temperatureConservation;
          }
          return false;
       }

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << ", Date Limite de consommation: " << dateLimite << " , température de conservation: " << temperatureConservation << endl;
        return ss.str();
       }

       string getTypeProduit() const override {
        return "Laitier";
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

       bool saisir() override {
         if (!Produit::saisir()) return false;
         
         double tempVolume, tempPoids;
         if (!validerDoublePositif(tempVolume, "Volume: ")) return false;
         if (!validerDoublePositif(tempPoids, "Poids: ")) return false;
         
         volume = tempVolume;
         poids = tempPoids;
         return true;
       }
       
       void afficher() const override {
        Produit::afficher();
         cout << "Volume: " << volume << endl;
         cout << "Poids: " << poids << endl;
       }

       bool operator == (const Produit& p) const override {
          const ProduitMobilier* otherMobilier = dynamic_cast <const ProduitMobilier*>(&p);
          if(otherMobilier) {
            return nom == otherMobilier->nom && otherMobilier->quantite == quantite 
            && code == otherMobilier->code &&  volume == otherMobilier->volume 
            && poids == otherMobilier->poids;
          }
            return false;
       };

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << " , Volume: " << volume << " , Poids: " << poids << endl;
        return ss.str();
       }

        string getTypeProduit() const override {
                return "Mobilier";
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

       bool saisir() override {
         if (!Produit::saisir()) return false;
         
         double tempTaille;
         string tempCouleur;
         if (!validerDoublePositif(tempTaille, "Taille: ")) return false;
         if (!validerChaine(tempCouleur, "Couleur: ")) return false;
         
         taille = tempTaille;
         couleur = tempCouleur;
         return true;
       }

       void afficher() const override {
            Produit::afficher();
            cout << "Taille: " << taille << endl;
            cout << "Couleur: " << couleur << endl;
       }
       
       
       bool operator == (const Produit& p) const override {
          const ProduitTextile* otherTextile = dynamic_cast <const ProduitTextile*>(&p);;
          if(otherTextile) {
            return nom == otherTextile->nom && quantite == otherTextile->quantite 
            && code == otherTextile->code &&  taille == otherTextile->taille 
            && couleur == otherTextile->couleur;
          }
            return false;
       };

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << " , Taille: " << taille << " , Couleur: " << couleur << endl;
        return ss.str();
       }

       string getTypeProduit() const override {
        return "Textile";
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

       bool saisir() override {
         if (!Produit::saisir()) return false;
         
         int tempAge;
         string tempType;
         if (!validerEntierPositif(tempAge, "Age limite: ")) return false;
         if (!validerChaine(tempType, "Type de joué: ")) return false;
         
         ageLimite = tempAge;
         typeJoue = tempType;
         return true;
       }
 
       void afficher() const override {
        Produit::afficher();
        cout << "Age limite: "<< ageLimite << " ans" << endl;
        cout << "Type de joué: " << typeJoue << endl;
       }

       
       bool operator == (const Produit& p) const override {
          const ProduitEnfant* otherEnfant = dynamic_cast <const ProduitEnfant*>(&p);
          if(otherEnfant) {
            return nom == otherEnfant->nom && quantite == otherEnfant->quantite 
            && code == otherEnfant->code &&  ageLimite == otherEnfant->ageLimite 
            && typeJoue == otherEnfant->typeJoue;
          }
            return false;
       };

       string toString() const override {
        stringstream ss;
        ss << Produit::toString() << " , Age limite " << ageLimite << " , Type de joue " << typeJoue << endl;
        return ss.str();
       }

       string getTypeProduit() const override {
        return "Enfant";
      }
};

class Stock {
    private:
       vector <Produit*> produits;
    
    public:
       
       Stock(){};

       // Vérifier si un code existe déjà
       bool codeExiste(int code) const {
           for (const auto* produit : produits) {
               if (produit->getCode() == code) {
                   return true;
               }
           }
           return false;
       }

       // Charger des données de test
       void chargerDonneesTest() {
           cout << "Chargement des donnees de test...\n";
           
           // Produits Electro
           ajouterProduit(new ProduitElectro("Television Samsung", 15, 1001, 2, 220));
           ajouterProduit(new ProduitElectro("Refrigerateur LG", 8, 1002, 3, 220));
           ajouterProduit(new ProduitElectro("Machine a laver", 12, 1003, 2, 220));
           
           // Produits Laitiers
           ajouterProduit(new ProduitLaitier("Lait frais", 50, 2001, "2024-02-15", 4.0));
           ajouterProduit(new ProduitLaitier("Yaourt nature", 30, 2002, "2024-02-10", 4.0));
           ajouterProduit(new ProduitLaitier("Fromage blanc", 25, 2003, "2024-02-12", 4.0));
           
           // Produits Mobilier
           ajouterProduit(new ProduitMobilier("Table de salle a manger", 5, 3001, 1.2, 25.5));
           ajouterProduit(new ProduitMobilier("Chaise de bureau", 20, 3002, 0.8, 8.0));
           ajouterProduit(new ProduitMobilier("Lit double", 3, 3003, 2.0, 45.0));
           
           // Produits Textiles
           ajouterProduit(new ProduitTextile("T-shirt coton", 100, 4001, 42.0, "Bleu"));
           ajouterProduit(new ProduitTextile("Jean slim", 75, 4002, 32.0, "Noir"));
           ajouterProduit(new ProduitTextile("Pull hiver", 45, 4003, 44.0, "Gris"));
           
           // Produits Enfants
           ajouterProduit(new ProduitEnfant("Puzzle 100 pieces", 30, 5001, 6, "Educatif"));
           ajouterProduit(new ProduitEnfant("Voiture telecommandee", 15, 5002, 8, "Jouet"));
           ajouterProduit(new ProduitEnfant("Poupée Barbie", 25, 5003, 3, "Poupée"));
           
           cout << "Donnees de test chargees avec succes!\n";
           cout << "Total: " << produits.size() << " produits ajoutes.\n\n";
       }

       void ajouterProduit(Produit* p) {
         if (p == nullptr) {
             cout << "Erreur: Produit invalide.\n";
             return;
         }
         
         if (codeExiste(p->getCode())) {
             cout << "Erreur: Un produit avec le code " << p->getCode() << " existe déjà.\n";
             delete p;
             return;
         }
         
         produits.push_back(p);
         cout << "Produit ajoute: " << p->getNom() << endl;
       }

       void supprimerProduit (int code) {
        bool trouve = false;
        for(auto it= produits.begin() ; it != produits.end() ;){
            if((*it)->getCode() == code) {
                delete *it;
                it = produits.erase(it);
                trouve = true;
                cout << "Produit supprime avec succes.\n";
            }
            else {
                ++it;
            }
        }
        if (!trouve) {
            cout << "Aucun produit avec le code " << code << " n'a ete trouve.\n";
        }
       }

       void afficher () const {
        if (produits.empty()) {
            cout << "Aucun produit dans le stock.\n";
            return;
        }
        
        cout << "=== LISTE DES PRODUITS ===\n";
        for(const Produit* p: produits) {
            p->afficher();
            cout << "------------------------\n";
        }
       }

       bool operator == (const Stock& other) const {
          if(produits.size() != other.produits.size()) {
            return false;
          }
           
          for(int i = 0 ; i < produits.size(); ++i) {
            if(!(produits[i] == other.produits[i])) {
                return false;
            }
          }
          return true;
       }   

       Produit* rechercherProduit (int code) {
        for (auto* produit : produits) {
            if(produit->getCode() == code) {
                return produit;
            }
        }
        return nullptr;
       } 

       void trierProduits() {
        if (produits.empty()) {
            cout << "Aucun produit a trier.\n";
            return;
        }
        
        sort(produits.begin(), produits.end(), [](Produit* a, Produit* b) {
            return *a < *b;
        });
        cout << "Produits tries par quantite croissante.\n";
       }   

       void sauvegarderDonnees(const string& nomFichier) {
          if (produits.empty()) {
              cout << "Aucun produit a sauvegarder.\n";
              return;
          }
          
          ofstream fichier(nomFichier);
          if(!fichier) {
            cerr << "Erreur : Impossible de creer ou d'ouvrir le fichier " <<nomFichier << endl;
            return;
          }

          fichier << "=== STOCK MAGAZIN - SAUVEGARDE ===\n";
          fichier << "Nombre de produits: " << produits.size() << "\n\n";

          for(auto it = produits.begin() ; it != produits.end() ; ++it) {
            fichier << "Type: " << (*it)->getTypeProduit() << "\n";
            fichier << (*it)->toString() << "\n";
            fichier << "------------------------\n";
          }

          fichier.close();
          cout << "Donnees sauvegardees dans le fichier " << nomFichier << endl;
       } 

       void reinitialiser () {
        for (auto* produit : produits) {
        delete produit;
        }
        produits.clear();
        cout << "Base de donnees reinitialisee.\n";
       }

       void afficherStatistaiques () {
        if (produits.empty()) {
            cout << "Aucun produit dans le stock.\n";
            return;
        }
        
        int Electro= 0 , Enfant = 0 , Laitier = 0 , Mobilier = 0 , Textile = 0 ;
        for(auto it = produits.begin(); it != produits.end() ; it++){
            if((*it)->getTypeProduit() == "Electro") Electro++;
            if((*it)->getTypeProduit() == "Enfant") Enfant++;
            if((*it)->getTypeProduit() == "Laitier") Laitier++;
            if((*it)->getTypeProduit() == "Mobilier") Mobilier++;
            if((*it)->getTypeProduit() == "Textile") Textile++;
        }

        cout << "=== STATISTIQUES DES PRODUITS ===\n";
        cout << "Total des produits: " << produits.size() << "\n";
        cout << "Produits Electro:  " << Electro << endl;
        cout << "Produits Laitiers: " << Laitier << endl;
        cout << "Produits Mobilier: " << Mobilier << endl;
        cout << "Produits Textiles: " << Textile << endl;
        cout << "Produits Enfants:  " << Enfant << endl;
       }

       void afficherProduitParType(const string& typeProduit) const {
        bool trouver = false;
        cout << "---Produits de type " << typeProduit << "---\n";
        for(auto produit : produits) {
          if(produit->getTypeProduit() == typeProduit) {
            produit->afficher();
            cout << "------------------------\n";
            trouver = true;
          }
        }
        if(!trouver) {
          cout << "Aucun produit de type " << typeProduit << " trouve.\n";
        }
       }
};

void afficherMenu() {
    cout << "\n=== MENU GESTION DES STOCKS ===\n";
    cout << "1. Afficher les produits\n";
    cout << "2. Ajouter un produit\n";
    cout << "3. Supprimer un produit\n";
    cout << "4. Rechercher un produit\n";
    cout << "5. Trier les produits\n";
    cout << "6. Sauvegarder les donnees\n";
    cout << "7. Reinitialiser les donnees\n";
    cout << "8. Afficher les statistiques\n";
    cout << "9. Recharger les donnees de test\n";
    cout << "10. Quitter\n";
    cout << "Votre choix: "; 
}

void afficherProduits(){
    cout << "Choissez le type de produit:\n";
    cout << "1. Produit Electro\n";
    cout << "2. Produit Laitier\n";
    cout << "3. Produit Mobilier\n";
    cout << "4. Produit Enfant\n";
    cout << "5. Produit Textile\n";
    cout << "Votre choix: ";
}

int main() {
    Stock stock;
    int choix , codeProduit , typeProduit;
    
    cout << "=== BIENVENUE DANS LE SYSTEME DE GESTION DES STOCKS ===\n";
    
    // Charger automatiquement les données de test
    stock.chargerDonneesTest();
    
    do {
         afficherMenu();
         
         if (!(cin >> choix)) {
             cout << "Erreur: Veuillez entrer un nombre valide.\n";
             clearInputBuffer();
             continue;
         }

         switch(choix) {
            case 1: {
                afficherProduits();
                if (!(cin >> typeProduit) || typeProduit < 1 || typeProduit > 5) {
                    cout << "Choix invalide.\n";
                    clearInputBuffer();
                    break;
                }
                
                switch (typeProduit)
                {
                case 1: stock.afficherProduitParType("Electro");break;
                case 2: stock.afficherProduitParType("Laitier");break;
                case 3: stock.afficherProduitParType("Mobilier");break;
                case 4: stock.afficherProduitParType("Enfant");break;
                case 5: stock.afficherProduitParType("Textile");break;
                default:
                    cout << "Choix invalide.\n";
                    break;
                }
                break;
            }
            case 2: {
                afficherProduits();
                if (!(cin >> typeProduit) || typeProduit < 1 || typeProduit > 5) {
                    cout << "Choix invalide.\n";
                    clearInputBuffer();
                    break;
                }

                Produit* produit = nullptr;
                switch (typeProduit)
                {
                case 1: produit = new ProduitElectro();break;
                case 2: produit = new ProduitLaitier();break;
                case 3: produit = new ProduitMobilier();break;
                case 4: produit = new ProduitEnfant();break;
                case 5: produit = new ProduitTextile();break;
                default:
                    cout << "Choix invalide.\n";
                    break;
                }
                if(produit != nullptr) {
                  if (!produit->saisir()) {
                      cout << "Erreur lors de la saisie. Produit non ajoute.\n";
                      delete produit;
                  } else {
                  stock.ajouterProduit(produit);
                  }
                }
                break;
            }
            case 3: {
                if (!validerEntierPositif(codeProduit, "Entrez le code du produit a supprimer: ")) {
                    break;
                }
                stock.supprimerProduit(codeProduit);
                break;
            } 
            case 4: {
                if (!validerEntierPositif(codeProduit, "Entrez le code du produit a rechercher: ")) {
                    break;
                }
                Produit* produit = stock.rechercherProduit(codeProduit);
                if(produit) {
                    cout << "Produit trouve:\n";
                    produit->afficher();
                }
                else {
                    cout << "Produit non trouve.\n";
                }
                break;
            }

            case 5:{
                stock.trierProduits();
                stock.afficher();
                break;
            }

            case 6: {
                string nomFichier;
                if (!validerChaine(nomFichier, "Entrez le nom du fichier pour sauvegarder: ")) {
                    break;
                }
                stock.sauvegarderDonnees(nomFichier);
                break;
            }

            case 7: {
                char confirmation;
                cout << "Etes-vous sur de vouloir reinitialiser toutes les donnees? (o/n): ";
                cin >> confirmation;
                if (tolower(confirmation) == 'o' || tolower(confirmation) == 'y') {
                stock.reinitialiser();
                } else {
                    cout << "Operation annulee.\n";
                }
                break;
            }

            case 8: {
                stock.afficherStatistaiques();
                break;
            }
            case 9: {
                char confirmation;
                cout << "Etes-vous sur de vouloir recharger les donnees de test? (o/n): ";
                cin >> confirmation;
                if (tolower(confirmation) == 'o' || tolower(confirmation) == 'y') {
                    stock.reinitialiser();
                    stock.chargerDonneesTest();
                } else {
                    cout << "Operation annulee.\n";
                }
                break;
            }
            case 10: {
                cout << "Merci d'avoir utilise le systeme de gestion des stocks!\n";
                break;
            }
            default: 
                cout << "Choix invalide. Veuillez choisir entre 1 et 10.\n";
         }
    } while (choix != 10);
    
    // Nettoyage final
    stock.reinitialiser();
    return 0;
};
