#include <iostream>
#include <cstring>

using namespace std;

class String{
char *c;
public:

    String(){
    c=NULL;
}
    String(const char sc[]){
    c= new char[strlen(sc)+1];//alocare dinamica, avem un pointer c care va indica adresa de inceput a unui sir de carac
    strncpy(c,sc,strlen(sc));//facem un nou sir de caractere
    c[strlen(sc)] = '\0';
    }
    String(const String &str){//copy constructor
        if(str.c==NULL)
            c=NULL;
        else{
        c= new char[strlen(str.c)+1];
        strcpy(c,str.c);
        }
    }
    void operator=(const String &str){//supraincarcarea =
        if(c!=NULL)
            delete[] c;
        c= new char[strlen(str.c)+1];
        strcpy(c,str.c);
    }
    ~String(){
        if(c!=NULL)
          delete[] c;
    }
friend ostream & operator << (ostream &out,const String &s);
friend istream & operator >>(istream &in, String &s);
friend bool operator==(const String &s,const String &t);
};
ostream & operator << (ostream &out, const String &s) {
    out<<s.c;
    return out;
}
istream& operator>>(istream& in, String& s) {
    char sir[100];
    if (in.getline(sir, 100)) {
        s = String(sir);
    }
    return in;
}

bool operator==(const String &s,const String &t){
    if (strcmp(s.c,t.c)==0)
        return true;
    else
        return false;
}
class Carte{
    String titlu,autor,categorie,limba;
    double pret;
    unsigned long long int cod;
    int nr_copii;

public:

    Carte(){//constructor fara parametru
        titlu="Fara titlu";
        autor="Fara autor";
        categorie="Nu exista categorie";
        limba="Nu exista limba";
        pret=0.0;
        cod=0;
        nr_copii=0;
    }
    Carte (const Carte &c){//copy constructor
        titlu=c.titlu;
        autor=c.autor;
        categorie=c.categorie;
        limba=c.limba;
        pret=c.pret;
        cod=c.cod;
        nr_copii=c.nr_copii;
    }
    Carte(String titlu,String autor,String categorie,String limba,double pret,unsigned long long int cod,int nr_copii){//constructor cu parametru
        this->titlu=titlu;
        this->autor=autor;
        this->categorie=categorie;
        this->limba=limba;
        this->pret=pret;
        this->cod=cod;
        this->nr_copii=nr_copii;

    }

    void operator=(const Carte &c){//supraincarcarea =
    this->titlu = c.titlu;
    this->autor = c.autor;
    this->categorie = c.categorie;
    this->limba = c.limba;
    this->pret = c.pret;
    this->cod = c.cod;
    this->nr_copii=c.nr_copii;
}
    String get_titlu(){//getter titlu
        return titlu;
    }
    String get_limba(){//getter limba
        return limba;
    }
    int get_nr_copii(){//getter nr copii
        return nr_copii;
  }
  String get_autor(){//getter nume autor
      return autor;
  }
  double get_pret(){//getter pret
      return pret;
  }
   long long int get_cod(){//getter cod ISBN
       return cod;
   }
   void set_nr_copii(int nr){//setter pt nr copii
       nr_copii=nr;
   }
    friend ostream & operator << (ostream &out, Carte &c);
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
ostream & operator << (ostream &out, Carte &c)
{
    out<<"Titlul cartii este: "<<c.titlu<<endl<<"Autorul cartii este: "<<c.autor<<endl<<"Cartea face parte din categoria: "<<c.categorie<<endl<<"Cartea este in limba: "<<c.limba<<endl<<"Pretul este: "<<c.pret;
    return out;
}

class Inventar{
    Carte *vector_carti;//pointer la un array de carti
    int nr_titluri;//nr total de titluri din librarie
public:

    Inventar(){//constructor fara param
        vector_carti=NULL;
        nr_titluri=0;
    }
    Inventar(int nr_titluri){//constructor cu parametri
        this->nr_titluri=nr_titluri;
        vector_carti=new Carte[nr_titluri];
    }

