#include <sys/types.h>               // 헤더 파일
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define  FIFO_FILE   "/tmp/fifo"

int main( void)
{
   int   fd;
   char *str   = "system programming\n\r";

   if ( -1 == ( fd = open( FIFO_FILE, O_WRONLY)))           //  fifo 파일 열기
   {
      perror( "open() error");
      exit( 1);
   }

   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, str, strlen( str));			   //  fifo 파일 쓰기
   sleep(1);
   write( fd, "q", 1);			   //  fifo 파일 쓰기
   sleep(1);
   close( fd);
}
