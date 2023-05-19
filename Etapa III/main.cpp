#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <memory>
#include <chrono>
#include <cmath>
using namespace std;
//design pattern template method: o clasa abstracta care defineste structura de baza
//a unui obiect din librarie, apoi fiecare obiect are atributele sale specifice
class ProdusLibrarie{
    string titlu,autor,limba,tip_produs;
    double pret;
    unsigned long long int cod;
    int nr_copii;
public:
    ProdusLibrarie(){}
    ProdusLibrarie(string titlu,string autor,string limba,double pret,unsigned long long int cod,int nr_copii,string tip_produs){//constr cu param
        this->titlu=titlu;
        this->autor=autor;
        this->limba=limba;
        this->pret=pret;
        this->cod=cod;
        this->nr_copii=nr_copii;
        this->tip_produs=tip_produs;
        }
        ProdusLibrarie(const ProdusLibrarie &p){//copy constructor
            titlu=p.titlu;
            autor=p.autor;
            limba=p.limba;
            pret=p.pret;
            cod=p.cod;
            nr_copii=p.nr_copii;
            tip_produs=p.tip_produs;
        }
    void operator=(const ProdusLibrarie &p){//supraincarcarea =
    this->titlu = p.titlu;
    this->autor = p.autor;
    this->limba = p.limba;
    this->pret = p.pret;
    this->cod = p.cod;
    this->nr_copii=p.nr_copii;
    }
   string get_titlu() const{//getter titlu
        return titlu;
    }
    string get_limba() const {//getter limba
        return limba;
    }
    int get_nr_copii() const {//getter nr copii
        return nr_copii;
  }
  string get_autor()const {//getter nume autor
      return autor;
  }
  double get_pret() const {//getter pret
      return pret;
  }
   unsigned long long int get_cod() const{//getter cod
       return cod;
   }
   void set_nr_copii(int nr){//setter pt nr copii
       nr_copii=nr;
   }
    bool verificare_stoc(const ProdusLibrarie &p){
        if(p.get_nr_copii()!=0)
            return 1;
        else
          return 0;
    }
void adaugare_nr_copii( int nr){
    nr_copii=nr_copii+nr;
}
void scoate_nr_copii( int nr){
    nr_copii=nr_copii-nr;
}
 virtual void afisare()=0;
};
class Revista:public ProdusLibrarie{
    string data_publicare;
    int nr_publicatie;
public:
      Revista(string titlu, string autor, string limba, double pret, unsigned long long int cod, int nr_copii,string tip_produs,string data_publicare, int nr_publicatie)
    : ProdusLibrarie(titlu, autor, limba, pret, cod, nr_copii, tip_produs), data_publicare(data_publicare), nr_publicatie(nr_publicatie) {}
     void afisare(){
     cout<<"Revista "<<get_titlu()<<" "<<"numarul "<<nr_publicatie<<" publicata in data "<<data_publicare<<" Editor: "<<get_autor()<<endl;
     }
};
class Carte:public ProdusLibrarie{
    string gen_carte;
    bool impachetata;
public:
    Carte(string titlu, string autor, string limba, double pret, unsigned long long int cod, int nr_copii,string tip_produs, string gen_carte):ProdusLibrarie(titlu, autor, limba, pret, cod, nr_copii, tip_produs), gen_carte(gen_carte),impachetata(false){}
  string get_categorie(){
   return gen_carte;
   }
    void setImpachetata(bool impachetata) {
        this->impachetata = impachetata;
    }

    void afisare() {
        cout << "Cartea " << get_titlu() << " scrisa de " << get_autor();
        if (impachetata) {
            cout << " (Impachetata)";
        }
        cout << endl;
    }
};
//decorator pattern
class ImpachetareCarte : public Carte {
public:
    ImpachetareCarte(const Carte& carte) : Carte(carte) {
        setImpachetata(true);
    }
};

class AudioBook:public Carte{
    string narator;
    int durata;
public:

    AudioBook(string titlu, string autor, string limba, double pret, unsigned long long int cod, int nr_copii,string tip_produs, string gen_carte,string narator,int durata):Carte(titlu, autor, limba, pret,  cod,  nr_copii,  tip_produs,gen_carte),narator(narator),durata(durata){}
    void afisare(){
        cout<<"Cartea audio "<<get_titlu()<<" scrisa de "<<get_autor()<<" narata de "<<narator<<endl;
    }
};