    Inventar(const Inventar &inventar){//copy constructor
        nr_titluri= inventar.nr_titluri;
        vector_carti= new Carte[nr_titluri];
        for (int i=0;i<nr_titluri;i++)
            vector_carti[i]=inventar.vector_carti[i];
    }
    int get_nr_titluri(){
        return nr_titluri;
    }
    void set_nr_titluri(int nr){
        nr_titluri=nr;
    }
    void afisare(){
        cout<<"In inventar se afla urmatoarelele carti:"<<endl;
        if(vector_carti!=NULL)
            for(int i=0;i<nr_titluri;i++)
                cout<<vector_carti[i].get_titlu()<< " scrisa de "<<vector_carti[i].get_autor()<<endl;
    }
    ~Inventar(){
        delete [] vector_carti;
    }

friend void adaugare_inventar(Inventar &inv,Carte &c);
friend void scoatere_inventar(Inventar &i,Carte &c);
friend void scoate_nr_copii(Inventar &inventar,Carte &c, int nr_copii);
friend void statistica_limba_carti(Inventar &i);
};
void adaugare_inventar(Inventar &inv,Carte &c) {
    if (inv.vector_carti == NULL) {//alocam memorie pt prima data
        inv.nr_titluri=1;
        inv.vector_carti=new Carte[1];
        inv.vector_carti[0]=c;
    }

    else {
            int i;
            inv.nr_titluri++;//marim nr de titluri din inventar
            Carte *new_vector_carti;
            new_vector_carti=new Carte[inv.nr_titluri];//alocam spatiu pentru un nou vector in care vom include si cartea nou adaugata
            for (i = 0; i < inv.nr_titluri-1; i++) {
                new_vector_carti[i] = inv.vector_carti[i];
            }
            new_vector_carti[i] = c;
            delete[] inv.vector_carti;
            inv.vector_carti=new_vector_carti;
    }
}

void scoatere_inventar(Inventar &i, Carte &c) {
    int index=-1,j;
        for (j = 0;j<i.nr_titluri; j++)
             if(i.vector_carti[j].get_cod()==c.get_cod()){//cautam cartea dupa codul unic
              index=j;
              break;
              }
        if(index!=-1){
            for(j=index;j<i.nr_titluri-1;j++)
              i.vector_carti[j] = i.vector_carti[j+1];
          i.nr_titluri--;
          cout<<"Scoaterea din inventar a fost efectuata cu succes!"<<endl;
          }
    }
void scoate_nr_copii(Inventar &inventar,Carte &c, int nr_copii){
    if(c.get_nr_copii()>nr_copii)
     c.set_nr_copii(c.get_nr_copii()-nr_copii);
    else
        if(c.get_nr_copii()==nr_copii){
        scoatere_inventar(inventar,c);
        c.set_nr_copii(c.get_nr_copii()-nr_copii);
        }
        else
            cout << "Numarul cartilor scoase este prea mare, mai sunt disponible "<< c.get_nr_copii() << " exemplare din cartea "<<c.get_titlu()<<endl;
}

void statistica_limba_carti(Inventar &inv){
    int total_titluri=inv.nr_titluri;
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
    cout<<(c_franceza*100)/total_titluri<<" % carti in limba franceza si "<<endl<<(c_alte_limbi*100)/total_titluri<<"% alte limbi."<<endl;
}

class Cont_client{
    String nume,prenume,email,parola,adresa;
    double nr_puncte;
public:

    Cont_client(String nume,String prenume, String email,String parola, String adresa){//constructor cu parametru
        this->nume=nume;
        this->prenume=prenume;
        this->email=email;
        this->parola=parola;
        this->adresa=adresa;
        nr_puncte=0.0;

    }

    String get_prenume(){
        return prenume;
    }
     String get_nume(){
        return nume;
    }
     String get_adresa(){
        return adresa;
    }
     double get_nr_puncte(){
      return nr_puncte;
  }
  void set_nr_puncte( double nr_pct){
      nr_puncte=nr_pct;
  }
  void set_schimbare_nume(String new_nume){
      nume=new_nume;
  }
   void set_schimbare_adresa(String adr){
        adresa=adr;
    }

  void afis_detaliile_contului(){
      cout<<"Numele utilizatorlui este "<<nume<<" "<<prenume<<endl<<"Email-ul este: "<<email<<endl<<"Adresa este: "<<adresa<<endl;
  }
  friend double reducere_puncte(Cont_client &c);
};
double reducere_puncte(Cont_client &c){
    double reducere;
    reducere=c.nr_puncte/50;
    return reducere;
}

class Tranzactie{

    Carte *cos_cumparaturi;
    int nr_produse;
    double suma,taxa_transport;
    String metoda_plata,nume_client,prenume_client,adresa_livrare;
public:

