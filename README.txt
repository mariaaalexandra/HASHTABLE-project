DRUGA MARIA-ALEXANDRA
313 CB

~TEMA 1 SD~

In functia main initializez M, numarul de bucket-uri si apelez functia IniTH
care initializeaza tabela H cu numarul M de bucket-uri si cu functia specifica
codHash. Deschid fisierele de citire si scriere, verificand ulterior.
Aloc dinamic linia din fisier si citesc cu functia fgets fiecare string. Apoi
verific operatia ceruta prin functia strcmp si apelez functiile create. 

->Functia PUT
Adauga perechea key-value in hashtable. Daca key exista in hashtable, aceasta
nu va mai fi adaugata. In functia main verific prin find daca key exista, iar
in caz negativ inserez perechea. Functia put insereaza structura in bucket dupa
codul Hash calculat. In InsL verific pozitia in care trebuie sa adaug elementul.
Sunt 4 posibilitati: inserare in lista vida, inserare la inceput de lista,
inserare inaintea unui element si inserare la final de lista.

->Functia FIND
Cauta key in hashtable. In functia find parcurg lista dublu inlantuita si verific
daca elementul se afla in lista, prin functia f data ca parametru. Functia find
intoarce valoarea 1 daca elementul se gaseste in lista si 0, in caz contrar. In
main functia find este apelata cu functia comp_key care verifica daca doua
elemente din lista au valorile key egale. Daca functia find intoarce 0 se afiseaza
"False" in fisierul de out sau "True", in caz contradictoriu.

->Functia GET
Intoarce valoarea corespunzatoare lui key, daca key nu exista intoarce NULL.
In functia get calculez codul hash al elementului si parcurg lista. Daca
elementul este gasit returnez adresa elementului, altfel NULL. In final afiseaz
valoarea key a elementului in fisierul de output.

->Functia REMOVE 
Sterge perechea key-value, daca aceasta exista. In functia eliminare calculez
codul hash al elementului si parcurg lista. Exista 3 posibilitati: eliminare
element din lista cu un singur element, eliminare primul element si eliminare
element oarecare.

->Functia PRINT_BUCKET
Afiseaza valorile value din bucketul cu indicele index_bucket, pe o singura
linie; daca lista asociata bucketului este vida se va afisa "VIDA".
In functia print_bucket verifc numarul bucketului si daca lista este vida, caz
in care afisez mesajul "VIDA" in fisierul de output dat ca parametru. Daca lista
nu este vida parcurg lista si afisez informatia din celula cu functia af.

->Functia PRINT
Afiseaza toate valorile value din hashtable, daca bucket-ul este nevid se va
afisa indicele si toate elementele acestuia, value.
In functia print parcurg fiecare bucket, iar daca este nevid, afisez indicele
corespunzator fiecarui bucket si apelez functia print_bucket pentru bucket-ul
curent.

La sfarsitul functiei main apelez dezalocarea tabelei Hash si inchid fisierele de
citire si scriere.

DOCUMENTATIE CODURI DE EROARE:
---EXIT(1) = eroare de alocare
---EXIT(2) = eroare deschidere fisier

In fisierul list.c am impementat algoritmii pentru inserarea in lista si distru-
gere lista, iar in fisierul list.h am declarat structura listei dublu inlantuite
circulare, structura paginei web si functiile InsL, afiEL, DistrL. In fisierul
table.c am impelementat algoritmii de initializare tabela si distrugere, iar in
fisierul table.h am declarat structura tabelei Hash si functiile IniTH, DistrTH,
functiile de comparare, afisare si cod Hash. 

