main.c
- deschid fisierele de citire/intrare
- extrag cerinta din argv
- daca este prima cerinta apelez functia de citire scrisa in functii1 .am o repetitiva care imi apeleaza functia de trecere un an de K ori. apelez functia de afisare, cea care afiseasa indicele traseelor cu uzura acceptata si functia de dezalocare, dupa care ies din functia cu un return
- pentru cea de a doua cerinta apelez citirea implementata in functii2. aloc spatiu necesar pentru vectorii de distante minime si de tati folositi la functia care calculeaza drumurile de distante minime. apelez, intr-o repetitiva, functia care selecteaza arcele care urmeaaz a fi pastrate, pana cand numarul acestora este egal cu numarul maxim de arce care trebuiesc pastrate sau am (practic) un fel de apm. afisez numarul de arce pastrate si apelez functiile de afisare si de dezalocare

functii1.h
- am o structura penttru lsita de vecini care contine campurile:
    id (al catelea traseu este citit), cod (codul orasului destinatie), nr (numarul de tronsoane), tronsoane (vectorul cu graduri de uzura), newt(un auxiliar pentru calcularea uzurii dupa un an, pentru a nu modifica uzura initiala de care tinem cont pentru restul calculelor), oras (numele orasului) si urm (pt adresa urmatorului element din lista)
- mai este o structura pentru lista efectiva de adiacenta care are n (nr de orase) celule:
    cod (codul orasului), oras (numele orasului), vecini (pointer sprem lista de noduri adiacente) si urm (pointer spre urmatorul oras)

functii1.c
- am definit o functie pentru maxim
- AllocCell1 : aloca o celula de oras la lista de adiacenta
    aloc spatiul epntru o celula de tip TLista1, initializez codul orasului cu valoarea primita ca parametru, aloc spatiu pentru vectorul de oras si copiez oarasul primit tot ca parametru, iar pentru pointerii de urmator si vecini ii initializez cu NULL si returnez celula creata
- AllocVecin1 : aloca o celula pentru lista de vecini
    similar cu functia anterioara numai ca in plus mai pun la campul id cu id-ul primit ca parametru si nr de tronsoane il initializez cu 0, initializez si pointerul de newt cu NULL
- InsertVecin1 : inserreaza o noua celula tip vecin in vector
    aloc o celula si initializez nr de tronsoane cu numarul primit ca parametru, aloc spatiu pentru vectorul de tronsoane si copiez informatia leagata de degradarea tronsoanelor in el, aloc spatiul pentru vectorul auxiliar si inserez celula la inceputul listei
- IndiceOras1 : returneaza codul orasului primit ca parametru
    parcurg lista de orase si compar numele orasului curent cu cel al oarsului parametru. daca acestea coincid returnez indicele, altfel returnez -1 (pentru a spune ca orasul nu face parte di lista)
- swap1 : face swap intre 2 valori
- Reverse1 : inverseaza elementele unui sir
    parcurg sirul pana la jumatatea lungimii si inversez elementul curent cu simetricul sau fata de jumatate folosind functia swap1
- Citire1 : citeste graful si creaza lista de adiacenta aferenta
    citesc R (nr de rute), L (gradul de uzura maxim), K (nr de ani) si aloc spatiul pentru 2 vectori de char in care citesc orasele
    cu un for de la 1 la nr de rute si citesc pentru fiecare cele doua orase si calculez indicele orasului. daca acesta nu exista deja in lsita aloc o celula noua pentru oras si o adaug la sfarsitul listei (pentru ambele orase se aplica). citesc nr de tronsoane si aloc un vector in care citesc gradele de degradare ale acestuia. inserez in vectorul de vecini al primului oras, al doilea oras dupa care inserez la cel de al doilea oras, primul oras cu tronsoanele inversate. id-ul la cea de  a doua insertie il pun negativ pentru a putea face diferenta intre traseele originale si cele inveraste (folosite numai pentru calcule). in final dezaloc vecotii folositi pentru citirea tronsoanelor si a oraselor.
- Afisare1 : afiseaza tronsoanele si gradul lor de degradare
    am un for de la 0 la nr de trasee (folosit pentru a putea afisa traseele in ordinea citirii). in acesa parcurg lista de orase si pentru fiecare oras parcurg lista de vecini. in cazul in care id-ul nodului curent coincide cu cu cel la care am ajuns, afisez orasele si gradurile tronsoanelor cu 2 zecimale.