//functie template pentru adaugarea unui produs intr-un vector
template<typename T>
void adauga_produs(shared_ptr<T>& p, vector<shared_ptr<T>>& vector_prod_librarie) {
    vector_prod_librarie.push_back(p);
}

//specializare pentru vectorul de cos de cumparaturi
template<typename T>
void adauga_produs(shared_ptr<T>& p, vector<shared_ptr<ProdusLibrarie>>& vector_prod_librarie) {
    //dam upcast obiectului derivat pentru a il putea adauga in vectorul cu obiecte din clasa de baza
    shared_ptr<ProdusLibrarie> upcast_p = static_pointer_cast<ProdusLibrarie>(p);
    vector_prod_librarie.push_back(upcast_p);
    upcast_p->scoate_nr_copii(1);
    cout<<"Produsul a fost adaugat in cosul de cumparaturi!"<<endl;
}

//functie template pentru scoaterea unui produs dintr-un vector
template<typename T>
void scoate_produs(shared_ptr<T>& p, vector<shared_ptr<T>>& vector_prod_librarie) {
    auto it = find(vector_prod_librarie.begin(), vector_prod_librarie.end(), p);
    if (it != vector_prod_librarie.end()) {
        vector_prod_librarie.erase(it);
    }
}


//specializare pentru vectorul de cos de cumparaturi
template<typename T>
void scoate_produs(shared_ptr<T>& p, vector<shared_ptr<ProdusLibrarie>>& vector_prod_librarie) {
    //dam upcast obiectului derivat pentru a il putea scoate din vectorul cu obiecte din clasa de baza
    shared_ptr<ProdusLibrarie> upcast_p = static_pointer_cast<ProdusLibrarie>(p);

    //functia utilitara find
    auto it = find(vector_prod_librarie.begin(), vector_prod_librarie.end(), upcast_p);
    if (it != vector_prod_librarie.end()) {
        vector_prod_librarie.erase(it);
        cout<<"Produsul a fost scos din cosul de cumparaturi!"<<endl;
        upcast_p->adaugare_nr_copii(1);
    }
    else
        cout<<"Cartea nu se afla in cosul de cumparaturi!"<<endl;
}
template<typename T>
void verificare_stoc(vector<shared_ptr<T>>& vector_prod_librarie) {
    vector_prod_librarie.erase(
        remove_if(vector_prod_librarie.begin(), vector_prod_librarie.end(),
            [](const shared_ptr<T>& p) { return p->get_nr_copii() == 0; }),
        vector_prod_librarie.end()
    );
}
//clasa template pentru a crea un inventar pentru fiecare tip de produs din librarie
template<typename T>
class Inventar {
    vector<shared_ptr<T>> vector_prod_librarie;

public:
    Inventar() {}

    Inventar(const Inventar& inventar) {
        for (const auto& produs : inventar.vector_prod_librarie) {
            vector_prod_librarie.push_back(make_shared<T>(*produs));
        }
    }

    int get_nr_prod() {
        return vector_prod_librarie.size();
    }

    vector<shared_ptr<T>>& getVectorProdLibrarie() {
        return vector_prod_librarie;
    }

    Inventar& operator=(const Inventar& inventar) {
        if (this == &inventar) {
            return *this;  //vedem daca e self-assig
        }

        //stergem vectorul curent
        vector_prod_librarie.clear();

        // copiem elem din celalalt vector
        for (const auto& produs : inventar.vector_prod_librarie) {
            vector_prod_librarie.push_back(make_shared<T>(*produs));
        }

        return *this;
    }
     shared_ptr<T> cautare_titlu(const string& title) {
        for (const auto& produs : vector_prod_librarie) {
            if (produs->get_titlu() == title) {
                return produs;
            }
        }

        return nullptr;
    }

    void statistica_limba_carti() {
        int total_titluri = vector_prod_librarie.size();
        int c_romana = 0;
        int c_engleza = 0;
        int c_franceza = 0;
        int c_alte_limbi = 0;

        for (const auto& produs : vector_prod_librarie) {
            if (produs->get_limba() == "Romana") {
                c_romana++;
            } else if (produs->get_limba() == "Engleza") {
                c_engleza++;
            } else if (produs->get_limba() == "Franceza") {
                c_franceza++;
            } else {
                c_alte_limbi++;
            }
        }

        cout << "In inventarul magazinului sunt " << (c_romana * 100) / total_titluri << "% carti in limba romana, "
             << (c_engleza * 100) / total_titluri << "% carti in limba engleza, "
             << (c_franceza * 100) / total_titluri << "% carti in limba franceza si "
             << (c_alte_limbi * 100) / total_titluri << "% alte limbi." << endl;
    }
        void afisare() {
        if (vector_prod_librarie.size() != 0) {
            for (const auto& produs : vector_prod_librarie) {
                produs->afisare();
            }
        }
    }

