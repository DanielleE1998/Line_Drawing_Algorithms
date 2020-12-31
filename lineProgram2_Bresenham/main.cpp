//Program2; Bresenham’s Line Generation 
#include <bits/stdc++.h> 
#include <cstdlib> //for rand value
#include "SDL2/SDL.h"
#include <ctime>
#define WINDOW_WIDTH 600
using namespace std; 
SDL_Window     *window;
SDL_Renderer *renderer;

// Function that returns -1,0,1 
//depending on whether x is < 0, = 0, > 0 respectively */
int sign(int x){
if(x > 0)
	return 1;
else if(x < 0)
	return -1;
else
	return 0;
}

void brz(int x0,int y0, int x1, int y1){
	
	//set initial values
	int x,y;
	x = x0;
	y = y0;

	//find change in x and y
	int dx, dy;
	dx = abs(x1-x0);
	dy = abs(y1-y0);
	
	int s1, s2;
	s1 = sign(x1 - x0); //find direction (-1, 0, or 1) to increment
	s2 = sign(y1 - y0); //to increment x and y

	//initialize flag value
	int swap = 0;
	//Compare ranges and swap if 
    //dy has a greater range than dx
	if (dy > dx){
	 int temp = dx;
	 dx = dy;
	 dy = temp;
	 swap = 1; //set flag to true
	}
	
	//set initial decision parameter
	int m = 2 * dy - dx;
	for(int i = 0; i < dx; i++){
		SDL_RenderDrawPoint(renderer, x, y);
		while(m >= 0){
		  m -= 2 * dx;
		  if(swap)//previously swapped dy and dx
		   x += s1; //increment x in direction determined by sign
		  else
		   y += s2; //increment y in direction determined by sign
		}
		  
		 m += 2 * dy;
		 if(swap)
		  y += s2;
		 else
		  x += s1;
	}
	//place pixel
	SDL_RenderDrawPoint(renderer, x, y); 
}

//draw N(provided by user) lines, with positions(start and end coordinates)
//provided by random number generator
main(int argc, char* argv[]){
	cout << "How many lines should be Drawn?:";
	int lineNum;
	cin >> lineNum;
	int randx0, randx1, randy0, randy1;
	 
//SDL stuff
	SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  
  if(window==NULL)
  {   
    printf("Could not create window: %s\n", SDL_GetError());
    return 1;
  }
    
	//set up timer
	clock_t start;
    double duration;
    start = clock();
	
	for(int i = 0; i < lineNum; i++){
		randx0 = rand() % WINDOW_WIDTH; //range from 0 to 599
		randx1 = rand() % WINDOW_WIDTH; //generated for each line 
		randy0 = rand() % WINDOW_WIDTH; 
		randy1 = rand() % WINDOW_WIDTH;
		cout <<"("<<randx0 <<","<< randy0 << ") ("<< randx1<<","<< randy1<<")\n";
		brz(randx0, randy0, randx1, randy1);   
		//brz(100,10,100,500); //test vertical
		//brz(100,100,500,100); //test horizontal
	}	
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout<<"Duration in seconds: "<< duration <<'\n';
	 
	//more SDL stuff
	 SDL_RenderPresent(renderer);
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS; 
}