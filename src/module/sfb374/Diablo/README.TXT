README-file zur Diffusionsrechnung

Folgende Dateien m�ssen f�r eine Diffusionsrechnung vorhanden sein:
Diffusionskoeff
Martensitdaten
Parameter
ZTA
Zwischengefuege

Um f�r mehr als 5500 Knoten die H�rte berchnen zu k�nnen mu� in den
folgenden Dateien die Feldgr��e der angegebenen Variablen auf den gw�nschten
Wert gesetzt werden. Es mu� allerdings sichergestellt sein, da� gen�gend
Arbeitspeicher vorhanden ist. Nach der �nderung mu� das Programm neu
compiliert werden. Dies kann mit 'make' geschehen. Make ben�tzt das
beigef�gte 'Makefile'.

Zu �ndernde Dateien     Variablen

main.f                  MS, MF, DTKRIT, HMMART, HAUST, HZWI, NNDMAX
hard.f                  MS, MF, DTKRIT, HMMART, HAUST, HZWI, NNDMAX
prep.f                  XND, YND, ZND, NODEID, IDS, Zeile 416
rdmart.f                MS, MF, DTKRIT, HMMART, HAUST
rdzw.f                  HZWI
wrtver.f                MS, MF, DTKRIT, HMMART, HAUST
wrxcel.f                MS, MF, DTKRIT, HMMART, HAUST, HZWI


Nun m�ssen in der Datei 'Parameter' die Parameter wie gew�nscht gesetzt
werden.

Eine Beschreibung, was die einzelnen Subroutines machen folgt:
main.f
Hauptprogramm

dif1dim.f
C=======================================================================
C     Vorbereitung der eindimensionalen Diffusionsrechnung
C     ------------------------------------------------------------------

difkug.f
C=======================================================================
C     kugelymmetrische eindimensionalen Diffusionsrechnung
C     ------------------------------------------------------------------

diflin.f
C=======================================================================
C     lineare eindimensionalen Diffusionsrechnung
C     ------------------------------------------------------------------

hard.f
C=======================================================================
C     H�rtewert der Mikrostruktur bestimmen
C     ------------------------------------------------------------------
C     F�r jeden Punkt der Mikrostruktur wird aufgrund der erreichten
C     C-Konzentr. unter Beachtung der Abk�hlkurve und unter Verwendung
C     der Martensit- und Zwischengef�gedaten der erreichte H�rtewert
C     errechnet. Der resultierende H�rtewert der Mikrostruktur wird als
C     Mittelwert aller H�rtewerte der Mikrostrukturknoten bestimmt.
C     ------------------------------------------------------------------

prep.f
C=======================================================================
C     FIDAP-Ausgabedatei "temp.FIOUT" aufbereiten
C     ------------------------------------------------------------------
C     Liest aus der FIDAP-Ausgabedatei "???", f�r welche MAKROSKOPISCHEN
C     Knoten die H�rteberechnung erfolgen soll.
C     Der Array NODEID(i) wird mit den Knoten-"ID"s (= FIDAP-Knoten-
C     nummern) dieser Knoten belegt, die Arrays XND(i), YND(i), ZND(i)
C     mit den Koordinaten der Knoten.
C     Die Datenzeilen dieser Knoten werden aus "temp.FIOUT" nach
C     "T_VERLAEUFE" kopiert.
C     Die zugeh�rigen Zeiten werden im Array TAU[j] gespeichert.
C     Die Anzahl zu bearbeitender Knoten NNODES sowie die Anzahl
C     vorhandener Zeitst�tzstellen NTAU wird bestimmt.
C     ------------------------------------------------------------------

rdabk.f
C=======================================================================
C     Abk�hlkurve einlesen
C     ------------------------------------------------------------------
C     Liest aus "T_VERLAUF" die Abk�hlkurve (ab unterschreiten von Ac3x)
C     ein, und speichert sie als Array dT/dt = f(T) im Bereich
C     1K <= T <= Tschmelz
C     Der Array wird wie folgt belegt:
C     1    <= T <= Tx      :  dT/dt = const. = 0
C     Tx   <= T <= Tmin    :  linear ansteigend von 0 nach dT/dt(Tmin)
C     Tmin <= T <= Ac3x    :  linear interpoliert zw. St�tzstellen
C     Ac3x <= T <= Tschmelz:  dT/dt = const. = dT/dt(Ac3x)
C     Tx.....Abschrecktemperatur
C     Tmin...niedrigste eingelesene Temperatur
C     Ac3x...Ac3-Temperatur f�r t -> unendlich
C     Ist die niedrigste gefundene Temperatur kleiner als Tx, so wird Tx
C     auf Tmin gesetzt
C     ------------------------------------------------------------------

