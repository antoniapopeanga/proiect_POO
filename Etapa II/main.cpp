#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class Carte{
    string titlu,autor,limba;
    double pret;
    unsigned long long int cod;
    int nr_copii;

public:

    Carte(){//constructor fara parametru
        titlu="Fara titlu";
        autor="Fara autor";
        limba="Nu exista limba";
        pret=0.0;
        cod=0;
        nr_copii=0;
    }
    Carte (const Carte &c){//copy constructor
        titlu=c.titlu;
        autor=c.autor;
        limba=c.limba;
        pret=c.pret;
        cod=c.cod;
        nr_copii=c.nr_copii;
    }
    Carte(string titlu,string autor,string limba,double pret,unsigned long long int cod,int nr_copii){//constructor cu parametru
        this->titlu=titlu;
        this->autor=autor;
        this->limba=limba;
        this->pret=pret;
        this->cod=cod;
        this->nr_copii=nr_copii;

    }

    void operator=(const Carte &c){//supraincarcarea =
    this->titlu = c.titlu;
    this->autor = c.autor;
    this->limba = c.limba;
    this->pret = c.pret;
    this->cod = c.cod;
    this->nr_copii=c.nr_copii;
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
   long long int get_cod() const{//getter cod ISBN
       return cod;
   }
   void set_nr_copii(int nr){//setter pt nr copii
       nr_copii=nr;
   }
  virtual void afisare(){
   cout<<titlu<<" scrisa de "<<autor<<endl;
   }
    friend ostream & operator << (ostream &out, const Carte &c);
    friend bool verificare_stoc(Carte &c);
    friend void adaugare_nr_copii(Carte &c, int nr_copii);

};
bool verificare_stoc(Carte &c){
        if(c.get_nr_copii()!=0)
            return 1;
        else
          return 0;
    }
void adaugare_nr_copii(Carte &c, int nr_copii){
    c.nr_copii=c.nr_copii+nr_copii;
}
ostream & operator << (ostream &out, const Carte &c)
{
    out<<"Titlul cartii este: "<<c.titlu<<endl<<"Autorul cartii este: "<<c.autor<<endl<<"Cartea este in limba: "<<c.limba<<endl<<"Pretul este: "<<c.pret<<endl<<"Numarul de copii este: "<<c.nr_copii<<endl;
    return out;
}
class GenCarte: public Carte{//mostenire cu public
    string categorie;
public:
    GenCarte(){}
    //apelarea constructorului clasei de baza cu param din clasa copil fol liste de initializare
    GenCarte(string titlu,string autor,string limba,double pret,unsigned long long int cod,int nr_copii,string categ): Carte(titlu,autor,limba,pret,cod,nr_copii), categorie(categ){}
   string get_categorie(){
   return categorie;
   }
    ~GenCarte(){}
};
class Gestiune_Vector_Carti{//interfata
public:
    virtual void adauga_carte(GenCarte &c) = 0;
    virtual void scoate_carte(GenCarte &c) = 0;
    virtual ~Gestiune_Vector_Carti(){
    cout<<"Destructor clasa interfata"<<endl;
    }
};
class Inventar:public Gestiune_Vector_Carti,public Carte {//mostenire multipla cu public
    std::vector<GenCarte> vector_carti;
public:

    Inventar(){}


    Inventar(const Inventar &inventar){//copy constructor
        vector_carti=inventar.vector_carti;
    }
    int get_nr_titluri(){
        return vector_carti.size();
    }
    GenCarte& return_carte(string titlu){
        int i;
        for (i =0;i<vector_carti.size(); i++)
            if(vector_carti[i].get_titlu()==titlu)
                return vector_carti[i];
    }

  void adauga_carte (GenCarte &c){
    vector_carti.push_back(c);//polimorfism la executie
}
     void scoate_carte( GenCarte &c){//polimorfism la executie
        int i;
        for (i =0;i<vector_carti.size(); i++)
            if (vector_carti[i].get_cod()==c.get_cod()) {
                vector_carti.erase(vector_carti.begin() + i);
                break;
            }
        cout << "Scoaterea din inventar a fost efectuata cu succes!" << endl;
    }
    bool cautare_carte_titlu(string titlu){
        int i;
        for (i =0;i<vector_carti.size(); i++)
            if(vector_carti[i].get_titlu()==titlu){
                return 1;
            }
        return 0;
    }
    void afisare() {
        if(vector_carti.size()!=0)
            for(int i=0;i<vector_carti.size();i++){
                Carte *carte = &vector_carti[i];//upcasting
                cout<<i+1<<".";
                carte->afisare();
    }
    }
   Inventar& operator=(const Inventar& i) {
    if (this!=&i){
        vector_carti=i.vector_carti;
    }
    return *this;
}

