#include <stdio.h>
#include <sys/types.h> 			// 헤더 파일
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


char buff[BUFF_SIZE];
int fd_from_yolo;
int fd_to_yolo;

int send_state;
// 쓰레드 함수
void *t_function(void *data)
{
    while(1)
    {
        while(read(fd_to_yolo, buff, BUFF_SIZE) != 0)
        {
            printf("%s\n", buff);
            send_state = 1;
        }
    }
}

int main( void)
{
    pthread_t p_thread[2];
    int thr_id;
    printf("main start\n");
    // 쓰레드 생성 아규먼트로 1 을 넘긴다. 
    thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)NULL);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    }

    printf("thread done!!!!\n");
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
    printf("fifo done!!!!\n");

    while( 1 )
    {
        if(send_state == 1)
        {
            send_state = 0;
            printf("echo start!!!!\n");

            write( fd_from_yolo, buff, 1 );
            printf("%s send\n", buff);

            if( buff[0]=='q')
            {
               close(fd_from_yolo);
               close(fd_to_yolo);
               //system("rm -rf /tmp/fifo");
               exit(0);
            }
            memset(buff, 0x00, BUFF_SIZE);
       }
    }
    close(fd_from_yolo);
    close(fd_to_yolo);
}
