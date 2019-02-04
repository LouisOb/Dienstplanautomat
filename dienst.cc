#include<stdlib.h>
#include <cstdlib> 
#include <ctime>
#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
using namespace std;
//Funktionendekleration
void fullergebnis(int *,int,int,int);
int test(int *,int,int,int,int*);
int quersumme(int*,int);
int ntest(int*,int,int,int,int*);
int nbtest(int*,int*,int,int,int,int,int);
void copy(int*,int*,int,int,int);



int main(int argc, char *argument[]){
//Variablen Dekleration

//Anzahl der Personen
int grosse;
//Der Tag an dem Der Ausflug ist
int ausflugtag=6;
//Dauer des Zeltlagers
int dauer=15;
//Anzahl der zu vergebenden Dienste
int dienste=4;
//Datei aus der Ausgelesen wird
char * Datei = argument[1];
//ebenfalls Anzahl der Personen historisch noch im Code
int persons=0;
//eine Variable zum Auslesen
string dummy;
//Datei zum Auslesen wird geöffnet und ausgelesen
std::ifstream Offen(Datei);
//Wenn die Datei nicht geöffent werden kann wird ein Error ausgegeben
if(Offen.bad()){
	std::cout << "error";
	return 1;
	}
//Die erste Zeile ist unwichtig und wird übergangen
    getline(Offen,dummy);
//Es wird die Anzahl der Personen bestimmt
    while(getline(Offen,dummy)){
	persons+=1;
	}
Offen.close();
//Die Liste mit der Namen der Personen
    string Personen[persons];
//#1 Eine neue Datei wird geöffent, da cursor verschiebungen nicht geholfen haben eventuell ergänzen
	std::ifstream nOffen(Datei);
//erste Zeile wird ausgelassen
    getline(nOffen,dummy);
//anzahl der personen wird gesetzt
    grosse=persons;
//Die Anwesenheitsliste der Personen wird erstellt
int anwesenheit[persons][dauer];
//Die Attributliste der Personen 0: Dienst der nicht gemocht wird 1: Neubetreuer 2: Schaffer 3: Ausflugplaner 4: Fahrer
int Attributliste[persons][5];
// Eine Variable um die Person zu zählen die gerade ausgelesen wird
	int Person=0;
//Die Daten werden ausglesen, zeilenweise
    while(getline(nOffen,dummy)){
//eine Variable um zu wissen ob die Person in die Namen der Liste eingetragen wurde
	int persongesetzt=0;
//in der csv datei werden Kommas als Spaltentrenner verwendet und damit hier der String getrennt
	std::string delimiter = ",";
//die position des string cursors wird erstellt
	size_t pos = 0;
//der ausgeschnittene Stringteil ist der token
	std::string token;
//Die Zeile wird ausglesen spaltenweise
	for(int Tag=0;Tag<dauer;Tag++){
	    pos=dummy.find(delimiter);
	    token = dummy.substr(0, pos);
//Wenn noch keine Person eingetragen wurde so geschieht dies hier
	    if(persongesetzt==0){Personen[Person]=token; persongesetzt++; dummy.erase(0, pos + delimiter.length()); Tag=-1; continue;}
//die Anwesenheit wird in die Liste eingetragen
	    anwesenheit[Person][Tag]=atoi(token.c_str());
//Aus der Zeile werden die einegtragenen Werte entfernt
	    dummy.erase(0, pos + delimiter.length());

	}
//Die Attribute werden ausgelesen aus der Zeile
	for(int i=0; i<5;i++){
	  pos=dummy.find(delimiter);
	    token = dummy.substr(0, pos);
	    Attributliste[Person][i]=atoi(token.c_str());
	    dummy.erase(0, pos + delimiter.length());
	}
//Die nächste Person wird ausgelesen
	Person++;
	}
//Die Datei wird geschlossen
    nOffen.close();
//#2 Die anzahl der personen wird gesetzt historisch noch vorhanden
int anzahl=grosse;

srand(time(NULL)); //den Zufallsgenerator einstellen
int ergebnis[anzahl][dauer+1][dienste];//das ergebniss array wird erstellt, die Tage 0 bis dauer-1 sind normale Tage mit Diensten, im letzten werden die Daten gespeichert wie oft eine Person den Dienst bereits hat Bsp. ergebnis[0][dauer][1]=2 die Person hat schon 2 mal Fahrdienst 
//das ergebniss wird mit Nullen gefüllt
fullergebnis(&ergebnis[0][0][0],anzahl,dienste,dauer);
//die Anzahl der Iterationen wird gezählt
int count=0;
//Variable zählt die Tagesleitungen am Ausflig die vergeben sind
int ausflug=0;

//**********************erstes Auffüllen des ergebnis***************************
//Die Tagesleitungen am Ausflug werden vergeben
while(ausflug!=2){
int i = rand() % anzahl ;
if(Attributliste[i][3] && !ergebnis[i][ausflugtag][0]){ergebnis[i][ausflugtag][0]=1;ergebnis[i][dauer][0]+=1; ausflug++;} 
}
//Variable die Tagesleitung am letzten Tag zählt
int lastday=0;
//Die Tagesleitung am letzten Tag wird vergeben
while(lastday!=2){
int i = rand() % anzahl ;
if(Attributliste[i][0]!= 0 && Attributliste[i][2] && !ergebnis[i][dauer-1][0]){ergebnis[i][dauer-1][0]=1;ergebnis[i][dauer][0]+=1; lastday++;} 
}
//eine Kopie des bisherigen ergebnis
int cpergebnis[anzahl][dauer+1][dienste];
//kopiere das Eregebnis
copy(&cpergebnis[0][0][0],&ergebnis[0][0][0],anzahl,dauer,dienste);

//***********************Neubetreuer Dienste werden zugeteilt*******************

//Die Neubetreuer Dienste werden zuerst festgelegt
while(ntest(&ergebnis[0][0][0],anzahl,dienste,dauer,&Attributliste[0][0])){
//Schleife endet wenn ein passendes ergebnis gefunden wurde
//Zufallszahlen werden gezogen um einer Person einen Dienst zuzuweisen
//wenn die Schleife mehr als 100000 mal durchgelaufen ist wird das voherige ergebnis wiederhergestellt und von neuem angefangen
if(count>1000000){count=0;copy(&ergebnis[0][0][0],&cpergebnis[0][0][0],anzahl,dauer,dienste);}
int i = rand() % anzahl ;
int j = rand() % dauer-1 ;
int k = rand() % dienste ;
if(!Attributliste[i][1]) continue;//Wenn kein Neubetreuer wird der Dienst abgewiesen

if(anwesenheit[i][j]){//Es wird getestet ob die Person an dem Tag anwesend ist

if(Attributliste[i][1] && nbtest(&ergebnis[0][0][0],&Attributliste[0][0], anzahl,dauer,dienste,j, k)) continue;//keine zwei Neubetreuer an einem dienst

if((k==2 || k==3) && j>0 && ((ergebnis[i][j-1][2] || ergebnis[i][j-1][3]) || (ergebnis[i][j+1][2] || ergebnis[i][j+1][3]))){ continue;}//Nachttwachen werden nicht an leut vergeben die Nachtwache hatten

if(j==0 && (k==2 || k==3) && (ergebnis[i][j+1][2] || ergebnis[i][j+1][3])) continue;//Nachttwachen werden nicht an leut vergeben die Nachtwache haben werden wegen zufälliger Verteilung

if(j>0 && k==0 && ((ergebnis[i][j-1][2] || ergebnis[i][j-1][3]) || (ergebnis[i][j+1][2] || ergebnis[i][j+1][3]))) continue;//Es werden keine Tagesleitungen an leute vergeben die Nachtwache hatten

if(j==12 && (k==2 || k==3) && !Attributliste[i][2]) continue; //Wenn kein Schaffer, so wird am letzten Tag keine Nachtwache vergeben.
if(ergebnis[i][dauer][k]) continue;//schon einmal den Dienst gehabt
if(!quersumme(ergebnis[i][j],dienste)){//Es wird getestet ob die Person bereits einen Dienst an diesem Tag hat
int Tageszaeler=0;
for(int l=0; l<anzahl;l++)
		Tageszaeler+=ergebnis[l][j][k];
if(Tageszaeler!=2){//Es wird getetstet ob der Dienst an diesem tag bereits vergeben ist
//Dienste wird gesetzt und der Dienstzähler erhöht
	ergebnis[i][j][k]=1;
	ergebnis[i][dauer][k]+=1;
	}}}
count++;

}
//Sicherheitskopie des bisherigen ergebnis
copy(&cpergebnis[0][0][0],&ergebnis[0][0][0],anzahl,dauer,dienste);
//Variable die die Fahrdienste zählt die an Fahrer vergeben sind
int fahrdienst=0;


//**********************Alle Betreuer werden vergeben*********************
while(test(&ergebnis[0][0][0],anzahl,dienste,dauer,&Attributliste[0][0])){//die Schleife endet wenn ein passendes ergebnis gefunden wurde
//Zufallszahlen werden gezogen um einer Person einen Dienst zuzuweisen
if(count>1000000){count=0;fahrdienst=0;copy(&ergebnis[0][0][0],&cpergebnis[0][0][0],anzahl,dauer,dienste);}
int i = rand() % anzahl ;
int j = rand() % dauer-1 ;
int k = rand() % dienste ;

if(anwesenheit[i][j]){//Es wird getestet ob die Person an dem Tag anwesend ist

if(j==12 && (k==2 || k==3) && !Attributliste[i][2]) continue; //Wenn kein Schaffer, so wird am letzten Tag keine Nachtwache vergeben.

if(fahrdienst!=13){//Fahrdienste werden zuerst an Fahrer verteilt

if(k==1 && !Attributliste[i][4]) continue;//Fahrer werden zuerst verteilt
fahrdienst++;
}

if(Attributliste[i][1] && nbtest(&ergebnis[0][0][0],&Attributliste[0][0], anzahl,dauer,dienste,j, k)) continue;//keine zwei Neubetreuer an einem dienst

if(j>0 && k==1 && ((ergebnis[i][j-1][2] || ergebnis[i][j-1][3]) || (ergebnis[i][j+1][2] || ergebnis[i][j+1][3]))){continue;}//Fahrdienste werden nicht an leut vergeben die Nachtwache hatten

if(j>0 && (k==2 || k==3) && ((ergebnis[i][j-1][2] || ergebnis[i][j-1][3]) || (ergebnis[i][j+1][2] || ergebnis[i][j+1][3]))) continue;//Nachttwachen werden nicht an leut vergeben die Nachtwache hatten



if(j==0 && (k==2 || k==3) && (ergebnis[i][j+1][2] || ergebnis[i][j+1][3])) continue;//Nachttwachen werden nicht an leut vergeben die Nachtwache haben werden wegen zufälliger Verteilung

if(j>0 && k==0 && ((ergebnis[i][j-1][2] || ergebnis[i][j-1][3]) || (ergebnis[i][j+1][2] || ergebnis[i][j+1][3]))) continue;//Es werden keine Tagesleitungen an leute vergeben die Nachtwache hatten

if((Attributliste[i][1]==0) && Attributliste[i][0]==k) continue;//Wenn kein Neubetreuer wird der Dienst abgewiesen wenn nicht erwünscht

if(ergebnis[i][dauer][k]<2){//Personen können maximal 2 mal den Dienst erhalten
if(!quersumme(ergebnis[i][j],dienste)){//Es wird getestet ob die Person bereits einen Dienst an diesem Tag hat

int Tageszaeler=0;
for(int l=0; l<anzahl;l++)
		Tageszaeler+=ergebnis[l][j][k];
if(Tageszaeler!=2){//Es wird getetstet ob der Dienst an diesem tag bereits vergeben ist
//Dienste wird gesetzt und der Dienstzähler erhöht
	ergebnis[i][j][k]=1;
	ergebnis[i][dauer][k]+=1;
	}}}}
//Iterationszählung wird erhöht
count++;
}

//Ausgabedatei wird geöffent
std::ofstream Daten("Dienstplan.csv");
//linke obere Zelle leer
Daten << ",";
//Die Wochentage werden in die Tabelle einegtragen
for(int tag=0;tag<dauer;tag++){
		switch(tag%7){
		case 0: Daten << "Freitag,";break;
		case 1: Daten << "Samstag,";break;
		case 2: Daten << "Sonntag,";break;
		case 3: Daten << "Montag,";break;
		case 4: Daten << "Dienstag,";break;
		case 5: Daten << "Mittwoch,";break;
		case 6: Daten << "Donnerstag,";break;
		}
}
//in die nächste Zeile gehen 
Daten << '\n';
//Es werden die Daten der Betreuer eingetragen
for(int person=0;person<anzahl;person++){
	Daten << Personen[person] << ",";
	for(int tag=0;tag<dauer;tag++){
		if(ergebnis[person][tag][0]){ Daten <<  "Tagesleitung,";continue;}
		if(ergebnis[person][tag][1]){ Daten <<  "Fahrdienst,";continue;}
		if(ergebnis[person][tag][2]){ Daten <<  "1.Nachwache,";continue;}
		if(ergebnis[person][tag][3]){ Daten <<  "2.Nachtwache,";continue;}
		Daten << ",";
	}
	Daten << '\n';
}
Daten.close();


//Programm zu ende
return 0;
}