    ~Inventar(){
    cout<<"Destructor clasa Inventar"<<endl;
    }//dupa ce se apeleaza destructorul clasei inventar se apeleaza si destructorul virtual

friend void scoate_nr_copii(Inventar &inventar,Carte &c, int nr_copii);
friend void statistica_limba_carti(Inventar &inv);
};

void scoate_nr_copii(GenCarte &c, int nr_copii){
    if(c.get_nr_copii()>=nr_copii)
     c.set_nr_copii(c.get_nr_copii()-nr_copii);
    else
     cout << "Numarul cartilor scoase este prea mare, mai sunt disponible "<< c.get_nr_copii() << " exemplare din cartea "<<c.get_titlu()<<endl;
}
void statistica_limba_carti(Inventar &inv){
    int total_titluri=inv.vector_carti.size();
    int c_romana=0;
    int c_engleza=0;
    int c_franceza=0;
    int c_alte_limbi=0;
    for(int i=0;i<total_titluri;i++){
        if(inv.vector_carti[i].get_limba()=="Romana")
            c_romana++;
        else
            if(inv.vector_carti[i].get_limba()=="Engleza")
            c_engleza++;
        else
            if(inv.vector_carti[i].get_limba()=="Franceza")
            c_franceza++;
            else
                c_alte_limbi++;
    }
    cout<<"In inventarul magazinului sunt "<<(c_romana*100)/total_titluri<<" % carti in limba romana, "<<(c_engleza*100)/total_titluri<<" % carti in limba engleza, ";
    cout<<(c_franceza*100)/total_titluri<<" % carti in limba franceza si "<<(c_alte_limbi*100)/total_titluri<<"% alte limbi."<<endl;
}
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
    virtual void set_parola(string parola)=0;
    virtual void set_adresa(string adresa)=0;
    virtual void set_email(string email)=0;
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
class Tranzactie: public Gestiune_Vector_Carti{

    vector <GenCarte> cos_cumparaturi;
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

    void afis_cos(){//afisarea cartilor din cosul de cumparaturi
        cout<<"--->In cosul de cumparaturi se afla cartile:"<<endl;
         if(cos_cumparaturi.size()!=0)
            for(int i=0;i<cos_cumparaturi.size();i++)
                cout<<cos_cumparaturi[i].get_titlu()<<" scrisa de "<<cos_cumparaturi[i].get_autor()<<endl;
            cout<<"--->Valoarea comenzii este de : "<<suma<<" lei"<<endl;
    }
  double get_suma(){
      return suma;
  }
  static double get_taxa_transport(){//functie statica
      return taxa_transport;
  }
  static void set_taxa_transport(double taxa) {//functie statica
    taxa_transport=taxa;
    cout << "--->Taxa de transport a fost actualizata la "<<taxa_transport<<" lei."<<endl;
}
  void adauga_carte (GenCarte &c)//polimorfism la executie
  {   if(verificare_stoc(c)==1){
          cos_cumparaturi.push_back(c);
          scoate_nr_copii(c,1);
          suma=suma+c.get_pret();
          cout<<"--->Cartea a fost adaugata in cosul de cumparaturi!"<<endl;
  }
     else
        cout<<"--->Cartea nu mai este pe stoc!"<<endl;
  }
  void scoate_carte (GenCarte &c) {//polimorfism la executie
        int i,ok=0;
        for (i =0;i<cos_cumparaturi.size(); i++)
            if (cos_cumparaturi[i].get_cod()==c.get_cod()) {
            cos_cumparaturi.erase(cos_cumparaturi.begin() + i);
            suma=suma-c.get_pret();
            ok=1;
            cout << "--->Cartea a fost scoasa din cosul de cumparaturi." << endl;
            adaugare_nr_copii(c,1);
            break;
            }
        if(ok==0)
       cout<<"--->Cartea nu exista in cosul de cumparaturi!"<<endl;
  }

