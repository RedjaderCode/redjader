//
// Using polymorphism, I'm going to attempt to make a dynamic IMG viewer //

#include <SDL.h>
#include <SDL_Image.h>

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>

#define Title "DynImgViewer"

class sGet_Time{

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> F;
		std::chrono::time_point<std::chrono::high_resolution_clock> L;
		std::chrono::duration<float> dDur;
	public:

		sGet_Time()
			:
				F(std::chrono::high_resolution_clock::now())
	{}

		~sGet_Time(){
		
			L = std::chrono::high_resolution_clock::now();
			dDur = L - F;

			std::cout << "\n\nafter " << dDur.count() << " seconds" << std::endl;
		}
};

int nScreenWidth = 640;
int nScreenHeight = 400;

const char * assetsPath = "assets";

auto GetFileCount = std::filesystem::directory_iterator(assetsPath);

int CreateImgIteration();
int iterator;

SDL_Window * cWindow;
SDL_Renderer * cRender;
SDL_Surface * IMG;

SDL_Texture ** cTexture = new SDL_Texture * [iterator];

SDL_Event e;

void INIT(){

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	cWindow = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			nScreenWidth, nScreenHeight, SDL_WINDOW_SHOWN);

	cRender = SDL_CreateRenderer(cWindow, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture * LoadIMG(std::string PTH){

	SDL_Texture * LoadedTexture;

	IMG = IMG_Load(PTH.c_str());

	LoadedTexture = SDL_CreateTextureFromSurface(cRender, IMG);

	if(LoadedTexture == NULL)
		printf ("    :SDL_ERROR[%s]", SDL_GetError());

	SDL_FreeSurface(IMG);

	return LoadedTexture;
}

int CreateImgIteration(){

	sGet_Time s;

	iterator = 0;

	for(auto& s : GetFileCount){

		std::cout << "\n\t->> Loading: " << s.path();
		cTexture[iterator] = LoadIMG(s.path().string());

		if(s.is_regular_file()){
			
			iterator++;
		}
	}

	return iterator;
}

void QUIT(){

	SDL_DestroyWindow(cWindow);
	SDL_DestroyRenderer(cRender);
	for(int i=0; i<iterator; i++){
		
		SDL_DestroyTexture(cTexture[i]);
	}

	std::cout << "\t->> Deallocating SDL_Texture ** cTexture = new SDL_Texture * [iterator]";

	delete[] cTexture;
}

int main(int args, char * argz[]){

	bool running = true;
	int IMG_SEL_ITERATION = 0;

	INIT();
	printf("\n\nThere are %d PNG files loaded\n", CreateImgIteration());
		
	while(running){
	
		while(SDL_PollEvent(&e)){
			
			switch(e.type){
			
				case SDL_QUIT:
					QUIT();
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){
					
						case SDLK_RIGHT:
							IMG_SEL_ITERATION++;
							if(IMG_SEL_ITERATION > (iterator - 1))
								IMG_SEL_ITERATION = iterator;
							break;
						case SDLK_LEFT:
							IMG_SEL_ITERATION--;
							if(IMG_SEL_ITERATION <= 0)
								IMG_SEL_ITERATION = 0;
							break;
					}
			}
		}

		SDL_Rect rec;
		rec.x = NULL;
		rec.y = NULL;
		rec.w = nScreenWidth;
		rec.h = nScreenHeight;

		SDL_RenderCopy(cRender, cTexture[IMG_SEL_ITERATION], NULL, &rec);
		SDL_RenderPresent(cRender);
	}

	return 0;
}
