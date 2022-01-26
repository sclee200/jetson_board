#include <sys/types.h>                                        // 헤더파일
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int state;
    if (argc !=2 )
    {
        fprintf(stderr,"Usage : %s [filename]\n", argv[0]);
        return 1;
    }
    state = mkfifo("/tmp/myfifo", S_IRUSR|S_IWUSR);        // fifo 파일 생성
    if (state < 0)
    {
        perror("mkfifo error \n");
        return 1;
    }
    return 0;
}
