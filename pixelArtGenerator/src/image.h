#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

typedef struct{
    int w,h,c;
    float *data;
} image;

typedef enum RGB_eComponents
{
	RGB_R = 0,
	RGB_G = 1,
	RGB_B = 2,
	RGB_lastElement
}RGB_Components;

typedef enum efilterMode
{
	filterMode_8bit = 0,
	filterMode_16bit = 1,
	filterMode_lastElement
} filterMode;

// Basic operations
image nn_resize(image im, int w, int h);
float get_pixel(image im, unsigned int x, unsigned int y, unsigned int c);
void set_pixel(image im, unsigned int x, unsigned int y, unsigned int c, float v);
void pixelTransformation(image inputImg, int resizeFactor, filterMode Mode, uint8_t grayscaleMode);
void filterPixel(image reducedResImage, int x, int y, unsigned int bitsPP_Range, unsigned int colorDepth, RGB_Components Layer);


// Loading and saving
image make_image(int w, int h, int c);
image load_image(char *filename);
void save_image(image im, const char *name);
void save_png(image im, const char *name);
void free_image(image im);

#endif

