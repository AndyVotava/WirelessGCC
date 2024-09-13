#include "gcconsole.h"

void gcconsole::outmode(){
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_init(pio, sm, offset+joybus_offset_outmode, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
    pio_sm_set_enabled(pio, sm, true);
}


gcconsole::gcconsole(uint8_t pin){
    sm = pio_claim_unused_sm(pio, true);

    offset = pio_add_program(pio, &joybus_program);

    c = joybus_program_get_default_config(offset);

    sm_config_set_set_pins(&c, pin, 1);
    sm_config_set_in_pins(&c, pin);
    sm_config_set_out_pins(&c, pin, 1);
    sm_config_set_in_shift(&c, false, true, 8);
    sm_config_set_out_shift(&c, true, false, 32);

    pio_gpio_init(pio, pin);
    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_clkdiv(pio, sm, 5);
}


bool gcconsole::write_data(GCreport origin, GCreport report){
    uint8_t request = pio_sm_get_blocking(pio, sm);


    if(request == 0x00){
        sleep_us(5);

        outmode();

        pio_sm_put_blocking(pio, sm, 0b10101010101010101110101110101010);
        pio_sm_put_blocking(pio, sm, 0b111110101010101011);

        return false;
    }

    else if(request == 0x41){

        sleep_us(5);

        outmode();
        
        pio_sm_put_blocking(pio, sm, to_pio(origin.SYXBA << 8 | origin.LRZD));
        pio_sm_put_blocking(pio, sm, to_pio(origin.xStick << 8 | origin.yStick));
        pio_sm_put_blocking(pio, sm, to_pio(origin.cxStick << 8 | origin.cyStick));
        pio_sm_put_blocking(pio, sm, to_pio(origin.analogL << 8 | origin.analogR));
        pio_sm_put_blocking(pio, sm, TWO_NULL_BYTES);
        pio_sm_put_blocking(pio, sm, 0b11);
        
        return true;
    }

    else if (request == 0x40){
        pio_sm_get_blocking(pio, sm);
        pio_sm_get_blocking(pio, sm);

        sleep_us(5);

        outmode();
        
        pio_sm_put_blocking(pio, sm, to_pio(report.SYXBA << 8 | report.LRZD));
        pio_sm_put_blocking(pio, sm, to_pio(report.xStick << 8 | report.yStick));
        pio_sm_put_blocking(pio, sm, to_pio(report.cxStick << 8 | report.cyStick));
        pio_sm_put_blocking(pio, sm, to_pio(report.analogL << 8 | report.analogR));
        pio_sm_put_blocking(pio, sm, 0b11);

        return true;

    }

    
    return false;
}

bool gcconsole::init(){

    uint8_t request = pio_sm_get_blocking(pio, sm);


    if(request == 0x00){
        sleep_us(5);

        outmode();

        pio_sm_put_blocking(pio, sm, 0b10101010101010101110101110101010);
        pio_sm_put_blocking(pio, sm, 0b111110101010101011);

        return true;
    }

    return false;
}

bool gcconsole::write_origin(){
    uint8_t request = pio_sm_get_blocking(pio, sm);


    if(request == 0x41){

        sleep_us(5);

        outmode();
        
        pio_sm_put_blocking(pio, sm, to_pio(default_GCreport.SYXBA << 8 | default_GCreport.LRZD));
        pio_sm_put_blocking(pio, sm, to_pio(default_GCreport.xStick << 8 | default_GCreport.yStick));
        pio_sm_put_blocking(pio, sm, to_pio(default_GCreport.cxStick << 8 | default_GCreport.cyStick));
        pio_sm_put_blocking(pio, sm, to_pio(default_GCreport.analogL << 8 | default_GCreport.analogR));
        pio_sm_put_blocking(pio, sm, TWO_NULL_BYTES);
        pio_sm_put_blocking(pio, sm, 0b11);
        
        return true;
    }
    return false;
}

bool gcconsole::write_report(GCreport report){
    uint8_t request = pio_sm_get_blocking(pio, sm);

    if (request == 0x40){
        pio_sm_get_blocking(pio, sm);
        pio_sm_get_blocking(pio, sm);

        busy_wait_us(5);

        outmode();

        pio_sm_put_blocking(pio, sm, to_pio(report.SYXBA << 8 | report.LRZD));
        pio_sm_put_blocking(pio, sm, to_pio(report.xStick << 8 | report.yStick));
        pio_sm_put_blocking(pio, sm, to_pio(report.cxStick << 8 | report.cyStick));
        pio_sm_put_blocking(pio, sm, to_pio(report.analogL << 8 | report.analogR));
        pio_sm_put_blocking(pio, sm, 0b11);

        return true;

    }

    return false;

}

void gcconsole::begin(){
    pio_sm_set_enabled(pio, sm, true);
}