#include <stdlib.h>
#include <stdio.h>
#include "menu.h"
#include "config.h"
#include "sensor.h"
#include "ecu.h"


void bao_cao_thong_tin(ECU_Data *ecu) {
  float tb = avg_speed(ecu->wheel_spd, NUM_WHEELS);

  printf("\n");
  printf("------------------------------------------------\n");
  printf("                 BAO CAO THONG TIN            \n");
  printf("------------------------------------------------\n");
  printf("\n [1] NHIET DO DONG CO \n");
  check_engine_temp(&ecu->engine_temp);
  printf("\n [2] AP SUAT LOP \n");
  check_tire_psi(ecu->tire_psi, tire_names, NUM_TIRES);
  printf("\n [3] PHAN TRAM NHEN LIEU \n");
  check_fuel_pct(&ecu->fuel_pct);
  printf("\n [4] TOC DO BANH XE(ABS) \n");
  check_abs(ecu->wheel_spd, wheel_names, NUM_WHEELS);
  printf("\n [5] DAY AN TOAN \n");
  check_seatbel(ecu->seatbel, seat_names, NUM_SEATS, tb);
  printf("\n [6] CANH CUA XE \n");
  check_door(ecu->door, door_names, NUM_DOORS, tb);
}

void update_engine_temp(ECU_Data *ecu) {

  printf("\n Nhiet do hien tai: %.1f C \n", ecu->engine_temp);
  printf("Moi nhap nhiet do moi(C)");
  scanf("%f", &ecu->engine_temp);
  getchar();
  printf("Da cap nhat nhiet do moi: %.1f C\n", ecu->engine_temp);
}

void update_tire_psi(ECU_Data *ecu) {
  int i, banh;

  for (i = 0; i < NUM_TIRES; i++) {
    printf("    [%d] %-14s  %.1f PSI\n", i+1, tire_names[i], ecu->tire_psi[i]);
    printf("  Chon banh (1-%d): ", NUM_TIRES);
    scanf("%d", &banh);
    getchar();
    if (banh < 1 || banh > NUM_TIRES) {
      printf("  Khong hop le!\n");
      return;
      }
    printf("  Nhap ap suat moi cho [%s] (PSI): ", tire_names[banh-1]);
    scanf("%f", &ecu->tire_psi[banh-1]); getchar();
    printf(" Da cap nhat: %.1f PSI\n", ecu->tire_psi[banh-1]);
  }
}

void update_fuel_pct(ECU_Data *ecu) {

  printf("\n Muc nhien lieu hien tai: %.1f %%\n", ecu->fuel_pct);
  printf("Moi nhap muc nhien lieu moi(%%): ");
  scanf("%f", &ecu->fuel_pct);
  getchar();
  if (ecu->fuel_pct > 100.0f)
    ecu->fuel_pct = 100.0f;
  if(ecu->fuel_pct < 0.0f) ecu->fuel_pct = 0.0f;
  printf("Da cap nhat muc nhien lieu moi: %.1f %%\n", ecu->fuel_pct);
}

void update_wheel_spd(ECU_Data *ecu) {
  int i, banh;

  printf("\n  Toc do hien tai:\n");

  for (i = 0; i < NUM_WHEELS; i++) {
    printf("    [%d] %-14s  %.1f km/h\n", i+1, wheel_names[i], ecu->wheel_spd[i]);
    printf("  Chon banh (1-%d): ", NUM_WHEELS);
    scanf("%d", &banh);
    getchar();

    if (banh < 1 || banh > NUM_WHEELS) {
      printf("  Khong hop le!\n");
      return;
    }
    
    printf("  Nhap toc do moi cho [%s] (km/h): ", wheel_names[banh-1]);
    scanf("%f", &ecu->wheel_spd[banh-1]); getchar();
    printf(" Da cap nhat: %.1f km/h\n", ecu->wheel_spd[banh-1]);
  }
}

void update_seatbel(ECU_Data *ecu) {
  int i, cho;

  printf("\n  Trang thai cho ngoi hien tai:\n");

  for (i = 0; i < NUM_SEATS; i++) {
    printf("    [%d] %-14s  %s\n", i+1, seat_names[i], ecu->seatbel[i] ? "Da that" : "Chua that");
    printf("  Chon cho ngoi (1-%d): ", NUM_SEATS);
    scanf("%d", &cho);
    getchar();

    if (cho < 1 || cho > NUM_SEATS) {
      printf("  Khong hop le!\n");
      return;
    }
    
    printf("  Nhap trang thai moi cho [%s]: ", seat_names[cho-1]);
    scanf("%d", &ecu->seatbel[cho-1]); getchar();
    printf(" Da cap nhat: %s\n", ecu->seatbel[cho-1] ? "Da that" : "Chua that");
  }
}

