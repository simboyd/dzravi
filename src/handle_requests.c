#include "handle_requests.h"


void handle_connection(int sock)
{
	uint8_t receive_buffer[BUFFER_LENGTH] = {0};

	int res = 0;
	if((res = recv(sock, receive_buffer, BUFFER_LENGTH, 0)) > 0) // this is pretty bad
	{
		http_request_t request = parse_request(receive_buffer);
		uint8_t* response = get_response(&request);
		
		int a = send(sock, response, strlen((char*)response), 0);

		char log[128];
		sprintf(log, "Sent %d bytes.", a);
		lgr_log_text(log);
		
		free(response);
	}

	lgr_log_text("Connection closed!");
	close(sock);
}

http_request_t parse_request(uint8_t buffer[])
{
	http_request_t request = {0};
	char* char_buffer = (char*)buffer;
	char delimiter[2] = " ";

	char* token = strtok(char_buffer, delimiter);
	strcpy(request.verb, token);

	token = strtok(NULL, delimiter);
	strcpy(request.uri, token);

	get_protocol(token + strlen(token), request.protocol);
	get_host(token + strlen(token) + strlen(request.protocol), request.host);

	return request;
}

void get_protocol(char* buffer, char* outbuffer)
{
	char* it = buffer;

	// advance by 1 to skip the whitespace
	it++;
	
	
	// copy to result until carriage return is reached
	int i;
	for(i = 0; i < 32; i++)
	{
		outbuffer[i] = *(it++);

		if(*it == '\r')
			break;
	}
	
}

void get_host(char* buffer, char* outbuffer)
{
	char* it = buffer;

	// skip CRLF
	it += 2;

	// find next whitespace
	while(*(it++) != ' ') ;

	// skip the whitespace
	//it++;

	// get host until CR 
	int i = 0;
	while(*it != '\r')
	{
		outbuffer[i++] = *it;
		it++;
	}
}

uint8_t* get_response(http_request_t* request)
{
	
	char* response = (char*)malloc(1024 * 1024);

	if(strcmp("GET", request->verb) != 0 || strcmp("HTTP/1.1", request->protocol) != 0)
	{
		char* resp_tmp = "HTTP/1.1 400 Bad Request\r\n"
			 	"Content-Type: text/html\r\n"
				"Content-Length: 12\r\n\n"
				"Bad request";
		memcpy(response, resp_tmp, strlen(resp_tmp));
		return (uint8_t*)response;
	}

	int filesize = 0;
	uint8_t* filecontent = get_file(request->uri, &filesize);
	if(!filecontent)
	{
		char* resp_not_found = 	"HTTP/1.1 404 Not Found\r\n"
								"Content-Type: text/html\r\n"
								"Content-Length: 3\r\n\n"
								"404";
		memcpy(response, resp_not_found, strlen(resp_not_found));
		return (uint8_t*)response;
	}

	
	sprintf((char*)response, "HTTP/1.1 200 OK\r\n"
							 "Content-Type: text/html\r\n"
							 "Content-Length: %d\r\n\n"
							 "%s", filesize, (char*)filecontent);
	free(filecontent);
	return (uint8_t*)response;
}

uint8_t* get_file(char* path, int* outfilesize)
{
	if(strcmp(path, "/") == 0) path = "/index";
	
	char realpath[2048] = {0};
	sprintf(realpath, "../html%s", path);

	FILE* fp = fopen(realpath, "rb");
	if(!fp) return NULL;

	fseek(fp, 0, SEEK_END);
   	long filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	uint8_t* buffer = (uint8_t*)malloc(filesize + 1);
	fread(buffer, 1, filesize, fp);
	
	fclose(fp);
	buffer[filesize] = 0;

	*outfilesize = filesize - 1;
	return buffer;

		
}
