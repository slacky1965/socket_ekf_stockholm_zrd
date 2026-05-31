#include "app_socket.h"

static light_t light;

void led_on(uint32_t pin)
{
    drv_gpio_write(pin, LED_ON);
}

void led_off(uint32_t pin)
{
    drv_gpio_write(pin, LED_OFF);
}

void set_led_status(bool status) {
#if !UART_PRINTF_MODE
    switch(socket_settings.led_control) {
        case CONTROL_LED_OFF:
            led_off(light.led_status_pin);
            break;
        case CONTROL_LED_ON:
            led_on(light.led_status_pin);
            break;
        case CONTROL_LED_ON_OFF:
            if (socket_settings.status_onoff) led_on(light.led_status_pin);
            else led_off(light.led_status_pin);
            break;
        case CONTROL_LED_OFF_ON:
            if (socket_settings.status_onoff) led_off(light.led_status_pin);
            else led_on(light.led_status_pin);
            break;
        default:
            break;
    }
#endif
}

void led_init(void) {
    TL_SETSTRUCTCONTENT(light, 0);
    light.timerLedEvt = NULL;
    light.led_net_pin = LED_NET_GPIO;
#if !UART_PRINTF_MODE
    light.led_status_pin = LED_STATUS_GPIO;
    led_off(light.led_status_pin);
#endif
    led_off(light.led_net_pin);

}


int32_t zclLightTimerCb(void *arg)
{
    uint32_t interval = 0;

    if (light.timer_stop) {
        led_off(light.led_net_pin);
        light.timer_stop = false;
        light.times = 0;
        light.timerLedEvt = NULL;
        return -1;
    }

    if(light.sta == light.oriSta) {
        light.times--;
        if(light.times <= 0){
            led_off(light.led_net_pin);
            light.timerLedEvt = NULL;
            return -1;
        }
    }

    light.sta = !light.sta;
    if(light.sta) {
        led_on(light.led_net_pin);
        interval = light.ledOnTime;
    } else {
        led_off(light.led_net_pin);
        interval = light.ledOffTime;
    }

    return interval;
}

void light_blink_start(uint8_t times, uint16_t ledOnTime, uint16_t ledOffTime)
{
    uint32_t interval = 0;
    light.times = times;

    if(!light.timerLedEvt){
        if(light.oriSta){
            led_off(light.led_net_pin);
            light.sta = 0;
            interval = ledOffTime;
        }else{
            led_on(light.led_net_pin);
            light.sta = 1;
            interval = ledOnTime;
        }
        light.ledOnTime = ledOnTime;
        light.ledOffTime = ledOffTime;

        light.timerLedEvt = TL_ZB_TIMER_SCHEDULE(zclLightTimerCb, NULL, interval);
    }
}

void light_blink_stop(void) {

    uint8_t ret = 0;

    if(light.timerLedEvt){
        ret = TL_ZB_TIMER_CANCEL(&light.timerLedEvt);
        if (ret == NO_TIMER_AVAIL || ret == SUCCESS) {
            light.timerLedEvt = NULL;
        } else if (ret == TIMER_CANCEL_NOT_ALLOWED) {
            light.timer_stop = true;
        }

        light.times = 0;
        led_off(light.led_net_pin);
//        if(light.oriSta){
//            led_on(light.led_net_pin);
//        }else{
//            led_off(light.led_net_pin);
//        }
    }
}