    Tranzactie(Cont_client &cont,String plata){//constructor cu param
       suma=0;
       metoda_plata=plata;
       nume_client=cont.get_nume();
       prenume_client=cont.get_prenume();
       adresa_livrare=cont.get_adresa();
       cos_cumparaturi=NULL;
       nr_produse=0;
       taxa_transport=15.0;
    }
    void afis_cos(){//afisarea cartilor din cosul de cumparaturi
        cout<<"In cosul de cumparaturi se afla cartile:"<<endl;
         if(cos_cumparaturi!=NULL)
            for(int i=0;i<nr_produse;i++)
                cout<<cos_cumparaturi[i]<<endl;
            cout<<endl<<"Valoarea comenzii este de : "<<suma<<" lei"<<endl;
    }
  double get_suma(){
      return suma;
  }

    void factura(Cont_client &c){
        c.set_nr_puncte(c.get_nr_puncte()+suma);
        cout << "Detaliile comenzii:" << endl;
        cout << "Numele clientului: " << c.get_nume() << " " << c.get_prenume() << endl;
        cout << "Adresa de livrare a comenzii: " << c.get_adresa() << endl;
        cout<<"Metoda de plata: "<<metoda_plata<<endl;
        cout << "Cartile comandate: " << endl;
        for (int i = 0; i < nr_produse; i++) {
            cout << "-> " << cos_cumparaturi[i].get_titlu() << " scrisa de " << cos_cumparaturi[i].get_autor() << ", pret: " << cos_cumparaturi[i].get_pret() << endl;
        }
        cout<<"Suma inainte de adaugarea taxei de transport: "<<suma<<endl;
        suma=suma+taxa_transport;
          cout << "Suma totala dupa adaugarea taxei de livrare in valoare de 15 lei este: " << suma << endl;

        double r=reducere_puncte(c);
        cout<<"Aveti un numar de "<<c.get_nr_puncte()<<" puncte ceea ce inseamna o reducere de "<<r<<" lei (50 puncte=1 leu reducere)"<<endl;
    }
    ~Tranzactie(){
        delete [] cos_cumparaturi;
    }
friend void adaugare_cos_cumparaturi(Inventar &inventar,Tranzactie &t, Carte &c);
friend void scoate_cos_cumparaturi(Tranzactie &t,Carte &c);
friend void aplicare_reducere(Tranzactie &t,Cont_client &c);
friend void reducere10(Tranzactie &t);//reducere 10% si transport gratuit pt comenzile>300 lei
};

void adaugare_cos_cumparaturi(Inventar &inventar,Tranzactie &t, Carte &c) {
    int i;
    if(verificare_stoc(c)==1){
    if (t.nr_produse == 0) {
        t.nr_produse=1;
        t.cos_cumparaturi=new Carte[1];
        t.cos_cumparaturi[0] = c;
        t.suma=c.get_pret();
        cout<<"Cartea a fost adaugata in cosul de cumparaturi!"<<endl;
        scoate_nr_copii(inventar,c,1);
    }
    else {
        t.nr_produse++;
        Carte *new_cos_cumparaturi;
        new_cos_cumparaturi=new Carte[t.nr_produse];
        for (i = 0; i < t.nr_produse-1; i++) {
            new_cos_cumparaturi[i] = t.cos_cumparaturi[i];
        }
        new_cos_cumparaturi[i] = c;
        t.suma=t.suma+c.get_pret();
        cout<<"Cartea a fost adaugata in cosul de cumparaturi!"<<endl;
        scoate_nr_copii(inventar,c,1);
        delete[] t.cos_cumparaturi;
        t.cos_cumparaturi=new_cos_cumparaturi;
    }
    }
    else
        cout<<"Cartea nu mai este pe stoc."<<endl;
}

   void scoate_cos_cumparaturi(Tranzactie &t,Carte &c) {
        int index=-1,i;
        for (int i= 0;i<t.nr_produse;i++)
            if (t.cos_cumparaturi[i].get_cod() == c.get_cod()) {
                index = i;
                break;
            }

        if (index!=-1) {
            for (i=index; i<t.nr_produse-1;i++)
                t.cos_cumparaturi[i] = t.cos_cumparaturi[i+1];
            t.nr_produse--;
            t.suma=t.suma-c.get_pret();
            cout << "Cartea a fost scoasa din cosul de cumparaturi." << endl;
            adaugare_nr_copii(c,1);
        }

    }
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
        t.suma=t.suma-15;//transport gratuit la comenzi peste 300 de lei
        t.suma=t.suma-0.1*t.suma;
}

