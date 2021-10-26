#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 50

struct _student;
typedef struct _student* Pozicija;
typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godiste;
	Pozicija next;
}Student;

int UnosNaPocetak(Pozicija p, char* ime, char* prezime, int godiste);
int IsprintajListu(Pozicija p);
int UnosNaKraj(Pozicija p, char* ime, char* prezime, int godiste);
Pozicija Trazi(char* prezime, Pozicija p);
Pozicija TraziPrethodni(char* prezime, Pozicija p);
int Obrisi(char* prezime, Pozicija p);
int UnosIza(char* ime, char* prezime1, int godiste, char* prezime2, Pozicija p);
int ObrisiNakon(char* prezime, Pozicija p);
int UnosIspred(char* ime, char* prezime1, int godiste, char* prezime2, Pozicija p);

int main(int argc, char** argv)
{
	Student head = { .ime = {0}, .prezime = {0}, .godiste = 0, .next = NULL };
	Pozicija p = &head;
	char z;
	Student temp = { .ime = {0}, .prezime = {0}, .godiste = 0, .next = NULL };
	Pozicija t = &temp;
	Student temp1 = { .ime = {0}, .prezime = {0}, .godiste = 0, .next = NULL };
	Pozicija t1 = &temp1;
	Pozicija trazeni;
	Pozicija prethodni;

	while (1) {
		printf("IZBORNIK\nUnesite:\nP - unos na pocetak\nK - unos na kraj\n"
			"I - ispis liste\nT - trazi osobu\nR - trazi prethodnu osobu\n"
			"O - obrisi osobu\nZ - unos iza odredene osobe\nN - obrisi nakon"
			"\nS - unos ispred odredene osobe\nE - izlaz\n\n");
		scanf(" %c", &z);
		switch (toupper(z))
		{
		case 'P':
			printf("Unesite podatke osobe");
			printf("\nIme: ");
			scanf(" %s", temp.ime);
			printf("Prezime: ");
			scanf(" %s", temp.prezime);
			printf("Godiste: ");
			scanf("%d", &temp.godiste);
			UnosNaPocetak(p, t->ime, t->prezime, t->godiste);
			printf("\nOsoba je dodana na pocetak liste!\n\n");
			break;

		case 'K':
			printf("Unesite podatke osobe");
			printf("\nIme: ");
			scanf(" %s", temp.ime);
			printf("Prezime: ");
			scanf(" %s", temp.prezime);
			printf("Godiste: ");
			scanf("%d", &temp.godiste);
			UnosNaKraj(p, t->ime, t->prezime, t->godiste);
			printf("\nOsoba je dodana na kraj liste!\n\n");
			break;

		case 'I':
			printf("LISTA:\n");
			IsprintajListu(p->next);
			puts("\n");
			break;

		case 'T':
			printf("Unesite prezime osobe koju trazite: ");
			scanf(" %s", temp.prezime);
			trazeni = Trazi(t->prezime, p->next);
			printf("\nTrazena osoba:\nIme: %s\nPrezime: %s\nGodiste: %d\n\n"
				, trazeni->ime, trazeni->prezime, trazeni->godiste);
			break;

		case 'R':
			printf("Unesite prezime osobe od koje trazite prethodnu: ");
			scanf(" %s", temp.prezime);
			prethodni = TraziPrethodni(t->prezime, p->next);
			if (prethodni != NULL)
				printf("\nPrethodna osoba u listi:\nIme: %s\nPrezime: %s\nGodiste: %d\n\n"
					, prethodni->ime, prethodni->prezime, prethodni->godiste);
			break;

		case 'O':
			printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
			scanf(" %s", temp.prezime);
			Obrisi(t->prezime, p);
			printf("\nOsoba je izbrisana iz liste!\n\n");
			break;

		case 'N':
			printf("Unesite prezime osobe iza koje ce se izbrisati osoba: ");
			scanf(" %s", temp.prezime);
			ObrisiNakon(t->prezime, p);
			printf("\nOsoba iza je uspjesno izbrisana (ili nije ni postojala)!\n\n");
			break;

		case 'Z':
			printf("Unesite podatke nove osobe");
			printf("\nIme: ");
			scanf(" %s", temp.ime);
			printf("Prezime: ");
			scanf(" %s", temp.prezime);
			printf("Godiste: ");
			scanf("%d", &temp.godiste);
			printf("Unesite prezime osobe iza koje zelite unijeti novu osobu: ");
			scanf(" %s", temp1.prezime);
			UnosIza(t->ime, t->prezime, t->godiste, t1->prezime, p->next);
			break;

		case 'S':
			printf("Unesite podatke nove osobe");
			printf("\nIme: ");
			scanf(" %s", temp.ime);
			printf("Prezime: ");
			scanf(" %s", temp.prezime);
			printf("Godiste: ");
			scanf("%d", &temp.godiste);
			printf("Unesite prezime osobe ispred koje zelite unijeti novu osobu: ");
			scanf(" %s", temp1.prezime);
			UnosIspred(t->ime, t->prezime, t->godiste, t1->prezime, p->next);
			break;

		case 'E':
			puts("\nIzlaz iz programa!\n");
			return 1;
			break;

		default:
			printf("\nGreska pri unosu!\nPokusajte ponovno!\n");
			break;
		}
	}


	return EXIT_SUCCESS;
}

