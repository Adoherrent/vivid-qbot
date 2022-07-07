#pragma once

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <err.h> 
#include <errno.h>
#include <ctype.h>
#include <fcntl.h>
#include <netdb.h>
#include <net/if.h> 
#include <dirent.h>
#include <signal.h>
#include <pthread.h>
#include <sys/time.h>   
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h> 
#include <linux/limits.h>
#define tf(gg)   (gg) + 0x22
#define tsu(timed)  do { char * times = timed ; while (*times) *times++ -= 0x22; } while(0)
#define tsh(timed)  do {char * times = timed ; while (*times) *times++ += 0x22;} while(0)
#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define INET_ADDR(o1,o2,o3,o4) (htonl((o1 << 24) | (o2 << 16) | (o3 << 8) | (o4 << 0)))
typedef uint32_t ipv4_t;
ipv4_t LOCAL_ADDR;

#define CLS "\e[1;1H\e[2J"
#define W "\x1b[37m"
#define R "\x1b[31m"
#define G "\x1b[32m"
#define CY "\x1b[1;36m"
#define Y "\x1b[1;33m"
#define CR "\x1b[0m"
#define UND "\x1b[1;4;36m"
#define NUND "\x1b[1;24;36m"
#define VIVY ""W"["CY"+"W"]"
#define VIVN ""W"["R"-"W"]"
/*
	RyM Gang
*/
