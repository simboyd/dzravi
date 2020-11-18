#include "log.h"

void lgr_log_bytes(uint8_t* bytes, int length)
{
	printf("[LOG]\tsize: %d\n" , length);
}

void lgr_log_error(const char* msg, int additional)
{
	printf("[ERROR]\t%s additional data -> %d\n", msg, additional);
}

void lgr_log_text(const char* msg)
{
	printf("[LOG]\t%s\n", msg);
}