#pragma config(Sensor, S1,     Touch1,         sensorTouch)
#pragma config(Sensor, S2,     Touch2,         sensorTouch)
#pragma config(Motor,  motorA,          cam,           tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          mB,            tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          mC,            tmotorNXT, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int position = 0;
int speed = 15;
float k1, k2;
int u, u_old;

#include "1tasks.h"

task main()
{
	StartTask(screen);
	StartTask(bt);
	StartTask(camera);

	//PD-reg
	position = 1;
	speed = 20; k1 = 0.5; k2 = 0; u_old = 0;
	while(isAnyTouched() == false)
	{
		u = k1 * u_input + k2 * (u_input - u_old);
		Motors(speed + u, speed - u);
		u_old = u_input;
		wait1Msec(1);
	}

	//Aligning
	position = 2;
	StartTask(align);
	while(isAllTouched() == false) wait1Msec(1);
	StopTask(align);

	//Reverse driving
	position = 3;
	ReverseDriving(-600);

	//Special-reg
	position = 4;
	StartTask(SpecialReg);
	while(isAnyTouched() == false) wait1Msec(1);
	StopTask(SpecialReg);

	//Aligning. Again.
	position = 5;
	StartTask(alignSmall);
	while(isAllTouched() == false) wait1Msec(1);
	StopTask(alignSmall);

	//Small reverse driving
	position = 6;
	ReverseDriving(-600);

	//Setting Research Module
	position = 7;
	while(isAllTouched() == false) wait1Msec(1);

	//Drilling
	PlaySound(soundUpwardTones);
	position = 8;
	StopAndWait(1000);
	Motors(30, 30);
	wait1Msec(7000);
	Motors(100, 100);
	wait1Msec(7000);
	Motors(0, 0);

	//Reverse driving
	PlaySound(soundUpwardTones);
	position = 9;
	ReverseDriving(-800);

	StopTask(camera);
	motor[cam] = 0;
	nMotorEncoder[cam] = 0;
	//DEMO
	wait1Msec(100000);//------------------------------- LONG WAITING -----------------------------------------------
	PlaySound(soundUpwardTones);
	PlaySound(soundDownwardTones);
	wait1Msec(20000);
	position = 10;
	PlaySound(soundBeepBeep);
	ZeroEnc();
	Motors(20, 20);
	while(abs(nMotorEncoder[mB]) < 500) wait1Msec(1);
	Motors(0, 0);
	ZeroEnc();
	Motors(-40, -10);
	while(abs(nMotorEncoder[mB]) < 1700) wait1Msec(1);
	Motors(0, 0);
	ZeroEnc();
	Motors(20, 20);
	while(abs(nMotorEncoder[mB]) < 400) wait1Msec(1);
	Motors(0, 0);
	PlaySound(soundBeepBeep);
	wait1Msec(1000);
	position = 11;
	for(int x = 1; x <= 3; x++)
	{
		nMotorEncoder[motorA] = 0;
		motor[motorA] = 10;
		while(nMotorEncoder[motorA] < 90) wait1Msec(1);
		wait1Msec(500);
		motor[motorA] = - 10;
		while(nMotorEncoder[motorA] > 0) wait1Msec(1);
	}
	motor[motorA] = 0;
	position = 12;
}
