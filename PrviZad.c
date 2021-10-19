#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024
#define MAX_BR 100

typedef struct _student{
	char Ime[MAX_SIZE];
	char Prezime[MAX_SIZE];
	double bodovi;
} Student;

int ProcitajRetke(char* ImeDatoteke);
Student* AlocirajZaNizStruktura(int BrojStudenata, char* ImeDatoteke);
double MaxBodova(int BrojStudenata, Student* Niz);

int main(){
	int i = 0;
	int n = 0;
	Student* p = NULL;
	n = ProcitajRetke("Studentici.txt");
	p = AlocirajZaNizStruktura(n, "Studentici.txt");
	
	for(i = 0; i < n; i++){
		printf("Ispis za %d. studenta\n", i+1);
		printf("Ime: %s\n", p[i].Ime);
		printf("Prezime: %s\n", p[i].Prezime);
		printf("Apsolutni broj bodova: %lf\n", p[i].bodovi);
		printf("Relativni broj bodova: %lf\n", (p[i].bodovi / MaxBodova(n, p))*(double)100);
	}
		
	return 0;	
}

int ProcitajRetke(char* ImeDatoteke){
	int brojac = 0;
	FILE *datoteka = NULL;
	char buffer[MAX_LINE] = {0};
	
	datoteka = fopen(ImeDatoteke, "r");
	if(!datoteka){
		printf("Greska!");
		return -1;
	}
	
	while(!feof(datoteka)){
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}
	
	fclose(datoteka);
	return brojac;
}

Student* AlocirajZaNizStruktura(int BrojStudenata, char* ImeDatoteke){
	int brojac = 0;
	FILE *datoteka = NULL;
	Student* studenti = NULL;
	
	studenti = (Student*)malloc(BrojStudenata * sizeof(Student));
	datoteka = fopen(ImeDatoteke, "r");
	if(!datoteka){
		printf("Greska alociranja!");
		free(studenti);
		return NULL;
	}
	
	while(!feof(datoteka)){
		fscanf(datoteka, " %s %s %lf", studenti[brojac].Ime, studenti[brojac].Prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	
	fclose(datoteka);
	
	return studenti;
}

double MaxBodova(int BrojStudenata, Student* p){
	int i = 0;
	double maxbod = 0.0;
	
	maxbod = p[0].bodovi;
	
	for(i = 0; i < BrojStudenata; i++){
		if(p[i].bodovi > maxbod)
			maxbod = p[i].bodovi;
	}
	
	return maxbod;
}
