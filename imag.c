#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "pixel_operations.h"
#include <err.h>
#include "create_array.h"
#include "imag.h"

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}

void treatmentImag(int argc, char *argv []){
	if(argc < 3)
		errx(1, "pas d'image");
	float sum;
	init_sdl();
	SDL_Surface* img = load_image(argv[2]);
	display_image(img);
	load_image(argv[2]);
	for(int y = 0; y < img->h; y++)
	{
		for(int x = 0; x < img->w; x++)
		{
			Uint32 p = getpixel(img, x, y);
			Uint8 r, g, b;
			SDL_GetRGB(p, img->format, &r, &g, &b);
			sum = 0.3*(float)r + 0.59*(float)g + 0.11*(float)b;
			// binarize the pictures
			if(sum >= 128)
				sum = 255;
			else
				sum = 0;
			p = SDL_MapRGB(img->format, sum, sum, sum);
			putpixel(img, x, y, p);
		}
	}

}

int main_imag(int argc, char *argv [])
{
  	init_sdl();
	SDL_Surface* img = load_image(argv[2]);
	load_image(argv[2]);


  	treatmentImag(argc, argv);
	int** array = segmentation(makeArray(/*argv,*/ img)/*, argv*/, img);
	//SDL_Surface* newImg = NouvelleImage(array[0], img);
	printf("\n");
	int *arrayX  = *array;
	for(int i = 0; arrayX[i] != 42; ++i){
	  for(int j = 0; arrayX[j] != 20; ++j){
	    printf("%d", arrayX[i + j]);
	  }
	  printf("\n");
	}

	int* letter = tabLetter(array[0]);
	for(int i = 0; i < 20; ++i){
	  for(int j = 0; j < 20; ++j){
	    printf("%d", letter[i + j]);
	  }
	  printf("\n");
	}
	printf("\n");//Display
	printf("End");
       	printf("\n");

        display_image(img);
        SDL_FreeSurface(img);
	//display_image(newImg);
	//SDL_FreeSurface(newImg);
	return 0;
}
