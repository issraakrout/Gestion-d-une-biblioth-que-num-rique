#include"document.h"
#include<typeinfo>
#include <limits>

// CLASSE CHAPITRE **********************************************************************

Chapitre::Chapitre(string titre, int numero, int pageDebut, int pageFin)
{
    this->titre = titre;
    this->numero = numero;
    this->pageDebut = pageDebut;
    this->pageFin = pageFin;
}

Chapitre::~Chapitre()
{
}

Chapitre::Chapitre(const Chapitre& autre)
{
    this->titre = autre.titre;
    this->numero = autre.numero;
    this->pageDebut = autre.pageDebut;
    this->pageFin = autre.pageFin;
}

string Chapitre::GetTitre()
{
    return this->titre;
}

int Chapitre::GetNumero()
{
    return this->numero;
}

int Chapitre::GetPageDebut()
{
    return this->pageDebut;
}

int Chapitre::GetPageFin()
{
    return this->pageFin;
}

void Chapitre::SetTitre(string nouveauTitre)
{
    this->titre = nouveauTitre;
}

void Chapitre::SetNumero(int nouveauNumero)
{
    this->numero = nouveauNumero;
}

void Chapitre::SetPages(int debut, int fin)
{
    this->pageDebut = debut;
    this->pageFin = fin;
}

void Chapitre::Afficher()
{
    cout << "Chapitre " << this->numero << ": " << this->titre << endl;
    cout << "Pages: " << this->pageDebut << "-" << this->pageFin << endl;
}

Chapitre& Chapitre::operator=(const Chapitre& autre) {
    if (this != &autre) {
        titre = autre.titre;
        numero = autre.numero;
        pageDebut = autre.pageDebut;
        pageFin = autre.pageFin;
    }
    return *this;
}

ostream& operator<<(ostream& out, const Chapitre& chap)
{
    out << chap.titre << " ";
    out << chap.numero << " ";
    out << chap.pageDebut << " ";
    out << chap.pageFin;
    return out;
}

istream& operator>>(istream& in, Chapitre& chap)
{
    in >> chap.titre;
    in >> chap.numero;
    in >> chap.pageDebut;
    in >> chap.pageFin;
    return in;
}

ostream& operator<<(ostream& out, const Chapitre* chap)
{
    out << chap->titre << " ";
    out << chap->numero << " ";
    out << chap->pageDebut << " ";
    out << chap->pageFin;
    return out;
}

istream& operator>>(istream& in, Chapitre* chap)
{
    in >> chap->titre;
    in >> chap->numero;
    in >> chap->pageDebut;
    in >> chap->pageFin;
    return in;
}

//CLASSE PAGE *************************************************************************************************************

Page::Page(string content, int pageNumber)
{
    this->content = content;
    this->pageNumber = pageNumber;
}

Page::~Page()
{
}

Page::Page(const Page& autre)
{
    this->content = autre.content;
    this->pageNumber = autre.pageNumber;
}

string Page::getContent()
{
    return this->content;
}

int Page::getPageNumber()
{
    return this->pageNumber;
}

void Page::setContent(string newContent)
{
    this->content = newContent;
}

void Page::setPageNumber(int newPageNumber)
{
    this->pageNumber = newPageNumber;
}

void Page::afficher()
{
    cout << "Page " << this->pageNumber << ":" << endl;
    cout << this->content << endl;
}

ostream& operator<<(ostream& out, const Page& P)
{
    out << P.content << " ";
    out << P.pageNumber;
    return out;
}

istream& operator>>(istream& in, Page& P)
{
    getline(in, P.content);
    in >> P.pageNumber;
    return in;
}

ostream& operator<<(ostream& out, const Page* P)
{
    out << P->content << " ";
    out << P->pageNumber;
    return out;
}

istream& operator>>(istream& in, Page* P)
{
    getline(in, P->content);
    in >> P->pageNumber;
    return in;
}

//CLASSE DOCUMENT *********************************************************************************************************

int Document::nombreTotalDocuments = 0;
Document::Document()
{
    this->id = 0;
    this->titre = "";
    this->auteur = "";
    this->AnneePublication = 0;
    this->prix = 0.0;
    nombreTotalDocuments++;
}

