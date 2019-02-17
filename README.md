# Dienstplan Automatisierer

Der Dienstplan wird mit diesem Programm automatisch erstellt und in die Datei Dienstplan.csv ausgegeben.
Der Benutzer muss folgendes tun, um das Programm zu verwenden.

1. Das Programm durch das Ausführen des **make** Befehls kompilieren.
2. Die csv Datei **template.csv** ausfüllen mit den Daten der Betreuer, Anwesenheit und Attribute. Die Dienste haben folgende Nummern, die in die Spalte der nicht gemochten Dienste (Diese werden nicht vergeben wenn es sich nicht um einen Neubetreuer handelt) eingetragen werden.
	*  Tagesleitung = 0
	*  Fahrdienst = 1
	*  1\. Nachtwache = 2
	*  2\. Nachtwache = 3

	Es müssen außerdem die Auflugsbeauftragten in die "Ausflug"-Spalte eingetragen werden.
Sowie mindestens 6 Schaffer in der "Schaffer"-Spalte, die die Nachtwachen vor dem Abbau übernehmen und die Tagesleitung am Abbau.
3. Das Programm aufrufen durch `./Dienstplan.exe template.csv`.
4. Der fertige Dienstplan ist nun in der Datei **Dienstplan.csv** enthalten.



