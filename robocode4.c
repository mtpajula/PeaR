#pragma config(Sensor, S1,     etaluotain,     sensorEV3_IRSensor)
#pragma config(Sensor, S2,     variluotain,    sensorEV3_Color)
#pragma config(Sensor, S3,     kosketus,       sensorEV3_Touch)
#pragma config(Sensor, S4,     Gyroskooppi,    sensorEV3_Gyro, modeEV3Gyro_Rate)
#pragma config(Motor,  motorA,          Mkippi,        tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          Ma,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          Mb,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// === Asetukset ===
int SYKLI = 50; // moottorien kayttoaika
int PEHMEYS = 10; // Kiihdytyksen ja hidastuksen lisays
int NOPEUS = 100; // Matkanopeus
int KAANTONOPEUS = 30; // kaantymisen nopeus

// Abstrakti funktio, jonka kautta kaikki moottorikomennot ajetaan
void liiku(int b, int c) {
	motor[Ma] = b * -1;
	motor[Mb] = c * -1;
	wait1Msec(SYKLI);
	displayCenteredBigTextLine(6, "Kulma: %d", SensorValue(Gyroskooppi));
}

void kuljeEteen() {
	liiku(NOPEUS,NOPEUS);
}

void kuljeTaakse() {
	liiku(NOPEUS*-1,NOPEUS*-1);
}

// Kiihdytetaan
void kiihdyta(int k1) {
	int i = 0;
  while (i <= NOPEUS) {
  	liiku(i*k1,i*k1);
		i += PEHMEYS;
	}
	return;
}

// Hidastetaan
void hidasta(int k1) {
	int i = NOPEUS;
  while (i >= 0) {
  	liiku(i*k1,i*k1);
		i -= PEHMEYS;
	}
	return;
}

void kiihdytaEteen() {
	liiku(0,0);
	kiihdyta(1);
}

void hidastaEteen() {
	hidasta(1);
	liiku(0,0);
}

void kiihdytaTaakse() {
	liiku(0,0);
	kiihdyta(-1);
}

void hidastaTaakse() {
	hidasta(-1);
	liiku(0,0);
}

void peruuta() {
	int i;
	for (i = 1; i <= 7; i++) {
		kuljeTaakse();
	}

}

void kaanny(short kulma) {

	while (true) {

		// Kaantyminen valmis
		if (SensorValue(Gyroskooppi) > kulma-20 && SensorValue(Gyroskooppi) < kulma+20) {
			liiku(0,0);
			return;
		}

		// Kaaannytaan kohti tavoitekulmaa
		if (SensorValue(Gyroskooppi) > kulma) {
			liiku(KAANTONOPEUS,KAANTONOPEUS*-1);
		} else if (SensorValue(Gyroskooppi) < kulma) {
			liiku(KAANTONOPEUS*-1,KAANTONOPEUS);
		}

	}
}

void etene(short kulma) {

	while (true) {

		// Jos edessa jotain, lopetetaan eteneminen
		if (getIRDistance(etaluotain) < 20) {
			return;
		}

		// Eroa kaytetaan, kun paatetaan, kuinka jyrkasti korjataan
		int ero = abs(kulma - SensorValue(Gyroskooppi));

		// Jos gyro eroaa tavoitelinjasta
		if (SensorValue(Gyroskooppi) > kulma) {
			if (ero < 30) {
				// Jos ero on alle 30astetta, niin loiva kaannos
				liiku(NOPEUS,NOPEUS-30);
			} else {
				// Muuten jyrkka kaannos
				liiku(NOPEUS,NOPEUS/3);
			}
		} else if (SensorValue(Gyroskooppi) < kulma) {
			if (ero < 30) {
				liiku(NOPEUS-30,NOPEUS);
			} else {
				liiku(NOPEUS/3,NOPEUS);
			}
		} else {
			kuljeEteen();
		}

	}
}


void kaannyYmpari(short kulma) {
	wait1Msec(SYKLI*10);
	kaanny(kulma);
	wait1Msec(SYKLI*10);
}


void perilla() {

	wait1Msec(1000);
	playTone(500, 50);
	wait1Msec(1000);
	playTone(700, 50);
	wait1Msec(1000);
	playTone(500, 50);
	wait1Msec(1000);

	motor[Mkippi] = -100;
	wait1Msec(500);
	motor[Mkippi] = 0;

	wait1Msec(2000);

	motor[Mkippi] = 30;
	wait1Msec(500);
	motor[Mkippi] = 0;

	wait1Msec(2000);
}


/*
bool haistele() {

}
*/

void mene(short kulma) {

	displayCenteredBigTextLine(3, "kaanny");
	kaanny(kulma);
	displayCenteredBigTextLine(3, "kiihdytaEteen");
	kiihdytaEteen();
	displayCenteredBigTextLine(3, "etene");
	etene(kulma);
	displayCenteredBigTextLine(3, "hidastaEteen");
	hidastaEteen();
	displayCenteredBigTextLine(3, "kiihdytaTaakse");
	kiihdytaTaakse();
	displayCenteredBigTextLine(3, "peruuta");
	peruuta();
	displayCenteredBigTextLine(3, "hidastaTaakse");
	hidastaTaakse();

	/*
	// Vaihtoehtoinen tapa
	bool roskilla = haistele();

	if (roskilla) {
		perilla();
	} else {
		peruuta();
	}
	*/
}

void odotaKosketusta() {
	while (true) {
		// Tarkistetaan, että roska on laitettu kyytiin
		if (SensorValue[kosketus]) {
			return;
		}
		wait1Msec(SYKLI);
	}
}

task main()
{
	// Nollataan gyro robotin menosuunnan mukaiseksi
	setSensorMode(Gyroskooppi, modeEV3Gyro_Angle);
	resetGyro(Gyroskooppi);

	displayCenteredBigTextLine(1, "odotaKosketusta");
	odotaKosketusta();
	displayCenteredBigTextLine(1, "mene %d", 0);
	mene(0);
	displayCenteredBigTextLine(1, "mene %d", 90);
	mene(90);
	displayCenteredBigTextLine(1, "mene %d", 0);
	mene(0);
	displayCenteredBigTextLine(1, "kaannyYmpari %d", 180);
	kaannyYmpari(180);
	displayCenteredBigTextLine(1, "perilla");
	perilla();
}