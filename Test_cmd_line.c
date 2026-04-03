#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cmd_line.h"

// --- CAC HAM XU LY LENH (HANDLER) ---
int32_t cmd_led_on(const uint8_t* argv) {
    printf("[DEVICE]: Da bat den LED THANH CONG!\n");
    return (int32_t)CMD_SUCCESS;
}

int32_t cmd_get_version(const uint8_t* argv) {
    printf("[DEVICE]: Phien ban phan mem VER 1 NAM 2026\n");
    return (int32_t)CMD_SUCCESS;
}

// --- KHOI TAO BANG LENH ---
cmd_line_t my_table[] = {
    {(const int8_t*)"led_on",  cmd_led_on,      (const int8_t*)"Bat den LED"},
    {(const int8_t*)"version", cmd_get_version, (const int8_t*)"Xem version"},
    {NULL, NULL, NULL} 
};

// --- HAM CHAY UNIT TEST ---
void run_test(const char* test_name, cmd_line_t* table, const char* input_str, uint8_t expected_result) {
    uint8_t input[50];
    strcpy((char*)input, input_str);
    
    printf("Test: %s\n", test_name);
    printf("User nhap: \"%s\"\n", input);
    
    uint8_t result = cmd_line_parser(table, input);
    
    if (result == expected_result) {
        printf("=> KET QUA: PASS\n");
    } else {
        printf("=> KET QUA: FAIL (Ma loi thuc te: %d, Mong doi: %d)\n", result, expected_result);
    }
    printf("------------------------------------------\n");
}

int main() {
    printf("--- BAT DAU KIEM THU 5 TRUONG HOP ---\n\n");

    // 1. Test thanh cong (CMD_SUCCESS)
    run_test("Lenh dung", my_table, "led_on", CMD_SUCCESS);

    // 2. Test sai lenh (CMD_NOT_FOUND)
    run_test("Lenh khong ton tai", my_table, "sontungMTP", CMD_NOT_FOUND);

    // 3. Test bang lenh bi rong (CMD_TBL_NOT_FOUND)
    run_test("Bang lenh NULL", NULL, "led_on", CMD_TBL_NOT_FOUND);

    // 4. Test lenh qua dai (CMD_TOO_LONG)
    // MAX_CMD_SIZE dang la 12, ta nhap chuoi dai hon 12 ky tu
    run_test("Lenh qua dai", my_table, "day_la_mot_lenh_rat_dai_vuot_qua_buffer", CMD_TOO_LONG);

    // 5. Test lenh co tham so (CMD_SUCCESS voi tham so)
    run_test("Lenh kem tham so", my_table, "version -all", CMD_SUCCESS);
    
    // Case 6: User chi nhan Enter, khong nhap chu nao
    run_test("Lenh rong", my_table, "", CMD_EMPTY);

    return 0;
}
