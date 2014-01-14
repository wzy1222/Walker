#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "walkerstd.h"


void err_quit(const char *fmt,...);
ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);
// I don't like readline,I would rather than use readn(MAXLINE)..haha.
ssize_t readline(int fd, void *buf, size_t maxlen);

