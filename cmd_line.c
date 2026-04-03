#include <string.h>
#include "cmd_line.h"

uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command) {
    uint8_t cmd_tmp[MAX_CMD_SIZE]; // Bien tam luu tu khoa vua tach
    const uint8_t* p_cmd = command;      // Con tro chay doc chuoi nhap vao
    uint8_t i = 0;                 // Bien dem index cho mang tam
    uint8_t idx = 0;               // Bien dem de duyet bang lenh

    // Kiem tra neu user ko nhap gi (chi nhan Enter)
    if (command[0] == '\0' || command[0] == '\r' || command[0] == '\n') {
        return CMD_EMPTY; 
    }

    // Kiem tra neu bang lenh bi rong thi bao loi ngay
    if (cmd_table == (cmd_line_t*)0) {
        return CMD_TBL_NOT_FOUND;
    }

    // Tach lay tu dau tien truoc khoang trang hoac xuong dong
    while (*p_cmd) {
        if (*p_cmd == ' ' || *p_cmd == '\r' || *p_cmd == '\n') {
            break;
        } 
        else {
            cmd_tmp[i++] = *(p_cmd++);
            // Neu tu khoa dai qua muc cho phep thi bao loi
            if (i >= MAX_CMD_SIZE) {
                return CMD_TOO_LONG;
            }
        }
    }
    cmd_tmp[i] = 0; // Ket thuc chuoi bang ky tu null

    // Duyet qua tung dong cua bang lenh de so sanh
    while (cmd_table[idx].cmd) {
        // So sanh tu khoa vua tach voi lenh trong bang
        if (strcmp((const char*)cmd_table[idx].cmd, (const char*)cmd_tmp) == 0) {
            // Neu khop thi goi ham xu ly va truyen toan bo tham so vao
            cmd_table[idx].func(command);
            return CMD_SUCCESS;
        }
        idx++; // Chuyen sang kiem tra lenh tiep theo
    }
    
    


    // Neu chay het bang ma ko thay thi bao loi ko tim thay
    return CMD_NOT_FOUND;
}
