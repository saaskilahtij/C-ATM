// Funktioiden esittelyt erillisenä header.c tiedostona
// Järjestys ei ole järjestelty funktiot.c mukaisesti

void lueMerkkijono(char merkkijono[], int pituus);
void lueRoskat(void);
int lueKokonaisluku(void);
double lueReaaliluku(void);
double haeSaldo(char* tiedosto);
void jakaaSetelit(int * maarat, int summa);
double nostovalikko(char *tiedosto, char *pin);
void tapahtumavalikko(char * tiedosto);
int valiValikko();
void saldovalikko(char *tiedosto);
int muokkaaSaldoa(char *tiedosto, char *pin, double saldo);
void talletusValikko(char *tiedosto, char *pin);
int haePin(char *tiedosto, char *validPin);
void virheValikko();