int UnosNaPocetak(Pozicija p, char* ime, char* prezime, int godiste)
{
	Pozicija NovaOsoba = NULL;
	NovaOsoba = (Pozicija)malloc(sizeof(Student));
	if (!NovaOsoba)
		return -1;
	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godiste = godiste;
	NovaOsoba->next = p->next;
	p->next = NovaOsoba;
	return EXIT_SUCCESS;
}

int IsprintajListu(Pozicija p)
{
	Pozicija temp = p;
	if (temp == NULL)
		printf("Lista je prazna!\n\n");
	while (temp) {
		printf("Ime: %s\nPrezime: %s\nGodiste: %d\n", temp->ime, temp->prezime, temp->godiste);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int UnosNaKraj(Pozicija p, char* ime, char* prezime, int godiste)
{
	Pozicija NovaOsoba = NULL;
	Pozicija temp = p;
	NovaOsoba = (Pozicija)malloc(sizeof(Student));
	if (!NovaOsoba)
		perror("Greska pri alociranju!");
	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime);
	NovaOsoba->godiste = godiste;
	while (temp->next) {
		temp = temp->next;
	}
	NovaOsoba->next = temp->next;
	temp->next = NovaOsoba;

	return EXIT_SUCCESS;
}

Pozicija Trazi(char* prezime, Pozicija p)
{
	Pozicija temp = p;
	while (temp) {
		if (!strcmp(prezime, temp->prezime))
			return temp;
		temp = temp->next;
	}
	printf("\nTrazeni student se ne nalazi u listi!\n");
	return NULL;
}

Pozicija TraziPrethodni(char* prezime, Pozicija p)
{
	Pozicija temp = p;
	while (temp->next != NULL && strcmp(temp->next->prezime, prezime)) {
		temp = temp->next;
	}
	if (temp->next == NULL) {
		printf("\nTrazeni student se ne nalazi u listi!\n");
		return NULL;
	}
	return temp;
}

int Obrisi(char* prezime, Pozicija p)
{
	Pozicija temp = p;
	Pozicija prethodni = TraziPrethodni(prezime, p);
	if (prethodni != NULL) {
		temp = prethodni->next;
		prethodni->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int ObrisiNakon(char* prezime, Pozicija p)
{
	Pozicija temp = Trazi(prezime, p);
	if (temp->next != NULL) {
		temp->next = temp->next->next;
		free(temp->next);
	}
	return EXIT_SUCCESS;
}

int UnosIza(char* ime, char* prezime1, int godiste, char* prezime2, Pozicija p)
{
	Pozicija NovaOsoba = NULL;
	Pozicija temp = Trazi(prezime2, p);
	NovaOsoba = (Pozicija)malloc(sizeof(Student));
	if (!NovaOsoba)
		return -1;
	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime1);
	NovaOsoba->godiste = godiste;
	if (temp) {
		NovaOsoba->next = temp->next;
		temp->next = NovaOsoba;
	}
	return EXIT_SUCCESS;
}

int UnosIspred(char* ime, char* prezime1, int godiste, char* prezime2, Pozicija p)
{
	Pozicija NovaOsoba = NULL;
	Pozicija prethodni = TraziPrethodni(prezime2, p);
	NovaOsoba = (Pozicija)malloc(sizeof(Student));
	if (!NovaOsoba)
		return -1;
	strcpy(NovaOsoba->ime, ime);
	strcpy(NovaOsoba->prezime, prezime1);
	NovaOsoba->godiste = godiste;
	if (prethodni != NULL) {
		NovaOsoba->next = prethodni->next;
		prethodni->next = NovaOsoba;
	}
	return EXIT_SUCCESS;
}