int ntest(int *ergebnis, int anzahl, int dienste, int dauer, int *Attribute){
//Alle Neubetreuer müssen jeden Dienst einmal gehabt haben
for(int l=0;l<anzahl;l++)
	for(int k=0;k<dienste;k++){
	if(!Attribute[5*l+1]) break;
	if(Attribute[5*l+1] && ergebnis[dienste*(dauer+1)*l+dienste*dauer+k]<1){return 1;}
	}


return 0;


}

int test(int *ergebnis, int anzahl, int dienste, int dauer, int *Attribute){//die Testfunktion die entscheidet ob eine Konstellation funktioniert

//Es wird getestet ob auch alle Dienste an allen Tagen vergeben sind
for(int l=0;l<dauer-1;l++)
	for(int k=0;k<dienste;k++){
		int testsum=0;
		for(int m=0;m<anzahl;m++)
			testsum+=ergebnis[k+l*dienste+m*dienste*(dauer+1)];
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




void fullergebnis(int *ergebnis,int anzahl, int dienste, int dauer){
//ergebnis wird mit Nullen vollgestopft
for(int i=0; i<anzahl;i++)
	for(int j=0; j<dauer+1;j++)
		for(int k=0;k<dienste;k++)
			ergebnis[i*dienste*(dauer+1)+j*dienste+k]=0;
}

void copy(int *array1, int *array2,int anzahl,int dauer,int dienste)
{//Das Array 1 wird zu array2
for(int i=0;i<anzahl;i++)
	for(int j=0;j<dauer+1;j++)
		for(int k=0;k<dienste;k++)
			array1[(dauer+1)*dienste*i+dienste*j+k]=array2[(dauer+1)*dienste*i+dienste*j+k];
}

int nbtest(int *ergebnis,int *Attributliste,int anzahl,int dauer,int dienste,int tag, int dienst){//Ein test um zu prüfen ob bereits ein Neubetreuer diesen Dienst an diesem Tag hat
for(int i=0;i<anzahl;i++)
	if(ergebnis[dienste*(dauer+1)*i+tag*dienste+dienst] && Attributliste[anzahl*i+1]) return 1;
return 0;





}





















