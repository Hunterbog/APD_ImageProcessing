# APD_ImageProcessing
Grayscale+colorMask
Procesarea imaginilor 


Proiectul are ca scop implementarea unui algoritm eficient pentru procesarea și manipularea imaginilor în limbajul de programare C++, folosind bibliotecile STB_IMAGE.H și STB_IMAGE_WRITE.H pentru citirea și scrierea de imagini.
Cerințe tehnice:
Algoritm de conversie în grayscale: Implementarea unui algoritm eficient pentru conversia imaginilor color la grayscale. Acest algoritm trebuie să fie optimizat pentru a asigura performanțe ridicate și o acuratețe maximă a conversiei.
Manipulare și prelucrare a imaginilor: Dezvoltarea unor funcționalități pentru manipularea și prelucrarea imaginilor, cum ar fi redimensionarea, rotirea, aplicarea de filtre și efecte speciale.
Am folosit Microsoft Visual Studio Code 2022.
Limbaj de programare și biblioteci:
⦁	Limbaj de programare: C++
⦁	Biblioteci externe: STB_IMAGE.H și STB_IMAGE_WRITE.H pentru citirea și scrierea de imagini în formatele PNG, JPEG, BMP etc.
Detalii tehnice:
⦁	Implementarea algoritmului va fi structurată în clase și funcții pentru a asigura modularitate și reutilizabilitate.
⦁	Se va efectua testarea riguroasă a funcționalităților implementate pentru a asigura corectitudinea și robustețea acestora.

Analiză:

 **gray_avg (0.051 seconds):**
   Este un algoritm simplu care parcurge fiecare pixel și calculează valoarea grayscale, apoi o aplică pe toate cele trei canale.

 **gray_avg_parallel (0.021 seconds):**
   Aceasta este versiunea paralelizată folosind OpenMP (#pragma omp parallel for).
   OpenMP permite paralelizarea automată a buclei for, împărțind munca între multiple fire de execuție.
   Observăm o reducere semnificativă a timpului de execuție comparativ cu versiunea secvențială. Aceasta arată că utilizarea OpenMP pentru paralelizare a fost eficientă.
   Timpul este aproape jumătate față de cel al metodei secvențiale, ceea ce indică faptul că distribuirea sarcinilor a fost relativ eficientă.

 **gray_avg_parallel_threads (0.027 seconds):**
    Aceasta este versiunea care utilizează threads manual, prin crearea de threads și împărțirea sarcinilor între ele(10 fire de executie in cazul de fata).
    Diferența mică de timp (0.027 seconds vs. 0.021 seconds) indică faptul că ambele metode de paralelizare sunt eficiente, dar OpenMP este puțin mai optimizat pentru acest tip de sarcină.

 
 
