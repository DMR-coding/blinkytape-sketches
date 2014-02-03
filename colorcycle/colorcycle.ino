#include <FastSPI_LED2.h>
#include <Animation.h>

#define LED_COUNT 60 // BlinkyTape has 60 LEDs!
struct CRGB leds[LED_COUNT]; // this struct contains 60 CRGB values.  This is where 

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

#define R_STEP 8
#define G_STEP 4
#define B_STEP 2
#define MAX_COLOR 255
#define PAUSE_TIME 500

int R = 0;
boolean R_bounced = false;
int G = 0;
boolean G_bounced = false;
int B = 0;
boolean B_bounced = false;

// first, let's get ready to blink using some FastSPI_LED2 routines
// take a look at the FastSPI_LED2 example called Fast2Dev for more usage info
void setup()
{  
  LEDS.addLeds<WS2811, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0)); // set the color for the strip all at once.
  LEDS.setBrightness(0); // start out with LEDs off
  LEDS.show(); // you'll always need to call this function to make your changes happen.
}

int cycle_color(int color, int stepping, boolean &bounced){
    if(! bounced){
      if(color + stepping > MAX_COLOR){
         bounced = true; 
         return cycle_color(color, stepping, bounced);
      }else{
         return color + stepping;
      }
    }else{
      if(color - stepping < 0){
         bounced = false;
         return cycle_color(color, stepping, bounced);
        }
        else{
           return color - stepping; 
        }
    }
    
    if(color + stepping > MAX_COLOR){
       return color - stepping;   
    }else{
       return color + stepping;
    }
}

void loop() {
  R = cycle_color(R, R_STEP, R_bounced);
  G = cycle_color(G, G_STEP, G_bounced);
  B = cycle_color(B, B_STEP, B_bounced);
  
  LEDS.showColor(CRGB(R, G, B)); // set the color for the strip all at once.
  LEDS.setBrightness(20);

  delay(PAUSE_TIME);
}
