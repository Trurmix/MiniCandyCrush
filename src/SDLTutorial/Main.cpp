#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

int main(int, char*[]) {
	try {
		//INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();
		const Uint8 imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		//Si no ha ido bien se comprueba el error
		if (!(IMG_Init(imageFlags) & imageFlags)) throw IMG_GetError();
		//WINDOW
		const int WIDTH = 640, HEIGHT = 480;

		SDL_Window *window = SDL_CreateWindow("Hello SDL",
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED, 
										WIDTH, HEIGHT,
										SDL_WINDOW_SHOWN);

		if (window == nullptr) throw SDL_GetError();
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
													SDL_RENDERER_ACCELERATED | 
													SDL_RENDERER_PRESENTVSYNC);
		if (renderer == nullptr) throw SDL_GetError();
		//SPRITES
		SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "../../res/gfx/bg.jpg"); //Path relativos 
		SDL_Texture *playerTexture = IMG_LoadTexture(renderer, "../../res/gfx/blue.png");
		if (bgTexture == nullptr || playerTexture == nullptr) throw IMG_GetError();
		SDL_Rect bgRect = { 0, 0, WIDTH, HEIGHT };
		SDL_Rect playerRect = { (WIDTH >> 1)-50, (HEIGHT >> 1)-50, 100, 100 };
		SDL_Rect playerTarget = { 0, 0, 100, 100 };
								//Mover una posicion == (WIDTH / 2)
																				  
		//GAME LOOP
		SDL_Event evnt;
		for (bool isRunning = true; isRunning;) {
			//IMPUT HANDLER	
			while (SDL_PollEvent(&evnt)) {
				switch (evnt.type)
				{
				case SDL_QUIT: isRunning = false; break;
				case SDL_MOUSEMOTION: playerTarget.x = evnt.motion.x - 50;
									  playerTarget.y = evnt.motion.y - 50;
				default:;
				}
			}
			//UPDATE
			playerRect.x += (playerTarget.x - playerRect.x) * 0.1f;
			playerRect.y += (playerTarget.y - playerRect.y) * 0.1f;
			//DRAW
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			SDL_RenderCopy(renderer, playerTexture, nullptr, &playerRect);
			SDL_RenderPresent(renderer);
		}
		//DESTROY
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	} 
	catch (const char *msg) { //(const char * const msg) Puntero constante
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
	SDL_Quit();
	IMG_Quit();
	return 0;
}

//Operaciones bit a bit | &, solo uno, suma de caracteristicas.