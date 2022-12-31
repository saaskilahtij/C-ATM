
// Tarvittavat standardikirjastot
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Funktioiden prototyypit erillisenä header.h tiedostona
#include "headers.h"

#define MAX 256 // Maksimi jota käytetään merkkijonojen pituuksina

// Funktio lueMerkkijono() haettu Oulun Yliopiston Ohjelmointi 1 kurssimateriaalista
// Funktio lukee turvallisesti merkkijonon
// Alkuperäiseen funktioon verrattuna poistin tästä error printin ja hoidan sen kutsun yhteydessä
void lueMerkkijono(char merkkijono[], int pituus)
{      
   fgets( merkkijono, pituus, stdin );

   if( merkkijono[ strlen(merkkijono)-1 ] == '\n')  
        merkkijono[ strlen(merkkijono)-1 ] = '\0';       // \n poistetaan merkkijonon lopusta ja korvataan NUL (\0) merkillä
   else
        lueRoskat();
}


// Funktio lueKokonaisluku() haettu Oulun Yliopiston Ohjelmointi 1 kurssimateriaalista
// Funktio lukee turvallisesti kokonaisluvun ja tyhjentää puskurin tarvittaessa
// Alkuperäiseen funktioon verrattuna poistin tästä error printin ja hoidan sen kutsun yhteydessä
int lueKokonaisluku(void)
{
   int luku = 0;
   char mki =' ';
   int status = 0;

   while (((status = scanf("%d%c", &luku, &mki)) == 0)  || (2 == status && mki != '\n')){
        lueRoskat();
        break;
   }

   return luku;
}


// Funktio lueReaaliluku() haettu Oulun Yliopiston Ohjelmointi 1 kurssimateriaalista
// Funktio lukee turvallisesti reaaliluvun ja tyhjentää puskurin tarvittaessa
// Alkuperäiseen funktioon verrattuna poistin myös tästä error printin ja hoidan sen kutsun yhteydessä
double lueReaaliluku(void){

   double luku = 0.0;
   char mki = ' ';
   int status = 0;

   while (((status = scanf("%lf%c", &luku, &mki)) == 0)  || (2 == status && mki != '\n')){
      lueRoskat();
      break;
   }

   return luku;
}


// Funktio lueRoskat() haettu Oulun Yliopiston Ohjelmointi 1 kurssimateriaalista
// Funktio tyhjentää puskurin
void lueRoskat(void)
{
    while( fgetc(stdin) != '\n');
}

// Funktio hakee pin-koodin tiedoston ensimmäiseltä riviltä ja palauttaa sen muokkaamalla pinin merkkijonoa osoittimen avulla
// Parametreinä tiedosto josta pin haetaan ja taulukko johon se tallennetaan 
// Palauttaa joko (1) jos tiedoston luku onnistuu ja (-1) jos lukeminen ei jostain syystä onnistu 
// Vähän hauska muuttujan nimi validPin, mutta pin haetaan vain kerran oikean pin-koodin merkkijonoon
// ja sitä verrataan sen jälkeen käyttäjän syöttämään merkkijonoon
int haePin(char *tiedosto, char *validPin)
{
    int i = 0;
    char pinLuku;
    FILE *fileRead;


    if((fileRead = fopen(tiedosto, "r")) == NULL){
        printf("\n\n---------------------------");
        printf("\nPin-koodin luku epäonnistui");      // Jos tiedoston lukeminen epäonnistuu palautetaan error (-1)
        printf("\n---------------------------"); 
        fclose(fileRead);
        return -1;
    }

    while ((pinLuku = fgetc(fileRead)) != '\n'){         // Koska pin on tiedoston ensimmäisellä rivillä, luetaan pin ensimmäiseen rivinvaihtoon asti
        validPin[i] = pinLuku;
        i++;
    }

    fclose(fileRead);

    return 1;
}

