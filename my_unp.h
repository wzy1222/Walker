#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>

#define MAXLINE 1024

void err_quit(const char *fmt,...);
ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);
// I don't like readline,I would rather than use readn(MAXLINE)..haha.
ssize_t readline(int fd, void *buf, size_t maxlen);