Document::~Document()
{
    for(int i = 0; i < pages.size(); i++)
    {
        delete pages[i];
    }
    pages.clear();
    nombreTotalDocuments--;
}

Document::Document(const Document& autre) :
    id(autre.id), titre(autre.titre), auteur(autre.auteur),
    AnneePublication(autre.AnneePublication), prix(autre.prix)
{
    for(int i = 0; i < autre.pages.size(); i++)
    {
        this->pages.push_back(new Page(*autre.pages[i]));
    }
}

void Document::SaisirDocument()
{
    cout << "Entrez l'ID: ";
    cin >> this->id;
    cout << "Entrez le titre: ";
    cin.ignore();
    getline(cin, this->titre);
    cout << "Entrez l'auteur: ";
    getline(cin, this->auteur);
    cout << "Entrez l'annee de publication: ";
    cin >> this->AnneePublication;
    cout << "Entrez le prix: ";
    cin >> this->prix;
}

int Document::CalculerAge(int AnneeActuelle)
{
    return AnneeActuelle - this->AnneePublication;
}

int Document::GetId()
{
    return this->id;
}

int Document::GetNombreTotalDocuments()
{
    return nombreTotalDocuments;
}

void Document::SetTitre(string nouveauTitre)
{
    this->titre = nouveauTitre;
}

float Document::GetPrix()
{
    return this->prix;
}

void Document::SetPrix(float nouveauPrix)
{
    this->prix = nouveauPrix;
}

void Document::AjouterPage(Page* page)
{
    this->pages.push_back(page);
}

vector<Page*> Document::GetPages()
{
    return this->pages;
}

Document* Document::operator+(const Document& autre)
{
    Document* resultat;
    resultat->id = this->id;
    resultat->titre = this->titre + " + " + autre.titre;
    resultat->auteur = this->auteur;
    resultat->AnneePublication = this->AnneePublication;
    resultat->prix = this->prix + autre.prix;
    for(int i = 0; i < this->pages.size(); i++)
    {
        resultat->pages.push_back(new Page(*this->pages[i]));
    }
    for(int i = 0; i < autre.pages.size(); i++)
    {
        resultat->pages.push_back(new Page(*autre.pages[i]));
    }
    return (resultat);
}

ostream& operator<<(ostream& out, const Document& D)
{
    out << D.id << " ";
    out << D.titre << " ";
    out << D.auteur << " ";
    out << D.AnneePublication << " ";
    out << D.prix << " ";
    out << D.pages.size() << " ";

    for(int i = 0; i < D.pages.size(); i++)
    {
        out << *D.pages[i] << " ";
    }
    return out;
}

istream& operator>>(istream& in, Document& D)
{
    in >> D.id;
    in.ignore();
    getline(in, D.titre);
    getline(in, D.auteur);
    in >> D.AnneePublication >> D.prix;
    int nbPages;
    in >> nbPages;
    for(int i = 0; i < nbPages; i++)
    {
        Page* p = new Page("", 0);
        in >> *p;
        D.pages.push_back(p);
    }
    return in;
}

ostream& operator<<(ostream& out, const Document* D)
{
    out << D->id << " ";
    out << D->titre << " ";
    out << D->auteur << " ";
    out << D->AnneePublication << " ";
    out << D->prix << " ";
    out << D->pages.size() << " ";
    for(int i = 0; i < D->pages.size(); i++)
    {
        out << *D->pages[i] << " ";
    }
    return out;
}

istream& operator>>(istream& in, Document* D)
{
    in >> D->id;
    in.ignore();
    getline(in, D->titre);
    getline(in, D->auteur);
    in >> D->AnneePublication >> D->prix;
    int nbPages;
    in >> nbPages;
    for(int i = 0; i < nbPages; i++)
    {
        Page* p = new Page("", 0);
        in >> *p;
        D->pages.push_back(p);
    }
    return in;
}

//CLASSE LIVRE **************************************************************************************************************

Livre::Livre() : Document()
{
    this->nombrePages = 0;
    this->editeur = "";
}

