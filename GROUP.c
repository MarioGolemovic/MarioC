#define _CRT_SECURE_NO_WARNINGS
#include "StdLibs.h"
#include "GroupHeader.h"
#include "Utils.h"

GRUPA* alocirajGrupu(void) {
	GRUPA* grupa = (GRUPA*)malloc(sizeof(GRUPA));
	if (grupa == NULL) exit(EXIT_FAILURE);

	grupa->timovi = (TIM*)malloc(BROJ_TIMOVA_U_GRUPI * sizeof(TIM));
	if (grupa->timovi == NULL) exit(EXIT_FAILURE);

	grupa->brojTimova = BROJ_TIMOVA_U_GRUPI;

	for (int i = 0; i < grupa->brojTimova; i++) {
		grupa->timovi[i].igraci = (IGRAC*)malloc(BROJ_IGRACA_U_TIMU * sizeof(IGRAC));
		if (grupa->timovi[i].igraci == NULL) exit(EXIT_FAILURE);
		grupa->timovi[i].brojIgraca = BROJ_IGRACA_U_TIMU;
	}

	return grupa;
}

void unosIzDatoteke(GRUPA* grupa, char* fileName) {
	FILE* inFile = fopen(fileName, "r");
	if (inFile == NULL) exit(EXIT_FAILURE);

	for (int i = 0; i < grupa->brojTimova; i++) {

		fgets(grupa->timovi[i].imeTima, 20, inFile);
		removeNewLine(grupa->timovi[i].imeTima);
		grupa->timovi[i].bodovi = 0;

		for (int j = 0; j < grupa->timovi->brojIgraca; j++) {

			fgets(grupa->timovi[i].igraci[j].imeIgraca, 20, inFile);
			removeNewLine(grupa->timovi[i].igraci[j].imeIgraca);

			fgets(grupa->timovi[i].igraci[j].prezimeIgraca, 20, inFile);
			removeNewLine(grupa->timovi[i].igraci[j].prezimeIgraca);

			fscanf(inFile, "%hu", &grupa->timovi[i].igraci[j].datumRodjenja.yyyy);
			fgetc(inFile);

			fscanf(inFile, "%hu", &grupa->timovi[i].igraci[j].datumRodjenja.mm);
			fgetc(inFile);

			fscanf(inFile, "%hu", &grupa->timovi[i].igraci[j].datumRodjenja.dd);
			fgetc(inFile);
		}
	}
	fclose(inFile);
}

TIM* odigrajTurnir(GRUPA* grupa) {
	for (int i = 0; i < grupa->brojTimova - 1; i++) {
		for (int j = i + 1; j < grupa->brojTimova; j++) {
			odigrajUtakmicu(&grupa->timovi[i], &grupa->timovi[j]);
		}
	}
	return dohvatiPobjednika(grupa);
}

void odigrajUtakmicu(TIM* prvi, TIM* drugi) {

	printf("Utakmicu igra %s protiv %s.\n", prvi->imeTima, drugi->imeTima);

	printf("Unesite broj golova za %s ", prvi->imeTima);
	scanf("%d", &prvi->golovi);
	getchar();

	printf("Unesite broj golova za %s ", drugi->imeTima);
	scanf("%d", &drugi->golovi);
	getchar();

	if (prvi->golovi > drugi->golovi) prvi->bodovi += 3;
	else if (prvi->golovi < drugi->golovi) drugi->bodovi += 3;
	else {
		prvi->bodovi++;
		drugi->bodovi++;
	}
}

TIM* dohvatiPobjednika(GRUPA* grupa) {
	TIM* pobjednik = &grupa->timovi[0];
	for (int i = 0; i < grupa->brojTimova; i++) {
		if (pobjednik->bodovi < grupa->timovi[i].bodovi)
			pobjednik = &grupa->timovi[i];
	}
	return pobjednik;
}

void* oslobodiGrupu(GRUPA* grupa) {
	for (int i = 0; i < grupa->brojTimova; i++) {
		free(grupa->timovi[i].igraci);
	}
	free(grupa->timovi);
	free(grupa);
	return NULL;
}

void sortGrupe(GRUPA* grupa) {
	for (int i = 0; i < grupa->brojTimova - 1; i++) {
		for (int j = 0; j < grupa->brojTimova - i - 1; j++) {
			if (grupa->timovi[j].bodovi < grupa->timovi[j + 1].bodovi) {
				swap(&grupa->timovi[j], &grupa->timovi[j + 1]);
			}
		}
	}
}

void swap(TIM* prvi, TIM* drugi) {
	TIM help = *prvi;
	*prvi = *drugi;
	*drugi = help;
}

void ispisTima(TIM* pobjednik, FILE* stream) {
	fputs(pobjednik->imeTima, stream); fputs("\n", stream);
	for (int j = 0; j < pobjednik->brojIgraca; j++) {

		fputs(pobjednik->igraci[j].imeIgraca, stream); fputs("\n", stream);
		fputs(pobjednik->igraci[j].prezimeIgraca, stream); fputs("\n", stream);

		fprintf(stream, "%hu\n", pobjednik->igraci[j].datumRodjenja.yyyy);

		fprintf(stream, "%hu\n", pobjednik->igraci[j].datumRodjenja.mm);

		fprintf(stream, "%hu\n", pobjednik->igraci[j].datumRodjenja.dd);
	}
}

void ispisTimaFormatiran(TIM* pobjednik, FILE* stream) {
	fputs(pobjednik->imeTima, stream); 
	fputs("\n", stream);
	fputs("Igraci tima su:\n", stream);
	for (int j = 0; j < pobjednik->brojIgraca; j++) {
		fputs(pobjednik->igraci[j].imeIgraca, stream);
		fputs(" ", stream);
		fputs(pobjednik->igraci[j].prezimeIgraca, stream);

		printf(", ");
		fprintf(stream, "%hu.", pobjednik->igraci[j].datumRodjenja.dd);
		fprintf(stream, "%hu.", pobjednik->igraci[j].datumRodjenja.mm);
		fprintf(stream, "%hu.", pobjednik->igraci[j].datumRodjenja.yyyy);
		printf("\n");

	}
}

void zapisUDatoteku(GRUPA* grupa, char* fileName) {
	FILE* outFile = fopen(fileName, "w");
	if (outFile == NULL) exit(EXIT_FAILURE);
	for (int i = 0; i < grupa->brojTimova; i++) {
		ispisTima(&grupa->timovi[i], outFile);
	}
	fclose(outFile);
}