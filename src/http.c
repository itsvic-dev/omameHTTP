#include <stdio.h>
#include <string.h>

// if you see any compile-time errors, you're compiling for an unsupported
// ELVM backend, feel free to add the definition here and test!
#define ELVM_py "Python"
#define ELVM_bf "Brainfuck"
#define ELVM_bef "Befunge"

#ifndef TARGET
#define TARGET "Native"
#endif

#define PARSER_VERSION "1.2"

char* index_html = "<html><head><title>Hello!</title></head><body><p>Hello from %s!</p></body></html>";
char* not_found_html = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1></body></html>";
char* bad_request_html = "<html><head><title>400 Bad Request</title></head><body><h1>Bad Request</h1></body></html>";

void http_respond() {
	char request_buffer[512];
	int current_char = 0;
	int reading = 1;

	while (reading) {
		char data = (char) getchar();
		request_buffer[current_char] = data;
		if (data == '\n') {
			reading = 0;
		}
		current_char ++; // this also functions as string length
	}

	int cmp = strncmp(request_buffer, "GET / HTTP/1.1", current_char - 2); // strip line endings, in worst case removes the leading 1
	char* dataToPrint = index_html;

	if (cmp == 0 && current_char > 1) {
		printf("HTTP/1.1 200 OK\r\n");
	}

	if (cmp > 0) {
		printf("HTTP/1.1 404 Not Found\r\n");
		dataToPrint = not_found_html;
	}

	if (cmp < 0 || current_char <= 1) {
		printf("HTTP/1.1 400 Bad Request\r\n");
		dataToPrint = bad_request_html;
	}

	printf("Server: omameHTTP/%s (%s)\r\n", PARSER_VERSION, TARGET);
	printf("Content-Type: text/html\r\n");

	printf("\r\n");
	printf(dataToPrint, TARGET);
	printf("\r\n");
}