    ~Inventar() {}
};


class Cont{//clasa abstracta
protected:
    string email,parola,adresa;//date membru protected
    virtual string get_email()=0;//functii protected
    virtual string get_parola()=0;
    virtual string get_adresa()=0;

public:
    Cont(){}
    Cont(string email,string parola, string adresa){
        this->email=email;
        this->parola=parola;
        this->adresa=adresa;
        }
    virtual void afis_detaliile_contului()=0;
    virtual ~Cont(){}
};
class Cont_client:protected Cont{//mostenire cu protected
    double nr_puncte;
    string nume,prenume;
public:
    Cont_client(){
    nr_puncte=0;
    nume="nu exista";
    prenume="nu exista";
    }
    Cont_client(string nume,string prenume, string email,string parola, string adresa):nume(nume),prenume(prenume),Cont(email,parola,adresa), nr_puncte(0.0){}

  void set_nr_puncte( double nr_pct){
      nr_puncte=nr_pct;
  }
    double get_nr_puncte(){
      return nr_puncte;
  }
  void set_schimbare_nume(string new_nume){
      nume=new_nume;
  }
    string get_prenume(){
        return prenume;
    }
     string get_nume(){
        return nume;
    }
    //polimorfism la executie
    string get_adresa(){
        return adresa;
    }
   string get_email(){
   return email;
   }
    string get_parola(){
   return parola;
   }
   void set_parola(string parola){
   this->parola=parola;
   }

   void set_adresa(string adresa){
   this->adresa=adresa;
   }
  void set_email(string email){
   this->email=email;
   }
  void afis_detaliile_contului(){
      cout<<"Numele utilizatorlui este "<<nume<<" "<<prenume<<endl;
  }
  ~Cont_client(){}
  friend double reducere_puncte(Cont_client &c);
  friend bool validare_cont(string email, string parola,Cont_client &cont);
  friend  bool login(Cont_client& cont);
};
double reducere_puncte(Cont_client &c){
    double reducere;
    reducere=c.nr_puncte/50;
    return reducere;
}
bool validare_cont(string email, string parola, Cont_client &cont) {
    try {
        if (cont.email==email&&cont.parola==parola)
            return true;
        else
            throw runtime_error("Email-ul sau parola sunt gresite!");//aruncare de exceptie
    }
    //un bloc try-catch care re-arunca un alt tip de exceptie
    catch (const exception& e) {
        throw invalid_argument(e.what());//aruncare de exceptie
    }
}

 bool login(Cont_client& cont) {
    string email, parola;
    while (true) {
        cout << "Introduceti email-ul (sau exit pentru a iesi): ";
        cin >> email;
        if (email == "exit") {
            return false;
        }
        cout << "Introduceti parola: ";
        cin >> parola;
        if (validare_cont(email, parola, cont) == 1) {
            cout << "Autentificarea a fost facuta cu succes!" << endl;
            return true;
        } else {
            cout << "Email-ul sau parola sunt gresite!" << endl;
        }
    }
}
bool login_parola(Cont_client& cont){
  string parola;
    while (true) {
        cout << "Introduceti parola: ";
        cin >> parola;
        if (validare_cont(cont.get_email(), parola, cont) == 1) {
            cout << "Autentificarea a fost facuta cu succes!" << endl;
            return true;
        }
    }
}

class ExceptieCustom:public exception{//exceptia custom care extinde std::exception
public:
    const char* what() const throw(){
        return "Exceptie custom: contul nu a fost gasit";
    }
};
class VectorConturi:public Cont_client{
    vector<Cont_client> vector_conturi;
public:
    void adauga_cont(Cont_client &cont){
    vector_conturi.push_back(cont);
    }
    void afis_conturi(){
        for(int i=0;i<vector_conturi.size();i++)
            vector_conturi[i].afis_detaliile_contului();
    }

    Cont_client& cauta_cont(string e) {
        for (int i = 0; i < vector_conturi.size(); i++) {
            if (vector_conturi[i].get_email() == e) {
                return vector_conturi[i];
            }
        }
        throw ExceptieCustom();//aruncare de exceptie
    }

};

class Tranzactie{

    vector<shared_ptr<ProdusLibrarie>> cos_cumparaturi;
    double suma;
    static double taxa_transport;//variabila statica
    string metoda_plata,nume_client,prenume_client,adresa_livrare;
public:

