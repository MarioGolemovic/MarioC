#define _CRT_SECURE_NO_WARNINGS
#include "StdLibs.h"

int removeNewLine(char* buffer) {
	int i, flag = 0;
	for (i = 0; buffer[i] != '\0'; i++) {
		if (buffer[i] == '\n') {
			flag = 1;
			buffer[i] = '\0';
			break;
		}
	}
	return flag;
}