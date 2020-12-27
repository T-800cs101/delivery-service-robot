//Author: POVOLOTSKI GREGORI

#include<stub.h>
#include <stdio.h>
#define DIM_X 7
#define DIM_Y 10
#define MAX_POS (DIM_X * DIM_Y)
#define INIT (MAX_POS + 1)

unsigned int kostenMap[MAX_POS];
unsigned int kostenMap[MAX_POS];
unsigned char theWay[MAX_POS];
unsigned char theWayBuchstebe[MAX_POS];
unsigned char theWayBuchstebeBack[MAX_POS];
unsigned int theWay1[MAX_POS];
unsigned int theWay2[MAX_POS];
unsigned int theWay3[MAX_POS];
unsigned int theWay4[MAX_POS];
unsigned char fahrtRobot[MAX_POS];
unsigned char fahrtRobot1[MAX_POS];
unsigned char _fa[] = "xxFxxxxx..x..xx.x.x.xx.x...xx.x..xxx..x..xx...x.xxx..x.xx..x..xx..x..x";
int j, i, v, q;
int v = 0;
int w = 0;
int r = 0;

int kosten1 = 12;

void links() {
	lcd_cls();
	lcd_puts("L:  ");
	lcd_ubyte(analog(3));
	lcd_setxy(0, 6);
	sleep(20);
	motor_richtung(1, 1);
	motor_pwm(0, 5);
	motor_pwm(1, 6);
	sleep(1000);
	while (analog(1) < 100);
	//lcd_puts("Ende: ");
	//greiferZu();
}

void rechts() {
	lcd_cls();
	lcd_setxy(0, 6);
	lcd_puts("R: ");
	lcd_ubyte(analog(4));
	sleep(20);
	motor_richtung(0, 0);
	motor_pwm(0, 5);
	motor_pwm(1, 6);
	sleep(1000);
	while (analog(0) < 100);
	//lcd_puts("Ende: ");
	//greiferAuf();

}
void gerade() {
	if (analog(0) < 100 && analog(1) < 100)
	{//Gerade
		motor_richtung(1, 0);
		motor_richtung(0, 1);
		motor_pwm(0, 7);
		motor_pwm(1, 10);
	}

	else if (analog(0) > 100 && analog(1) < 100)
	{//linienfolge
		motor_richtung(0, 1);
		motor_pwm(0, 8);
		motor_pwm(1, 0);

	}

	else if (analog(0) < 100 && analog(1) > 100)
	{//linienfolge
		motor_richtung(1, 0);
		motor_pwm(0, 0);
		motor_pwm(1, 8);
	}
	while (analog(3) > 100 || analog(4) > 100);
	sleep(500);
}
void rueckFahrt() {
	motor_richtung(1, 1);
	motor_richtung(0, 0);
	motor_pwm(0, 3);
	motor_pwm(1, 6);
	/*if (analog(0) < 100 && analog(1) < 100){//Gerade
	motor_pwm(0, 3);
	motor_pwm(1, 6);

	}

	else if (analog(0) > 100 && analog(1) < 100){//linienfolge
	//motor_richtung(0, 0);
	motor_pwm(0, 0);
	motor_pwm(1, 10);

	}

	else if (analog(0) < 100 && analog(1) > 100){//linienfolge
	//motor_richtung(1, 1);
	motor_pwm(0, 0);
	motor_pwm(1, 10);


	}*/

	lcd_cls();
	lcd_puts("Zurueck: ");
	lcd_ubyte(analog(4));
	//sleep(100);
	while (analog(3) < 100 && analog(4) < 100);
	sleep(200);
}
void umdrehen() {
	motor_richtung(1, 0);
	motor_richtung(0, 1);

	lcd_cls();
	lcd_setxy(0, 6);
	lcd_puts("UMDREHEN!!!!");
	lcd_ubyte(analog(4));
	//sleep(20);
	motor_richtung(0, 0);
	motor_pwm(0, 4);
	motor_pwm(1, 5);
	sleep(2850);
	//stop();
	while (analog(0) < 100);
}
void stop() {
	motor_pwm(0, 0);
	motor_pwm(1, 0);
}

/*void greiferAuf(){
do{

for (servo = 0; servo <= 2; servo++){

for (winkel = 0; winkel <= 90; winkel++){

servo_arc(servo, winkel);

sleep(5);


}
}


}
}*/

/*void greiferAuf(){


servo_arc(0, 7);




}
void greiferZu(){


servo_arc(0, 80);



}*/