Livre::~Livre()
{
    for(list<Chapitre*>::iterator it = chap.begin(); it != chap.end(); ++it)
    {
        delete *it;
    }
    chap.clear();
}

Livre::Livre(const Livre& autre) : Document(autre)
{
    this->nombrePages = autre.nombrePages;
    this->editeur = autre.editeur;

    for(list<Chapitre*>::const_iterator it = autre.chap.begin(); it != autre.chap.end(); ++it)
    {
        this->chap.push_back(new Chapitre(**it));
    }
}

void Livre::SaisirDocument()
{
    Document::SaisirDocument();
    cout << "Entrez le nombre de pages: ";
    cin >> this->nombrePages;
    cout << "Entrez l'editeur: ";
    cin >> this->editeur;
}

void Livre::AfficherDetails()
{
    cout << "--- Livre ---" << endl;
    cout << "ID: " << this->id << endl;
    cout << "Titre: " << this->titre << endl;
    cout << "Auteur: " << this->auteur << endl;
    cout << "Annee: " << this->AnneePublication << endl;
    cout << "Prix: " << this->prix << endl;
    cout << "Pages: " << this->nombrePages << endl;
    cout << "Editeur: " << this->editeur << endl;
    cout << "Chapitres:" << endl;
    for(list<Chapitre*>::iterator it = chap.begin(); it != chap.end(); ++it)
    {
        (*it)->Afficher();
    }
}

bool Livre::estEpais()
{
    return this->nombrePages > 400;
}

int Livre::GetNombrePages()
{
    return this->nombrePages;
}

void Livre::SetNombrePages(int nouveauNbPages)
{
    this->nombrePages = nouveauNbPages;
}

string Livre::GetEditeur()
{
    return this->editeur;
}

void Livre::SetEditeur(string nouvelEditeur)
{
    this->editeur = nouvelEditeur;
}

void Livre::AjouterChapitre(Chapitre* chapitre)
{
    this->chap.push_back(chapitre);
}

void Livre::SupprimerChapitre(int numero)
{
    for(list<Chapitre*>::iterator it = chap.begin(); it != chap.end(); ++it)
    {
        if((*it)->GetNumero() == numero)
        {
            delete *it;
            chap.erase(it);
            break;
        }
    }
}

ostream& operator<<(ostream& out, const Livre& L)
{
    out << static_cast<const Document&>(L) << " ";
    out << L.nombrePages << " ";
    out << L.editeur << " ";
    out << L.chap.size() << " ";
    for(list<Chapitre*>::const_iterator it = L.chap.begin(); it != L.chap.end(); ++it)
    {
        out << **it << " ";
    }
    return out;
}

istream& operator>>(istream& in, Livre& L)
{
    in >> static_cast<Document&>(L);
    in >> L.nombrePages;
    in >> L.editeur;
    int nbChapitres;
    in >> nbChapitres;
    for(int i = 0; i < nbChapitres; i++)
    {
        Chapitre* c = new Chapitre("", 0, 0, 0);
        in >> *c;
        L.chap.push_back(c);
    }
    return in;
}

ostream& operator<<(ostream& out, const Livre* L)
{
    out << static_cast<const Document*>(L) << " ";
    out << L->nombrePages << " ";
    out << L->editeur << " ";
    out << L->chap.size() << " ";
    for(list<Chapitre*>::const_iterator it = L->chap.begin(); it != L->chap.end(); ++it)
    {
        out << **it << " ";
    }
    return out;
}

istream& operator>>(istream& in, Livre* L)
{
    in >> static_cast<Document*>(L);
    in >> L->nombrePages;
    in >> L->editeur;
    int nbChapitres;
    in >> nbChapitres;
    for(int i = 0; i < nbChapitres; i++)
    {
        Chapitre* c = new Chapitre("", 0, 0, 0);
        in >> *c;
        L->chap.push_back(c);
    }
    return in;
}

//CLASSE POINT DE VENTE ***************************************************************************************************

PointDeVente::PointDeVente()
{
    this->adresse = "";
    this->fax = 0;
}

PointDeVente::~PointDeVente()
{
}

PointDeVente::PointDeVente(const PointDeVente& autre)
{
    this->adresse = autre.adresse;
    this->fax = autre.fax;
}