// Funktio joka lukee ja hakee saldon tiedostosta ja palauttaa sen doublena
// Parametrina tiedosto josta saldo haetaan
// Palauttaa saldon doublena jos saldon haku onnistuu, virhetilanteessa palauttaa (-1)
double haeSaldo(char *tiedosto)
{

    FILE* FileRead;
    int luettuLuku;
    int riviNro = 1;        // Muuttuja rivinumerolle
    char luettuMerkki;     // Merkki joka haetaan tiedostosta
    double saldo;


    FileRead = fopen(tiedosto, "r");
        
    
    if (FileRead != NULL){
        do
        {
            if (luettuMerkki == '\n')   // Haetaan oikea rivi tiedostosta. Kun kohdataan (\n) inkrementoidaan riviNro
                riviNro++;
            if (riviNro == 2){             // Luetaan saldo toiselta riviltä, kun riviNro = 2
                fscanf(FileRead, "%lf", &saldo);
            }
        } while ((luettuMerkki = fgetc(FileRead)) != EOF);
     
    }else{
        printf("\n\n-----------------------");
        printf("\nVirhe luettaessa saldoa");    // Jos tiedoston avaus epäonnistuu
        printf("\n-----------------------");
        fclose(FileRead);
        return -1;
    }
   
    fclose(FileRead);

    return saldo;
}


// Funktio muokkaa saldoa tiedostossa ja palauttaa (1) jos muokkaus onnistuu ja (0) jos muokkaus epäonnistuu
// Parametreinä tiedosto jossa saldoa muokataan, pin ja uusi saldo joka kirjoitetaan vanhan sisälle
int muokkaaSaldoa(char *tiedosto, char *pin, double uusiSaldo)
{
    FILE *fileHandle;

    if((fileHandle = fopen(tiedosto, "r+")) != NULL){   // Jos tietokantaan saadaan yhteys, se muokataan
        fprintf(fileHandle, "%s\n%.2lf", pin, uusiSaldo);  // Tiedosto kirjoitetaan kokonaan uudestaan ja saldo päivitetään uusiSaldo argumenttiin
    }else{
        printf("\n\n-----------------------");      // Jos tietokantaan ei saada yhteyttä, palautetaan 0 ja tulostetaan virheviesti
        printf("\nVirhe muokatessa saldoa");
        printf("\n-----------------------");
        fclose(fileHandle);
        return 0;
    }

    fclose(fileHandle);

    return 1;
}


// Algoritmi joka jakaa 20€ sekä 50€ seteleitä mahdollisimman suurina seteleinä
// Parametreinä maarat taulukko sekä nostosumma
// Muokkaa maarat taulukkoa, josta löytyy setelien määrät
void jakaaSetelit(int * maarat, int summa)
{
    enum Setelit {kaksikymppinen, viisikymppinen};  // Selventääkseen koodia, koska setelit ovat taulukossa

    // Algoritmi joka iteroi summaa vähentämällä siitä setelin summan verran ja lisäämällä sen määrätyn setelin määrään
    // Algoritmi priorisoi viisikymppisiä, eli valitsee aina suurimmat mahdolliset setelit
    while (summa > 0){
        if (summa % 50 == 0){           
            maarat[viisikymppinen]++;
            summa -= 50; 
        }else if (summa % 20 == 0){
            maarat[kaksikymppinen]++;
            summa -= 20;
        }else if (summa >= 50){
            summa -= 50;
            maarat[viisikymppinen]++;
        }else if (summa < 50){
            summa -= 20;
            maarat[kaksikymppinen]++;
        }
    }
}


