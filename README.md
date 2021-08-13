# Inhalt

[Änderungshistorie - 2 -](#_Toc72400214)

[1 Das UMB Protokoll - 3 -](#_Toc72400215)

[2 Die UMB Bibliothek - 3 -](#die-umb-bibliothek)

[3 Lieferumfang - 4 -](#lieferumfang)

[4 Inbetriebnahme - 5 -](#inbetriebnahme)

[5 Verwendung - 5 -](#verwendung)

[5.1 System-Anbindung - 5 -](#system-anbindung)

[5.2 Initialisierung - 8 -](#initialisierung)

[5.3 Testprogramm - 9 -](#testprogramm)

[6 Hinweise zum Firmware-Update - 10 -](#hinweise-zum-firmware-update)

# Änderungshistorie

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 18%" />
<col style="width: 69%" />
</colgroup>
<thead>
<tr class="header">
<th>Version</th>
<th>Datum</th>
<th>Änderungen</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td>V0.1</td>
<td>12.03.2021</td>
<td>Erste Version</td>
</tr>
<tr class="even">
<td>V0.2</td>
<td>22.03.2021</td>
<td><p>Screenshots angepasst</p>
<p>Erläuterungen zur UMB Spezifikation</p></td>
</tr>
<tr class="odd">
<td>V0.3</td>
<td>19.04.2021</td>
<td>64-bit Versionen der Bibliothek</td>
</tr>
<tr class="even">
<td>V0.4</td>
<td>06.05.2021</td>
<td>64-bit Version für ARM</td>
</tr>
<tr class="odd">
<td>V0.5</td>
<td>20.05.2021</td>
<td>Tabelle mit unterstützten UMB Befehlen</td>
</tr>
</tbody>
</table>

# Das UMB Protokoll

Das UMB-Protokoll ist ein von der Firma Lufft spezifiziertes,
offengelegtes Binärprotokoll zur Konfiguration und Datenabfrage von
Messgeräten.

Die aktuelle Version der Spezifikation findet sich im Download-Bereich
der Homepage [www.Lufft.de](http://www.Lufft.de). Das Dokument enthält
alle Informationen zum Frame-Aufbau und zeitlichem Ablauf sowie eine
detaillierte Beschreibung aller Befehle.

# Die UMB Bibliothek

Die Bibliothek ist in der Sprache C geschrieben und für Windows sowie
für Linux verfügbar.

Sie verwendet keine dynamische Speicherallokation.

In der Bibliothek sind die in Tabelle 1 aufgeführten Befehle des UMB
Protokolls implementiert.

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 64%" />
<col style="width: 21%" />
</colgroup>
<tbody>
<tr class="odd">
<td><strong>&lt;cmd&gt;</strong></td>
<td><strong>Beschreibung</strong></td>
<td><strong>Bibliothek V0.4</strong></td>
</tr>
<tr class="even">
<td>20h</td>
<td>Hard- und Softwareversion</td>
<td></td>
</tr>
<tr class="odd">
<td>21h</td>
<td>EEPROM auslesen</td>
<td></td>
</tr>
<tr class="even">
<td>22h</td>
<td>EEPROM programmieren</td>
<td></td>
</tr>
<tr class="odd">
<td>23h</td>
<td>Onlinedatenabfrage</td>
<td></td>
</tr>
<tr class="even">
<td>24h</td>
<td>Offlinedatenabfrage</td>
<td></td>
</tr>
<tr class="odd">
<td>25h</td>
<td>Reset / Default</td>
<td></td>
</tr>
<tr class="even">
<td>26h</td>
<td>Statusabfrage</td>
<td></td>
</tr>
<tr class="odd">
<td>27h</td>
<td>Uhrzeit / Datum setzen</td>
<td></td>
</tr>
<tr class="even">
<td>28h</td>
<td>Uhrzeit / Datum auslesen</td>
<td></td>
</tr>
<tr class="odd">
<td>29h</td>
<td>Testbefehl</td>
<td></td>
</tr>
<tr class="even">
<td>2Ah</td>
<td>Monitor</td>
<td></td>
</tr>
<tr class="odd">
<td>2Bh</td>
<td>Protokollwechsel</td>
<td></td>
</tr>
<tr class="even">
<td>2Ch</td>
<td>letzte Fehlermeldung</td>
<td></td>
</tr>
<tr class="odd">
<td>2Dh</td>
<td>Geräteinformation</td>
<td>()</td>
</tr>
<tr class="even">
<td>2Eh</td>
<td>Reset mit Verzögerung</td>
<td></td>
</tr>
<tr class="odd">
<td><strong>&lt;cmd&gt;</strong></td>
<td><strong>Beschreibung</strong></td>
<td><strong>Bibliothek V0.4</strong></td>
</tr>
<tr class="even">
<td>2Fh</td>
<td>Onlinedatenabfrage mehrere Kanäle</td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td></td>
<td></td>
</tr>
<tr class="even">
<td>30h</td>
<td>neue Geräte-ID dauerhaft setzen<br />
(verc 1.0)</td>
<td></td>
</tr>
<tr class="odd">
<td>30h</td>
<td>neue Geräte-ID temporär setzen<br />
(verc 1.1)</td>
<td></td>
</tr>
<tr class="even">
<td>36h</td>
<td>UMB-Tunnel</td>
<td></td>
</tr>
<tr class="odd">
<td>37h</td>
<td>Firmware übertragen</td>
<td></td>
</tr>
<tr class="even">
<td>38h</td>
<td>Binärdaten übertragen</td>
<td></td>
</tr>
<tr class="odd">
<td></td>
<td></td>
<td></td>
</tr>
<tr class="even">
<td>40h – 7Fh</td>
<td>reserviert für gerätespezifische Kommandos</td>
<td></td>
</tr>
<tr class="odd">
<td>80h – 8Fh</td>
<td>reserviert für Entwicklung</td>
<td></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
</tr>
<tr class="odd">
<td>F0h</td>
<td>EEPROM programmieren mit PIN</td>
<td></td>
</tr>
</tbody>
</table>

Tabelle 1 Befehle des UMB Protokolls, die von der Bibliothek unterstützt
werden

Mit dem Befehl ‚Geräteinformation‘ (2Dh) kann eine Vielzahl von
Geräte-Eigenschaften abgefragt werden. Davon werden bislang die in
Tabelle 2 angegebenen Sub-Befehle unterstützt.

|             |                                                                  |                     |
|-------------|------------------------------------------------------------------|---------------------|
| **\<info>** | **Beschreibung**                                                 | **Bibliothek V0.4** |
| 10h         | Gerätebezeichnung                                                |                     |
| 11h         | Gerätebeschreibung                                               |                     |
| 12h         | Hard- und Softwareversion                                        |                     |
| 13h         | erweiterte Versions-Info                                         |                     |
| 14h         | Größe des EEPROM                                                 |                     |
| 15h         | Anzahl verfügbare Kanäle                                         |                     |
| 16h         | Nummern der Kanäle                                               |                     |
| 17h         | Anzahl der gerätespezifischen Versionsinformation-Slots auslesen |                     |
| 18h         | Gerätespezifische Versionsinformationen auslesen                 |                     |
| **\<info>** | **Beschreibung**                                                 | **Bibliothek V0.4** |
| 20h         | Messgröße des Kanals                                             |                     |
| 21h         | Messbereich des Kanals                                           |                     |
| 22h         | Messeinheit des Kanals                                           |                     |
| 23h         | Datentyp des Kanals                                              |                     |
| 24h         | Messwerttyp                                                      |                     |
|             |                                                                  |                     |
| 30h         | komplette Kanalinfo                                              |                     |
| 40h         | Anzahl der IP-Interfaces                                         |                     |
| 41h         | IP-Information                                                   |                     |

Tabelle 2 Sub-Befehle des Befehls ‚Geräteinformation‘, die von der
Bibliothek unterstützt werden

# Lieferumfang

Der Ordner „**lufft**“ enthält alle Dateien, die zur Verwendung der UMB
Bibliothek benötigt werden:

-   Die Software-Bibliotheken für Windows bzw. Linux / Linux auf ARM:

|            | **windows**             | **linux**             | **Linux / ARM**          |
|------------|-------------------------|-----------------------|--------------------------|
| **64 bit** | UmbControllerLib.lib    | libUmbController.a    | libUmbControllerArm_64.a |
| **32 bit** | UmbControllerLib_32.lib | libUmbController_32.a | libUmbControllerArm_32.a |

-   Die Header-Dateien zur Verwendung der Bibliothek:

> **UmbControllerLib.h**: Schnittstelle der Bibliothek
>
> **Umb_Types.h**: Allgemeine Typdefinitionen

Im Ordner „**src**“ findet man Dateien mit Beispielen für die Anbindung
der Bibliothek an das eigene System:

-   **UmbCtrlTest.cpp**: Testprogramm zur Veranschaulichung der
    Funktionsweise

-   **ComWin.c/.h**: Beispiel-Implementierung zur Anbindung unter
    Windows

-   **ComLinux.c/.h**: Beispiel-Implementierung zur Anbindung unter
    Linux

Der Ordner „**win**“ enthält nicht-Lufft-eigene Dateien, die im
Testprogramm bzw. in den Beispiel-Implementierungen unter Windows
verwendet werden. Hier sind die in den jeweiligen Quelldateien
festgelegten Nutzungsbedingungen zu beachten.

Im Ordner „**examples**“ befindet sich ein Beispiel für die Installation
der Bibliothek auf einem RaspberryPi. Weitere Beispiele sind geplant.

# Inbetriebnahme

Für die Verwendung der UMB Bibliothek müssen die beiden Header-Dateien
Umb_Types.h und UmbControllerLib.h in das eigene Projekt kopiert werden.

Abhängig vom verwendeten System (Windows, Linux, Linux auf ARM) wird die
zugehörige Bibliothek benötigt, siehe auch Kapitel 3.

Die Installationsanleitung für einen RaspberryPi ist separat in der
Datei README.txt im Verzeichnis /examples/RaspberryPi nachzulesen.

# Verwendung

Der jeweils aktuelle Funktionsumfang der Bibliothek ist der
Schnittstellendatei UmbControllerLib.h zu entnehmen.

## System-Anbindung

Die Ansteuerung der seriellen Schnittstelle erfolgt über
Funktionszeiger, die in der Struktur UMB_CTRL_COM_FUNCTION_T definiert
sind, siehe Abbildung 1.

<img src="./media/image2.png" style="width:6.29931in;height:2.73542in" />

Abbildung 1 Struktur mit Funktionszeigern zur Ansteuerung der seriellen
Schnittstelle

Die Funktionszeiger (\*pfnInit) und (\*pfnDeinit) sind optional und
können z. B. verwendet werden, um die serielle Schnittstelle zu öffnen
bzw. zu schließen. Wird dies aber bereits an anderer Stelle getan,
können die beiden Funktionszeiger auch auf NULL gesetzt werden.

Alle anderen Funktionszeiger sind obligatorisch und müssen implementiert
werden.

Die Funktionszeiger (\*pfnUse) und (\*pfnUnuse) sind für den Schutz von
Variablen oder Programmsegmenten durch Semaphoren vorgesehen. In den
Beispiel-Implementationen führen diese Funktionen derzeit keinen aktiven
Code aus.

Das Handle \*pUserHandle kann benutzt werden, um anwenderspezifische
Daten an die Callback-Funktionen durchzureichen. So werden in den
Beispiel-Implementierungen comWin.cpp und ComLinux.cpp alle Daten, die
im laufenden Betrieb benötigt werden, in einer Struktur COM_HANDLE_T
zusammengefasst. \*pUserHandle zeigt auf die Adresse eines solchen
Datensatzes, wodurch diese Daten dann in den Callback-Funktionen
verfügbar sind. Abbildung 2 zeigt die Initialisierung eines
\*pUserHandle, Abbildung 3 die spätere Anwendung.

<img src="./media/image3.png" style="width:6.29931in;height:1.86806in" />

Abbildung 2 Initialisierung eines \*pUserHandle

<img src="./media/image4.png" style="width:6.10053in;height:2.80858in" />

Abbildung 3 Verwendung eines \*pUserHandle

Die Module ComLinux.cpp/.h sowie ComWin.cpp/.h zeigen beispielhaft, wie
die Zuweisung dieser Funktionszeiger umgesetzt werden kann:

In ComLinux ist die Ansteuerung der seriellen Schnittstelle direkt
implementiert, ComWin dagegen verwendet Fremdsoftware (SerialPort.h),
für die nur noch die zur UMB Bibliothek kompatiblen Wrapper-Funktionen
bereitgestellt werden, siehe auch Abbildung 4.

<img src="./media/image5.png" style="width:10.90625in;height:4.80347in" />

Abbildung 4 Implementierungsbeispiele zur Ansteuerung der seriellen
Schnittstelle:  
links: Beispiel für Linux, manuelle Implementierung  
rechts: Beispiel für Windows, Verwendung bereits existierender
Implementierung

## Initialisierung

Die Initialisierung der UMB Bibliothek umfasst 3 Punkte:

-   Zuweisung der Funktionszeiger zur Ansteuerung der seriellen
    Schnittstelle

> Der Übersicht halber erfolgt die Zuweisung der benötigten
> Funktionszeiger am besten in einer eigenen, vom Anwender definierten
> Funktion, siehe hierzu Abschnitt 5.1.

-   Bereitstellung des Handles

> Die UMB Bibliothek verwendet keine dynamische Speicherallokation.
> Daher muss der Anwender den Speicher für die verwendeten
> Bibliotheks-Instanzen bereitstellen.
>
> Dieses Handle wird beim Aufruf aller weiteren Funktionen der UMB
> Bibliothek benötigt.

-   Aufruf der Initialisierungsfunktion der Bibliothek

> Der Initialisierungsfunktion UmbCtrl_Init() müssen das Handle sowie
> die Variable, die die Funktionszeiger enthält, übergeben werden.

Abbildung 5 zeigt exemplarisch die Initialisierungssequenz, Abbildung 6
die Abfrage von Geräte-Namen und -Status.

<img src="./media/image6.png" style="width:5.3588in;height:3.55031in" />

Abbildung 5 Initialisierung der UMB-Bibliothek

<img src="./media/image7.png" style="width:4.66707in;height:4.63373in" />

Abbildung 6 Abfrage von Geräte-Name und Geräte-Status

## Testprogramm

Das Testprogramm in UmbCtrlTest.cpp zeigt beispielhaft die Verwendung
der UMB Controller Bibliothek. Vor Verwendung des Testprogramms müssen
alle mit ‚TODO‘ gekennzeichneten Stellen im main()-Programm an das
eigene Testsystem angepasst werden . Diese sind

-   Präprozessor-Definition \_USE_NCURSES, um die graphische
    Fortschritts-Anzeige bei der Update-Funktion unter Linux nutzen zu
    können (Näheres siehe unten):

> #define \_USE_NCURSES

-   Verwendete serielle Schnittstelle, z. B.

> char serialIf\[\] = { "3" };
>
> Hinweis:
>
> Unter Linux muss hier der gesamte Pfad der seriellen Schnittstelle
> angegeben werden, z. B. char serialIf\[\] = { "/dev/tty03" };

-   Baudrate der seriellen Schnittstelle, z. B.

> comConfig.baudrate = 19200;

-   UMB-Adresse des UMB-Gerätes, mit dem kommuniziert werden soll, z. B.

> umbAddress.deviceId = 0x01; // device id: 1
>
> umbAddress.classId = 0x70; // class id: 7 = weather station

-   Pfad und Name der Firmware Datei, z. B.

> char fileName\[\] = {
> "C:\\\\Projekte\\\\UmbController\\\\WS100_update.bin" };

Die auskommentierten Funktionen (siehe Abbildung 7) werden am besten
einzeln und nach Bedarf in das Testprogramm übernommen, um mit der
jeweiligen Funktionalität vertraut zu werden.

<img src="./media/image8.png" style="width:2.94192in;height:1.31678in" />

Abbildung 7 Beispielfunktionen zur Verwendung der UMB-Bibliothek

**Zur Präprozessor-Definition \_USE_NCURSES**

Die Beispielimplementierung firmwareUpdate() verwendet eine grafische
Darstellung des Update-Fortschritts, die unter Linux das Paket ncurses
voraussetzt. Dieses muss z. B. auf einem RaspberryPi manuell installiert
werden, da es nicht über raspbian-stretch-lite vorinstalliert ist.

Eine Anleitung hierfür findet sich in der Datei README.txt im
Verzeichnis /examples/RaspberryPi.

Soll diese Fortschrittsanzeige genutzt werden, muss man bei
installiertem Paket ncurses die Präprozessor-Definition \_USE_NCURSES
setzen. Ist diese Anweisung dagegen auskommentiert, wird statt der
graphischen eine einfache Fortschrittsanzeige verwendet, die ohne
weitere Pakete auskommt.

# Hinweise zum Firmware-Update

Ältere UMB-Geräte wie WSx00, Ventus, Anacon etc. verwenden eine
Update-Datei im .mot-Format. Diese können nicht über das UMB-Protokoll,
sondern ausschließlich über Hexload auf ein Gerät übertragen werden.

Für die neue Generation der UMB-Geräte wie z. B. MARWIS, WS1000, WS100,
SHM31 u. a. wurde daher das Datei-Format .bin definiert, das auch ein
Firmware-Update über UMB ermöglicht.

-   Firmware-Updates über das UMB-Protokoll sind nur für die UMB-Geräte
    möglich, deren Update-Datei im .bin-Format vorliegt.