ostream& operator<<(ostream& out, const PointDeVente& PV)
{
    out << PV.adresse << " ";
    out << PV.fax;
    return out;
}

istream& operator>>(istream& in, PointDeVente& PV)
{
    in >> PV.adresse;
    in >> PV.fax;
    return in;
}

ostream& operator<<(ostream& out, const PointDeVente* PV)
{
    out << PV->adresse << " ";
    out << PV->fax;
    return out;
}

istream& operator>>(istream& in, PointDeVente* PV)
{
    in >> PV->adresse;
    in >> PV->fax;
    return in;
}
//CLASSE MAGAZINE *****************************************************************************************************

Magazine::Magazine() : Document()
{
    this->numero = 0;
    this->periodicite = "";
}

Magazine::~Magazine()
{
    for(int i = 0; i < vente.size(); i++)
    {
        delete vente[i];
    }
    vente.clear();
}

Magazine::Magazine(const Magazine& autre) : Document(autre)
{
    this->numero = autre.numero;
    this->periodicite = autre.periodicite;
    for(int i = 0; i < autre.vente.size(); i++)
    {
        this->vente.push_back(new PointDeVente(*autre.vente[i]));
    }
}

void Magazine::SaisirDocument()
{
    Document::SaisirDocument();
    cout << "Entrez le numero: ";
    cin >> this->numero;
    cout << "Entrez la periodicite: ";
    cin >> this->periodicite;
}

void Magazine::AfficherDetails()
{
    cout << "--- Magazine ---" << endl;
    cout << "ID: " << this->id << endl;
    cout << "Titre: " << this->titre << endl;
    cout << "Auteur: " << this->auteur << endl;
    cout << "Annee: " << this->AnneePublication << endl;
    cout << "Prix: " << this->prix << endl;
    cout << "Numero: " << this->numero << endl;
    cout << "Periodicite: " << this->periodicite << endl;
    cout << "Points de vente:" << endl;
    for(int i = 0; i < vente.size(); i++)
    {
        cout << "  " << *vente[i] << endl;
    }
}

int Magazine::GetNumero()
{
    return this->numero;
}

void Magazine::SetPeriodicite(string nouvellePeriodicite)
{
    this->periodicite = nouvellePeriodicite;
}

ostream& operator<<(ostream& out, const Magazine& M)
{
    out << static_cast<const Document&>(M) << " ";
    out << M.numero << " ";
    out << M.periodicite << " ";
    out << M.vente.size() << " ";
    for(int i = 0; i < M.vente.size(); i++)
    {
        out << *M.vente[i] << " ";
    }
    return out;
}

istream& operator>>(istream& in, Magazine& M)
{
    in >> static_cast<Document&>(M);
    in >> M.numero;
    in >> M.periodicite;
    int nbPointsVente;
    in >> nbPointsVente;
    for(int i = 0; i < nbPointsVente; i++)
    {
        PointDeVente* pv = new PointDeVente();
        in >> *pv;
        M.vente.push_back(pv);
    }
    return in;
}

ostream& operator<<(ostream& out, const Magazine* M)
{
    out << static_cast<const Document*>(M) << " ";
    out << M->numero << " ";
    out << M->periodicite << " ";
    out << M->vente.size() << " ";
    for(int i = 0; i < M->vente.size(); i++)
    {
        out << *M->vente[i] << " ";
    }
    return out;
}

istream& operator>>(istream& in, Magazine* M)
{
    in >> static_cast<Document*>(M);
    in >> M->numero;
    in >> M->periodicite;
    int nbPointsVente;
    in >> nbPointsVente;
    for(int i = 0; i < nbPointsVente; i++)
    {
        PointDeVente* pv = new PointDeVente();
        in >> *pv;
        M->vente.push_back(pv);
    }
    return in;
}

//CLASSE JOURNAL ******************************************************************************************************

Journal::Journal() : Document()
{
    this->datePublication = "";
}

Journal::~Journal()
{
}

Journal::Journal(const Journal& autre) : Document(autre)
{
    this->datePublication = autre.datePublication;
}

