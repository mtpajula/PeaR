#pragma config(Sensor, S1,     etaluotain,     sensorEV3_IRSensor)
#pragma config(Sensor, S2,     variluotain,    sensorEV3_Color)
#pragma config(Sensor, S3,     kosketus,        sensorEV3_Touch)
#pragma config(Sensor, S4,     Gyroskooppi,           sensorEV3_Gyro, modeEV3Gyro_Rate)
#pragma config(Motor,  motorA,          MotorA,        tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          MotorB,        tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          MotorC,        tmotorEV3_Large, PIDControl, encoder)

int tehtava = 0;
int nopeus = 0;

}

void liiku(int b,int c, int aika){
	motor[motorB] = b;
	motor[motorC] = c;
	wait1Msec(t);
	return;
}
/*void liiku(){

	if (getIRDistance(etaluotain) < 20){
			eteen += 1;
			return;
	}
	motor[motorB] = -100;
	motor[motorC] = -100;
	wait1Msec(100);

return;
}*/

/*void eteen(){
	//kiihdytä();
	liiku(100, 100, 50);

return;
}*/

void kiihdytaEteen(int k1, int k2) {
	int i = 0;
  while (i > -100) {
  	//eteen(i, 100);
  	liiku(i*k1,i*k2,60);
		i -= 10;
	}
	return;
}

void kiihdytaTaakse(){
	int i = -100;
	while (i < 0) {
		//eteen(i, 100);
		liiku(i/k1,i/k2,60);
		i += 10;

	return;
}

void eteen(int i, int aika){
		kiihdytaEteen();
		liiku(i, i, aika);
	return;
}
void kaanny(){
	kiihdytaTaakse();
	liiku(50, -50, 1000);

	return;
}
void hidasta(int k1, int k2) {
	int i = -100;
  while (i <= 0) {
  	//eteen(i, 100);
  	liiku(i*k1,i*k2,60);
		i += 10;
	}
	return;

void kaannaVasemmalle(){
	hidasta();
	liiku(50, 100, 1000);

	return;
}

void kaannaOikealle(){
	hidasta();
	liiku(100, 50, 1000);

	return;
}
roskilla(){
	hidastaEteen();
	kaanny();
	kippaa();

	tehtava = 0;
	return;
}


void toteutaTehtava(){

	sensor[S3] = kosketus;
	while (true){
		if (kosketus == 1){
			tehtava = 1;
		}
		return;
}

switch (tehtava) {
	case 0:
		break;
	case 1:
		eteen();
	case 2:
		kaannaVasemmalle();
		eteen();
	case 3:
		kaannaOikealle();
		eteen();
	case 4:
		roskilla();
}


task main(){
toteutaTehtava();

return;
}