    Tranzactie(Cont_client &cont,string plata){//constructor cu param
       suma=0.0;
       metoda_plata=plata;
       nume_client=cont.get_nume();
       prenume_client=cont.get_prenume();
       adresa_livrare=cont.get_adresa();
    }

    void afis_cos(){//afisarea produselor din cosul de cumparaturi
        cout<<"--->In cosul de cumparaturi se afla produsele:"<<endl;
         if(cos_cumparaturi.size()!=0)
            for(int i=0;i<cos_cumparaturi.size();i++)
                cos_cumparaturi[i]->afisare();
            calculTotal();
            cout<<"--->Valoarea comenzii este de : "<<suma<<" lei"<<endl;
    }
  double get_suma(){
      return suma;
  }
  static double get_taxa_transport(){//functie statica
      return taxa_transport;
  }
  vector<shared_ptr<ProdusLibrarie>>& get_cos_cumparaturi(){
       return cos_cumparaturi;
  }
  static void set_taxa_transport(double taxa) {//functie statica
    taxa_transport=taxa;
    cout << "--->Taxa de transport a fost actualizata la "<<taxa_transport<<" lei."<<endl;
}
    //functia utilitara accumulate pentru a calcula totalul comenzii
    void calculTotal() {
        suma =accumulate(cos_cumparaturi.begin(), cos_cumparaturi.end(), 0.0,
            [](double sum, const shared_ptr<ProdusLibrarie>& produs) {
                return sum + produs->get_pret();
            });
    }

    void factura(Cont_client &c){
        c.set_nr_puncte(c.get_nr_puncte()+suma);
        cout << "--->Detaliile comenzii:" << endl;
        cout << "Numele clientului: " << c.get_nume() << " " << c.get_prenume() << endl;
        cout << "Adresa de livrare a comenzii: " << c.get_adresa() << endl;
        cout<<"Metoda de plata: "<<metoda_plata<<endl;
        cout << "Produsele comandate: " << endl;
        for (int i = 0; i <cos_cumparaturi.size(); i++){
            cos_cumparaturi[i]->afisare();
        }
        calculTotal();
        cout<<"--->Suma inainte de adaugarea taxei de transport: "<<suma<<endl;
        suma=suma+taxa_transport;
          cout << "--->Suma totala dupa adaugarea taxei de livrare in valoare de 15 lei este: " << suma << endl;
         c.set_nr_puncte(suma);
        double r=reducere_puncte(c);
        cout<<"--->Aveti un numar de "<<c.get_nr_puncte()<<" puncte ceea ce inseamna o reducere de "<<r<<" lei (50 puncte=1 leu reducere)"<<endl;
    }
    ~Tranzactie(){}

friend void aplicare_reducere(Tranzactie &t,Cont_client &c);
friend void reducere10(Tranzactie &t);//reducere 10% si transport gratuit pt comenzile>300 lei
};
double Tranzactie::taxa_transport=15.0;
void aplicare_reducere(Tranzactie &t,Cont_client &c){
    double r=reducere_puncte(c);
    if(t.suma>=r){
        t.suma=t.suma-r;
        c.set_nr_puncte(0);
    }
    else{
        t.suma=0;
        c.set_nr_puncte(r-t.suma*50);
    }
}
void reducere10(Tranzactie &t){
        t.suma=t.suma-Tranzactie::get_taxa_transport();//transport gratuit la comenzi peste 300 de lei
        t.suma=t.suma-0.1*t.suma;
}
class Review_carte : public Cont_client {
    shared_ptr<Carte> carte;
    int nr_stele;
    string review;

public:
    Review_carte(Cont_client& cont, shared_ptr<Carte>& carte, int nr_stele, string review)
        : Cont_client(cont), carte(carte), nr_stele(nr_stele), review(review) {}

    int get_nr_stele() {
        return nr_stele;
    }

    string get_review() {
        return review;
    }

    void modificare_nr_stele(int nr_stele) {
        this->nr_stele = nr_stele;
    }

    void modificare_review(string review) {
        this->review = review;
    }

    void afisare() {
        cout << "Review pentru Cartea " << carte->get_titlu() << " scrisa de " << carte->get_autor() << endl;
        cout << "--> Numarul de stele acordat este " << nr_stele << endl;
        if (review.empty()) {
            cout << "--> Nu ati acordat recenzie." << endl;
        } else {
            cout << "--> Recenzia acordata este: " << review << endl;
        }
    }

