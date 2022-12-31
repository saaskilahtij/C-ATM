#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 256

char *strremove(char *str, const char *sub);
void lueMerkkijono(char merkkijono[], int pituus);
void lueRoskat(void);

int main(void)
{

   char suomenKieliset[MAX][MAX];
   char englanninKieliset[MAX][MAX];
   char kaannettava[MAX];
   bool suomeksi = true;
   char a;
   int i = 0;
   int j = 0;
   int rivit = 0;
   int tarkistus = 0;
   int indeksi = 0;


    printf(">");
    lueMerkkijono(kaannettava, MAX);
    
   FILE *FileRead;
    if((FileRead = fopen("sanakirja.txt", "r")) == NULL){
        return 1;
    }

   while ((a != EOF)){
        a = fgetc(FileRead);

        
        if (a == ';'){
            suomeksi = false;
            j=0;
        }else if (a == '\n'){
            suomeksi = true;
            rivit++;
            i=0;
        }
        
        if (suomeksi && a != ';' && a != '?' && a != '\n'){
            suomenKieliset[rivit][i] = a;
            i++;
        }else if (!suomeksi && a != ';' && a != '?' && a != '\n'){
            englanninKieliset[rivit][j] = a;
            j++;
        }
    }
    
    
    fclose(FileRead);

    for (int i = 0; i <= rivit; i++)
    {
        strremove(englanninKieliset[i], "englanniksi");
        strremove(suomenKieliset[i], "suomeksi");
    }

    printf("%s", englanninKieliset[1]);


    for (int i = 0; i <= rivit ; i++){
        
        if (strcmp(kaannettava, suomenKieliset[i]) == 0){
            suomeksi = false;
            tarkistus++;
            indeksi = i;
            break;
        }else if (strcmp(kaannettava, englanninKieliset[i]) == 0)
        {
            suomeksi = true;
            tarkistus--;
            indeksi = i;
            break;
        }
    }

        

    if (suomeksi == false && tarkistus > 0){
        printf("\nSana %s englanniksi on %s", suomenKieliset[indeksi], englanninKieliset[indeksi]);
    }else if (suomeksi == true && tarkistus < 0){
        printf("\nSana %s suomeksi on %s", englanninKieliset[indeksi], suomenKieliset[indeksi]);
    }else{
        printf("\nSanaa %s ei loytynyt sanakirjasta", kaannettava);
    }

    return 0;
}

char *strremove(char *str, const char *sub) {       // Funktio haettu Stackoverflow postauksesta käyttäjältä @chqrlie
    size_t len = strlen(sub);                      // Saatavilla netissä: https://stackoverflow.com/questions/47116974/remove-a-substring-from-a-string-in-c
    if (len > 0) {      
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}


void lueMerkkijono(char merkkijono[], int pituus){

   fgets( merkkijono, pituus, stdin );

   // Jos merkkijonon lopussa, ennen lopetusmerkki� on ylim��r�inen
   // rivinvaihto korvataan se lopetusmerkill�
   if( merkkijono[ strlen(merkkijono)-1 ] == '\n')
      merkkijono[ strlen(merkkijono)-1 ] = '\0';
   else
      lueRoskat();

}

void lueRoskat(void){

   // Tyhjennet��n puskuri
   while( fgetc(stdin) != '\n');
}