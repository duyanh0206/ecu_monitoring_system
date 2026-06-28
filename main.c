#include "menu.h"
#include "sensor.h"

int main() {

  ECU_Data ecu;
  static int lan = 0;
  
    ecu.engine_temp = 105.0f;

    ecu.tire_psi[0] = 32.5f;
    ecu.tire_psi[1] = 31.0f;
    ecu.tire_psi[2] = 30.5f;
    ecu.tire_psi[3] = 22.3f;

    ecu.fuel_pct = 26.0f; 

    ecu.wheel_spd[0] = 78.5f;
    ecu.wheel_spd[1] = 60.2f;  
    ecu.wheel_spd[2] = 79.1f;
    ecu.wheel_spd[3] = 77.8f;

    ecu.seatbel[0]   = 0;
    ecu.seatbel[1]   = 0;
    ecu.seatbel[2]   = 1;
    ecu.seatbel[3]   = 0;
    ecu.seatbel[4]   = 0;

    ecu.door[0] = 0; 
    ecu.door[1] = 0;
    ecu.door[2] = 1;
    ecu.door[3] = 0;

    display_sensor_menu(&ecu);

    return 0;
}
/* chay chupng trinh

gcc *.c -o main && ./main
*/