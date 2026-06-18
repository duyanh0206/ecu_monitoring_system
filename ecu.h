#include "config.h"

typedef enum {
  OK,
  WARN, // canh bao
  DANGER // nguy hiem
} Status;


typedef struct {
  float engine_temp; // nhiet do dong co (C)
  float tire_psi[NUM_TIRES]; // ap suat lop cua 4 banh xe (PSI)
  float fuel_pct; // phan tram nhien lieu (%)
  float wheel_spd[NUM_WHEELS]; // toc do cua 4 banh xe (km/h)
  int seatbel[NUM_SEATS];     // trang thai cua 5 cho ngoi (0:da that, 1: chua that)
  int door[NUM_DOORS];        // trang thai cua 4 canh cua (0: da mo, 1: chua mo)

} ECU_Data;

extern const char *tire_names[NUM_TIRES]; // lop xe
                                          
extern const char *wheel_names[NUM_WHEELS]; // banh xe

extern const char *seat_names[NUM_SEATS]; // cho ngoi

extern const char *door_names[NUM_DOORS]; // canh cua
                                          
const char* status_to_string(Status status); // chuyen enum sang chuoi