void Journal::SaisirDocument()
{
    Document::SaisirDocument();
    cout << "Entrez la date de publication (JJ/MM/AAAA): ";
    cin >> this->datePublication;
}

void Journal::AfficherDetails()
{
    cout << "--- Journal ---" << endl;
    cout << "ID: " << this->id << endl;
    cout << "Titre: " << this->titre << endl;
    cout << "Auteur: " << this->auteur << endl;
    cout << "Annee: " << this->AnneePublication << endl;
    cout << "Prix: " << this->prix << endl;
    cout << "Date Publication: " << this->datePublication << endl;
}

string Journal::GetDatePublication()
{
    return this->datePublication;
}

void Journal::SetDatePublication(string nouvelleDate)
{
    this->datePublication = nouvelleDate;
}

ostream& operator<<(ostream& out, const Journal& J)
{
    out << static_cast<const Document&>(J) << " ";
    out << J.datePublication;
    return out;
}

istream& operator>>(istream& in, Journal& J)
{
    in >> static_cast<Document&>(J);
    in >> J.datePublication;
    return in;
}

ostream& operator<<(ostream& out, const Journal* J)
{
    out << static_cast<const Document*>(J) << " ";
    out << J->datePublication;
    return out;
}

istream& operator>>(istream& in, Journal* J)
{
    in >> static_cast<Document*>(J);
    in >> J->datePublication;
    return in;
}

//CLASSE PUBLICATION PERIODIQUE ******************************************************************************************

PublicationPeriodique::PublicationPeriodique()
{
    this->frequence = 0;
}

PublicationPeriodique::~PublicationPeriodique()
{
}

PublicationPeriodique::PublicationPeriodique(const PublicationPeriodique& autre)
{
    this->frequence = autre.frequence;
}

void PublicationPeriodique::SaisiePub()
{
    cout << "Entrez la frequence (nombre de publications par an): ";
    cin >> this->frequence;
}

void PublicationPeriodique::AfficherFrequence()
{
    cout << "Frequence de publication: " << this->frequence << " fois par an" << endl;
}

ostream& operator<<(ostream& out, const PublicationPeriodique& PP)
{
    out << PP.frequence;
    return out;
}

istream& operator>>(istream& in, PublicationPeriodique& PP)
{
    in >> PP.frequence;
    return in;
}

ostream& operator<<(ostream& out, const PublicationPeriodique* PP)
{
    out << PP->frequence;
    return out;
}

istream& operator>>(istream& in, PublicationPeriodique* PP)
{
    in >> PP->frequence;
    return in;
}

//CLASSE JOURNAL SPECIAL ******************************************************************************************************

JournalSpecial::JournalSpecial() : Journal(), PublicationPeriodique()
{
    this->domaine = "";
}

JournalSpecial::~JournalSpecial()
{
}

JournalSpecial::JournalSpecial(const JournalSpecial& autre)
    : Journal(autre), PublicationPeriodique(autre)
{
    this->domaine = autre.domaine;
}

void JournalSpecial::SaisieJournalSpecial()
{
    Journal::SaisirDocument();
    PublicationPeriodique::SaisiePub();
    cout << "Entrez le domaine specialise: ";
    cin >> this->domaine;
}

void JournalSpecial::AfficherDetails()
{
    cout << "--- Journal Special ---" << endl;
    cout << "ID: " << this->id << endl;
    cout << "Titre: " << this->titre << endl;
    cout << "Auteur: " << this->auteur << endl;
    cout << "Annee: " << this->AnneePublication << endl;
    cout << "Prix: " << this->prix << endl;
    cout << "Date Publication: " << this->datePublication << endl;
    cout << "Frequence: " << this->frequence << endl;
    cout << "Domaine: " << this->domaine << endl;
}

ostream& operator<<(ostream& out, const JournalSpecial& JS)
{
    out << static_cast<const Journal&>(JS) << " ";
    out << static_cast<const PublicationPeriodique&>(JS) << " ";
    out << JS.domaine;
    return out;
}

istream& operator>>(istream& in, JournalSpecial& JS)
{
    in >> static_cast<Journal&>(JS);
    in >> static_cast<PublicationPeriodique&>(JS);
    in >> JS.domaine;
    return in;
}