    ~Review_carte() {}
};


void meniu_cumparaturi(Cont_client &cont,Inventar<Carte>& inventar1, Inventar<Revista>& inventar2, Inventar<AudioBook>& inventar3){
    char raspuns;
    int choice,ok=1;
    string plata,titlu,tip_produs;
    cout<<"Doriti sa faceti o comanda sau sa lasati un review pentru o carte?"<<endl;
    cout<<"(pentru comanda introduceti c, pentru review r si pentru exit e)"<<endl;
    cin>>raspuns;
    if(raspuns=='c')

{   cout<<"Selectati o metoda de plata cash/card"<<endl;
    cin>>plata;
    Tranzactie t(cont,plata);
    while (ok==1) {
    cout<<"---------------------------------------------"<<endl;
    cout << "Alegeti o optiune: " << endl;
    cout<<"---------------------------------------------"<<endl;
    cout << "1.Cautare produs" << endl;
    cout << "2.Adaugare produs in cosul de cumparaturi" << endl;
    cout << "3.Scoate produs din cosul de cumparaturi" << endl;
    cout << "4.Afisati cosul de cumparaturi" << endl;
    cout << "5.Afisati sumarul comenzii" << endl;
    cout << "6.Afisati lista de carti din inventar" << endl;
    cout << "7.Afisati lista de reviste din inventar" << endl;
    cout << "8.Afisati lista de carti audio din inventar" << endl;
    cout << "9.Exit" << endl;
    cout << "Introduceti optiunea: ";
    cin >> choice;

    switch (choice) {
        case 1:
           {cout<<"Introduceti tipul produsului pe care doriti sa il cautati in inventar(Carte/Revista/AudioBook): "<<endl;
           cin.ignore();
           getline(cin,tip_produs);
           if(tip_produs=="Carte"||tip_produs=="carte"){
            cout<<"Introduceti titlul cartii pe care doriti sa o cautati in inventar: "<<endl;
           getline(cin,titlu);
           cout<<titlu<<endl;
           if(inventar1.cautare_titlu(titlu)!=nullptr)
            cout<<"--->Cartea se afla in inventar!"<<endl;
           else
            cout<<"--->Cartea nu se afla in inventar!"<<endl;
           }
           else
            if(tip_produs=="Revista"||tip_produs=="revista"){
            cout<<"Introduceti titlul revistei pe care doriti sa o cautati in inventar: "<<endl;
           getline(cin,titlu);
           if(inventar2.cautare_titlu(titlu)!=nullptr)
            cout<<"--->Revista se afla in inventar!"<<endl;
           else
            cout<<"--->Revista nu se afla in inventar!"<<endl;
           }
           else
            if(tip_produs=="AudioBook"||tip_produs=="Audiobook"||tip_produs=="audiobook"){
            cout<<"Introduceti titlul cartii audio pe care doriti sa o cautati in inventar: "<<endl;
           getline(cin,titlu);
           if(inventar3.cautare_titlu(titlu)!=nullptr)
            cout<<"--->Cartea audio se afla in inventar!"<<endl;
           else
            cout<<"--->Cartea audio nu se afla in inventar!"<<endl;
           }
           else
            cout<<"In inventar nu exista acest tip de produs!"<<endl;
           break;
           }
        case 2:
            {cout<<"Introduceti tipul produsului pe care doriti sa il adaugati in cosul de cumparaturi (Carte/Revista/AudioBook): "<<endl;
            cin.ignore();
           getline(cin,tip_produs);
            if(tip_produs=="Carte"||tip_produs=="carte"){
            cout<<"Introduceti titlul cartii pe care doriti sa o adaugati in cosul de cumparaturi: "<<endl;
           getline(cin,titlu);
           if(inventar1.cautare_titlu(titlu)!=nullptr)
            {shared_ptr<Carte> c=inventar1.cautare_titlu(titlu);
             adauga_produs(c, t.get_cos_cumparaturi());
            }
           else
            cout<<"--->Cartea nu se afla in inventar!"<<endl;
            }
            else
             if(tip_produs=="Revista"||tip_produs=="revista"){
            cout<<"Introduceti titlul revistei pe care doriti sa o adaugati in cosul de cumparaturi: "<<endl;
           getline(cin,titlu);
           if(inventar2.cautare_titlu(titlu)!=nullptr)
            {shared_ptr<Revista> r=inventar2.cautare_titlu(titlu);
             adauga_produs(r, t.get_cos_cumparaturi());
            }
           else
            cout<<"--->Revista nu se afla in inventar!"<<endl;
            }
            else
            if(tip_produs=="Audiobook"||tip_produs=="AudioBook"||tip_produs=="audiobook"){
            cout<<"Introduceti titlul cartii audio pe care doriti sa o adaugati in cosul de cumparaturi: "<<endl;
           getline(cin,titlu);
           if(inventar3.cautare_titlu(titlu)!=nullptr)
            {shared_ptr<AudioBook> a=inventar3.cautare_titlu(titlu);
             adauga_produs(a, t.get_cos_cumparaturi());
            }
           else
            cout<<"--->Cartea audio nu se afla in inventar!"<<endl;
            }
           else
            cout<<"In inventar nu exista acest tip de produs!"<<endl;
            break;
            }
        case 3:
            {
               {cout<<"Introduceti tipul produsului pe care doriti sa il scoateti din cosul de cumparaturi (Carte/Revista/AudioBook): "<<endl;
            cin.ignore();
           getline(cin,tip_produs);
            if(tip_produs=="Carte"||tip_produs=="carte"){
            cout<<"Introduceti titlul cartii pe care doriti sa o scoateti din cosul de cumparaturi: "<<endl;
           getline(cin,titlu);
           if(inventar1.cautare_titlu(titlu)!=nullptr)
            {shared_ptr<Carte> c=inventar1.cautare_titlu(titlu);
             scoate_produs(c, t.get_cos_cumparaturi());
            }
           else
            cout<<"--->Cartea nu se afla in inventar!"<<endl;
            }
            else
             if(tip_produs=="Revista"||tip_produs=="revista"){
            cout<<"Introduceti titlul revistei pe care doriti sa o scoateti din cosul de cumparaturi: "<<endl;
           getline(cin,titlu);
           if(inventar2.cautare_titlu(titlu)!=nullptr)
            {shared_ptr<Revista> r=inventar2.cautare_titlu(titlu);
             scoate_produs(r, t.get_cos_cumparaturi());
            }
           else
            cout<<"--->Revista nu se afla in inventar!"<<endl;
            }
            else
            if(tip_produs=="Audiobook"||tip_produs=="AudioBook"||tip_produs=="audiobook"){
            cout<<"Introduceti titlul cartii audio pe care doriti sa o scoateti din cosul de cumparaturi: "<<endl;
           getline(cin,titlu);
           if(inventar3.cautare_titlu(titlu)!=nullptr)
            {shared_ptr<AudioBook> a=inventar3.cautare_titlu(titlu);
             scoate_produs(a, t.get_cos_cumparaturi());
            }
           else
            cout<<"--->Cartea audio nu se afla in inventar!"<<endl;
            }
           else
            cout<<"In inventar nu exista acest tip de produs!"<<endl;
            break;
            }
            }
        case 4:
            {
                t.afis_cos();
                break;
            }
        case 5:
            {
                t.factura(cont);
                char rasp = 'Y';
                while (rasp == 'Y') {
                    cout << "Doriti sa va impachetam o carte pentru cadou? (Y/N)" << endl;
                    cin >> rasp;
                    if (rasp == 'Y') {
                        cout << "Introduceti titlul cartii pe care doriti sa o impachetam" << endl;
                        cin.ignore();
                        getline(cin, titlu);
                        shared_ptr<Carte> c = inventar1.cautare_titlu(titlu);
                        if (c != nullptr) {
                            if (find(t.get_cos_cumparaturi().begin(), t.get_cos_cumparaturi().end(), c) != t.get_cos_cumparaturi().end()) {
                                c->setImpachetata(true); // starea impachetãrii
                                cout<<"Cartea va fi impachetata pentru cadou!"<<endl;
                            }
                            else {
                                cout << "Cartea nu se afla in cosul de cumparaturi!" << endl;
                            }
                        } else
                            cout << "Cartea nu exista in inventar!" << endl;

                    }
                }


                cout<<"Doriti sa va folositi punctele pentru aceasta comanda?(Y/N)"<<endl;
                cin>>raspuns;
                if(raspuns=='Y'){
                    aplicare_reducere(t,cont);
                        if(t.get_suma()>300){
                        cout<<"De asemenea, comanda dumneavoastra depaseste 300 de lei, beneficiati de o reducere de 10% si transport gratuit!"<<endl;
                        reducere10(t);

                        }
                double total=round(t.get_suma()*100.0)/100.0;
                cout<<"Suma finala de plata este: "<<total<<endl;
                }
                else
                    cout<<"Suma finala de plata este: "<<t.get_suma()<<endl;
                cout<<"Doriti sa confirmati comanda?(Y/N)"<<endl;
                cin>>raspuns;
                if(raspuns=='Y'){
                    verificare_stoc(inventar1.getVectorProdLibrarie());
                    verificare_stoc(inventar2.getVectorProdLibrarie());
                    verificare_stoc(inventar3.getVectorProdLibrarie());
                    cout<<"Comanda dumneavoastra a fost confirmata!"<<endl;
                    cout<<"Produsele comandate sunt urmatoarele:"<<endl;
                    for(int i=0;i<t.get_cos_cumparaturi().size();i++)
                          t.get_cos_cumparaturi()[i]->afisare();
                    //timpul curent
                    //folosirea bibliotecii utilitare chrono
                    auto timp = std::chrono::system_clock::now();
                    std::time_t timp_t = std::chrono::system_clock::to_time_t(timp);
                    std::string data_comanda = std::ctime(&timp_t);
                    data_comanda.erase(data_comanda.find_last_not_of("\n") + 1);
                    double total=round(t.get_suma()*100.0)/100.0;
                    cout<<"Total: "<<total<<endl;
                    cout << "Data plasarii comenzii: " << data_comanda << endl;
                    cout<<"Va mai asteptam!"<<endl;
                    ok=0;
                }
                else
                {   int r;
                    cout<<"Daca doriti sa va intoarceti la meniu tastati 1, daca doriti sa iesiti tastati 0 "<<endl;
                    cin>>r;
                    ok=r;
                }
                if(ok==0)
                    cout<<"La revedere!"<<endl;
                break;
            }
        case 6:
            {   cout<<"--->Lista cartilor disponibile este urmatoarea:"<<endl;
                inventar1.afisare();
                break;
            }
        case 7:
        {   cout<<"--->Lista revistelor disponibile este urmatoarea:"<<endl;
                inventar2.afisare();
                break;
            }
        case 8:
            {   cout<<"--->Lista cartilor audio disponibile este urmatoarea:"<<endl;
                inventar3.afisare();
                break;
            }
        case 9:
            {   ok=0;
            cout<<"La revedere!"<<endl;
                break;
            }
        default:
            {cout << "Alegere invalida incercati din nou!" << endl;
            break;
            }
    }
}
    }
    else
     if (raspuns == 'r') {
    int rating;
    string recenzie, titlu;
    int ok = 1,f=0;
    while (ok == 1) {
        cout << "------------------------------------------------------" << endl;
        cout << "Introduceti titlul cartii pe care doriti sa o evaluati" << endl;
        cout << "------------------------------------------------------" << endl;
        if(f==0)
        cin.ignore();//ignoram doar prima data cand citim un titlu
        getline(cin, titlu);
        cout<<titlu<<endl;

        try {
            if (inventar1.cautare_titlu(titlu) != nullptr) {
                shared_ptr<Carte> c = inventar1.cautare_titlu(titlu);
                f=0;
                cout << "Oferiti cartii un rating de la 1 la 5 stele" << endl;
                cin >> rating;
                cout << "Oferiti o recenzie cartii (daca nu doriti sa scrieti o recenzie apasati enter)" << endl;
                cin.ignore();
                getline(cin, recenzie);
                Review_carte r(cont, c, rating, recenzie);
                cout << "Detaliile review-ului:" << endl;
                cout << "Contul care a acordat review-ul: ";
                Cont_client* ptrCont = &r; // upcasting
                ptrCont->afis_detaliile_contului();
                cout << "Cartea careia i se acorda review: ";
                c->afisare();
                r.afisare();
                ok = 0;
                meniu_cumparaturi(cont,inventar1,inventar2,inventar3);
            }
             else {
                throw invalid_argument("Exceptie titlu invalid: Cartea nu exista in inventar"); // aruncare de exceptie

            }
        }
        catch (const exception& e) {
            f++;
            cout << e.what() << endl;
        }
    }
}

     else
        cout<<"La revedere"<<endl;

}