void update_door(ECU_Data *ecu) {
  int i, canh;

  printf("\n  Trang thai canh cua hien tai:\n");

  for (i = 0; i < NUM_DOORS; i++) {
    printf("    [%d] %-14s  %s\n", i+1, door_names[i], ecu->door[i] ? "Da mo" : "Chua mo");
    printf("  Chon canh cua (1-%d): ", NUM_DOORS);
    scanf("%d", &canh);
    getchar();

    if (canh < 1 || canh > NUM_DOORS) {
      printf("  Khong hop le!\n");
      return;
    }
    
    printf("  Nhap trang thai moi cho [%s]: ", door_names[canh-1]);
    scanf("%d", &ecu->door[canh-1]); getchar();
    printf(" Da cap nhat: %s\n", ecu->door[canh-1] ? "Da mo" : "Chua mo");
  }
}

void save_log(ECU_Data *ecu, int lan) {
  FILE *f = fopen(LOG_FILE, "wb");
  int i;

  if (!f) { printf("  [LOI] Khong mo duoc file log!\n");
    return;
  }
  
    fprintf(f, "=== LAN DO #%d ===\n", lan);
    fprintf(f, "Nhiet do : %.1f C\n", ecu->engine_temp);
    fprintf(f, "Ap suat  : ");

    for (i = 0; i < NUM_TIRES; i++)
      fprintf(f, "%s=%.1fPSI  ", tire_names[i], ecu->tire_psi[i]);

    fprintf(f, "\n Xang     : %.1f%%\n", ecu->fuel_pct);
    fprintf(f, " Toc do   : ");

    for (i = 0; i < NUM_WHEELS; i++)
        fprintf(f, "%s=%.1fkm/h  ", wheel_names[i], ecu->wheel_spd[i]);
    fprintf(f, "\n\n");

    fclose(f);

    printf("  >> Da luu log lan #%d vao [%s]\n", lan, LOG_FILE);
}


void view_log(void) {
  FILE *f = fopen(LOG_FILE, "r");

  char dong[256];

  if (!f) {
    printf("\n  Chua co log nao duoc luu.\n");
    return;
  }
  
    printf("\n  === NOI DUNG FILE LOG [%s] ===\n\n", LOG_FILE);
    while (fgets(dong, sizeof(dong), f))
      printf("  %s", dong);
    
    fclose(f);
}

void delete_log(void) {
  FILE *f = fopen(LOG_FILE, "w");
  
    if (f) fclose(f);
    printf(" [THONG BAIO] Da xoa toan bo log\n");
}

void edit_menu(ECU_Data *ecu) {
  static int lan = 0;
  int choice;

  while (1) {
    clear_screen();
    printf("\n");
        printf("  +------------------------------------------+\n");
        printf("  |        CHINH SUA DU LIEU CAM BIEN        |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  [1]  Nhiet do dong co                   |\n");
        printf("  |  [2]  Ap suat lop                        |\n");
        printf("  |  [3]  Muc nhien lieu                     |\n");
        printf("  |  [4]  Toc do banh xe                     |\n");
        printf("  |  [5]  Day an toan                        |\n");
        printf("  |  [6]  Cua xe                             |\n");
        printf("  |  [0]  Quay lai                           |\n");
        printf("  +------------------------------------------+\n");
        printf("  Moi nhap lua chon cau ban muon chinh sua(0-6): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
          update_engine_temp(ecu);
          break;
        case 2:
          update_tire_psi(ecu);
          break;
        case 3:
          update_fuel_pct(ecu);
          break;
        case 4:
          update_wheel_spd(ecu);
          break;
        case 5:
          update_seatbel(ecu);
          break;
        case 6:
          update_door(ecu);
          break;
        case 0:
          save_log(ecu, lan);
          return;
          break;
        default:
          printf("Lua chon khong hop le. Vui long nhap lai(0-6).\n");
          break;
        }
        if (choice != 0)
          pause_screen();
  }
}