ostream& operator<<(ostream& out, const JournalSpecial* JS)
{
    out << static_cast<const Journal*>(JS) << " ";
    out << static_cast<const PublicationPeriodique*>(JS) << " ";
    out << JS->domaine;
    return out;
}

istream& operator>>(istream& in, JournalSpecial* JS)
{
    in >> static_cast<Journal*>(JS);
    in >> static_cast<PublicationPeriodique*>(JS);
    in >> JS->domaine;
    return in;
}

//CLASSE CATALOGUE **********************************************************************************************************

Catalogue::Catalogue()
{
    this->nombreDocuments = 0;
    this->capacite = 10;
    this->tab.reserve(this->capacite);
}

Catalogue::~Catalogue()
{
    for(int i = 0; i < this->nombreDocuments; i++)
    {
        delete this->tab[i];
    }
}

Catalogue::Catalogue(const Catalogue& autre)
{
    this->nombreDocuments = autre.nombreDocuments;
    this->capacite = autre.capacite;
    for(int i = 0; i < autre.nombreDocuments; i++)
    {
        if(typeid(*autre.tab[i]) == typeid(Livre))
            this->tab.push_back(new Livre(*dynamic_cast<Livre*>(autre.tab[i])));
        else if(typeid(*autre.tab[i]) == typeid(Magazine))
            this->tab.push_back(new Magazine(*dynamic_cast<Magazine*>(autre.tab[i])));
        else if(typeid(*autre.tab[i]) == typeid(Journal))
            this->tab.push_back(new Journal(*dynamic_cast<Journal*>(autre.tab[i])));
        else if(typeid(*autre.tab[i]) == typeid(JournalSpecial))
            this->tab.push_back(new JournalSpecial(*dynamic_cast<JournalSpecial*>(autre.tab[i])));
    }
}

void Catalogue::AjouterDocument(Document* doc)
{
    if(this->nombreDocuments < this->capacite)
    {
        this->tab.push_back(doc);
        this->nombreDocuments++;
    }
}

void Catalogue::AfficherTousLesDocuments()
{
    for(int i = 0; i < this->nombreDocuments; i++)
    {
        this->tab[i]->AfficherDetails();
    }
}

void Catalogue::ModifierDocument(int id, string nouveauTitre)
{
    Document* doc = this->TrouverDocumentParId(id);
    if(doc != nullptr)
    {
        doc->SetTitre(nouveauTitre);
    }
}

void Catalogue::SupprimerDocument(int id)
{
    for(int i = 0; i < this->nombreDocuments; i++)
    {
        if(this->tab[i]->GetId() == id)
        {
            delete this->tab[i];
            this->tab.erase(this->tab.begin() + i);
            this->nombreDocuments--;
            break;
        }
    }
}

int Catalogue::GetNombreDocuments()
{
    return this->nombreDocuments;
}

Document* Catalogue::TrouverDocumentParId(int id)
{
    for(int i = 0; i < this->nombreDocuments; i++)
    {
        if(this->tab[i]->GetId() == id)
        {
            return this->tab[i];
        }
    }
    return nullptr;
}

void Catalogue::SauvegarderDansFichier(const string& FichierCatalogue)
{
    ofstream fichier(FichierCatalogue);
    if(fichier.is_open())
    {
        fichier << this->nombreDocuments << endl;
        for(int i = 0; i < this->nombreDocuments; i++)
        {
            if(dynamic_cast<Livre*>(this->tab[i]))
                fichier << "1 " << *dynamic_cast<Livre*>(this->tab[i]) << endl;
            else if(dynamic_cast<Magazine*>(this->tab[i]))
                fichier << "2 " << *dynamic_cast<Magazine*>(this->tab[i]) << endl;
            else if(dynamic_cast<Journal*>(this->tab[i]))
                fichier << "3 " << *dynamic_cast<Journal*>(this->tab[i]) << endl;
            else if(dynamic_cast<JournalSpecial*>(this->tab[i]))
                fichier << "4 " << *dynamic_cast<JournalSpecial*>(this->tab[i]) << endl;
        }
        fichier.close();
    }
}

