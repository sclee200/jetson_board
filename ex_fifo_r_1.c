#include <stdio.h>

#include <sys/types.h> // 헤더 파일

#include <sys/stat.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <unistd.h>

#include <pthread.h>

//#define FIFO_FILE "/tmp/fifo"

#define FIFO_FROM_YOLO "/tmp/from_yolo_fifo"

#define FIFO_TO_YOLO "/tmp/to_yolo_fifo"

#define BUFF_SIZE 1024

//char buff_a[BUFF_SIZE];
char buff[BUFF_SIZE];

int fd_from_yolo;

int fd_to_yolo;

// 쓰레드 함수

void *t_function(void *data)

{

int id;

int i = 0;

id = *((int *)data);


//from yolo

while(1)

{

while(read(fd_from_yolo, buff, BUFF_SIZE) != NULL)

{

//write( handle, buff, 1 );

printf("%s", buff);

memset(buff, 0x00, BUFF_SIZE);

}

}

}

int main( void)

{

pthread_t p_thread[2];

int thr_id;

int status;

int a = 1;

int b = 2;

int counter = 0;

int fd;

char buff[BUFF_SIZE];

// 쓰레드 생성 아규먼트로 1 을 넘긴다. 

thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)&a);

if (thr_id < 0)

{

perror("thread create error : ");

exit(0);

}

//if ( -1 == mkfifo( FIFO_FILE, 0666)) // fifo 파일 생성

//{

// perror( "mkfifo() run error");

// exit( 1);

//}


//if ( -1 == ( fd = open( FIFO_FILE, O_RDWR))) // fifo 파일 열기

//{

// perror( "open() error");

// exit( 1);

//}

// from wifi thread

if ( -1 == ( fd_from_yolo = open(FIFO_FROM_YOLO, O_RDWR) ))

{

if ( -1 == mkfifo( FIFO_FROM_YOLO, 0666))

{

perror( "mkfifo() run error");

//exit( 1);

}

if ( -1 == ( fd_from_yolo = open( FIFO_FROM_YOLO, O_RDWR)))

{

perror( "open() error");

//exit( 1);

}

}

// to wifi thread

if ( -1 == ( fd_to_yolo = open( FIFO_TO_YOLO, O_RDWR)))

{

if ( -1 == mkfifo( FIFO_TO_YOLO, 0666))

{

perror( "mkfifo() run error");

//exit( 1);

}

if ( -1 == ( fd_to_yolo = open( FIFO_TO_YOLO, O_RDWR)))

{

perror( "open() error");

//exit( 1);

}

}

while( 1 )

{

memset( buff, 0, BUFF_SIZE);

//read( fd, buff, BUFF_SIZE); // fifo 파일 읽기

//printf( "%d: %s\n", counter++, buff);

buff[0] = 'A';

write( fd_to_yolo, buff, 1 );

printf("%c send\n", buff[0]);

if( buff[0]=='q')

{

close(fd);

system("rm -rf /tmp/fifo");

exit(0);

}

}

close( fd);

}
