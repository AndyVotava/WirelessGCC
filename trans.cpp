#include "GCcontroller.h"
#include <RF24.h>

#define CE_PIN 20
#define CS_PIN 17

const uint8_t address[6] = "00001";

RF24 transmitter(CE_PIN, CS_PIN);

GCcontroller controller1(0);

int main(){

    gpio_init(PICO_DEFAULT_LED_PIN);

    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while(!transmitter.begin()){
        
    }

    sleep_ms(1);

    transmitter.openWritingPipe(address);

    transmitter.setPALevel(RF24_PA_LOW);

    transmitter.setPayloadSize(sizeof(controller1.report));

    transmitter.setDataRate(RF24_1MBPS);

    transmitter.setRetries(0, 0);

    transmitter.setAutoAck(false);

    transmitter.stopListening();
    
    controller1.init();
    sleep_us(25);
    controller1.get_origin();
    sleep_us(100);

    gpio_put(PICO_DEFAULT_LED_PIN, true);

    while (true)
    {
        controller1.get_report();
        
        transmitter.write(&controller1.report, sizeof(controller1.report));
    }
    
}   