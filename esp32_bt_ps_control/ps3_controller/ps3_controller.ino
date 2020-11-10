#include <Ps3Controller.h>
#include "key_events.h"
#include "configuration.h"
#include "tags.h"


/* BT MAC Address of ESP Devices */
#define BT_HOST_DEVICE_MAC_ADDR   "01:02:03:04:05:06"


/* Global Variables */
int player = 0;
int battery = 0;


/* Function invoked whenever there is any event observed on BT */
void notify()
{

    //---------------- Analog stick value events ---------------
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
       Serial.print(LEFT_JOYSTICK);
       
       Serial.print(":");
       Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(","); 
       Serial.print(Ps3.data.analog.stick.ly, DEC);
       
       Serial.println();
    }

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
        Serial.print(RIGHT_JOYSTICK);
        
        Serial.print(":");
        Serial.print(Ps3.data.analog.stick.rx, DEC);
        Serial.print(","); 
        Serial.print(Ps3.data.analog.stick.ry, DEC);

        Serial.println();
   }


   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print(BATT_STATUS);
        Serial.print(":");
        
        if( battery == ps3_status_battery_charging )      Serial.println( BATT_CHARGING );
        else if( battery == ps3_status_battery_full )     Serial.println( BATT_FULL );
        else if( battery == ps3_status_battery_high )     Serial.println( BATT_HIGH );
        else if( battery == ps3_status_battery_low)       Serial.println( BATT_LOW );
        else if( battery == ps3_status_battery_dying )    Serial.println( BATT_DYING );
        else if( battery == ps3_status_battery_shutdown ) Serial.println( BATT_SHUTDOWN );
        else Serial.println(BATT_UNDEFINED);
    }

}

void onConnect(){
    Serial.println("Connected.");
}


void setup()
{   
    Serial.begin(BAUDRATE);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin(BT_HOST_DEVICE_MAC_ADDR);

    Serial.println("Ready.");
}

void loop()
{
    if(!Ps3.isConnected())
        return;

#if 0
    //-------------------- Player LEDs -------------------
    Serial.print("Setting LEDs to player "); Serial.println(player, DEC);
    Ps3.setPlayer(player);

    player += 1;
    if(player > 10) player = 0;


    //------ Digital cross/square/triangle/circle buttons ------
    if( Ps3.data.button.cross && Ps3.data.button.down )
        Serial.println("Pressing both the down and cross buttons");
    if( Ps3.data.button.square && Ps3.data.button.left )
        Serial.println("Pressing both the square and left buttons");
    if( Ps3.data.button.triangle && Ps3.data.button.up )
        Serial.println("Pressing both the triangle and up buttons");
    if( Ps3.data.button.circle && Ps3.data.button.right )
        Serial.println("Pressing both the circle and right buttons");

    if( Ps3.data.button.l1 && Ps3.data.button.r1 )
        Serial.println("Pressing both the left and right bumper buttons");
    if( Ps3.data.button.l2 && Ps3.data.button.r2 )
        Serial.println("Pressing both the left and right trigger buttons");
    if( Ps3.data.button.l3 && Ps3.data.button.r3 )
        Serial.println("Pressing both the left and right stick buttons");
    if( Ps3.data.button.select && Ps3.data.button.start )
        Serial.println("Pressing both the select and start buttons");
#endif

    delay(2000);
}