int main()
{
     Carte c1("Ferma Animalelor","George Orwell","Distopie","Romana",23.7,9789734675722,10);
     Carte c2("War and peace","Leo Tolstoy","Fictiune istorica","Engleza",53.9,9781853260629,20);
     Carte c3("The Bell Jar","Silvia Plath","Fictiune","Engleza",43.0,9780060837020,42);
     Carte c4("Rebecca","Daphne de Maurier","Fictiune","Franceza",55.0,9780349006574,32);
     Carte c5("Patul lui Procust","Camil Petrescu","Fictiune","Romana",34.0,9786068391113,14);
     Carte c6("Fundamentals of Art History","Anne D'Alleva","Istoria Artei","Engleza",83.0,9781913947019,22);
     Carte c7("L'amica geniale","Elena Ferrante","Fictiune","Italiana",62.7,9788866320326,35);
     Carte c8("Anna Karenina","Lev Tolstoi","Fictiune","Romana",79.0,9786067797480,17);
     Carte c9("Cien anos de soledad","Gabriel Garcia Marquez","Fictiune","Spaniola",88.3,9788420471839,30);
     Carte c10("La apa Vavilonului","Monica Lovinescu","Memorialistica","Romana",59.0,9789735078515,26);
     Inventar inventar;
     adaugare_inventar(inventar,c1);
     adaugare_inventar(inventar,c2);
     adaugare_inventar(inventar,c3);
     adaugare_inventar(inventar,c4);
     adaugare_inventar(inventar,c5);
     adaugare_inventar(inventar,c6);
     adaugare_inventar(inventar,c7);
     adaugare_inventar(inventar,c8);
     adaugare_inventar(inventar,c9);
     adaugare_inventar(inventar,c10);
     scoatere_inventar(inventar,c4);
     inventar.afisare();
     adaugare_inventar(inventar,c4);
     Cont_client cont("Pop","Cristian","pop.cristian101@gmail.com","1H0D82u3mf8#","Bd. Ghica Tei nr. 81,bloc A20, scara 1, etaj 5, apartament 50, Sector 2, Bucuresti");
     //prima tranzactie de pe cont
     cout<<endl;
     cout<<"Prima tranzactie a primului utilizator este: "<<endl;
     Tranzactie tr(cont,"card bancar");
     adaugare_cos_cumparaturi(inventar,tr,c1);
     adaugare_cos_cumparaturi(inventar,tr,c3);
     adaugare_cos_cumparaturi(inventar,tr,c9);
     tr.afis_cos();
     tr.factura(cont);
     cout<<endl;//prima tranzactie pt contul 2
     cout<<"Prima tranzactie a celui dea-al doilea utilizator este: "<<endl;
     Cont_client cont1("Ionescu","Elena","elena.ionescu11@gmail.com","aHB68$u0mf8@","Bulevardul Iuliu Maniu 74-76 Bl.5, Sc. D, Ap. 123, Sector 6, Bucuresti");
     Tranzactie t(cont1,"plata cash la livrare");
     adaugare_cos_cumparaturi(inventar,t,c10);
     adaugare_cos_cumparaturi(inventar,t,c8);
     adaugare_cos_cumparaturi(inventar,t,c2);
     t.afis_cos();
     t.factura(cont1);
     cout<<endl;
     //a doua tranzactie pt contul2
     cout<<"A doua tranzactie a celui de-al doilea utilizator este:"<<endl;
     Tranzactie t2(cont1,"card bancar");
     adaugare_cos_cumparaturi(inventar,t2,c8);
     adaugare_cos_cumparaturi(inventar,t2,c6);
     adaugare_cos_cumparaturi(inventar,t2,c5);
     adaugare_cos_cumparaturi(inventar,t2,c2);
     adaugare_cos_cumparaturi(inventar,t2,c1);
     adaugare_cos_cumparaturi(inventar,t2,c5);
     adaugare_cos_cumparaturi(inventar,t2,c3);
     t2.factura(cont1);
     //aplic functia de reducere pt ultima tranzactie care depaseste 300 de lei
    if(t2.get_suma()>300){
        cout<<"Suma comenzii depaseste 300 de lei si beneficiati de o reducere de 10% si transport gratuit."<<endl;
        reducere10(t2);
        cout<<"Totalul dupa aplicarea reducerii de 10% si transport gratuit este: "<<t2.get_suma()<<endl;
     }
     cout<<"Totalul dupa aplicarea reducerii este: ";
     aplicare_reducere(t2,cont1);
     cout<<t2.get_suma()<<" lei"<<endl;
     cout<<endl;
     statistica_limba_carti(inventar);//statistica pentru cartile scrise intr- anumita limba din inventar
     return 0;
}
