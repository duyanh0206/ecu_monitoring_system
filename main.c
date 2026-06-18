#include "sensor.h"

int main() {
  
ECU_Data ecu;
  
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

    // check_engine_temp(&ecu.engine_temp); // kiem tra nhiet do dong co

    // check_tire_psi(ecu.tire_psi, tire_names, 4);    // kiem tra ap suat lop cua 4 banh xe

    // check_fuel_pct(&ecu.fuel_pct); // kiem tra phan tram nhien lieu

    // check_abs(ecu.wheel_spd, wheel_names, 4); // kiem tra ABS

    // check_seatbel(ecu.seatbel, seat_names, 5, ecu.engine_temp); // kiem tra day an toan
    
    check_door(ecu.door, door_names, 4, ecu.engine_temp); // kiem tra canh cua



    return 0;
}
/* chay chupng trinh

gcc *.c -o main && ./main
*/