    void factura(Cont_client &c){
        c.set_nr_puncte(c.get_nr_puncte()+suma);
        cout << "--->Detaliile comenzii:" << endl;
        cout << "Numele clientului: " << c.get_nume() << " " << c.get_prenume() << endl;
        cout << "Adresa de livrare a comenzii: " << c.get_adresa() << endl;
        cout<<"Metoda de plata: "<<metoda_plata<<endl;
        cout << "Cartile comandate: " << endl;
        for (int i = 0; i <cos_cumparaturi.size(); i++) {
                Carte *carte = &cos_cumparaturi[i];//upcasting
                carte->afisare();
                if (GenCarte* g = dynamic_cast<GenCarte*>(carte)) {//downcasting
                        cout<<"->categoria "<<g->get_categorie()<<endl;
                  }
                else {
                        cout<<"->nu are categorie"<<endl;
            }
        }
        cout<<"--->Suma inainte de adaugarea taxei de transport: "<<suma<<endl;
        suma=suma+taxa_transport;
          cout << "--->Suma totala dupa adaugarea taxei de livrare in valoare de 15 lei este: " << suma << endl;

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

class Review_carte: public Cont_client, public GenCarte{//mostenire multipla cu public
    int nr_stele;
    string review;
public:
    Review_carte(Cont_client &cont,GenCarte &carte, int nr_stele, string review): Cont_client(cont), GenCarte(carte), nr_stele(nr_stele), review(review){}
    int get_nr_stele(){
    return nr_stele;
    }
    string get_review(){
    return review;
    }
    void modificare_nr_stele(int nr_stele){
    this->nr_stele=nr_stele;
    }
    void modificare_review(string review){
    this->review=review;
    }
    void afis(){
    cout<<"-->Numarul de stele acordat este "<<nr_stele<<endl;
    if(review==" ")
    cout<<"-->Nu ati acordat recenzie."<<endl;
    else
        {cout<<"-->Recenzia acordata este: ";
        cout<<review<<endl;;

        }
    }
    ~Review_carte(){}
};
void meniu_cumparaturi(Cont_client &cont,Inventar &inventar){
    char raspuns;
    int choice,ok=1;
    Inventar inv(inventar);
    string plata,titlu;
    cout<<"Doriti sa faceti o comanda sau sa lasati un review pentru o carte? (pentru comanda introduceti c, pentru review r si pentru exit e)"<<endl;
    cin>>raspuns;
    if(raspuns=='c')

{   cout<<"Selectati o metoda de plata cash/card"<<endl;
    cin>>plata;
    Tranzactie t(cont,plata);
    while (ok==1) {
    cout<<"---------------------------------------------"<<endl;
    cout << "Alegeti o optiune: " << endl;
    cout<<"---------------------------------------------"<<endl;
    cout << "1.Cautare titlu" << endl;
    cout << "2.Adaugare titlu in cosul de cumparaturi" << endl;
    cout << "3.Scoate titlu din cosul de cumparaturi" << endl;
    cout << "4.Afisati cosul de cumparaturi" << endl;
    cout << "5.Afisati sumarul comenzii" << endl;
    cout << "6.Afisati lista de carti din inventar" << endl;
    cout << "7.Exit" << endl;
    cout << "Introduceti optiunea: ";
    cin >> choice;

    switch (choice) {
        case 1:
           {cout<<"Introduceti titlul unei carti pe care doriti sa o cautati in inventar: "<<endl;
           cin.ignore();
           getline(cin,titlu);
           if(inventar.cautare_carte_titlu(titlu)==1)
            cout<<"--->Cartea se afla in inventar!"<<endl;
           else
            cout<<"--->Cartea nu se afla in inventar!"<<endl;
           break;
           }
        case 2:
            {cout<<"Introduceti numele cartii pe care doriti sa o adaugati in cosul de cumparaturi: ";
            cin.ignore();
           getline(cin,titlu);
            if(inventar.cautare_carte_titlu(titlu)==1){
                GenCarte c;
                c=inventar.return_carte(titlu);
                t.adauga_carte(c);
                if(c.get_nr_copii()==0)
                    inv.scoate_carte(c);
            }
            else
              cout<<"--->Cartea nu se afla in inventar!"<<endl;
            break;
            }
        case 3:
            {
              cout<<"Introduceti numele cartii pe care doriti sa o scoateti din cosul de cumparaturi: ";
            cin.ignore();
            getline(cin,titlu);
            if(inventar.cautare_carte_titlu(titlu)==1){
                GenCarte c;
                c=inventar.return_carte(titlu);
                t.scoate_carte(c);
                if(inv.cautare_carte_titlu(titlu)==0){
                    cout<<inv.cautare_carte_titlu(titlu);
                    inv.adauga_carte(c);
                }
            }
            else
              cout<<"--->Cartea nu se afla in inventar!"<<endl;
            break;
            }
        case 4:
            {
                t.afis_cos();
                break;
            }
        case 5:
            {
                t.factura(cont);
                cout<<"Doriti sa va folositi punctele pentru aceasta comanda?(Y/N)"<<endl;
                cin>>raspuns;
                if(raspuns=='Y'){
                    aplicare_reducere(t,cont);
                        if(t.get_suma()>300){
                        cout<<"De asemenea, comanda dumneavoastra depaseste 300 de lei, beneficiati de o reducere de 10% si transport gratuit!"<<endl;
                        reducere10(t);

                        }
                cout<<"Suma finala de plata este: "<<t.get_suma()<<endl;
                }
                else
                    cout<<"Suma finala de plata este: "<<t.get_suma()<<endl;
                cout<<"Doriti sa confirmati comanda?(Y/N)"<<endl;
                cin>>raspuns;
                if(raspuns=='Y'){
                    cout<<"Comanda dumneavoastra a fost confirmata!"<<endl;
                    cout<<"Va mai asteptam!"<<endl;
                    inventar=inv;
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
                inv.afisare();
                break;
            }

        case 7:
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
    if(raspuns=='r')
     {int rating;
             string recenzie,titlu;
             int ok=1;
    while(ok==1){
             cout<<"------------------------------------------------------"<<endl;
             cout<<"Introduceti titlul cartii pe care doriti sa o evaluati"<<endl;
             cout<<"------------------------------------------------------"<<endl;
             cin.ignore();
               getline(cin,titlu);
               try{
                if(inventar.cautare_carte_titlu(titlu)==1)
                {   GenCarte c;
                    c=inventar.return_carte(titlu);
                    cout<<"Oferiti cartii un rating de la 1 la 5 stele"<<endl;
                    cin>>rating;
                    cout<<"Oferiti o recenzie cartii (daca nu doriti sa scrieti o recenzie apasati space si apoi enter)"<<endl;
                     cin.ignore();
                    getline(cin,recenzie);
                    Review_carte r(cont,c,rating,recenzie);
                    cout<<"Detaliile review-ului:"<<endl;
                    ok=0;
                    cout<<"Contul care a acordat review-ul: ";
                    Cont_client* ptrCont = &r;//upcasting
                    ptrCont->afis_detaliile_contului();
                    cout<<"Cartea careia i se acorda review: ";
                    GenCarte* ptrCarte =&r;//upcasting
                    cout <<ptrCarte->get_titlu()<< endl;
                    r.afis();
                    meniu_cumparaturi(cont,inventar);
            }
            else
                 throw invalid_argument("Exceptie titlu invalid: Cartea nu exista in inventar");//aruncare de exceptie
               }
               catch(const exception &e){
                cout<<e.what()<<endl;
               }

    }
     }
     else
        cout<<"La revedere"<<endl;

}
void meniu_start(Inventar &inventar, VectorConturi &v_conturi)
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
             if(login_parola(cont))
                log_in=1;
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
     meniu_cumparaturi(c,inventar);
}

int main()
{
     Inventar inventar;
     VectorConturi v_conturi;
     ifstream f("carti.in");
     ifstream g("conturi.in");
     string line;
     int choice,log_in=0;

    while (getline(f, line)) {
        stringstream ss(line);
        string titlu,autor,categorie,limba;
        double pret;
        long long int cod;
        int nr_copii;

        getline(ss, titlu, ',');
        getline(ss, autor, ',');
        getline(ss, categorie, ',');
        getline(ss, limba, ',');
        ss >> pret;
        ss>>cod;
        ss >>nr_copii;
        GenCarte c(titlu,autor,limba,pret,cod,nr_copii,categorie);
        inventar.adauga_carte(c);
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
    meniu_start(inventar,v_conturi);
    cout<<endl<<"In inventar se afla urmatoarele titluri:"<<endl;
    inventar.afisare();
    cout<<endl<<"Statistica inventarului:"<<endl;
    statistica_limba_carti(inventar);
    Tranzactie::set_taxa_transport(15.5);
    f.close();
    g.close();
    return 0;
}


