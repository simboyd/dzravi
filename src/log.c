#include "log.h"

void lgr_log_bytes(uint8_t* bytes, int length)
{
	bytes[length - 2] = 0; // for now; dont need the CR/LF shit
	printf("[MSG]\t%s (%d bytes)\n", (char*)bytes, length);
}

void lgr_log_error(const char* msg, int additional)
{
	printf("[ERROR]\t%s additional data -> %s\n", msg, strerror(additional));
}

void lgr_log_text(const char* msg)
{
	printf("[LOG]\t%s\n", msg);
}
