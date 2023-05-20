# Proiect_POO
### Tema proiectului <br />
Librarie online<br />
### Clasele implementate:<br />
-ProdusLibrarie: clasa de baza,definirea datelor generale pentru produsele unei librarii, metode de modificare a stocului, functie virtuala de afisare<br/>
- Carte: categoria cartii, statusul daca este impachetata pentru cadou <br />
- Revista: date despre data si numarul publicatiei revistei<br/>
- Audiobook: mentioneaza durata audiobook-ului si naratorul<br/>
- ImpachetareCarte: o clasa care primeste un obiect de tip Carte si ii schimba statusul in impachetata pentru cadou <br/>
- Inventar: clasa template, poate crea inventarul pentru orice tip de produse din librarie, contine functii de cautare a unei carti in inventar, o functie care face statistica a procentelor de carti scrise intr-o anumita limba si supraincarcarea operatorului = <br />
- Cont: clasa abstracta, are ca date membru parola, emailul si adresa cu modificatorul protected si functii pur virtuale<br />
- Cont_client: mosteneste cu protected clasa Cont si retine numele si prenumele unui client, are o functie care calculeaza reducerea comenzii in functie de numarul de puncte de pe cont, o functie in care sunt validate emailul si parola introduse de utilizator si una in care se face autentificarea <br />
- ExceptieCustom: in care se extinde std::exception<br />
- VectoriConturi: mosteneste clasa Cont_client si contine metode de adaugare conturi, afisarea detaliilor unui cont si cautarea contului in functie de email <br />
- Tranzactie: mosteneste Gestiune_Vectori_Carti si contine un array de carti ce reprezinta cosul de cumparaturi, o functie de afisare a continutului cosului de cumparaturi, de adaugare/scoatere a unei carti din cos, o functie care afiseaza pe ecran detaliile comenzii, o functie care calculeaza reducerea de 10% pentru comenzile ce depasesc 300 de lei si o functie ce aplica reducerea calculata in functie de numarul de puncte, totodata, contine si o variabila statica ce reprezinta taxa de transport <br />
- Review_carte: mosteneste clasele Cont_client si GenCarte si are rolul de a gestiona review-ul dat de un client unei carti <br />
### Functionalitati<br />
- meniu interactiv <br />
- meniul are optinea de conectare la un cont existent sau crearea unui cont nou <br />
- meniul are optiunea de a da o comanda de un produs sau a lasa review unei carti <br />
- citirea obiectelor de tip Carte/Revista/Audiobook/Cont_client dintr-un fisier si adaugarea lor intr-un vector <br />
- posibilitatea de a crea un inventar pentru fiecare tip de produs <br/>
- utilizarea functiilor template pentru a adauga/scoate produse dintr-un vector
- crearea de obiecte de tip Carte/Revista/Audiobook si adaugarea/scoaterea lor dintr-un inventar/cos de cumparaturi<br />
- adaugarea in cosul de cumparaturi obiecte din clasele derivate folosind shared_ptr <br/>
- afișarea detaliilor comenzii pe ecran si data exacta a plasarii acesteia<br />
- calcularea reducerii in functie de numarul de puncte de pe contul clientului<br />
- calcularea reducerii de 10% pentru comenzile ce depasesc 300 de lei<br />
- posibiliatea de a modifica taxa de transport prin o functie statica <br />
