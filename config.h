#ifndef CONFIG_H
#define CONFIG_H

// hang so
#define NUM_TIRES 4 // so luong lop
#define NUM_WHEELS 4 // so luong banh
#define NUM_DOORS 4 // so luong canh cua
#define NUM_SEATS 5 // so luong cho ngoi

// log file
#define LOG_FILE "ecu_log.txt"

// Nguong nhiet do dong co
#define ENGINE_TEMP_WARN 105.0f
#define ENGINE_TEMP_DANGER 120.0f

// Nguong ap suat lop
#define TIRES_PSI_LOW 26.0f
#define TIRES_PSI_HIGH 36.0f

// Nguong phan tram nhien lieu
#define FUEL_PCT_WARN 15.0f
#define FUEL_PCT_DANGER 5.0f

// Nguong ABS
#define ABS_DIFF_THRESHOLD 8.0f

#endif