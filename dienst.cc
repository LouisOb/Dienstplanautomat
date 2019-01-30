#ifndef Hello
#define Hello 1
#include<stdlib.h>
#include <cstdlib> 
#include <ctime>
#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#endif
using namespace std;

int test(int *ergebnis, int anzahl, int dienste){//die Testfunktion die entscheidet ob eine Konstellation funktioniert
//Es wird getestet ob auch alle Dienste an allen Tagen vergeben sind
for(int l=0;l<14;l++)
	for(int k=0;k<dienste;k++){
		int testsum=0;
		for(int m=0;m<anzahl;m++)
			testsum+=ergebnis[k+l*dienste+m*dienste*15];
	if(testsum!=2) return 1;
	}
//Wenn alle Parameter stimmen wird ein go zurückgegeben
return 0;
}




int quersumme(int *teilarray,int menge){//Eine Funktion zur Berechnung der Quersumme der Dienste einer Person eines Tages
int summe=0;
for(int i=0;i<menge;i++)
	summe+=teilarray[i];
return summe;
}




void fullergebnis(int *ergebnis,int anzahl, int dienste){
for(int i=0; i<anzahl;i++)
	for(int j=0; j<15;j++)
		for(int k=0;k<dienste;k++)
			ergebnis[i*dienste*15+j*dienste+k]=0;
}



















int main(int argc, char *argument[]){




int grosse;
int dienste=4;
char * Datei = argument[1];

int persons=0;
std::ifstream Offen(Datei);
if(Offen.bad()){
	cout << "error";
	return 1;
	}
    string dummy;
    getline(Offen,dummy);
    while(getline(Offen,dummy)){
//	cout << dummy << '\n';
	persons+=1;
	}
//	cout << persons;
//	cin >> grosse;
    string Personen[persons];
      Offen.close();
	std::ifstream nOffen(Datei);
    getline(nOffen,dummy);
    grosse=persons;
int anwesenheit[persons][14];
	int Person=0;
    while(getline(nOffen,dummy)){
//		cout << dummy << "	";
	int persongesetzt=0;
	std::string delimiter = ",";

	size_t pos = 0;
	std::string token;
	for(int Tag=0;Tag<14;Tag++){
	    token = dummy.substr(0, pos);
//		cout << token << '\n';
	    if(persongesetzt==0){Personen[Person]=token; persongesetzt++; dummy.erase(0, pos + delimiter.length()); continue;}
	    anwesenheit[Person][Tag]=atoi(token.c_str());
	    dummy.erase(0, pos + delimiter.length());
//		cout << token << '\n';
	}
	token = dummy.substr(0, pos);
	anwesenheit[Person][Tag]=atoi(token.c_str());
	dummy.erase(0, pos + delimiter.length());
	Person++;
	}

    Offen.close();
int anzahl=grosse;

srand(time(NULL)); //den Zufallsgenerator einstellen
int ergebnis[anzahl][15][dienste];//das ergebniss array wird erstellt
fullergebnis(&ergebnis[0][0][0],anzahl,dienste);
/*for(int i=0;i<anzahl;i++){
	for(int j=0;j<15;j++)
		for(int k=0;k<dienste;k++){
			if(k==3){ cout << ergebnis[i][j][k] << '\n'; continue;}
			cout << ergebnis[i][j][k] << '\t';
  			}
	if(i==anzahl-1) cout << '\n' << '\n';
	}*/
int count=0;
//test(&ergebnis[0][0][0],anzahl,dienste)
while(test(&ergebnis[0][0][0],anzahl,dienste)){//die Schleife endet wenn ein passendes ergebnis gefunden wurde
//Zufallszahlen werden gezogen um einer Person einen Dienst zuzuweisen
if(count>20000){fullergebnis(&ergebnis[0][0][0],anzahl,dienste); count=0;}
int i = rand() % anzahl ;
int j = rand() % 14 ;
int k = rand() % dienste ;

if(anwesenheit[i][j]){//Es wird getestet ob die Person an dem Tag anwesend ist
if(ergebnis[i][14][k]<2){//Personen können maximal 2 mal den Dienst erhalten
if(!quersumme(ergebnis[i][j],dienste)){//Es wird getestet ob die Person bereits einen Dienst an diesem Tag hat
int Tageszaeler=0;
for(int l=0; l<anzahl;l++)
		Tageszaeler+=ergebnis[l][j][k];
//cout << Tageszaeler << "\n";
if(Tageszaeler!=2){//Es wird getetstet ob der Dienst an diesem tag bereits vergeben ist
//cout << ++count << "\n";

	ergebnis[i][j][k]=1;
	ergebnis[i][14][k]+=1;
	}}}}
count++;
}
for(int i=0;i<anzahl;i++){

	for(int j=0;j<14;j++){
			int testsum=0;
		for(int k=0;k<dienste;k++){
			testsum+=ergebnis[i][j][k];
			if(ergebnis[i][j][k]==1) cout << ergebnis[i][j][k] << "  ";
  			}
		if(!testsum)
			cout << "0  ";
		}
	cout << '\n';
	}
return 0;
}

























