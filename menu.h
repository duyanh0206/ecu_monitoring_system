#ifndef MENU_H
#define MENU_H

#include "ecu.h"

void bao_cao_thong_tin(ECU_Data *ecu); // menu tat ca cac bao cao thong tin

void update_engine_temp(ECU_Data *ecu); // cap nhat nhiet do dong co

void update_tire_psi(ECU_Data *ecu);// cap nhat ap suat lop

void update_fuel_pct(ECU_Data *ecu);// cap nhat phan tram nhien lieu

void update_wheel_spd(ECU_Data *ecu);// cap nhat toc do

void update_seatbel(ECU_Data *ecu);// cap nhat day an toan

void update_door(ECU_Data *ecu); // cap nhat canh cua

void save_log(ECU_Data *ecu, int lan); // luu log

void view_log(void); // xem log

void delete_log(void); // xoa log

void edit_menu(ECU_Data *ecu); // chinh sua

void menu_log(ECU_Data *ecu); // menu log (luu, xem, xoa)

void display_sensor_menu(ECU_Data *ecu); // menu chinh

void view_each_sensor(ECU_Data *ecu); // xem tung cam bien

#endif 