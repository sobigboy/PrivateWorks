#pragma once
#ifndef _R_SOCKETCOM_H
#define _R_SOCKETCOM_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef LINUX
#include <WinSock2.h>

#else
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#endif

#define MAX_BUFFER_LEN	(512)

int create_udp_socket(u_short local_port);
int close_udp_socket(int sock_fd);
int recv_msg(int sock_fd, struct sockaddr* paddr_dest, unsigned char * recv_buf);


#endif	