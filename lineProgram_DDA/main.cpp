//Program1
#include <cstdlib> //for rand value
#include <iostream>
#include "SDL2/SDL.h"
#include <ctime>
#define WINDOW_WIDTH 600
using namespace std;
	SDL_Window     *window;
	SDL_Renderer *renderer;
	
basicAlg(int x0, int y0, int x1, int y1){
	
	//find change in x and y
	int dx = x1 - x0;
	int dy = y1 - y0;

	// Depending on the absolute value of dx and dy, find steps
	int steps;
	if (abs(dx) > abs(dy)) //greater change in abs(dx)
		steps = abs(dx);
	else						   // greater change in	abs(dy) or equal and aribitrary
		steps = abs(dy);

	// calculate increment in x & y for each steps
	float xInc = dx / (float)steps;
	float yInc = dy / (float)steps;

	//set initial values and begin placing a pixel for each step
	float x = x0;
	float y = y0;
	for (int i = 0; i < steps; i++)
	{
		SDL_RenderDrawPoint(renderer, (int)x, (int)y);
		x += xInc;
		y += yInc;
	}
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
    printf("Could not create window: %s\n", SDL_GetError()); //printf?
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
		basicAlg(randx0, randy0, randx1, randy1);  
		//basicAlg(100,10,100,500); //test vertical
		//basicAlg(100,100,500,100); //test horizontal  
	}	
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << "Duration in seconds: "<< duration <<'\n';
	 
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