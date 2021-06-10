#define _CRT_SECURE_NO_WARNINGS
#ifndef GRUPE_H
#define GRUPE_H

#define BROJ_TIMOVA_U_GRUPI 6
#define BROJ_IGRACA_U_TIMU 6

typedef struct datum {
	unsigned short yyyy;
	unsigned short mm;
	unsigned short dd;
}DATUM;

typedef struct igrac {
	char imeIgraca[20];
	char prezimeIgraca[20];
	DATUM datumRodjenja;
}IGRAC;

typedef struct tim {
	char imeTima[20];
	IGRAC* igraci;
	int brojIgraca;
	int bodovi;
	int golovi;
}TIM;

typedef struct grupa {
	TIM* timovi;
	int brojTimova;
}GRUPA;

GRUPA* alocirajGrupu(void);
void unosIzDatoteke(GRUPA* grupa, char* fileName);
void sortGrupe(GRUPA* grupa);
TIM* odigrajTurnir(GRUPA* grupa);
void odigrajUtakmicu(TIM* prvi, TIM* drugi);
TIM* dohvatiPobjednika(GRUPA* grupa);
void* oslobodiGrupu(GRUPA* grupa);
void ispisTima(TIM* pobjednik, FILE* stream);
void ispisTimaFormatiran(TIM* pobjednik, FILE* stream);
void swap(TIM* prvi, TIM* drugi);
void zapisUDatoteku(GRUPA* grupa, char* fileName);

#endif // !GRUPE