#define _CRT_SECURE_NO_WARNINGS
#include "StdLibs.h"
#include "GroupHeader.h"
#include "Utils.h"

int main() {

	const char* fileName = "grupe.txt";
	const char* sortedFileName = "sortiranaGrupa.txt";

	printf("\t\tDobrodosli u malonogometnu Premier ligu.\n\n");
	printf("\t\tClanovi lige su:\n");
	printf("1.Arsenal\n2.Manchester United\n3.Manchester City\n4.Chelsea\n5.Liverpool\n6.Tottenham\n\n");

	GRUPA* grupa = alocirajGrupu();

	unosIzDatoteke(grupa, fileName);

	TIM* pobjednik = odigrajTurnir(grupa);

	printf("Pobjednik lige je ");

	ispisTimaFormatiran(pobjednik, stdout);

	sortGrupe(grupa);

	zapisUDatoteku(grupa, sortedFileName);

	grupa = oslobodiGrupu(grupa);

	return 0;
}