#ifndef _CMD_LINE_H_
#define _CMD_LINE_H_

#include <stdint.h>

// Do dai toi da cua mot tu khoa lenh
#define MAX_CMD_SIZE 12 

// Cac ma loi tra ve cho he thong
#define CMD_SUCCESS          0  // Thuc thi thanh cong
#define CMD_TBL_NOT_FOUND    1  // Khong tim thay bang lenh
#define CMD_NOT_FOUND        2  // Lenh khong ton tai
#define CMD_TOO_LONG         3  // Lenh nhap vao qua dai
#define CMD_EMPTY            4  // Chuoi rong
// Dinh nghia kieu con tro ham cho cac lenh
typedef int32_t (*pf_cmd_func)(const uint8_t* argv);

// Cau truc cua mot dong trong bang lenh
typedef struct {
    const int8_t* cmd;    // Tu khoa lenh
    pf_cmd_func func;     // Ham xu ly tuong ung
    const int8_t* info;   // Mo ta lenh
} cmd_line_t;

// Khai bao prototype ham parser
uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command);

#endif
