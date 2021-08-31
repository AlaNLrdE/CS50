#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, unsigned int x, unsigned int y, unsigned int c)
{
	float fRetPixel = 0.0;
	unsigned int pixelPosition = 0;

	if( (c < im.c) && (c >= 0) )
	{
		/* clamping values if the coordinates of the pixel is out of range */
		if ( y >= im.h )
		{
			y = im.h - 1;
		}

		if( x >= im.w )
		{
			x = im.w - 1;
		}

		pixelPosition = (x + (im.w * y)) + (im.w*im.h*c);
		fRetPixel = im.data[pixelPosition];
	}
	else
	{
#ifdef DEBUG
		printf("get_pixel: invalid layer '%d'/n",c);
#endif
	}
    return fRetPixel;
}

void set_pixel(image im, unsigned int x, unsigned int y, unsigned int c, float v)
{
	unsigned int pixelPosition = ((x + (im.w * y)) + (im.w*im.h*c));
	/* image boundary check */
	if( (x < im.w) && (y < im.h) && (c <= im.c) )
	{
		im.data[pixelPosition] = v;
	}
	else
	{
		/* do nothing */
	}
}

image rgb_to_grayscale(image im)
{
	const int grayLayer = 0;
	unsigned int xPos;
	unsigned int yPos;
	float tempPixelValueR;
	float tempPixelValueG;
	float tempPixelValueB;
	float tempGrayIntensityPixel;
	image gray = make_image(im.w, im.h, 1);

	assert(im.c >= 3);


	for(yPos = 0; yPos < im.h; yPos++)
	{
		for(xPos = 0; xPos < im.w; xPos++)
		{
			tempPixelValueR = get_pixel(im,xPos,yPos,RGB_R);
			tempPixelValueR = tempPixelValueR * 0.299;

			tempPixelValueG = get_pixel(im,xPos,yPos,RGB_G);
			tempPixelValueG = tempPixelValueG * 0.587;

			tempPixelValueB = get_pixel(im,xPos,yPos,RGB_B);
			tempPixelValueB = tempPixelValueB * 0.114;

			tempGrayIntensityPixel = tempPixelValueR + tempPixelValueG + tempPixelValueB;

			set_pixel(gray,xPos,yPos,grayLayer,tempGrayIntensityPixel);
		}
	}

    return gray;
}

float nn_interpolate(image im, float x, float y, int c)
{
	x = round (x-0.5);
	y = round(y-0.5);
	return get_pixel(im, (int)x, (int)y, c);
}

image nn_resize(image im, int w, int h)
{
	int c = im.c;
	image ret = make_image(w,h,c);
	
	int oldW = im.w;
	int oldH = im.h;
	float xRate = (float)oldW * 1.0 / w;
	float yRate = (float)oldH * 1.0 /h;
	float x;
	float y;

	for(int i = 0; i < c; i++)
	{
		for(int j = 0; j < h; j++)
		{
			for(int k = 0; k< w;k++)
			{
				x = xRate * (k + 0.5);
				y = yRate * (j + 0.5);
				set_pixel(ret, k, j, i, nn_interpolate(im, x, y, i));
			} 
		} 
	}
	return ret;
}

void pixelTransformation(image inputImg, int resizeFactor, filterMode Mode, uint8_t grayscaleMode)
{
    image reducedResImage;
    image restoredResImage;
    char *outputFile = "output";
    const unsigned char bitsPP_8bitRange = 0xFF;
    /* Represents the maximum different levels of Red and Green with 3bpp 
       and  Blue with 2bpp*/
    const unsigned char colorDepth8bit_R = 0x7;
    const unsigned char colorDepth8bit_G = 0x7;
    const unsigned char colorDepth8bit_B = 0x3;

    const unsigned int bitsPP_16bitRange = 0xFFFF;
    /* Represents the maximum different levels of Red and Green with 3bpp 
       and  Blue with 2bpp*/
    const unsigned int colorDepth16bit_R = 0x3F;
    const unsigned int colorDepth16bit_G = 0x3F;
    const unsigned int colorDepth16bit_B = 0xF;

    unsigned int bitsPP_Range;
    unsigned int colorDepth_R;
    unsigned int colorDepth_G;
    unsigned int colorDepth_B;

    
    if( Mode == filterMode_8bit )
    {
        bitsPP_Range = bitsPP_8bitRange;
        colorDepth_R = colorDepth8bit_R;
        colorDepth_G = colorDepth8bit_G;
        colorDepth_B = colorDepth8bit_B;
    }
    else if (Mode == filterMode_16bit)
    {
        bitsPP_Range = bitsPP_16bitRange;
        colorDepth_R = colorDepth16bit_R;
        colorDepth_G = colorDepth16bit_G;
        colorDepth_B = colorDepth16bit_B;
    }

    reducedResImage = nn_resize(inputImg, inputImg.w/resizeFactor, inputImg.h/resizeFactor);

    for (int h = 0; h < reducedResImage.h; h++)
    {
        for (int w = 0; w < reducedResImage.w; w++)
        {
            filterPixel(reducedResImage, w, h, bitsPP_Range, colorDepth_R, RGB_R);
            filterPixel(reducedResImage, w, h, bitsPP_Range, colorDepth_G, RGB_G);
            filterPixel(reducedResImage, w, h, bitsPP_Range, colorDepth_B, RGB_B);
        }
    }

	if (grayscaleMode != 0)
	{
		reducedResImage = rgb_to_grayscale(reducedResImage);
	}
    restoredResImage = nn_resize(reducedResImage, inputImg.w*resizeFactor, inputImg.h*resizeFactor);
    save_image(restoredResImage, outputFile);
}

void filterPixel(image inputImage, int x, int y, unsigned int bitsPP_Range, unsigned int colorDepth, RGB_Components Layer)
{
    float tmpPixel;

    tmpPixel = bitsPP_Range * get_pixel(inputImage, x, y, Layer);
    tmpPixel = (int)(tmpPixel * colorDepth / bitsPP_Range); 
    tmpPixel = tmpPixel * bitsPP_Range / colorDepth;
    set_pixel(inputImage, x, y, Layer, tmpPixel / bitsPP_Range);
}

