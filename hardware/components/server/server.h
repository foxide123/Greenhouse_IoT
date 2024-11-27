#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>
#include <stddef.h>

void build_http_response(char* data, int client_fd);

void *handle_client(void *arg);

int server_init(void);
#endif