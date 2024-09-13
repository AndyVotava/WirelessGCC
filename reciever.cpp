#include "GCconsole.h"
#include <RF24.h>
#include "pico/time.h"
#include <stdio.h>

#define CE_PIN 7
#define CS_PIN 8

const uint8_t address[6] = "00001";

RF24 reciever(CE_PIN, CS_PIN);

GCreport report = default_GCreport;

gcconsole console(0);

alarm_id_t alarm;

int count = 0;

//NOTE CANNOT SLEEP IN ALARM CALLBACK FUNCTION USE BUSY WAIT INSTEAD
int64_t alarm_callback(alarm_id_t id, void *user_data){

    console.write_report(report);
    console.write_report(report);

    count += 1;
    
    alarm = add_alarm_in_ms(15, alarm_callback, NULL, false);  

    return 0;
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

    alarm = add_alarm_in_ms(15, alarm_callback, NULL, false);  

    gpio_put(PICO_DEFAULT_LED_PIN, true);

    while(true)
    {
        if (reciever.available()) {
            reciever.read(&report, sizeof(report));
            count = 0;
            gpio_put(PICO_DEFAULT_LED_PIN, true);
        }
        else if (count >= 5)
        {
            //disconnected controller
            gpio_put(PICO_DEFAULT_LED_PIN, false);
        }
    }
}   