- ModifPrim1 : modificarea primului grad de degradare din traseu
    daca valoarea curenta este diferita de 0 si de 100, dublez acea valoare si ies din functie. daca este 0 valoarea, calculez maximul dintre tronsoanele vecine: initializez maximul cu valoarea de pe a doua pozitie in traseul curent dupa care parcurg toata lista de adiacenta si calculez maximul in functie de gradele de degradeare finale la nodurile adiacente. in final atribui la primul grad de degradare maximul impartit la 2
- ModifUltim1 : modificarea ultimului grad de degradare din traseu
    similar cu functia anterioara numai ca initializarea maximului o fac cu elementul anterior din traseul curent si compararea pentru aflarea maximului se face cu gradele de inceput din traseele adiacente
- TreceUnAn1 : modificarea gradurilor de degradare dupa un an
    parcurg lista de adiacenta si pentru elementele din traseu care nu sunt la inceput/final calculez gradul de degradare nou (daca e diferit de 0 l inmultesc cu 2, altfel compar elementul de dinainte si cel de dupa si gradul nou devine maximul dintre cele doua impartit la 2). apoi modific si primul/ultimul grad folosind functiile descrise anterior.
    in final copiez in vectorul de tronsoane valorile din vectorul auxiliar, unde am valorile calculate dupa un an.
- VerifUzura1 : afisez indicele traseelor care indepinesc conditia de uzura (K)
    parcurg lista de adiacenta si pt traseul de la indicele curent calculez media aritmetica a degradarilor, iar daca aceasta este mai mica ca indicele maxim de degradare afisez indicele tronsonului
- Dezaloc1 : functia de dezalocare a listei de adiacenta
    parcurg lista si pentru fiecare vecin dezaloc cei doi vectori de tronsoane si cel de oras dupa care eliberez memoria vecinului curent. dupa ce termin cu vecinii unui oras, dezaloc si orasul respectiv

functii2.h
- structura unui vecin este similara cu cea din functii1.h, doar ca in loc de nr de tronsoane si vectorii de tronsoane, am doar un int in care se retine distanta dintre nodul sura si cel adiacent
- cea de-a doua structrura este exact ca in celalalt fisier

functii2.c
- AllocCell2 : aloca o celula din lista de adiacenta
    exact ca la AllocCell1
- AllocVecin2 : aloca o celula de vecin
    similar cu AllocVecin1, doar ca distanta este initializata cu 0
- InsertVecin2 : adauga un element in lista de vecini
    similar cu InserVecin1, doar ca distanta este initializata cu cea primita ca parametru
- IndiceOras2 : calculeaza indicele orasului dat ca parametru
    exact ca IndiceOras1
- Citire2 : citeste si construieste graful
    aloc spatiu pentru orasul sursa si il citesc. in rest este similar cu AllocCell1
- Dijkstra2 : algoritmul pentru aflarea drumurilor de cost minim de la un nod sursa
    aloc spatiul pentru vectorul de vizitat si il initializez cu 0. pentru vectorul de distante initilaizez cu o valoare foarte mare iar la cel de tati cu -1 (-1 inseamna ca nodul acela este sursa). fac distnata orasului de start egala cu 0. parcurg toate nodurile grafului si calculez distanta minima de la sursa la nodurile nevizitate si salvez si indicele acelui nod. marchez ca vizitat nodul urmator. parcurg lista de noduri pana ajung la nodul next caruia ii parcurg lista de vecini si actualizez distantele si vectorul de parinti. in final marchez distanta de la nodul de start cu o valoare mare pentru a nu afecta selectiad e arce si dezaloc vectorul de vizitat.
- SelectArce2 : selecteaza arcele care vor fi pastrate
    calculez valoarea mimima din vectroul de distante, salvez indicele nodului destinatie si marchez distanta de la acea pozitie cu o valoare mare pentru a nu influenta calculul urmator. parcurg lista pana ajung la nodul tata al minimului si apoi ii parcurg vecinii pana ajung la nodul minim unde fac codul orasului negativ ca sa stiu la afisare ca trebuie pastrat. fac si in oglinda aceasta marcare.
- Afisare2 : afisez traseele care trebuiesc pastrate
    similar cu Afisare1, doar ca conditia in cazul in care trebuie afisat este influentat atat de id cat si de codul care numai daca este negativ trebuie pastrat
- Dealoc2 : deazloca graful
    similar cu Dezaloc1