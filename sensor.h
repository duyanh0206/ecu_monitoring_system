#include "ecu.h"

Status check_engine_temp(float *engine_temp); // kiem tra nhiet do dong co

Status check_tire_psi(float *tire_psi, const char **tire_name, int n); // kiem tra ap suat lop cua 4 banh xe

Status check_fuel_pct(float *fuel_pct); // kiem tra phan tram nhien lieu

float avg_speed(float *wheel_spd, int n);

void check_abs(float *wheel_spd, const char **wheel_name,
               int n); // kiem tra ABS

void check_seatbel(int *seatbel, const char **seat_name, int n,
                   float tb); // kiem tra day an toan

void check_door(int *door, const char **door_name,
                int n, float tb); // kiem tra canh cua

void clear_screen(void); // xoa man hinh

void pause_screen(void); // dung man hinh


