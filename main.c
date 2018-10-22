#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

int main ( int argc, char *argv[] )
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
		printf("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow(
		"Shifu",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		1080,
		SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE
	);

	if (win == NULL) {
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Sets window border
	SDL_SetWindowBordered(win, SDL_TRUE);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		SDL_DestroyWindow(win);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Render Play Button
	SDL_Surface* playBtnSheet = IMG_Load("play-button.png");
	if (!playBtnSheet) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		printf("IMG_Load Error: %s\n", IMG_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Texture *playBtnTexture = SDL_CreateTextureFromSurface(ren, playBtnSheet);
	SDL_FreeSurface(playBtnSheet);
	if (playBtnTexture == NULL) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Rect playBtnWindow;
	playBtnWindow.x = 0;
	playBtnWindow.y = 300;
	playBtnWindow.w = 190;
	playBtnWindow.h = 90;

	SDL_Rect playBtnTextureWindow;
	playBtnTextureWindow.x = 0;
	playBtnTextureWindow.y = 0;

	// Render Options Button
	
	SDL_Surface* optionsBtnSheet = IMG_Load("options-button.png");
	if (!optionsBtnSheet) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		printf("IMG_Load Error: %s\n", IMG_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Texture *optionsBtnTexture = SDL_CreateTextureFromSurface(ren, optionsBtnSheet);
	SDL_FreeSurface(optionsBtnSheet);
	if (playBtnTexture == NULL) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Rect optionsBtnWindow;
	optionsBtnWindow.x = 0;
	optionsBtnWindow.y = 500;
	optionsBtnWindow.w = 190;
	optionsBtnWindow.h = 90;

	SDL_Rect optionsBtnTextureWindow;
	optionsBtnTextureWindow.x = 0;
	optionsBtnTextureWindow.y = 0;

	SDL_GetWindowSize(win, &playBtnWindow.x, NULL);
	SDL_GetWindowSize(win, &optionsBtnWindow.x, NULL);

	SDL_QueryTexture(playBtnTexture, NULL, NULL, &playBtnTextureWindow.w, &playBtnTextureWindow.h);
	SDL_QueryTexture(optionsBtnTexture, NULL, NULL, &optionsBtnTextureWindow.w, &optionsBtnTextureWindow.h);

	playBtnTextureWindow.h /= 2;
	optionsBtnTextureWindow.h /= 2;
	// button logic (highlighted, not highlighted)
	// button logic (button spritesheets are highlighted when the frame is at their height / 2)
	int playBtnFrame = 1;
	int optionsBtnFrame = 0;
	int btnArr[2] = {playBtnFrame, optionsBtnFrame};

	// select the first btn in the Array
	int currentBtnFrame = 0;

	int btnArrayLen = sizeof(btnArr) / sizeof(btnArr[0]);

	// Loop flag
	bool quit = false;

	// Event Handler
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent (&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case SDLK_UP:
							if (currentBtnFrame > 0) {
								btnArr[currentBtnFrame] -= 1;
								currentBtnFrame -= 1;
								btnArr[currentBtnFrame] += 1;
							}
							break;

						case SDLK_DOWN:
							if (currentBtnFrame < (btnArrayLen - 1)) {
								btnArr[currentBtnFrame] -= 1;
								currentBtnFrame += 1;
								btnArr[currentBtnFrame] += 1;
							}
							break;
					}
			}
		}

		playBtnTextureWindow.y = btnArr[0] * playBtnTextureWindow.h;
		optionsBtnTextureWindow.y = btnArr[1] * optionsBtnTextureWindow.h;
		
		// clear the renderer
		SDL_RenderClear(ren);

		// Draw the texture
		SDL_RenderCopy(ren, playBtnTexture, &playBtnTextureWindow, &playBtnWindow);
		SDL_RenderCopy(ren, optionsBtnTexture, &optionsBtnTextureWindow, &optionsBtnWindow);

		// Update the screen
		SDL_RenderPresent(ren);

		// Delay for a hot minute
		SDL_PumpEvents();
		SDL_Delay(1);
	}

	SDL_DestroyTexture(playBtnTexture);
	SDL_DestroyTexture(optionsBtnTexture);
	SDL_DestroyRenderer(ren);
	// Close and Destroy the Window
	SDL_DestroyWindow(win);

	//CLean up
	SDL_Quit();

	return 0;
}