void Catalogue::ChargerDepuisFichier(const string& FichierCatalogue)
{
    ifstream fichier(FichierCatalogue);
    for(int i = 0; i < this->nombreDocuments; i++) {
        delete this->tab[i];
    }
    this->tab.clear();
    this->nombreDocuments = 0;
    try
    {
        if(!fichier.is_open())
        {
            throw "Erreur";
        }
        int nbDocs;
        fichier >> nbDocs;
        for(int i = 0; i < nbDocs; i++)
        {
            char type;
            fichier >> type;
            Document* doc = nullptr;
            if(type == '1') doc = new Livre();
            else if(type == '2') doc = new Magazine();
            else if(type == '3') doc = new Journal();
            else if(type == '4') doc = new JournalSpecial();
            else throw "Erreur";
            fichier >> *doc;
            this->tab.push_back(doc);
            this->nombreDocuments++;
        }
    }
    catch(const char*)
    {
        cerr << "Erreur de chargement" << endl;
    }
    fichier.close();
}

ostream& operator<<(ostream& out, const Catalogue& cat)
{
    out << cat.nombreDocuments << " ";
    for(int i = 0; i < cat.nombreDocuments; i++)
    {
        if(dynamic_cast<const Livre*>(cat.tab[i]))
            out << "1 " << *dynamic_cast<const Livre*>(cat.tab[i]) << " ";
        else if(dynamic_cast<const Magazine*>(cat.tab[i]))
            out << "2 " << *dynamic_cast<const Magazine*>(cat.tab[i]) << " ";
        else if(dynamic_cast<const Journal*>(cat.tab[i]))
            out << "3 " << *dynamic_cast<const Journal*>(cat.tab[i]) << " ";
        else if(dynamic_cast<const JournalSpecial*>(cat.tab[i]))
            out << "4 " << *dynamic_cast<const JournalSpecial*>(cat.tab[i]) << " ";
    }
    return out;
}

istream& operator>>(istream& in, Catalogue& cat)
{
    int nbDocs;
    in >> nbDocs;
    for(int i = 0; i < nbDocs; i++)
    {
        char type;
        in >> type;
        Document* doc = nullptr;
        if(type == '1') doc = new Livre();
        else if(type == '2') doc = new Magazine();
        else if(type == '3') doc = new Journal();
        else if(type == '4') doc = new JournalSpecial();
        in >> *doc;
        cat.tab.push_back(doc);
        cat.nombreDocuments++;
    }
    return in;
}

ostream& operator<<(ostream& out, const Catalogue* cat)
{
    out << cat->nombreDocuments << " ";
    for(int i = 0; i < cat->nombreDocuments; i++)
    {
        if(dynamic_cast<const Livre*>(cat->tab[i]))
            out << "1 " << *dynamic_cast<const Livre*>(cat->tab[i]) << " ";
        else if(dynamic_cast<const Magazine*>(cat->tab[i]))
            out << "2 " << *dynamic_cast<const Magazine*>(cat->tab[i]) << " ";
        else if(dynamic_cast<const Journal*>(cat->tab[i]))
            out << "3 " << *dynamic_cast<const Journal*>(cat->tab[i]) << " ";
        else if(dynamic_cast<const JournalSpecial*>(cat->tab[i]))
            out << "4 " << *dynamic_cast<const JournalSpecial*>(cat->tab[i]) << " ";
    }
    return out;
}

istream& operator>>(istream& in, Catalogue* cat)
{
    int nbDocs;
    in >> nbDocs;
    for(int i = 0; i < nbDocs; i++)
    {
        char type;
        in >> type;
        Document* doc = nullptr;
        if(type == '1') doc = new Livre();
        else if(type == '2') doc = new Magazine();
        else if(type == '3') doc = new Journal();
        else if(type == '4') doc = new JournalSpecial();
        in >> *doc;
        cat->tab.push_back(doc);
        cat->nombreDocuments++;
    }
    return in;
}

// Affichage du menu principal
void afficherMenuPrincipal() {
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Gerer les documents" << endl;
    cout << "2. Gestion des fichiers" << endl;
    cout << "3. Quitter" << endl;
    cout << "Choix : ";
}

