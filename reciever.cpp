#include "GCconsole.h"
#include <RF24.h>

#define CE_PIN 7
#define CS_PIN 8

const uint8_t address[6] = "00001";

RF24 reciever(CE_PIN, CS_PIN);

GCreport report;

gcconsole console(0);

int main(){

    //stdio_init_all();

    reciever.begin();

    reciever.openReadingPipe(0, address);

    reciever.setPALevel(RF24_PA_LOW);

    reciever.setPayloadSize(sizeof(report));

    reciever.setDataRate(RF24_2MBPS);

    reciever.setRetries(0, 0);

    reciever.setAutoAck(false);

    reciever.startListening();

    sleep_ms(1000);

    console.write_data(default_GCreport, default_GCreport);

    console.write_data(default_GCreport, default_GCreport);

    console.write_data(default_GCreport, default_GCreport);

    console.write_data(default_GCreport, default_GCreport);

    console.write_data(default_GCreport, default_GCreport);


    while (true)
    {

        if (reciever.available()) {
            reciever.read(&report, sizeof(report));
            console.write_data(default_GCreport, report);
        }
        
    } 
}   