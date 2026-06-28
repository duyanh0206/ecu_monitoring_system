#include "ecu.h"
// Lop xe
const char *tire_names[NUM_TIRES] = {
    "Truoc Trai", "Truoc Phai", "Sau Trai", "Sau Phai"};
// Banh xe
const char *wheel_names[NUM_WHEELS] = {
    "Banh TT", "Banh TP", "Banh ST", "Banh SP"};
// Cho ngoi
const char *seat_names[NUM_SEATS] = {
    "Lai xe", "Phu xe", "Hang2_Trai", "Hang2_Giua", "Hang2_Phai"};
// Canh cua
const char *door_names[NUM_DOORS] = {
    "Cua Truoc Trai", "Cua Truoc Phai", "Cua Sau Trai", "Cua Sau Phai"};


//Chuyen enum sang chuoi
const char* status_to_string(Status s) {
  if (s == WARN)
    return "Canh bao!!!";
  if (s == DANGER)
    return "Nguy hiem!!!";

  return "OK";   
}