#include "fileControl.h"

fileControl::fileControl(const char *pname)
{
	ssize_t len = strlen(pname);
	if(len >= FILE_NAME_MAX)
		err_quit("fileControl::fileControl(): file name is too long");
	strncpy(pfilename, pname, FILE_NAME_MAX - 1);
	pfilename[FILE_NAME_MAX - 1] = '\0';	
}

fileControl::~fileControl()
{

}


bool fileControl::splitFile(int nBlock, bool bOneLine)
{
	if(nBlock > FILE_SPLIT_MAX)
		err_quit("fileControl::splitFile: block is too many\n");
	int fd = open(pfilename, O_RDONLY);
	if(fd < 0)
		err_quit("fileControl::splitFile: failed in open()\n");

	off_t nfilesize;
	nfilesize = lseek(fd, 0, SEEK_END);
	if(nfilesize == -1)
		err_quit("fileControl::splitFile: failed in lseek()\n");

	off_t offarr[FILE_SPLIT_MAX];
	off_t off_each = nfilesize / nBlock;
	off_t offpre = 0;
	off_t offtmp;
	char ch;
	off_t offadd;


	if(bOneLine == false)
	{
		for(int i = 0; i < nBlock; ++i)
			offarr[i] = off_each * (i+1);
		offarr[nBlock - 1] = nfilesize;
	}
	else
	{
		for(int i = 0; i < nBlock; ++i)
		{
		   offtmp = offpre + off_each;
		   if(-1 == lseek(fd, offtmp, SEEK_SET))
		   {
			   offtmp = nfilesize;
			   lseek(fd, offtmp, SEEK_SET);
		   }
		   offadd = 0;

		   while(true)
		   {
			   if(-1 == read(fd, &ch, 1))
				   break;
			   if(ch != '\n')
			   {
				   ++offadd;
				   continue;
			   }
			   if(ch == '\n')
			   {
				   ++offadd;
				   break;
			   }
		   }
		   offarr[i] = offtmp + offadd;
		   offpre = offarr[i];
		}
	}

	char outname[FILE_NAME_MAX + 5];
	int fdout;
	char buf[MAXLINE];
	int nleft;
	ssize_t nread,nwrite;
	
	offpre = 0;
	for(int i = 0; i < nBlock; ++i)
	{
		sprintf(outname, "%s.tmp%d", pfilename, i);
		fdout = open(outname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(fdout == -1)
			err_quit("open %s failed\n", outname);
		// copy to new small file.
		nleft = offarr[i] - offpre;
		if(-1 == lseek(fd, offpre, SEEK_SET))
			err_quit("copy failed! failed in lseek()\n");
		while(nleft > 0)
		{
			if(nleft > MAXLINE)
			{
				nread = read(fd, buf, MAXLINE);
				if(nread == -1)
					err_quit("copy failed! read() return -1\n");
				nwrite = write(fdout, buf, nread);
				if(nread != nwrite)
					err_quit("copy failed! write() != read()\n");
				nleft -= MAXLINE;
			}
			else
			{
				nread = read(fd, buf, nleft);
				if(nread == -1)
					err_quit("copy failed! read() return -1\n");
				nwrite = write(fdout, buf, nread);
				if(nread != nwrite)
					err_quit("copy failed! write() != read()\n");
				nleft -= nleft;
			}
		}
		close(fdout);
		offpre = offarr[i];
	}
    return true;
}

