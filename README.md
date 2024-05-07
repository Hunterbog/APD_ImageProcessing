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

Am aplicat două metode diferite pentru conversia imaginilor la grayscale. Prima metodă a constat în calcularea mediei componentelor de culoare pentru fiecare pixel, iar rezultatul a fost o imagine în tonuri de gri în care culorile au fost echilibrate uniform. Cu toate acestea, în a doua metodă, am folosit o formulă care a ponderat intensitatea fiecărei culori în funcție de importanța lor în percepția umană a luminii. Rezultatul a fost o imagine grayscale în care contrastul și detaliile au fost mai bine evidențiate în comparație cu metoda simplă a mediei componentelor de culoare. 
Am folosit urmatoare imagine:

Ca timp de executie am 0,6secunde pt fiecare modalitate de a modifica pozele
 
 