// Nostovalikon funktio jolla voi nostaa 20 ja 50 jaollisia summia ja suurin nostosumma on 1000
// Muokkaa sisälle syötettyä saldon arvoa ja palauttaa saldon uuden arvon doublena
// Parametreinä tiedosto jonka tietoja käsitellään ja pin saldon muokkausta varten
double nostovalikko(char *tiedosto, char *pin)
{
    int yhteysTietokantaan = 0;     // Muuttuja joka auttaa yhteyden tarkistamisessa
    double saldo;
    int nostoSumma;
    enum Setelit {kaksikymppinen, viisikymppinen};  // Enum, jotta listasta tulisi helppolukuisempi
    int maarat[2] = {0,0};      // Setelien määrät listana, jotta setelien käsittely on helpompaa
                                // Koska jakaaSetelit() funktio ei pysty palauttamaan kahtaa arvoa (molempien setelien määriä)
                                // on helpompaa muokata taulukkoa. 
                                // maarat[0] = 20€ setelien määrät || maarat[1] = 50€ setelien määrät, jota pyrin selventämään enum Setelit avulla
    
    
    if ((saldo = haeSaldo(tiedosto)) == -1)     // Kun saldon hakeminen epäonnistuu, tarkoittaa se ettei tietokantaan saada yhteyttä
        return saldo;                           // Tässä tapauksessa asiakas palautetaan valintavalikkoon
    
    
    while (1)
    {        
        printf("\n\nMahdolliset nostettavat summat ovat:");
        printf("\n|| 20€ || 40€ || Omavalintainen summa (max 1000€) ||");
        printf("\nValitse nostettava rahamäärä syöttamällä nostettava summa >");                      
        nostoSumma = lueKokonaisluku();        


            if ((saldo = haeSaldo(tiedosto)) == -1){     // Kun saldon hakeminen epäonnistuu, tarkoittaa se ettei tietokantaan saada yhteyttä
                    virheValikko();
                    return saldo;                              // Tässä tapauksessa asiakas palautetaan valintavalikkoon returnin kautta
            }else if (nostoSumma < 50 && (nostoSumma % 20) == 0 && nostoSumma > 0){   // Hardkoodatut poikkeustapaukset alle 50€ summille joita on vain (2) kappaletta
                                                            
                if (nostoSumma == 20){                           
                    saldo -= 20;
                    printf("\n\nOlkaa hyvä!");
                    printf("\nSetelit tulostuvat...");
                    printf("\n|| 1 kpl. 20€ || 0 kpl. 50€ ||");
                    printf("\nYhteensä: 20€");
                    printf("\nTilin saldo: %.2lf€", saldo);
                    muokkaaSaldoa(tiedosto, pin, saldo);
                    break;

                }else if (nostoSumma == 40){
                    saldo -= 40;
                    printf("\n\nOlkaa hyvä!");
                    printf("\nSetelit tulostuvat...");
                    printf("\n|| 2 kpl. 20€ || 0 kpl. 50€ ||");
                    printf("\nYhteensä: 40€");
                    printf("\nTilin saldo: %.2lf€", saldo);
                    muokkaaSaldoa(tiedosto, pin, saldo);
                    break;

                } 

        }else if (nostoSumma <= 1000 && nostoSumma >= 50 &&                     // Jos nostosumma on pienempi kuin 1000€ ja se on jaollinen joko 20 tai 50 ja nostosumma <= saldo 
            (nostoSumma % 50 == 0 || nostoSumma % 20 == 0 ||                    // Lisäehtona ((nostosumma-50) % 20) joka auttaa esim. 170€ ja 130€ tapauksissa
            (nostoSumma - 50) % 20 == 0) && nostoSumma <= saldo){   
            
            jakaaSetelit(maarat, nostoSumma);       // Kutsutaan jakaaSetelit() joka laskee setelien määrät ja muokkaa (maarat[]) taulukkoa osoittimien avulla
            saldo -= nostoSumma;
            printf("\n\nOlkaa hyvä!");
            printf("\nSetelit tulostuvat...");
            printf("\n|| %d kpl. 20€ || %d kpl. 50€ ||", maarat[kaksikymppinen], maarat[viisikymppinen]); 
            printf("\nYhteensä: %d€", nostoSumma);     
            printf("\nTilin saldo: %.2lf€", saldo);
            muokkaaSaldoa(tiedosto, pin, saldo);
            break;

        }else if(nostoSumma > saldo){                              // Varmistetaan että tilillä on saldoa ja printataan tarvittaessa virheviesti
            printf("\nTilillä ei tarpeeksi katetta");               
            printf("\nTilin saldo: %.2lf€", saldo);
        }else{
            printf("\n\n------------------------");         // else haara jos nostosumma on virheellinen 
            printf("\nVirheellinen nostosumma!");
            printf("\n------------------------");
        }
    }


    maarat[kaksikymppinen] = 0;              // Nollataan vielä setelien määrät jos asiakas nostaa vielä rahaa ohjelman aikana
    maarat[viisikymppinen] = 0; 

    return saldo;
}