rdcc1d.f
C=======================================================================
C     liest aus 'CCOUT' C-Konzentrationen nach der Diff.-Rechnung (1dim)
C     ablauf vergleiche rdcout.f
C     ------------------------------------------------------------------

rdcout.f
C=======================================================================
C     C-Konzentrationswerte nach Diffusion einlesen
C     ------------------------------------------------------------------
C     Liest aus der FIDAP-Ausgabedatei "diff.FIOUT" alle errechneten
C     C-Konzentrationswerte ein, jedoch maximal NNDMAX Werte.
C     Mit CCMIN und CCMAX k�nnen der erlaubte Minimal- und Maximalwert
C     vorgegeben werden. Werte darunter oder dar�ber werden auf CCMIN
C     bzw. CCMAX gesetzt.
C     ------------------------------------------------------------------

rdmart.f
C=======================================================================
C     Martensitdaten einlesen
C     ------------------------------------------------------------------
C     Liest die Kurven Ms, Mf, (dT/dt)krit, Hm, Ha = f(cC) in COMMON-
C     Block-Arrays. Laufvariable dieser Arrays ist die normierte, ganz-
C     zahlige, C-Konzentration CCNORM
C         1 <= CCNORM <= CCRESM
C     Die Kurven m�ssen mindestens im Wertebereich
C         0 <= cC <= CCMAX
C     vorliegen. Aus (dT/dt)krit wird die maximale kritische Abschreck-
C     geschwindigkeit bestimmt.
C     ------------------------------------------------------------------

rdparm.f
C=======================================================================
C     Parameterdatei einlesen
C     ------------------------------------------------------------------

rdzta.f
C=======================================================================
C     ZTA-Diagramm einlesen
C     ------------------------------------------------------------------

rdzw.f
C=======================================================================
C     H�rtewerte f�r Zwischenstufengef�ge einlesen
C     ------------------------------------------------------------------
C     Liest das Diagramm Hzw = f((dT/dt),cC) in einen COMMON-Block-Array
C     (Matrix). Laufvariable sind die normierten, ganzzahlg., Variablen
C     DTNORM: Abschreckgeschwindigkeit
C         1 <= DTNORM <= DTRESZ
C     CCNORM: C-Konzentration
C         1 <= CCNORM <= CCRESZ
C     Das Diagramm mu� mindestens im Wertebereich
C         0 <=  cC   <= CCMAX
C              dT/dt <= DTMAX
C     vorliegen. DTMAX ist der Maximalwert (dT/dt)kritMax aus der in den
C     Martensitdaten gegebenen Kurve (dT/dt)krit = f(cC). Die H�rtewerte
C     f�r C-Konzentrationswerte mit kleinerem (dT/dt)krit m�ssen also
C     entsprechend extrapoliert sein.
C     F�r (dT/dt)min > 0 wird von (dT/dt)=0 bis (dT/dt)min mit dem
C     jeweiligen H�rtewert H((dT/dt)min,cC) aufgef�llt.
C     ------------------------------------------------------------------

ipol1p.f
C=======================================================================
C     Linearinterpolation
C     ------------------------------------------------------------------

ipol2p.f
C=======================================================================
C     Interpolation einer zweiparametrigen Funktion
C     ------------------------------------------------------------------

tridag.f
C=======================================================================
C     Loest eine Tridiagonal-Matrix
C     ------------------------------------------------------------------

wrfiin.f
C=======================================================================
C     FIDAP-Eingabedatei "FDREAD.diff" f�r aktuellen Knoten erstellen
C     wird nur f�r zweidimensionale Diffusionsrechnung ben�tigt
C     ------------------------------------------------------------------

wrtver.f
C=======================================================================
C     Datei "T_VERLAUF" erstellen
C     ------------------------------------------------------------------
C     Bereitet die Temperaturkurve f�r den aktuellen makroskopischen
C     Knoten aus den Angaben in "T_VERLAEUFE" auf.
C     ------------------------------------------------------------------

wrxcel.f
C=======================================================================
C     Materialdaten-Arrays in Excel-Dateien speichern
C     ------------------------------------------------------------------
