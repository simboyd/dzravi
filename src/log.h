#pragma once
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void lgr_init();
void lgr_log_bytes(uint8_t*, int);
void lgr_log_error(const char*, int);
void lgr_log_text(const char*);