void meniu_start(Inventar<Carte>& inventar1, Inventar<Revista>& inventar2, Inventar<AudioBook>& inventar3, VectorConturi& v_conturi)
{     string nume, prenume, adresa,email, parola;
     int choice,log_in=0,ok=1;
     Cont_client c;
    while (log_in!=1&&ok==1) {
    cout<<"---------------------------------------------"<<endl;
    cout << "Bine ati venit la libraria noastra online!" << endl;
    cout<<"---------------------------------------------"<<endl;
    cout<<"Alegeti o optiune:"<<endl;
    cout << "0. Exit"<< endl;
    cout << "1. Creati-va un cont" <<endl;
    cout<<"2. Conectati-va la un cont deja existent"<<endl;
    cout << "Introduceti optiunea: ";
    try{
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');//ignora un sir de carac de max 100
        throw invalid_argument("Optiune invalida!");//aruncare de exceptie
    }

    switch (choice) {
        case 1:
            {cout << "Introduceti numele dumneavoastra: ";
            cin >> prenume;
            cout << "Introduceti prenumele dumneavoastra: ";
            cin >> nume;
            cout << "Introduceti email-ul dumneavoastra: ";
            cin >> email;
            cout << "Introduceti parola dumneavoastra: ";
            cin >> parola;
            cout << "Introduceti adresa dumneavoastra: ";
            cin.ignore();
            getline(cin,adresa);

            Cont_client cont(nume,prenume,email,parola,adresa);
            c=cont;
            cout<<"Contul dumneavoastra a fost creat cu succes! Va rugam sa va logati in cont pentru a continua."<<endl;
            if(login(c))
                log_in=1;
           break;}
        case 2:{
            cout << "Introduceti email-ul dumneavoastra: ";
            cin.ignore();
            getline(cin,email);
            try {
            Cont_client& cont=v_conturi.cauta_cont(email);
            cont.afis_detaliile_contului();
             if(login_parola(cont)){
                log_in=1;
                c=cont;
                }
        }
        catch (const exception& ex) {
            cout<<ex.what()<<endl;

        }

           break;
        }
        case 0:{
            ok=0;
            cout<<"La revedere!"<<endl;
            break;
        }
        default:
    {
        cout<<"Alegere invalida incercati din nou!"<<endl;
         break;
     }
}
}
    catch (const invalid_argument& e) {//prinde o exceptie cu mentiunea explicita a tipului acesteia
        cout << "Eroare de argument: "<< e.what() << endl;
    }
}
cin.ignore();
    if(log_in==1)
     meniu_cumparaturi(c,inventar1,inventar2,inventar3);
}

