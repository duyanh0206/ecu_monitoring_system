#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include "config.h"

Status check_engine_temp(float *engine_temp) {
  Status s;

  if (*engine_temp < ENGINE_TEMP_WARN)
    s = OK;
  else if (*engine_temp >= ENGINE_TEMP_WARN && *engine_temp <= ENGINE_TEMP_DANGER)
    s = WARN;
  else
    s = DANGER;

  printf("%s %.1f C [%s]\n", "Nhiet do dong co:", *engine_temp,
         status_to_string(s));

  return s;
}

Status check_tire_psi(float *tire_psi, const char **tire_name, int n) {
  int i;
  Status overall = OK;

  printf("%-14s %s %s\n", " Lop xe", "Ap suat", "Trang thai"); 
  printf("%-14s %s %s\n", "-------", "--------", "----------");

  for (i = 0; i < n; i++) {
    float psi = *(tire_psi + i); 
    Status s;

    if (psi < TIRES_PSI_LOW)
      s = DANGER;
    else if (psi >= TIRES_PSI_LOW && psi <= TIRES_PSI_HIGH)
      s = OK;
    else
      s = WARN;

    printf("  %-14s  %5.1f PSI  [%s]\n", tire_name[i], psi,
        status_to_string(s));
}
  return overall;
}

Status check_fuel_pct(float *fuel_pct) {
  int numr_bars = (int)(*fuel_pct / 10.f), i; // Muc nhien lieu
  char bar[11] = {0};
  Status s;

  for (i = 0; i < 10; i++) {
    bar[i] = (i < numr_bars) ?  '#' : '.';

    if(*fuel_pct > FUEL_PCT_WARN)
      s = OK;
    else if (*fuel_pct >= FUEL_PCT_WARN && *fuel_pct <= FUEL_PCT_DANGER)
      s = WARN;
    else
      s = DANGER;
  }

  printf("  %s %.1f%%  [%s]  [%s]\n",
           "Muc nhien lieu:", *fuel_pct, bar, status_to_string(s));
  return s;
}

float avg_speed(float *wheel_spd, int n){
  float tong = 0.0f;
  int i;

  for (i = 0; i < NUM_WHEELS; i++) {
    tong += wheel_spd[i];
  }
  return tong / NUM_WHEELS;
}

void check_abs(float *wheel_spd, const char **wheel_name, int n) {
  int i;
  float tb = avg_speed(wheel_spd, n);

  printf(" %-10s %-12s  %s\n ", "Banh xe", "Toc do", "ABS Check");
  printf("%-10s %-12s  %s\n ", "-------", "--------", "----------");

  for (i = 0; i < n; i++) {
    float vel = *(wheel_spd + i);

    Status s = (fabsf(vel - tb) > ABS_DIFF_THRESHOLD) ? WARN : OK; // fabsf la ham tinh gia tri tuyet doi

    printf(" %-10s %6.1f km/h  [%s]\n", *(wheel_name + i), vel,
           status_to_string(s));
    
  }
  printf("Trunh binh: %.1f km/h\n", tb);
}

void check_seatbel(int *seatbel, const char **seat_name, int n, float tb) {
  int i;
  Status s = OK;

  printf("%-14s %s\n", "Ghe ngoi", "Day an toan");
  printf("%-14s %s\n", "--------", "----------");

  for (i = 0; i < n; i++) {
    printf("%-14s %s\n", *(seat_name + i),
           *(seatbel + i) ? "!!! CHUA THAT DAY AN TOAN !!!"
                          : "DA THAT DAY AN TOAN        ");
    if (*(seatbel + i) == 1)
      s = DANGER;
  }
  if (s && tb > 5.0f) {
    for (i = 0; i < n; i++) {
      if (seatbel[i]) {
        printf("\n !!! CANH BAO !!!\n");
        printf("[%s] CHUA THAT DAY AN TOAN KHI XE DANG CHAY !\n", seat_name[i]);
        printf("YEU CAU THAT DAY AN TOAN NGAY !\n");
      }
    }
  }
}

void check_door(int *door, const char **door_name, int n, float tb) {
  int i;
  Status s = OK;

  printf("%-14s %s\n", "Cua xe", "Trang thai");
  printf("%-14s %s\n", "--------", "----------");

  for (i = 0; i < n; i++) {
    printf("%-18s %s\n", *(door_name + i),
           *(door + i) ? "!!! CHUA DONG CUA XE !!!"
                          : "DA DOMG CUA XE       ");
    if (*(door + i) == 1)
      s = DANGER;
  }
  if (s && tb > 2.0f) {
    for (i = 0; i < n; i++) {
      if (door[i]) {
        printf("\n !!! CANH BAO !!!\n");
        printf("[%s] CHUA DONHG KHI XE DANG CHAY !\n", door_name[i]);
        printf("YEU CAU DONG CUA XE NGAY LAP TUC !\n");
      }
    }
  }
}

// xoa toan bo noi dung dang hien thi tren man hinh
void clear_screen(void) {
  #ifdef _WIN32 // Windows
    system("cls"); 
  #else //  Linux, macOS
    system("clear");
  #endif
}

// dung man hinh
void pause_screen(void) {
  printf("\n Nhan Enter de quay lai menu...");
  while(getchar() != '\n');
}





        