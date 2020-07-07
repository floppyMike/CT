# Ampel Simulation

## Klassendiagramm
![KlassenDiagramm](https://github.com/floppyMike/CT/blob/Panic_Mode/docs/Klassendiagramm.svg)

Das Diagramm oben beschreibt die Struktur des Programmes.
`Setup`, `Compile` und `Simulation` sind die Kern Zustände des Programmes. `Setup` handelt die einstellungen von der Simulation. `Compile` handelt das Bearbeiten der Daten von `Setup`. `Simulation` veranschaulicht die Daten von `Setup`. Die Daten werden in `TrafficNodeDB`, `NodeDB`, `LinkDB`. Die Handlung der ausgesuchten Ampel wird über `Selected` gemacht.

## Use Case Diagramm
![UseCase](https://github.com/floppyMike/CT/blob/Panic_Mode/docs/UseCase.svg)

Das Diagramm oben beschreibt die Möglichkeiten der Autos und User dar.
Die Autos werden während der Simulation den Zustand der Ampel befolgen. Während der Setup Phase hat der User die Möglichkeit die Ampeln auf der Fläche mit 'c' zu spawnen, mit 'p' Knotenpunkte erzeugen und mit Mouse Bewegung und Clicken die Pfade mit die jeweiligen Ampeln verbinden. 's' muss gedrückt werden um die Compiliation und Simulation zu starten.

## Ablaufdiagramm
![Activity](https://github.com/floppyMike/CT/blob/Panic_Mode/docs/Activity.svg)

Das Diagramm oben beschreibt den Ablauf der 3 Phasen.
Die Phasen `Setup` und `Simulation` laufen unendlich lang. `Setup` hört und reagiert nur auf Fenster Ereignisse. `Simulation` läuft selbstständig und reagiert nicht auf Fenster Ereignisse.

## Erstellung des Codes und der Diagramme
Zu Beginn des Projektes erstellte ich eine kleine Skizze vom Plan wie ich das Programm gestalte. Ich habe mich entschieden meinen [Bibliothek](https://github.com/floppyMike/CustomLibrary) zu benutzen, weil ich mit schon da sehr gut auskenne. Am Ende habe ich mich für das Phasen Konzept entschieden. Ich programmierte das Programm und habe es dann für eine Zeitlang gelassen. Ich habe während dessen an anderen Projekten gearbeitet. Dadurch ist leider dann am Ende mein Projekt veraltet geworden, weil mein [Bibliothek](https://github.com/floppyMike/CustomLibrary) wurder nach der Zeit geupdatet. Ich musste dann am Ende ein paar compatibility Updates machen. Ich habe auch dann die Diagramme erstellt mit dem Tool [Bouml](https://bouml.fr/).

## Probleme die Aufgetaucht sind
Am Anfang des ganzen sind mit nur kleine Debug Fehler passiert die schnell gepatch worden sind. Am Ende aber habe ich Probleme mit den jetzigen Programm bekommen. Zuerst sind die [Bibliothek](https://github.com/floppyMike/CustomLibrary) Schnittstellen outdatet und das Programm ist mit meiner Programmstil von führer programmiert geworden. Diese stört mich einbisschen, weil es in meinem jetzigen Perspektive unsauber und Problematisch ist. Aber wegen der wenigen Zeit die ich mir am Ende gelassen habe, hatte ich nicht genügend Zeit sie zu updaten.
Ich habe mir daher fest genommen auf der Branch [`master`](https://github.com/floppyMike/CT) weiter zu machen (der Abgabe Stand bleibt auf [`Panic_Mode`](https://github.com/floppyMike/CT/tree/Panic_Mode)). 

## Persönliches Resümee
Meiner Meinung nach ging das Projekt gut nur ich habe mir alles schwer gemacht. Ich hätte meinen [Bibliothek](https://github.com/floppyMike/CustomLibrary) mit der Subprojekt Feature von Git inkludieren sollen. Ich habe auch die Zeit zu sehr überschätzt. Ich habe auch erkannt, dass die anderen Leute nicht so viel C++ können oder garnicht obwohl sie ein paar Konzepte im Unterricht hatten. Ich denke ich hätte mehr Zeit benötigt die Leute die Basics von C++ beizubringen. Doch ich finde die Entscheidung um MFC zu benutzen nicht so toll, weil es nicht mit modernen C++ geschrieben ist, nicht cross-plattform ist und recht schwierig im Gegensatz zu .NET von C# ist. Ich wurde lieber C# für Windows Applikationen benutzen oder wenn es unbedingt C++ sein muss, dann würde ich [wxwidgets](https://www.wxwidgets.org/) benutzen. Es ist moderner und einfacher als MFC und es ist cross-plattform.
