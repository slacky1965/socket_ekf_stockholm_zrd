#ifndef SRC_INCLUDE_APP_LED_H_
#define SRC_INCLUDE_APP_LED_H_

typedef enum {
    CONTROL_LED_OFF = 0,
    CONTROL_LED_ON,
    CONTROL_LED_ON_OFF,
    CONTROL_LED_OFF_ON,
    CONTROL_LED_MAX,
} control_led_t;

typedef struct {
    ev_timer_event_t *timerLedEvt;

    bool     timer_stop;
    bool     status;

    uint32_t led_net_pin;
    bool     led_status;
    uint32_t led_status_pin;

    uint16_t ledOnTime;
    uint16_t ledOffTime;
    uint8_t  oriSta;     //original state before blink
    uint8_t  sta;        //current state in blink
    int8_t   times;      //blink times
} light_t;

void led_init(void);
void led_on(uint32_t pin);
void led_off(uint32_t pin);
void set_led_status(bool status);
void light_blink_start(uint8_t times, uint16_t ledOnTime, uint16_t ledOffTime);
void light_blink_stop(void);

#endif /* SRC_INCLUDE_APP_LED_H_ */