// Sous-menu pour la gestion des documents
void gererDocuments(Catalogue& cat) {
    int choix;
    do {
        cout << "\n=== GESTION DES DOCUMENTS ===" << endl;
        cout << "1. Ajouter un document" << endl;
        cout << "2. Afficher tous les documents" << endl;
        cout << "3. Modifier un document" << endl;
        cout << "4. Supprimer un document" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout << "Choix : ";

        // Gestion robuste de la saisie
        while (!(cin >> choix)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Saisie invalide. Veuillez entrer un nombre entre 1 et 5 : ";
        }
        cin.ignore();

        switch (choix) {
            case 1: {
                cout << "Type de document (1: Livre, 2: Magazine, 3: Journal, 4: JournalSpecial) : ";
                int type;
                while (!(cin >> type) || type < 1 || type > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Type invalide. Veuillez entrer 1, 2, 3 ou 4 : ";
                }
                cin.ignore();

                Document* doc = nullptr;
                switch (type) {
                    case 1: doc = new Livre(); break;
                    case 2: doc = new Magazine(); break;
                    case 3: doc = new Journal(); break;
                    case 4: doc = new JournalSpecial(); break;
                }

                if (doc) {
                    doc->SaisirDocument();
                    cat.AjouterDocument(doc);
                }
                break;
            }
            case 2:
                cat.AfficherTousLesDocuments();
                break;
            case 3: {
                int id;
                string nouveauTitre;
                cout << "ID du document à modifier : ";
                cin >> id;
                cout << "Nouveau titre : ";
                cin.ignore();
                getline(cin, nouveauTitre);
                cat.ModifierDocument(id, nouveauTitre);
                break;
            }
            case 4: {
                int id;
                cout << "ID du document a supprimer : ";
                cin >> id;
                cat.SupprimerDocument(id);
                break;
            }
            case 5:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Option invalide." << endl;
        }
    } while (choix != 5);
}

// Sous-menu pour la gestion des fichiers
void gererFichiers(Catalogue& cat) {
    int choix;
    do {
        cout << "\n=== GESTION DES FICHIERS ===" << endl;
        cout << "1. Sauvegarder le catalogue" << endl;
        cout << "2. Charger le catalogue" << endl;
        cout << "3. Retour au menu principal" << endl;
        cout << "Choix : ";

        // Gestion robuste de la saisie
        while (!(cin >> choix) || choix < 1 || choix > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Option invalide. Veuillez entrer 1, 2 ou 3 : ";
        }
        cin.ignore();

        string nomFichier;
        switch (choix) {
            case 1: {
                cout << "Nom du fichier de sauvegarde : ";
                getline(cin, nomFichier);
                if (nomFichier.empty()) {
                    cout << "Nom de fichier invalide!" << endl;
                    break;
                }
                cat.SauvegarderDansFichier(nomFichier);
                cout << "Catalogue sauvegarde dans " << nomFichier << endl;
                break;
            }
            case 2: {
                cout << "Nom du fichier a charger : ";
                getline(cin, nomFichier);
                if (nomFichier.empty()) {
                    cout << "Nom de fichier invalide!" << endl;
                    break;
                }

                // Vérifier si le fichier existe avant de charger
                ifstream test(nomFichier);
                if (!test.good()) {
                    cout << "Erreur: Fichier non trouve!" << endl;
                    test.close();
                    break;
                }
                test.close();

                cat.ChargerDepuisFichier(nomFichier);
                cout << "Catalogue charge depuis " << nomFichier << endl;
                cout << "Nombre de documents charges: " << cat.GetNombreDocuments() << endl;
                break;
            }
            case 3:
                cout << "Retour au menu principal." << endl;
                break;
        }
    } while (choix != 3);
}


//PROGRAMME PRINCIPAL ************************************************************************************************

int main() {
    Catalogue catalogue;
    int choix;

    do {
        afficherMenuPrincipal();
        cin >> choix;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choix) {
            case 1:
                gererDocuments(catalogue);
                break;
            case 2:
                gererFichiers(catalogue);
                break;
            case 3:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Option invalide. Réessayez." << endl;
        }
    } while (choix != 3);

    return 0;
}
