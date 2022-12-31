

// atm.c Copyright (c) Johan Sääskilahti. All rights reserved.
// Pankkiautomaatti joka on tehty osana Oulun Yliopiston Ohjelmointi 1 kurssin kotitehtävänä
// Pankkiautomaatista löytyy valinnat rahan nostamiseen, sen tallettamiseen, saldon tarkasteluun sekä tilin historian tarkasteluun
// Tilin tiedot on tallennettu tiedostoon 12345.acc, jossa 12345 viittaa tilinumeroon
// Tiedostosta löytyy tilin pin koodi (1122) ensimmäiseltä riviltä ja saldo toiselta riviltä.
// Ääkkösiä käytän printeissä siksi, koska käytän 7-bittisen ASCII:iin sijasta ylivoimaista 8-bittistä UTF-8:saa


// Tarvittavat standardikirjastot
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Oma tekemä kirjasto josta löytyy tarvittavat funktiot
#include "funktiot.c"

// Vakio merkkijonojen pituuksille
#define MAX 256


typedef struct{         // Käyttäjätietue josta löytyy käyttäjän tilinumero, pin-koodi sekä saldo

    char tiliNro[MAX];
    char pinKoodi[MAX];
    int saldo;

}Kayttaja;


/////////////////////////////////////
//////Pääohjelma ///////////////////
///////////////////////////////////

// main() funktio on melko sekava ja abstraktiotasoa nostamalla siitä olisi voinut tehdä selvemmän
// esimerkiksi tilinumeron ja pin-koodin kysymiselle oma valikko (funktio)
// sekä valintavalikolle oma funktio

