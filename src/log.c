#include "log.h"

#define CHANGE_COLOR(x) { printf(x); fflush(stdout); }
#define TEXT_RED "\033[1;31m"
#define TEXT_BLUE "\033[1;34m"
#define TEXT_DEFAULT "\033[0m"

void lgr_log_bytes(uint8_t* bytes, int length)
{
	bytes[length - 2] = 0; // for now; dont need the CR/LF shit
	printf("[MSG]\t%s (%d bytes)\n", (char*)bytes, length);
}

void lgr_log_error(const char* msg, int additional)
{
	const char* add = NULL;
	if(additional == 0xDEADBEEF)
		add = "UNDEFINED_ERROR";
	else
		add = strerror(additional);

	CHANGE_COLOR(TEXT_RED);
	printf("[ERR]\t%s (%d: %s)\n", msg, additional, add);
	CHANGE_COLOR(TEXT_DEFAULT);
}

void lgr_log_text(const char* msg)
{
	CHANGE_COLOR(TEXT_BLUE);
	printf("[LOG]\t%s\n", msg);
	CHANGE_COLOR(TEXT_DEFAULT);
}
