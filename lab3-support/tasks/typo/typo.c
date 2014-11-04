/** @file typo.c
 *
 * @brief Echos characters back with timing data.
 * 
 * Authors: shang <shang@andrew.cmu.edu>          
 * Date:    9:22 Nov 3
 * Links to libc.
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BLOCK 100

int main(int argc, char** argv)
{
	char buffer[BLOCK+1];
	char prompt[] = "Please type characters within 100 length!\n";
	int length;
	unsigned long systime;

	while(1){
		write(STDOUT_FILENO, prompt, sizeof(prompt));
		systime = time();
		length = read(STDIN_FILENO, buffer, BLOCK);
		systime = time()- systime;
		write(STDOUT_FILENO, buffer, length+1);
		printf("%d.%ds\n", (int) systime/1000, (int) systime % 1000);	
	}
	return 0;
}