void fahrtMitZahlen(int n)
{
	// int n = 12;
	int b = kostenMap[n];
	theWay1[0] = kostenMap[n];
	theWay3[0] = n;
	/*int v = 0;
	int w = 0;
	int r = 0;*/
	for (i = 0; i < MAX_POS; i++)
	{
		for (j = 0; j < MAX_POS; j++)
		{
			if (kostenMap[j] != 0 && _fa[j] == '.')
			{
				if (kostenMap[j - DIM_X] == kostenMap[i] - 1 && kostenMap[i] == b)
				{
					theWay1[v + 1] = kostenMap[j - DIM_X];
					theWay3[v + 1] = j - DIM_X;
					b--;
					v++;
				}
				else if (kostenMap[j - 1] == kostenMap[i] - 1 && kostenMap[i] == b)
				{
					theWay1[v + 1] = kostenMap[j - 1];
					theWay3[v + 1] = j - 1;
					b--;
					v++;
				}
				else if (kostenMap[j + DIM_X] == kostenMap[i] - 1 && kostenMap[i] == b)
				{
					theWay1[v + 1] = kostenMap[j + DIM_X];
					theWay3[v + 1] = j + DIM_X;
					b--;
					v++;
				}
				else if (kostenMap[j + 1] == kostenMap[i] - 1 && kostenMap[i] == b)
				{
					theWay1[v + 1] = kostenMap[j + 1];
					theWay3[v + 1] = j + 1;
					b--;
					v++;
				}

			}
		}

	}
	//printf("\n\n");
	w = 0;
	for (i = MAX_POS; i >= 0; i--)// thWay1 Schleife umdrehen (theWay2)
	{
		if (theWay3[i] <= 69 && theWay3[i] > 0)
		{
			theWay4[w] = theWay3[i];
			//printf("%d ,", theWay4[w]);
			w++;
		}
	}
	//printf("\n\n");

	for (i = 0; i < 13; i++)// jetzt Kordinatenweg uebersetze ich zum Fahrtplan
	{
		if (theWay4[i] - DIM_X == theWay4[i + 1] && theWay4[i + 1] == theWay4[i + 2] - 1)
		{
			theWayBuchstebe[i + 1] = 'R';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
		}
		else if (theWay4[i + 1] == theWay4[i] - DIM_X && theWay4[i + 1] - 1 == theWay4[i + 2])
		{
			theWayBuchstebe[i + 1] = 'L';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
		}
		else if (theWay4[i + 1] == theWay4[i] - DIM_X && theWay4[i + 2] == theWay4[i] - 14)
		{
			theWayBuchstebe[i + 1] = 'G';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
		}
		else if (theWay4[i + 1] == theWay4[i] - DIM_X && theWay4[i - 1] == theWay4[i] + DIM_X)
		{
			theWayBuchstebe[i + 1] = 'G';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
		}
		else if (theWay4[i] + 1 == theWay4[i + 1] && theWay4[i + 1] - DIM_X == theWay4[i + 2])
		{
			theWayBuchstebe[i + 1] = 'L';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
		}
		else if (theWay4[i] - 1 == theWay4[i + 1] && theWay4[i + 1] - DIM_X == theWay4[i + 2])
		{
			theWayBuchstebe[i + 1] = 'R';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
		}
		else if (theWay4[i + 1] <= 0) {
			theWayBuchstebe[i + 1] = 'F';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
			i = 14;
		}
		else
		{
			theWayBuchstebe[i + 1] = 'F';
			//	printf("%c ,", theWayBuchstebe[i + 1]);
			i = 14;
		}

	}
	//printf("\n\n");

	for (i = MAX_POS; i >= 0; i--)//Rueckwert
	{

		if (theWayBuchstebe[i] == 'R' || theWayBuchstebe[i] == 'L' || theWayBuchstebe[i] == 'G')
		{
			if (theWayBuchstebe[i] == 'R')
			{
				theWayBuchstebeBack[r] = 'L';
				//   printf("%c ,", theWayBuchstebeBack[r]);
				r++;
			}
			else if (theWayBuchstebe[i] == 'L' && theWayBuchstebe[i + 1] == 'F')
			{
				theWayBuchstebeBack[r] = 'L';
				//   printf("%c ,", theWayBuchstebeBack[r]);
				r++;
			}
			else if (theWayBuchstebe[i] == 'R' && theWayBuchstebe[i + 1] == 'F')
			{
				theWayBuchstebeBack[r] = 'R';
				//   printf("%c ,", theWayBuchstebeBack[r]);
				r++;
			}
			else if (theWayBuchstebe[i] == 'G' && theWayBuchstebe[i + 1] == 'F')
			{
				theWayBuchstebeBack[r] = 'U';
				//   printf("%c ,", theWayBuchstebeBack[r]);
				r++;
			}
			else if (theWayBuchstebe[i] == 'L')
			{
				theWayBuchstebeBack[r] = 'R';
				//     printf("%c ,", theWayBuchstebeBack[r]);
				r++;
			}
			else
			{
				theWayBuchstebeBack[r] = 'G';
				//      printf("%c ,", theWayBuchstebeBack[r]);
				r++;
			}
		}
		else  if ((theWayBuchstebe[i] != 'R' || theWayBuchstebe[i] != 'L' || theWayBuchstebe[i] != 'G') && i < 3) {
			theWayBuchstebeBack[r] = 'U';
			//   printf("%c ,", theWayBuchstebeBack[r]);
			// i= 0;
		}
	}
	//	printf("\n\n");
	for (i = 0; i < MAX_POS; i++) {
		if (theWayBuchstebe[i] == 'F') {
			for (j = 1; j < MAX_POS; j++) {
				theWayBuchstebe[i + j] = theWayBuchstebeBack[j - 1];
			}
		}
	}
	for (j = 1; j < MAX_POS; j++) {
		//	printf("%c ,", theWayBuchstebe[j]);
	}
	////	printf("\n\n");
	//	memset(&theWayBuchstebeBack[0], 0, sizeof(theWayBuchstebeBack));
	//	memset(&theWayBuchstebe[0], 0, sizeof(theWayBuchstebe));
	//	memset(&theWay4[0], 0, sizeof(theWay4));
	//	memset(&theWay3[0], 0, sizeof(theWay3));
	//	memset(&theWay2[0], 0, sizeof(theWay2));
	//	memset(&theWay1[0], 0, sizeof(theWay1));

}










