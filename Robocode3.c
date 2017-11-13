#pragma config(Sensor, S1,     etaluotain,     sensorEV3_IRSensor)
#pragma config(Sensor, S2,     variluotain,    sensorEV3_Color)
#pragma config(Sensor, S3,     kosketus,        sensorEV3_Touch)
#pragma config(Sensor, S4,     Gyroskooppi,           sensorEV3_Gyro, modeEV3Gyro_Rate)
#pragma config(Motor,  motorA,          MotorA,        tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          MotorB,        tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          MotorC,        tmotorEV3_Large, PIDControl, encoder)

int vaihe = 0;
int nopeus = 0;


void eteen(){
	//kiihdytä();
	liiku();
	
return;
}

task main()
{
while (true){	
	if (vaihe == 0){
		eteen();		
	}
		
	}
return;
}

void liiku(){
	
	if (getIRDistance(etaluotain) < 20){
			eteen += 1;
			return;
	}
	motor[motorB] = -100;
	motor[motorC] = -100;
	wait1Msec(100);

return;
}