int main(void)
{

    Kayttaja kayttaja;              // Sisältää tilinumeron, pin-koodin sekä saldon
    char tilinTietokanta[MAX];      // Muuttuja käyttäjän tilitiedostolle joka selventää koodia. Tähän talletetaan tiedoston nimi, josta käyttäjän tiedot löytyy.
    char validPin[MAX] = {' '};



    printf("\nPankkiautomaatti.c");
    printf("\n\n\n-----------");
    printf("\nTervetuloa!");
    printf("\n-----------");

    // Silmukka joka pyytää tilinumeroa
    while (1)
    {
        FILE *isAvailable;
        
        printf("\n\nSyotä viisinumeroinen tilinumero >");       // Käyttäjän tilinumeroa pyydetään. Oikea tilinumero on 12345, joka avaa tiedoston
        lueMerkkijono(kayttaja.tiliNro, MAX);                // josta löytyy asiakkaan tiedot
                                                          // Tällä hetkellä tilinumeron oikeellisuuden varmistus on kovakoodattu. 
        if (strcmp(kayttaja.tiliNro, "12345") == 0 && (isAvailable = fopen("12345.acc", "r")) != NULL){        // Varmistetaan että tilinumero on oikea
            strcat(kayttaja.tiliNro, ".acc");           // Lisää tiedoston loppupäätteen tilinumeron perään
            fclose(isAvailable);
            break;
        }else if (isAvailable == NULL)
        {
            printf("\n\n----------------------------");
            printf("\nTilinumeron luku epäonnistui");       // Jos tiedostoon ei saada yhteyttä tilinumeroa syöttäessä
            printf("\n----------------------------");
            virheValikko();
        }else{                              
            printf("\n\n----------------------------------------\n");
            printf("Virheellinen tilinumero, yritä uudestaan");
            printf("\n----------------------------------------");
        }
    }
    strcpy(tilinTietokanta, kayttaja.tiliNro);      // Tästä lähtien tiedostoa käsitellään nimellä tilinTietokanta, joka on osuvampi kuin kayttaja.tiliNro


    // Silmukka joka pyytää pin-koodia ja päästää eteenpäin oikealla pin-koodilla
    while (1)
    {
        // Ensin katsotaan saadaanko tietokantaan yhteyttä
        
    
        // Jos tietokantaan saadaan yhteys, ohjelma pyytää syöttämään pin-koodia
        printf("\n\nSyötä pinkoodi >");
        lueMerkkijono(kayttaja.pinKoodi, MAX);      // Kysyy pin-koodia joka on 1122
        
        if(haePin(tilinTietokanta, validPin) == -1){              // Haetaan tilin tietokannasta oikea pin-koodi vertailua varten        
            virheValikko();                                 // Jos tietokantaan ei saada yhteyttä, ohjelma poistuu virhevalikon kautta
        }  
        
        if(strcmp(validPin, kayttaja.pinKoodi) == 0){                                // ja varmistetaan tässä että pin-koodi on oikean pituinen
            break;
        }else{                                              // Jos lukeminen onnistuu mutta pin on väärin, tulostetaan virhe
            printf("\n\n---------------------------------\n");
            printf("Virheellinen pin, yritä uudestaan");
            printf("\n---------------------------------");

        }
    }


    // Siirrytään valintavalikkoon
    while (1)
    {
        int valinta = 0;    // Loopissa käytetään ainoastaan yhtä valintamuuttujaa jokaiselle valinnalle
                                                        
                                                        /* Ohjelmoin vielä vaihtoehdon rahan talletukselle, että tiedostoa ei tarvitse mennä muokkaamaan jos rahat loppuu
                                                            Nyt sen voi tehdä suoraan ohjelman avulla */
        printf("\n\nValitse yksi neljästä vaihtoehdosta syöttämällä sen numero");
        printf("\nVaihtoehdot ovat: \n(1). : Otto \n(2). : Saldo \n(3). : Tapahtumat \n(4). : Rahan talletus \n(5) : Toimintojen lopetus\n>");   

        valinta = lueKokonaisluku();        

        switch (valinta)
        {
        case 1:      // Ensimmäinen vaihtoehto kutsuu nostovalikkoa
            kayttaja.saldo = nostovalikko(tilinTietokanta, kayttaja.pinKoodi);       // Kutsutaan nostovalikkoa
            valinta = valiValikko();                   // Välivalikko on hyödyllinen kun halutaan pysyä ohjelmassa. Se palauttaa valinnan poistutaanko                                    
            switch (valinta)                           // Se palauttaa valinnan poistutaanko vai pysytäänkö ohjelmassa
            {
            case 1:
                continue;
            case 2:
                printf("\n\nKiitos käynnistä, tervetuloa uudelleen!");
                return 0;}

        case 2:
            saldovalikko(tilinTietokanta);      // Kutsutaan valikkoa jossa haetaan nykyinen saldo tietokannasta ja se tulostetaan
            valinta = valiValikko();
            switch (valinta)
            {
            case 1:
                continue;
            case 2:
                printf("\n\nKiitos käynnistä, tervetuloa uudelleen!");
                return 0;}

        case 3:
            tapahtumavalikko(tilinTietokanta);                             // Tapahtumavalikossa on pseudotapahtumia, jotka tulostetaan.
            valinta = valiValikko(); 
            switch (valinta)
            {
            case 1:
                continue;
            case 2:
                printf("\n\nKiitos käynnistä, tervetuloa uudelleen!");
                return 0;}

        case 4:
            talletusValikko(tilinTietokanta, kayttaja.pinKoodi);  // Talletusvalikko jossa voi tallettaa tilille rahaa
            valinta = valiValikko();                                              // Kätevä ettei tarvitse mennä manuaalisesti sörkkimään tiedostoa
            switch (valinta)
            {
            case 1:
                continue;
            case 2:
                break;}

        case 5:
            printf("\n\nKiitos käynnistä, tervetuloa uudelleen!");
            return 0;
        
        default:                                    // Tässä napataan virheellinen valinta ja tulostetaan käyttäjäystävällinen virheviesti
            printf("\n\n--------------------");
            printf("\nVirheellinen valinta");
            printf("\n--------------------");
        }

        valinta = 0;        // Nollataan valinta jos käyttäjä palaa valikkoon vielä
    }
    
    printf("\n\nKiitos käynnistä, tervetuloa uudelleen!");

    return 0;
}