int main() {
    Inventar<Carte> inventar1;
    Inventar<Revista>inventar2;
    Inventar<AudioBook> inventar3;
    VectorConturi v_conturi;
     ifstream f("produse_librarie.in");
     ifstream g("conturi.in");
     string line;
     int choice,log_in=0;



    while (getline(f, line)) {
        stringstream ss(line);
        string titlu,autor,categorie,limba,tip_produs,data_publicatie,narator;
        double pret;
        long long int cod;
        int nr_copii,nr_publicatie,durata;

        getline(ss, titlu, ',');
        getline(ss, autor, ',');
        getline(ss, limba, ',');
        getline(ss, tip_produs, ',');
        ss >> pret;
        ss.ignore();

        ss >> cod;
        ss.ignore();

        ss >> nr_copii;
        ss.ignore();
        if(tip_produs=="Carte"){
            getline(ss, categorie, '\n');
            shared_ptr<Carte> c = make_shared<Carte>(titlu, autor, limba, pret, cod, nr_copii,tip_produs, categorie);
            adauga_produs(c, inventar1.getVectorProdLibrarie());
        }
        else
        if(tip_produs=="Revista"){
            getline(ss, data_publicatie, ',');
            ss>>nr_publicatie;
            shared_ptr<Revista> r = make_shared<Revista>(titlu, autor, limba, pret, cod, nr_copii,tip_produs, data_publicatie, nr_publicatie);
            adauga_produs(r, inventar2.getVectorProdLibrarie());
        }
        else
        if(tip_produs=="AudioBook"){
            getline(ss, categorie, ',');
            getline(ss, narator, ',');
            ss>>durata;
            shared_ptr<AudioBook> a = make_shared<AudioBook>(titlu, autor, limba, pret, cod, nr_copii,tip_produs, categorie,narator,durata);
            adauga_produs(a, inventar3.getVectorProdLibrarie());
        }
    }
    while (getline(g, line)) {
        stringstream ss(line);
        string prenume,nume,email,parola,adresa;

        getline(ss, prenume, ',');
        getline(ss, nume, ',');
        getline(ss, email, ',');
        getline(ss, parola, ',');
        getline(ss, adresa);
        Cont_client c(nume,prenume,email,parola,adresa);
        v_conturi.adauga_cont(c);
    }
    meniu_start(inventar1,inventar2,inventar3,v_conturi);

    return 0;
}
