#include "msp.h"
//#include "..\inc\Bump.h"
//#include "..\inc\BumpInt.h"
#include "..\inc\Clock.h"
#include "..\inc\SysTick.h" 
#include "..\inc\CortexM.h"
#include "..\inc\LaunchPad.h" 
#include "..\inc\Motor.h" 
#include "..\inc\TimerA1.h" 
#include "..\inc\TExaS.h" 
#include "..\inc\Reflectance.h"
void TimedPause(uint32_t time){
  Clock_Delay1ms(time);          // run for a while and stop
  Motor_Stop();
  while(LaunchPad_Input()==0);  // wait for touch
  while(LaunchPad_Input());     // wait for release
}

uint8_t Data; // QTR-8RC
int32_t Position; // 332 is right, and -332 is left of center

int main(void){
    TExaS_Init(LOGICANALYZER_P2);
    Clock_Init48MHz();
    LaunchPad_Init(); // built-in switches and LEDs
    //TimerA1_Init(&bump_interrupt,50000);  // 10 Hz
    EnableInterrupts();
    //Bump_Init();      // bump switches
    Motor_Init();     // your function
    Reflectance_Init();

    int speed = 1000, backup_speed = 4000;
    int time1 = 50,
        time2 = 100,
        time3 = 150,
        time_backup = 300;

    TimedPause(1000);
    LaunchPad_LED(1); //robot activated

    while(1){
        Data = Reflectance_Read(1000);
        printf("%x \n", Data);
        Position = Reflectance_Position(Data);
        Clock_Delay1ms(10);

        if (Data == 0b11111111 && Position == 0) { // 2nd t-join
            Motor_Right(2000,2000);
            Clock_Delay1ms(1500);
            Motor_Stop();
            Motor_Forward(4000,4000);
            Clock_Delay1ms(500);
            Motor_Stop();
        }
        else if (Position >-47 && Position <47) { //center
            Motor_Forward(speed,speed);
            Clock_Delay1ms(time3);
            Motor_Stop();
            LaunchPad_Output(0b111); //white LED
            //break;
        } else if (Position <= -47 && Position > -142) { //slightly off to the left
            Motor_Left(0,speed);
            Clock_Delay1ms(time1);
            Motor_Stop();
            LaunchPad_Output(0b010); //green LED
        } else if (Position >= 47 && Position <142) { //slightly off to the right
            Motor_Right(speed,0);
            Clock_Delay1ms(time1);
            LaunchPad_Output(0b011); //yellow LED
            Motor_Stop();
        } else if (Position <= -142 && Position >-237) { //off to the left
            Motor_Left(0,2*speed);
            Clock_Delay1ms(time2);
            LaunchPad_Output(0b110); //cyan LED
            Motor_Stop();
        } else if (Position >= 142 && Position < 237) { // off to the right
            Motor_Right(2*speed,0);
            Clock_Delay1ms(time2);
            LaunchPad_Output(0b001); //red LED
            Motor_Stop();
        } else if (Position <= -237 && Position > -332) { // way off left
            Motor_Left(0,3*speed);
            Clock_Delay1ms(time3);
            LaunchPad_Output(0b100); //blue LED
            Motor_Stop();
        } else if (Position >= 237 && Position < 332) { // way off right
            Motor_Right(3*speed,0);
            Clock_Delay1ms(time3);
            LaunchPad_Output(0b101); //magenta LED
            Motor_Stop();
        } else if (Data == 0b00000000 && Position == 333) { // goal
            Motor_Stop();
            LaunchPad_Output(0b010); //green LED
            //break;
        } else {
            Motor_Backward(backup_speed,backup_speed);
            Clock_Delay1ms(time_backup);
            Motor_Stop();
            LaunchPad_Output(0b001); //red LED
        }
    }
}
