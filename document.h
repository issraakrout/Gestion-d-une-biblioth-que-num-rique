#ifndef DOCUMENT_H
#define DOCUMENT_H
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;

class Chapitre
{
private:
    string titre;
    int numero;
    int pageDebut;
    int pageFin;

public:
    Chapitre(string titre, int numero, int pageDebut, int pageFin);
    ~Chapitre();
    Chapitre(const Chapitre& autre);
    string GetTitre();
    int GetNumero();
    int GetPageDebut();
    int GetPageFin();
    void SetTitre(string nouveauTitre);
    void SetNumero(int nouveauNumero);
    void SetPages(int debut, int fin);
    void Afficher();
    Chapitre& operator=(const Chapitre& autre);
    friend ostream& operator<<(ostream& out, const Chapitre& chap);
    friend istream& operator>>(istream& in, Chapitre& chap);
    friend ostream& operator<<( ostream&out,const Chapitre* chap);
    friend istream& operator>>(istream&in,Chapitre* chap);
};

class Page
{
private:
    string content;
    int pageNumber;

public:
    Page(string content, int pageNumber);
    virtual ~Page();
    Page(const Page& autre);
    string getContent();
    int getPageNumber();
    void setContent(string newContent);
    void setPageNumber(int newPageNumber);
    void afficher();
    friend ostream& operator<<( ostream& out,const Page& P);
    friend istream& operator>>(istream&in,Page& P);
    friend ostream& operator<<( ostream&out,const Page* P);
    friend istream& operator>>(istream&in,Page* P);
};

class Document
{
protected:
    int id;
    string titre;
    string auteur;
    int AnneePublication;
    float prix;
    static int nombreTotalDocuments;
    vector<Page*>pages;
public:
    Document();
    virtual ~Document();
    Document(const Document& autre);
    virtual void AfficherDetails() = 0;
    virtual void SaisirDocument();
    int CalculerAge(int AnneeActuelle);
    int GetId();
    static int GetNombreTotalDocuments();
    void SetTitre(string nouveauTitre);
    float GetPrix();
    void SetPrix(float nouveauPrix);
    void AjouterPage(Page* page);
    vector<Page*> GetPages();
    Document* operator+(const Document& autre);
    friend ostream& operator<<( ostream& out,const Document& D);
    friend istream& operator>>(istream&in,Document& D);
    friend ostream& operator<<( ostream&out,const Document* D);
    friend istream& operator>>(istream&in,Document* D);
};

class Livre : public Document
{
private:
    int nombrePages;
    string editeur;
    list<Chapitre*> chap;
public:
    Livre();
    ~Livre();
    Livre(const Livre& autre);
    void SaisirDocument();
    void AfficherDetails();
    bool estEpais();
    int GetNombrePages();
    void SetNombrePages(int nouveauNbPages);
    string GetEditeur();
    void SetEditeur(string nouvelEditeur);
    void AjouterChapitre(Chapitre* chapitre);
    void SupprimerChapitre(int numero);
    friend ostream& operator<<( ostream& out,const Livre& L);
    friend istream& operator>>(istream&in,Livre& L);
    friend ostream& operator<<( ostream&out,const Livre* L);
    friend istream& operator>>(istream&in,Livre* L);
};

class PointDeVente
{
public:
    string adresse ;
    int fax;
public:
    PointDeVente();
    ~PointDeVente();
    PointDeVente(const PointDeVente& autre);
    friend ostream& operator<<( ostream& out,const PointDeVente& PV);
    friend istream& operator>>(istream&in,PointDeVente& PV);
    friend ostream& operator<<( ostream&out,const PointDeVente* PV);
    friend istream& operator>>(istream&in,PointDeVente* PV);
};

class Magazine : public Document
{
private:
    int numero;
    string periodicite;
    vector<PointDeVente*> vente;
public:
    Magazine();
    ~Magazine();
    Magazine(const Magazine& autre);
    void SaisirDocument();
    void AfficherDetails();
    int GetNumero();
    void SetPeriodicite(string nouvellePeriodicite);
    friend ostream& operator<<( ostream& out,const Magazine& M);
    friend istream& operator>>(istream&in,Magazine& M);
    friend ostream& operator<<( ostream&out,const Magazine* M);
    friend istream& operator>>(istream&in,Magazine* M);
};

class Journal : public Document
{
protected:
    string datePublication;
public:
    Journal();
    ~Journal();
    Journal(const Journal& autre);
    void SaisirDocument();
    void AfficherDetails();
    string GetDatePublication();
    void SetDatePublication(string nouvelleDate);
    friend ostream& operator<<( ostream& out,const Journal& J);
    friend istream& operator>>(istream&in,Journal& J);
    friend ostream& operator<<( ostream&out,const Journal* J);
    friend istream& operator>>(istream&in,Journal* J);
};

class PublicationPeriodique
{
protected:
    int frequence;
public:
    PublicationPeriodique();
    ~PublicationPeriodique();
    PublicationPeriodique(const PublicationPeriodique& autre);
    void SaisiePub();
    void AfficherFrequence();
    friend ostream& operator<<( ostream& out,const PublicationPeriodique& PP);
    friend istream& operator>>(istream&in,PublicationPeriodique& PP);
    friend ostream& operator<<( ostream&out,const PublicationPeriodique* PP);
    friend istream& operator>>(istream&in,PublicationPeriodique* PP);
};

class JournalSpecial : public Journal, public PublicationPeriodique
{
private:
    string domaine;
public:
    JournalSpecial();
    ~JournalSpecial();
    JournalSpecial(const JournalSpecial& autre);
    void SaisieJournalSpecial();
    void AfficherDetails();
    friend ostream& operator<<( ostream& out,const JournalSpecial& JS);
    friend istream& operator>>(istream&in,JournalSpecial& JS);
    friend ostream& operator<<( ostream&out,const JournalSpecial* JS);
    friend istream& operator>>(istream&in,JournalSpecial* JS);
};

class Catalogue
{
private:
    vector<Document*> tab;
    int nombreDocuments;
    int capacite;
public:
    Catalogue();
    ~Catalogue();
    Catalogue(const Catalogue& autre);
    void AjouterDocument(Document* doc);
    void AfficherTousLesDocuments();
    void ModifierDocument(int id, string nouveauTitre);
    void SupprimerDocument(int id);
    int GetNombreDocuments();
    Document* TrouverDocumentParId(int id);
    void SauvegarderDansFichier(const string& nomFichier);
    void ChargerDepuisFichier(const string& nomFichier);
    friend ostream& operator<<( ostream& out,const Catalogue& );
    friend istream& operator>>(istream&in,Catalogue& );
    friend ostream& operator<<( ostream&out,const Catalogue* );
    friend istream& operator>>(istream&in,Catalogue* );
};

#endif






