// Use this to experiment
#include "SpriteWalker.h"

void GetTexture::free(){
	SDL_DestroyTexture(cTexture);

	IMG_Width = 0;
	IMG_Height = 0;
}

GetTexture::GetTexture()
	:
		IMG_Width(0),
		IMG_Height(0)
{}

GetTexture::~GetTexture(){

	free();
}

GetTexture::sGet_Time::sGet_Time()
	:
		nFirst(std::chrono::high_resolution_clock::now())
{}

GetTexture::sGet_Time::~sGet_Time(){

	nLast = std::chrono::high_resolution_clock::now();
	dDuration = nLast - nFirst;

	printf("%f\n", dDuration);
}

SDL_Window * cWindow;
SDL_Renderer * cRender;

const int SpriteIteration = 3;

GetTexture nSpriteSheetTexture;
SDL_Rect nSpriteClip[ SpriteIteration ];

const char * Title = "redjader";

const int nScreenWidth = 640;
const int nScreenHeight = 400;

SDL_Event e;

void Init(){

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	cWindow = SDL_CreateWindow(Title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			nScreenWidth, nScreenHeight, SDL_WINDOW_RESIZABLE);

	cRender = SDL_CreateRenderer(cWindow, -1, SDL_RENDERER_ACCELERATED);
}

int IMGW;
int IMGH;

void GetTexture::LoadTexture(const char * PTH){

	free();

	SDL_Surface * IMG = IMG_Load(PTH);

	SDL_SetColorKey(IMG, SDL_TRUE, SDL_MapRGB(IMG->format, 0x00, 0xFF, 0xFF));
	
	cTexture = SDL_CreateTextureFromSurface(cRender, IMG);
	IMG_Width = IMG->w;
	IMG_Height = IMG->h;

	IMGW = IMG->w;
	IMGH = IMG->h;

	SDL_FreeSurface(IMG);
}

void GetTexture::render(int x, int y, SDL_Rect * clip){

	SDL_Rect rec = {x, y, IMG_Width, IMG_Height};

	if(clip != NULL){
	
		rec.w = clip->w;
		rec.h = clip->h;

		IMGW = clip->w;
		IMGH = clip->h;
	}

	SDL_RenderCopy(cRender, cTexture, clip, &rec);
}

void GetTexture::LOADIMG(){

	GetTexture::sGet_Time s;

	nSpriteSheetTexture.LoadTexture("assets/spritesheet.png");

	nSpriteClip[0].x = 0;
	nSpriteClip[0].y = 0;
	nSpriteClip[0].w = IMG_Width*0.5;
	nSpriteClip[0].h = IMG_Height*0.5;

	nSpriteClip[1].x = IMG_Width*0.5;
	nSpriteClip[1].y = 0;
	nSpriteClip[1].w = IMG_Width*0.5;
	nSpriteClip[1].h = IMG_Height*0.5;

	nSpriteClip[2].x = 0;
	nSpriteClip[2].y = IMG_Height*0.5;
	nSpriteClip[2].w = IMG_Width*0.5;
	nSpriteClip[2].h = IMG_Height*0.5;

	nSpriteClip[3].x = IMG_Width*0.5;
	nSpriteClip[3].y = IMG_Height*0.5;
	nSpriteClip[3].w = IMG_Width*0.5;
	nSpriteClip[3].h = IMG_Height*0.5;

	printf("LOADIMG().SecondsToCompute: ");
}

void close(){

	SDL_DestroyWindow(cWindow);
	SDL_DestroyRenderer(cRender);

	nSpriteSheetTexture.free();
}

int main(int as, char * az[]){

	Init();
	nSpriteSheetTexture.LOADIMG();

	bool running = true;

	int IMG_POSITION_X = (nScreenWidth - (IMGW*0.5))*0.5;
	int IMG_POSITION_Y = (nScreenHeight - (IMGH*0.5))*0.5;

	int nFrame = 0;

	while(running){
	
		while(SDL_PollEvent(&e)){
		
			switch(e.type){

				case SDL_QUIT:
					close();
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym){

						case SDLK_d:
							nFrame++;
							if((nFrame + 1)/4 > SpriteIteration)
								nFrame = 0;

							//IMG_POSITION_X += 10;
							break;

						/*case SDLK_a:
							nFrame--;
							if(nFrame - 1 < 0)
								nFrame = 3;

							IMG_POSITION_X -= 10;
							break;
						*/
					}
				case SDL_MOUSEBUTTONDOWN: 

						switch(e.button.button){

							case SDL_BUTTON_LEFT:
								printf("Background\n");

								if(e.motion.x >= IMG_POSITION_X && e.motion.x <= (IMG_POSITION_X + IMGW) && e.motion.y >= IMG_POSITION_Y && e.motion.y <= (IMG_POSITION_Y + IMGH)){
									
								printf("Player\n");
								
								//offsetX = e.motion.x - IMG_POSITION_X;
								//offsetY = e.motion.y - IMG_POSITION_Y;

								//IMG_POSITION_X = e.motion.x - offsetX;
								//IMG_POSITION_Y = e.motion.y - offsetY;

								}
							}
						break;
						}
		}

		SDL_SetRenderDrawColor(cRender, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(cRender);

		SDL_Rect * cClip = &nSpriteClip[nFrame / 4];

		nSpriteSheetTexture.render(IMG_POSITION_X, IMG_POSITION_Y, cClip);

		SDL_RenderPresent(cRender);

	}

	return 0;
}