void AksenMain(void) {

	char schalter;

	unsigned char pin = 0;
	unsigned char wert = 0;
	//unsigned char theWayBuchstebe[MAX_POS] = = "LFLURLGGLRGGLFLGGGLRGRLURLGGGLRGGRLFS";;

	//unsigned char karte[] = "GRLGLLGLRGRR";// Fahrplan
	//unsigned char karte[] = "GGS";// Fahrplan
	//unsigned char karte[] = "LFLURLGGLRGGLFLGGGLRGRLURLGGGLRGGRLFS";
	//unsigned char _fa[] = "xxFxFxxx..x..xF.x.x.Fx.x...xx.x..xxx..x..xx...x.xxx..x.xF..x..Fx..x..x";

	//unsigned char _fa[] = "xxFxFxxx..x..xF.x.x.Fx.x...xx.x..xxx..x..xx...x.xxx..x.xF..x..Fx..x..x";
	//unsigned char _fa[] = "xxFxxxxx..x..xF.x.x.xx.x...xx.x..xxx..x..xx...x.xxx..x.xx..x..xx..x..x";
	//unsigned char _fa[] = "xxFxxxxx..x..xF.x.x.xx.x...xx.x..xxx..x..xx...x.xxx..x.xF..x..xx..x..x";
	//unsigned char _fa[] = "xxxxxxxx..x..xx.x.x.xx.x...xx.x..xxx..x..xx...x.xxx..x.xF..x..xx..x..x";


	int a = 1;
	int i = 0;
	int j, v;
	int q = 0;
	int kosten = 0;
	led(3, 1);
	led(2, 1);
	led(1, 1);
	led(0, 1);
	motor_richtung(1, 0);
	motor_richtung(0, 1);

	sleep(20);

	//int i, j, v;
	//int kosten = 0;
	//int kosten1 = 12;


	for (i = 0; i < MAX_POS; i++)// tabelle KostenMap
	{
		if (i == 64)
		{
			kostenMap[i] = 0;
		}
		else
		{
			kostenMap[i] = INIT;
		}
	}
	for (j = 0; j < MAX_POS; j++)//TiefenSuche
	{
		for (i = 0; i < MAX_POS; i++)
		{
			if (((_fa[i] == 'F') || (_fa[i] == '.'))
				&& ((_fa[i] >= 0) && (_fa[i] <= 69))
				&& (kostenMap[i] != INIT)
				&& ((_fa[i] % 7 != 0) || (_fa[i] % 7 != 1)))
			{


				if (kostenMap[i] == kosten)
				{

					if (_fa[i + 1] != 'x' && kostenMap[i + 1] != kosten - 1)
					{
						kostenMap[i + 1] = kosten + 1;
					}
					if (_fa[i - 1] != 'x' && kostenMap[i - 1] != kosten - 1)
					{
						kostenMap[i - 1] = kosten + 1;
					}
					if (_fa[i + DIM_X] != 'x' && kostenMap[i + DIM_X] != kosten - 1 && _fa[i + DIM_X] < 69)
					{
						kostenMap[i + DIM_X] = kosten + 1;
					}
					if (_fa[i - DIM_X] != 'x' && kostenMap[i - DIM_X] != kosten - 1)
					{
						kostenMap[i - DIM_X] = kosten + 1;
					}
				}
			}
		}
		kosten++;
	}
	//for (j = 0; j < 70; j++)
	//{ //Ganze Route herstellen
	//	lcd_setxy(1, 0);
	//	lcd_puts(": ");
	//	lcd_ubyte(theWayBuchstebe[j]);
	//	if (_fa[j] == 'F')
	//	{
	//		fahrtMitZahlen(j);

	//	}
	//}



	//printf("\n");

	while (analog(8) > 100)
	{
		servo_arc(0, 0);
		lcd_cls();
		lcd_puts("W");
		lcd_ubyte(analog(8));
		lcd_setxy(1, 0);
		lcd_ubyte(theWayBuchstebe[q]);
		//lcd_puts("Licht bitte an!!! ");
		//stop();
		//sleep(200);

	}


	while (a = 1) {
		//	if (i < 38){


		lcd_cls();
		lcd_setxy(1, 8);
		lcd_puts("Q: ");
		lcd_ubyte(q);



		wert = digital_in(7);
		lcd_setxy(0, 0);
		lcd_ubyte(wert);
		if (wert == 0) {
			stop();
			servo_arc(0, 80);
			//sleep(100);
			j++;
			sleep(300);
			rueckFahrt();
			servo_arc(0, 0);
			sleep(100);

		}

		for (j = 0; j < 70; j++)
		{ //Ganze Route herstellen
			lcd_setxy(1, 0);
			lcd_puts(": ");
			//lcd_ubyte(theWayBuchstebe[j]);
			if (_fa[j] == 'F')
			{
				fahrtMitZahlen(j);
				lcd_puts("A");
				sleep(300);
			}
		}

		lcd_puts("B");
		sleep(300);
		if (analog(3) > 100 || analog(4) > 100)
		{ //Kreuzung.Hier wird Robot entscheiden biggt er links oder rechts ab oder gerade faehrt.
			lcd_cls();
			lcd_puts(theWayBuchstebe);

			if (theWayBuchstebe[q] == 'U')
			{
				lcd_cls();
				lcd_puts("ich bin da U");
				motor_richtung(1, 0);
				motor_richtung(0, 1);
				lcd_cls();
				lcd_puts("U:  ");
				lcd_ubyte(analog(3));
				lcd_setxy(1, 0);
				lcd_ubyte(theWayBuchstebe[q]);
				sleep(400);
				umdrehen();
				//stop();
				//sleep(1000);
				q++;
			}


			else if (theWayBuchstebe[q] == 'R')
			{
				lcd_cls();
				lcd_puts("ich bin da R");
				motor_richtung(1, 0);
				motor_richtung(0, 1);
				motor_pwm(0, 6);
				motor_pwm(1, 9);
				lcd_cls();
				lcd_setxy(1, 0);
				lcd_ubyte(theWayBuchstebe[q]);
				sleep(650);
				rechts();
				q++;
			}
			else if (theWayBuchstebe[q] == 'L')
			{
				lcd_cls();
				lcd_puts("ich bin da L");
				motor_richtung(1, 0);
				motor_richtung(0, 1);
				motor_pwm(0, 6);
				motor_pwm(1, 9);
				lcd_cls();
				lcd_setxy(1, 0);
				lcd_ubyte(theWayBuchstebe[q]);
				sleep(650);
				links();
				q++;
			}
			else if (theWayBuchstebe[q] == 'G')
			{
				lcd_cls();
				lcd_puts("ich bin da G");
				motor_richtung(1, 0);
				motor_richtung(0, 1);
				lcd_cls();
				lcd_puts("G:  ");
				lcd_setxy(1, 0);
				lcd_ubyte(theWayBuchstebe[q]);
				sleep(20);
				gerade();
				q++;

			}
			else if (theWayBuchstebe[q] == 'S')
			{
				lcd_cls();
				lcd_setxy(1, 0);
				lcd_ubyte(theWayBuchstebe[q]);
				stop();
				a++;

			}



		}
		else if (analog(0) < 100 && analog(1) < 100) {//Gerade
			motor_richtung(1, 0);
			motor_richtung(0, 1);
			motor_pwm(0, 8);
			motor_pwm(1, 10);
		}

		else if (analog(0) > 100 && analog(1) < 100) {//linienfolge
			motor_richtung(0, 1);
			motor_pwm(0, 10);
			motor_pwm(1, 0);

		}

		else if (analog(0) < 100 && analog(1) > 100) {//linienfolge
			motor_richtung(1, 0);
			motor_pwm(0, 0);
			motor_pwm(1, 10);


		}






		lcd_puts("C");
		sleep(300);


		//	}
		//stop();
	}





	lcd_puts("D");
	sleep(300);

}
//ende Method



