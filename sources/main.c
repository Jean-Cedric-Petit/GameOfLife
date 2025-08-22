#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

#define WIDTH 120
#define HEIGHT 30
#define SCREEN_SIZE (WIDTH+1)*HEIGHT+1 //64 chars wide + endline char & 16 lines for STR termination.
char screen1[SCREEN_SIZE]; 
char screen2[SCREEN_SIZE];
int main(){
	srand(time(NULL));
	char *scrn_ptr = screen1;
	char *buffer_ptr = screen2;
	char *temp = scrn_ptr;
	long tick = 0;
	
	
	system("mode con: cols=140 lines=40");  // Set console to 100x40
	
	//Initialize arrays with null terminators
    memset(screen1, 0, SCREEN_SIZE);
    memset(screen2, 0, SCREEN_SIZE);
    //Initial Compute on the buffer
	for(int i = 0; i < SCREEN_SIZE; i++){
		if(!((i + 1) % (WIDTH+1))) {
			buffer_ptr[i] = '\n';
			scrn_ptr[i] = '\n';
			continue;
		}
		buffer_ptr[i] = ' ';
		scrn_ptr[i] = ' ';

	}
	
	for(int k = 0; k < 5; k++) {
		int start_x = rand() % (WIDTH - 2);
		int start_y = rand() % (HEIGHT - 2);
		// Create 2x2 block
		buffer_ptr[start_y * (WIDTH + 1) + start_x] = 219;
		buffer_ptr[start_y * (WIDTH + 1) + start_x + 1] = 219;
		buffer_ptr[(start_y + 1) * (WIDTH + 1) + start_x] = 219;
		buffer_ptr[(start_y + 1) * (WIDTH + 1) + start_x + 1] = 219;
		// Do the same for scrn_ptr
		scrn_ptr[start_y * (WIDTH + 1) + start_x] = 219;
		scrn_ptr[start_y * (WIDTH + 1) + start_x + 1] = 219;
		scrn_ptr[(start_y + 1) * (WIDTH + 1) + start_x] = 219;
		scrn_ptr[(start_y + 1) * (WIDTH + 1) + start_x + 1] = 219;
	}
	
	for(int k = 0; k < 3*(WIDTH+HEIGHT); k++){
        int x = rand() % WIDTH;   // 0-63
        int y = rand() % HEIGHT;  // 0-15
        buffer_ptr[y * (WIDTH + 1) + x] = 219;
        scrn_ptr[y * (WIDTH + 1) + x] = 219;
	}
	
	while(1){
		system("cls");
					
		
		for(int x = 0; x < WIDTH; x++){
			for(int y = 0; y < HEIGHT; y++){
				int neighbours = 0;
				for(int a = -1; a < 2; a++){
					for(int b = -1; b < 2; b++){
						if(a == 0 && b == 0){continue;}
						int u = (x + a + WIDTH) % WIDTH;
						int v = (y + b + HEIGHT) % HEIGHT;
						if(scrn_ptr[v * (WIDTH+1) + u] != ' '){ neighbours++;}
					}
				}
				char current = scrn_ptr[y * (WIDTH+1) + x];
				if(current != ' '){
					if(neighbours == 3 || neighbours == 2 ){
						buffer_ptr[y * (WIDTH+1) + x] = -37;		
					}else{
						buffer_ptr[y * (WIDTH+1) + x] = ' ';
					}
				}else{
					if(neighbours == 3){ //Becomes alive again.
						buffer_ptr[y * (WIDTH+1) + x] = -37;
					}else{
						buffer_ptr[y * (WIDTH+1) + x] = ' ';
					}
				}
			}
		}
		
		
		buffer_ptr[SCREEN_SIZE - 1] = '\0'; //Str termination.
		
		//Print the array
		printf("%s\n\n\tTICK:%ld\n",scrn_ptr,tick);
		
		
		//Swap the ptr for compute/screen
        char *temp = scrn_ptr;
        scrn_ptr = buffer_ptr;
        buffer_ptr = temp;
		
		tick++;
		Sleep(1);	
	}

	printf("\nEND\n");
	return 0;
}