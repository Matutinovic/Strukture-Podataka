#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024

struct Polinom;
typedef struct Polinom* Pol;
typedef struct Polinom {
	int koef;
	int eksp;
	Pol next;
}Polinom;

int Unos(Pol p, int koef, int eksp);
int Ispis(Pol p);
int Suma(Pol p1, Pol p2, Pol s);
int Produkt(Pol p1, Pol p2, Pol p);
int UcitajIzDatoteke(Pol p1, Pol p2, char* imeDatoteke);

int main() {

	Polinom head = { .koef = 0, .eksp = 0, .next = NULL };
	Pol p1 = &head;
	Polinom head2 = { .koef = 0, .eksp = 0, .next = NULL };
	Pol p2 = &head2;
	Polinom suma = { .koef = 0, .eksp = 0, .next = NULL };
	Pol s = &suma;
	Polinom produkt = { .koef = 0, .eksp = 0, .next = NULL };
	Pol pr = &produkt;

	UcitajIzDatoteke(p1, p2, imeDatoteke);

	printf("Polinom 1: ");
	Ispis(p1->next);
	printf("\nPolinom 2: ");
	Ispis(p2->next);

	Suma(p1->next, p2->next, s);
	printf("\nSuma polinoma: ");
	Ispis(s->next);
	Produkt(p1->next, p2->next, pr);
	printf("\nProdukt polinoma: ");
	Ispis(pr->next);
	puts("\n");

	return EXIT_SUCCESS;
}

int UcitajIzDatoteke(Pol p1, Pol p2, char* imeDatoteke)
{
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(imeDatoteke, "r");
	if (!fp) {
		perror("Greska pri otvaranju datoteke!");
		return -1;
	}

	fgets(buffer, 1024, fp);
	ProcitajLiniju(p1, buffer);
	fgets(buffer, 1024, fp);
	ProcitajLiniju(p2, buffer);

	fclose(fp);
	return EXIT_SUCCESS;
}

int ProcitajLiniju(Pol p, char* buffer)
{
	buffer[strlen(buffer)] = 0;
	char* pok = buffer;
	int koef = 0;
	int eksp = 0;
	int br = 0;

	do {
		br = 0;
		if (sscanf(pok, " %d %d %n", &koef, &eksp, &br) == 2) {
			pok += br;
			Unos(p, koef, eksp);
		}
	} while (strlen(pok) > 1);

	return EXIT_SUCCESS;
}

int Unos(Pol p, int koef, int eksp)
{
	Pol temp = p;
	Pol Novi = NULL;

	while (temp->next != NULL && temp->next->eksp > eksp) {
		temp = temp->next;
	}
	if (temp->next != NULL && temp->next->eksp == eksp)
		temp->next->koef += koef;
	else {
		Novi = (Pol)malloc(sizeof(Polinom));
		Novi->koef = koef;
		Novi->eksp = eksp;
		Novi->next = temp->next;
		temp->next = Novi;
	}
	
	return EXIT_SUCCESS;
}

int Ispis(Pol p)
{
	Pol temp = p;
	while (temp != NULL) {
		if (temp->eksp == 0)
			printf("%d ", temp->koef);
		else if (temp->koef == 1)
			printf("x^%d", temp->eksp);
		else
			printf("%dx^%d ", temp->koef, temp->eksp);
		if (temp->next != NULL && temp->next->koef > 0)
			printf("+ ");
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int Suma(Pol p1, Pol p2, Pol s)
{
	Pol temp = NULL;
	while (p1 != NULL && p2 != NULL) {
		if (p1->eksp == p2->eksp) {
			Unos(s, p1->koef + p2->koef, p1->eksp);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->eksp > p2->eksp) {
			Unos(s, p1->koef, p1->eksp);
			p1 = p1->next;
		}
		else {
			Unos(s, p2->koef, p2->eksp);
			p2 = p2->next;
		}
	}
	if (p1 != NULL)
		temp = p1;
	else
		temp = p2;
	while (temp != NULL) {
		Unos(s, temp->koef, temp->eksp);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int Produkt(Pol p1, Pol p2, Pol pr)
{
	Pol pocetak = p2;
	while (p1 != NULL) {
		p2 = pocetak;
		while (p2 != NULL) {
			Unos(pr, p1->koef * p2->koef, p1->eksp + p2->eksp);
			p2 = p2->next;
		}
		p1 = p1->next;
	}

	return EXIT_SUCCESS;
}