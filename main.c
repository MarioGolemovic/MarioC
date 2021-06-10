#define _CRT_SECURE_NO_WARNINGS
#include "StdLibs.h"
#include "GroupHeader.h"
#include "Utils.h"

int main() {

	const char* fileName = "grupe.txt";
	const char* sortedFileName = "sortiranaGrupa.txt";

	printf("\t\tDobrodosli u malonogometnu Super ligu.\n\n");
	printf("\t\tClanovi Super lige su:\n");
	printf("1.Arsenal\n2.Barcelona\n3.Juventus\n4.Manchester United\n5.Manchester City\n6.Chelsea\n7.Real Madrid\n8.PSG\n9.Bayern\n10.Liverpool\n\n\n");

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