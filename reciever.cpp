#include "GCconsole.h"
#include <RF24.h>
#include "pico/time.h"
#include <stdio.h>

#define CE_PIN 7
#define CS_PIN 8

const uint8_t address[6] = "00001";

RF24 reciever(CE_PIN, CS_PIN);

GCreport report = default_GCreport;
GCreport origin = default_GCreport;

gcconsole console(0);


void callback(uint gpio, uint32_t events){
    gpio_set_irq_enabled_with_callback(0, GPIO_IRQ_EDGE_FALL, false, &callback);

    if(!console.write_data(origin, report)){
        gpio_put(PICO_DEFAULT_LED_PIN, true);   //An error occured
    }

    gpio_set_irq_enabled_with_callback(0, GPIO_IRQ_EDGE_FALL, true, &callback);

}


int main(){

    gpio_init(PICO_DEFAULT_LED_PIN);

    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    sleep_ms(1000);


    while(!reciever.begin()){
        
    }
    

    reciever.openReadingPipe(0, address);

    reciever.setPALevel(RF24_PA_LOW);

    reciever.setPayloadSize(sizeof(report));

    reciever.setDataRate(RF24_1MBPS);

    reciever.setRetries(0, 0);

    reciever.setAutoAck(false);

    reciever.startListening();

    sleep_ms(1000);

    console.begin();

    console.init();

    console.write_origin();

    console.write_report(report);

    gpio_set_irq_enabled_with_callback(0, GPIO_IRQ_EDGE_FALL, true, &callback);

    while(true)
    {
        if (reciever.available()) {
            reciever.read(&report, sizeof(report));
        }
    }
}   