void menu_log(ECU_Data *ecu) {
  static int lan = 0;
  int choice;

  while (1) {
    clear_screen();
    printf("\n");
        printf("  +------------------------------------------+\n");
        printf("  |        QUAN LY LOG CAM BIEN               |\n");
        printf("  +------------------------------------------+\n");
        printf("  |  [1]  Xem log                            |\n");
        printf("  |  [2]  Luu log                            |\n");
        printf("  |  [3]  Xoa log                            |\n");
        printf("  |  [0]  Quay lai                           |\n");
        printf("  +------------------------------------------+\n");
        printf("  Moi nhap lua chon cau ban muon chinh sua(0-3): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
          view_log();
          break;
        case 2:
          save_log(ecu, ++lan);
          break;
        case 3:
          delete_log();
          break;
        case 0:
          return;
          break;
        default:
          printf("Lua chon khong hop le. Vui long nhap lai(0-3).\n");
          break;
        }
        if (choice != 0)
          pause_screen();
  }
}

void view_each_sensor(ECU_Data *ecu) {
  int choice;
  float tb = avg_speed(ecu->wheel_spd, NUM_WHEELS);

  clear_screen();
  printf("\n");
  printf("  +---------------------------------------------+\n");
  printf("  |              XEM TUNG CAM BIEN              |\n");
  printf("  +---------------------------------------------+\n");
  printf("  |  [1]  Nhiet do dong co                      |\n");
  printf("  |  [2]  Ap suat lop                           |\n");
  printf("  |  [3]  Muc nhien lieu                        |\n");
  printf("  |  [4]  Toc do banh xe                        |\n");
  printf("  |  [5]  Day an toan                           |\n");
  printf("  |  [6]  Cua xe                                |\n");
  printf("  +---------------------------------------------+\n");
  printf("  Moi nhap lua chon cau ban muon chinh sua(0-6): ");
  scanf("%d", &choice);
  getchar();
  clear_screen();

  printf("\n");
  switch (choice) {
  case 1:
    check_engine_temp(&ecu->engine_temp);
    break;
  case 2:
    check_tire_psi(ecu->tire_psi, tire_names, NUM_TIRES);
    break;
  case 3:
    check_fuel_pct(&ecu->fuel_pct);
    break;
  case 4:
    check_abs(ecu->wheel_spd, wheel_names, NUM_WHEELS);
    break;
  case 5:
    check_seatbel(ecu->seatbel, seat_names, NUM_SEATS, tb);
    break;
  case 6:
    check_door(ecu->door, door_names, NUM_DOORS, tb);
  default:
    printf("Lua chon khong hop le. Vui long nhap lai(1-6).\n");
  }
}

void display_sensor_menu(ECU_Data *ecu) {
  int choice;
  float avg_spd;

    while (1) {
        avg_spd = avg_speed(ecu -> wheel_spd, NUM_WHEELS);
        clear_screen();
        printf("\n");
        printf("  +=============================================+\n");
        printf("  |      HE THONG GIAM SAT CAM BIEN O TO        |\n");
        printf("  +=============================================+\n");
        printf("  |                                             |\n");
        printf("  |   Toc do trung binh : %5.1f km/h            |\n", avg_spd); // sau khi thoat man hinh se luu lai du lieu vao file
        printf("  |   Nhiet do dong co  : %5.1f C               |\n", ecu->engine_temp);
        printf("  |   Muc nhien lieu    : %5.1f %%               |\n", ecu->fuel_pct);
        printf("  |                                             |\n");
        printf("  +---------------------------------------------+\n");
        printf("  |  [1]  Xem toan bo trang thai               |\n");
        printf("  |  [2]  Xem tung cam bien                    |\n");
        printf("  |  [3]  Chinh sua du lieu                    |\n");
        printf("  |  [4]  Quan ly file log                     |\n");
        printf("  |  [0]  Thoat                                |\n");
        printf("  +---------------------------------------------+\n");
        printf("  Lua chon: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
        case 1:
          clear_screen();
          bao_cao_thong_tin(ecu);
          pause_screen();
          break;
        case 2:
          view_each_sensor(ecu);
          pause_screen();
          break;
        case 3:
          edit_menu(ecu);
          break;
        case 4:
          menu_log(ecu);
          break;
        case 0:
          clear_screen();
          printf("\n  Tam biet! He thong ECU da tat.\n\n");
            return;
          default:
          printf("Lua chon khong hop le. Vui long nhap lai(0-4).\n");
          pause_screen();
        }
    }
}