// Saldovalikko joka hakee saldon tiedostosta ja tulostaa sen
// Jos tiedoston luku ei onnistu funktion suoritus keskeytyy
void saldovalikko(char *tiedosto)
{
    double saldo;

    if ((saldo = haeSaldo(tiedosto)) == -1){        // Suoritus keskeytyy jos tietokantaan ei saada yhteyttä
        virheValikko();
        return;
    }
    else
        printf("\n\n|| Tilisi saldo on: %.2lf€ ||", saldo);
}



// Oma funktio  tapahtumavalikolle, parametrinä tiedosto
// Tällä hetkellä vain pseudotapahtumia
void tapahtumavalikko(char *tiedosto)
{
    if (haeSaldo(tiedosto) == -1){          // Jos tietokantaan ei saada yhteyttä jossa tapahtumat näennäisesti ovat, funktion toiminta päättyy
        virheValikko();
        return;
    }else{
        printf("\n30.12 - S-Market - 13,45€ \n28.12 - K-Market - 7,60€ \n28.12 - Shell Oy - 19.99€");
        printf("\n27.12 - Gasthaus Ranua - 18.00€ \n27.12 - NotAPyramidScheme ltd. - 2450.50€\n");
    }
}




// Talletusvalikko jossa tilille voi tallettaa rahaa koskematta itse tiedostoon; ohjelmoitu enimmäkseen testaajan käyttöön
// Parametreinä tiedosto 
void talletusValikko(char *tiedosto, char *pin)
{
    double saldo;
    int talletettava = 0;
    int talletustenLkm = 0; // TalletustenLkm estää copy-pastella usean rivin summan laittamisen esim 100\n100\n100\n nostaa ainoastaan 100, eikä 300

    

    while (1){
        printf("\n\nValitse summa jonka haluat tallettaa >");
        
        if((talletettava = lueReaaliluku()) && talletettava > 0)    
            talletustenLkm++;                   // Haara tarkistaa ettei talletusta voi tehdä copy-paste rivinvaihdon kanssa. esim. 100\n100\n100 tallettaisi 300

        if ((saldo = haeSaldo(tiedosto)) == -1){     // Kun saldon hakeminen epäonnistuu, tarkoittaa se ettei tietokantaan saada yhteyttä
            virheValikko();
            return; 
        }else if (talletustenLkm == 1 && talletettava > 0){
            saldo += talletettava;
            printf("\nTilille talletettu %d€", talletettava);
            printf("\nTilin saldo: %.2lf€", saldo);
            muokkaaSaldoa(tiedosto, pin, saldo);
            break;  
        }else{
            printf("\n\n------------------");
            printf("\nVirheellinen summa");
            printf("\n------------------");
        }
    }
}


// Välivalikko joka palauttaa käyttäjävalinnan kokonaislukuna
// Jos käyttäjä haluaa jatkaa palauttaa funktio 1 ja jos käyttäjä haluaa poistua ohjelmasta palauttaa se 2
int valiValikko(void)
{
    int valinta = 0;

    while (1)
    {
        printf("\n\nHaluatko: \n(1). Palata valintavalikkoon\n(2). Lopettaa ohjelman\n>");
        valinta = lueKokonaisluku();
        switch (valinta)
        {
        case 1: 
            return 1;       
        case 2:
            return 2;
       default:
            printf("\n\n--------------------");
            printf("\nVirheellinen valinta");
            printf("\n--------------------");
        }
    }

    return 1; // Return varalta, jos jokin menee jostain syystä pieleen. Käyttäjälle ei tule ainakaan kovaa erroria ettei int funktio palauta mitään
}

// Virhevalikko jota kutsutaan jos tietokantaan ei saada yhteyttä
// Sisältää kehotuksen olemaan yhteydessä asiakaspalveluun
void virheValikko()
{
    printf("\n\nTietokantaan ei saatu yhteyttä");
    printf("\nOle hyvä ja ota yhteyttä asiakaspalveluun");
    printf("\n+358123456789");
    printf("\npankkiautomaatti@pankki.com");
}