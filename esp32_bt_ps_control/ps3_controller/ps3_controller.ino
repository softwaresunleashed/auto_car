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
   if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 )
   {
       Serial.print(LEFT_JOYSTICK);
       
       Serial.print(DELIMITER_TAG);
       Serial.print(Ps3.data.analog.stick.lx, DEC);
       Serial.print(DELIMITER_COORDINATE); 
       Serial.print(Ps3.data.analog.stick.ly, DEC);
       
       Serial.println();
    }

   if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 )
   {
        Serial.print(RIGHT_JOYSTICK);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(Ps3.data.analog.stick.rx, DEC);
        Serial.print(DELIMITER_COORDINATE); 
        Serial.print(Ps3.data.analog.stick.ry, DEC);

        Serial.println();
   }

    //--- Digital cross/square/triangle/circle button events ---
    if( Ps3.event.button_down.cross )
    {     
        Serial.print(CROSS_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);

        Serial.println();
    }
    
    if( Ps3.event.button_up.cross )
    {
        Serial.print(CROSS_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED);

        Serial.println();
    }

    if( Ps3.event.button_down.square )
    {
        Serial.print(SQUARE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);

        Serial.println();
    }

    if( Ps3.event.button_up.square )
    {
        Serial.print(SQUARE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED);

        Serial.println();
    }

    if( Ps3.event.button_down.triangle )
    {
        Serial.print(TRIANGLE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);

        Serial.println();
    }

    if( Ps3.event.button_up.triangle )
    {
        Serial.print(TRIANGLE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED);

        Serial.println();
    }

    if( Ps3.event.button_down.circle )
    {
        Serial.print(CIRCLE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.circle )
    {
        Serial.print(CIRCLE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    
    //--------------- Digital D-pad button events --------------
    if( Ps3.event.button_down.up )
    {
        Serial.print(UP_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MAX_ANALOG_VALUE);

        Serial.println();
    }

    if( Ps3.event.button_up.up )
    {
        Serial.print(UP_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MIN_ANALOG_VALUE); 

        Serial.println();
    }

    if( Ps3.event.button_down.right )
    {
        Serial.print(RIGHT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MAX_ANALOG_VALUE);

        Serial.println();
    }

    if( Ps3.event.button_up.right )
    {
        Serial.print(RIGHT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MIN_ANALOG_VALUE); 

        Serial.println();
    }

    if( Ps3.event.button_down.down )
    {
        Serial.print(DOWN_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MAX_ANALOG_VALUE);

        Serial.println();
    }

    if( Ps3.event.button_up.down )
    {
        Serial.print(DOWN_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MIN_ANALOG_VALUE); 
                
        Serial.println();
    }

    if( Ps3.event.button_down.left )
    {
        Serial.print(LEFT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MAX_ANALOG_VALUE);

        Serial.println();
    }

    if( Ps3.event.button_up.left )
    {
        Serial.print(LEFT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(MIN_ANALOG_VALUE); 
        
        Serial.println();
    }

    //------------- Digital shoulder button events -------------
    if( Ps3.event.button_down.l1 )
    {
        Serial.print(SHOULDER_BTN_L1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.l1 )
    {
        Serial.print(SHOULDER_BTN_L1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    if( Ps3.event.button_down.r1 )
    {
        Serial.print(SHOULDER_BTN_R1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.r1 )
    {
        Serial.print(SHOULDER_BTN_R1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 
        
        Serial.println();
    }

    //-------------- Digital trigger button events -------------
    if( Ps3.event.button_down.l2 )
    {
        Serial.print(SHOULDER_BTN_L2);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.l2 )
    {
        Serial.print(SHOULDER_BTN_L2);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    if( Ps3.event.button_down.r2 )
    {
        Serial.print(SHOULDER_BTN_R2);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.r2 )
    {
        Serial.print(SHOULDER_BTN_R2);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    
    //--------------- Digital stick button events --------------
    if( Ps3.event.button_down.l3 )
    {
        Serial.print(SHOULDER_BTN_L3);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.l3 )
    {
        Serial.print(SHOULDER_BTN_L3);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    if( Ps3.event.button_down.r3 )
    {
        Serial.print(SHOULDER_BTN_R3);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }

    if( Ps3.event.button_up.r3 )
    {
        Serial.print(SHOULDER_BTN_R1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    //---------- Digital select/start/ps button events ---------
    if( Ps3.event.button_down.select )
    {
        Serial.print(SELECT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }
    
    if( Ps3.event.button_up.select )
    {
        Serial.print(SELECT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }
    
    /* Start Button */
    if( Ps3.event.button_down.start )
    {
        Serial.print(START_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }
    
    if( Ps3.event.button_up.start )
    {
        Serial.print(START_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }

    /* PS Button */
    if( Ps3.event.button_down.ps )
    {
        Serial.print(PS_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED); 

        Serial.println();
    }
    
    if( Ps3.event.button_up.ps )
    {
        Serial.print(PS_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_RELEASED); 

        Serial.println();
    }


   //--------------- Analog D-pad button events ----------------
   if( abs(Ps3.event.analog_changed.button.up) )
   {
        Serial.print(UP_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.up, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.right) )
   {
        Serial.print(RIGHT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.right, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.down) )
   {
        Serial.print(DOWN_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.down, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.left) )
   {
        Serial.print(LEFT_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.left, DEC);

        Serial.println();
   }

   //---------- Analog shoulder/trigger button events ----------
   if( abs(Ps3.event.analog_changed.button.l1)){
        Serial.print(SHOULDER_BTN_L1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.l1, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.r1) ){
        Serial.print(SHOULDER_BTN_R1);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.r1, DEC);

        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.l2) ){
        Serial.print(SHOULDER_BTN_L2);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.l2, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.r2) ){
        Serial.print(SHOULDER_BTN_R2);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.r2, DEC);
        
        Serial.println();
   }


   //---- Analog cross/square/triangle/circle button events ----
   if( abs(Ps3.event.analog_changed.button.triangle))
   {
        Serial.print(TRIANGLE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.triangle, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.circle) )
   {
        Serial.print(CIRCLE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.circle, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.cross) )
   {
        Serial.print(CROSS_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.cross, DEC);
        
        Serial.println();
   }

   if( abs(Ps3.event.analog_changed.button.square) )
   {
        Serial.print(SQUARE_BTN);
        
        Serial.print(DELIMITER_TAG);
        Serial.print(KS_PRESSED);
        Serial.print(DELIMITER_ANALOG_VAL);
        Serial.println(Ps3.data.analog.button.square, DEC);
        
        Serial.println();
   }


   //---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
        battery = Ps3.data.status.battery;
        Serial.print(BATT_STATUS);
        Serial.print(DELIMITER_TAG);
        
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
    if(player > 10) {
      player = 0;
    }


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
