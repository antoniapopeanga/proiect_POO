# Proiect_POO
### Tema proiectului <br />
Librarie online<br />
### Clasele implementate:<br />
- Carte: definirea datelor despre obiectul carte si metode de verificare a stocului,adaugarea numarului de copii pentru o carte,supraincarcarea << <br />
- GenCarte: mosteneste clasa Carte si adauga in plus genul literar<br />
- Gestiune_Vector_Carti: o clasa interfata cu doua metode pur virtuale<br />
- Inventar: mosteneste clasa Gestiune_Vector_Carti si Carte, contine un array de obiecte GenCarte si implementeaza metodele de scoatere/adaugare carti din clasa Gestiune_Vector_Carti, contine functii de cautare a unei carti in inventar, de scoatere a unui numar de copii, o functie care face statistica a procentelor de carti scrise intr-o anumita limba si supraincarcarea operatorului = <br />
- Cont: clasa abstracta, are ca date membru parola, emailul si adresa cu modificatorul protected si functii pur virtuale<br />
- Cont_client: mosteneste cu protected clasa Cont si retine numele si prenumele unui client, are o functie care calculeaza reducerea comenzii in functie de numarul de puncte de pe cont, o functie in care sunt validate emailul si parola introduse de utilizator si una in care se face autentificarea <br />
- ExceptieCustom: in care se extinde std::exception<br />
- VectoriConturi: mosteneste clasa Cont_client si contine metode de adaugare conturi, afisarea detaliilor unui cont si cautarea contului in functie de email <br />
- Tranzactie: mosteneste Gestiune_Vectori_Carti si contine un array de carti ce reprezinta cosul de cumparaturi, o functie de afisare a continutului cosului de cumparaturi, de adaugare/scoatere a unei carti din cos, o functie care afiseaza pe ecran detaliile comenzii, o functie care calculeaza reducerea de 10% pentru comenzile ce depasesc 300 de lei si o functie ce aplica reducerea calculata in functie de numarul de puncte, totodata, contine si o variabila statica ce reprezinta taxa de transport <br />
- Review_carte: mosteneste clasele Cont_client si GenCarte si are rolul de a gestiona review-ul dat de un client unei carti <br />
### Functionalitati<br />
- meniu interactiv <br />
- meniul are optinea de conectare la un cont existent sau crearea unui cont nou <br />
- meniul are optiunea de a da o comanda de carti sau a lasa review unei carti <br />
- citirea obiectelor de tip GenCarte/Cont_client dintr-un fisier si adaugarea lor intr-un vector <br />
- crearea de obiecte de tip GenCarte si adaugarea/scoaterea lor dintr-un inventar/cos de cumparaturi<br />
- afișarea detaliilor comenzii pe ecran<br />
- calcularea reducerii in functie de numarul de puncte de pe contul clientului<br />
- calcularea reducerii de 10% pentru comenzile ce depasesc 300 de lei<br />
- posibiliatea de a modifica taxa de transport prin o functie statica <br />
