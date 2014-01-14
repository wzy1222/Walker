#include "my_unp.h"

void err_quit(const char *fmt,...)
{
    int res;
    va_list list;
    va_start(list,fmt);
    res = vfprintf(stderr,fmt,list);
    if( errno != 0 )
        fprintf(stderr," : %s",strerror(errno));
    fprintf(stderr,"\n",list);
    va_end(list);
    exit(1);
}

//when the socket invoke read(),the return value may less than the count
//because of the full buffer,and you need to invoke read() again.
ssize_t readn(int fd,void *buf,size_t count)
{
    // the count cant't greater than 65535, or you don't know the answer
    // the read() return :
    //1. full buffer                0<res<count
    //2. signal iterruption         res < 0, errno = EINTR
    //3  error                      res < 0
    //4  EOF                        res = 0


	/* 2013.01.14
	 * 解决 count是个大数的问题
	 * 只要缓冲区足够， 分次读
	 */

    size_t nleft;
    ssize_t nread;
	size_t n;
    char *ptr;

    ptr=(char *)buf;
    nleft=count;
    while(nleft>0)
    {
		if(nleft > MAXLINE)
			n = MAXLINE;
		else
			n = nleft;
        if((nread = read(fd,ptr,n)) < 0)
        {
            if(errno == EINTR)
                nread = 0;  /* interrupt by  the signal,call again */
            else
                return -1;  /* unexpect error */
        }
        else if(nread == 0)
            break;          /* EOF */
        else
        {
            nleft -= nread;
            ptr += nread;   /* full buffer */
        }
    }
    return (count - nleft);     /* return >= 0 */
}

//when the socket invoke write(),the return value may less than the count
//because of the full buffer,and you need to invoke write() again.
ssize_t writen(int fd,const void *buf,size_t count)
{
    //return situation is same as readn. 
	//
	
	/*
	 * 2013.01.14
	 * 解决count是个大数的问题
	 */

    size_t nleft;
    const char *ptr;
    ssize_t nwrite;
 
    ptr = (const char *)buf;
    nleft = count;
	size_t n;
    while(nleft>0)
    {
		if(nleft > MAXLINE)
			n = MAXLINE;
		else
			n = nleft;
        if( (nwrite = write(fd,ptr, n)) < 0)
        {
            if( errno == EINTR )
                nwrite = 0;         /* interrupt by signal */
            else
                return -1;          /* unexpect error */
        }
        else if(nwrite == 0 )
            break;                  /* EOF */
        else
        {
            ptr += nwrite;
            nleft -= nwrite;        /* full buffer */
        }
    }
    return (count - nleft);
}

static int read_cnt = 0;
static char *read_ptr;
static char read_buf[MAXLINE];

// my_read,read at most MAXLINE bytes,and return one byte each time.
static ssize_t my_read(int fd,char *ptr)
{
    while( read_cnt <= 0)
    {
        if( (read_cnt = read(fd,read_buf,sizeof(read_buf))) < 0 )
        {
            if( errno == EINTR )
                continue ; /* interrupt by signal */
            else
                return -1; /* unexpect error */
        }
        else if( read_cnt == 0 )
            return 0;       /* EOF */
        read_ptr = read_buf ;   /* read > 0, get something */
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}
ssize_t readline(int fd, void *buf, size_t maxlen)
{
    ssize_t res_count;
    char ch,*ptr;
    int i;

    ptr = (char *)buf;

    for(i=1;i<=maxlen;++i)
    {   
        if( 1 == ( res_count = my_read(fd,&ch)) )
        {
            *ptr++ = ch;
            if( ch == '\n' )
                break;  /* one line or one string got */
        }
        else if( res_count == 0)
        {
            *ptr = 0;   /* EOF */
            return (i-1);
        }
        else
            return -1; /* error, errno set by read() */
    }
    *ptr=0;
    return i;
}
