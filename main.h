#ifndef MAIN_H_
#define MAIN_H_

SDL_Surface* load_image(char *path);
void init_sdl(void);
SDL_Surface* display_image(SDL_Surface *img);
void treatmentImag(int argc, char *argv []);
#endif
