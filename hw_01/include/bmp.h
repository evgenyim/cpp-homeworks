#ifndef BMP_H
#define BMP_H
#include <stdio.h>

typedef struct BMPFILEHEADER {
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
} BMPFILEHEADER;
 
typedef struct BMPINFOHEADER {
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
} BMPINFO;
 
typedef struct RGBQUAD_S {
	int rgbBlue;
	int rgbGreen;
	int rgbRed;
} RGBQUAD;

RGBQUAD **load_bmp(FILE *fin, BMPINFO *header, BMPFILEHEADER *fheader);
int save_bmp(FILE *fout, BMPINFO *header, BMPFILEHEADER *fheader, RGBQUAD **rgb);
RGBQUAD **crop(RGBQUAD **rgb, int y, int x, int w, int h, BMPINFO *header);
RGBQUAD **rotate(RGBQUAD **rgb, BMPINFO *header);
void mem_free(RGBQUAD **rgb, int size);

#endif