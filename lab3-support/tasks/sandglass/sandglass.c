#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define ESCAPE 0x1B
#define BRACKET 0x5B
#define sandsize 10

int main(void)
{
    char buffer[2];
    int i,j,k,n,time;
    printf("Please maximize the terminal window and press any key :)");
    read(STDIN_FILENO, buffer, 1);
    while(1){
        for(time =0; time < sandsize -1 ;time++){
            for(i=0,k=-(sandsize-1);i<sandsize;i++,k++)//k=0,k++
            {
                if(k <=0)
                {
                  n = k + sandsize-1;//n = k
                }
                else
                {
                  n = (k-(sandsize-1))* -1;//n--
                }

                for (j=0;j<n;j++) {
                    printf(" ");
                }
                if(n <= time && n!=0){
                    printf("*");
                    for (j=1; j<(sandsize*2-1)-2*n-1; j++) {
                        printf(" ");
                    }
                    printf("*");
                }
                else{
                    for (j=0; j<(sandsize*2-1)-2*n; j++) {
                        printf("*");
                    }
                }
                printf("\n");
            }

            for(i=sandsize,k=0;i<sandsize*2;i++,k++)//k=0,k++
            {
                if(k <=0)
                {
                  n = k + sandsize-1;//n = k
                }
                else
                {
                  n = (k-(sandsize-1))* -1;//n--
                }

                for (j=0;j<n;j++) {
                    printf(" ");
                }

                if(n >time && n!=(sandsize-1) && n!=0){
                    printf("*");
                    for (j=1; j<(sandsize*2-1)-2*n-1; j++) {
                        printf(" ");
                    }
                    printf("*");
                }
                else{
                    for (j=0; j<(sandsize*2-1)-2*n; j++) {
                        printf("*");
                    }
                }
                printf("\n");
            }
            sleep(2000);
            printf("%c%c20A", ESCAPE, BRACKET);
        }
    }
    return 0;
}

