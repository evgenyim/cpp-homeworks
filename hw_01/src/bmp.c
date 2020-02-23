#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#define header_size 54
#define fields 16

int read_header(FILE *fin, BMPINFO *header, BMPFILEHEADER *fheader) {
	int count = 0;
	count += fread(&fheader->bfType, sizeof(int16_t), 1, fin);
	count += fread(&fheader->bfSize, sizeof(int32_t), 1, fin);
	count += fread(&fheader->bfReserved1, sizeof(int16_t), 1, fin);
	count += fread(&fheader->bfReserved2, sizeof(int16_t), 1, fin);
	count += fread(&fheader->bfOffBits, sizeof(int32_t), 1, fin);
	count += fread(&header->biSize, sizeof(int32_t), 1, fin);
	count += fread(&header->biWidth, sizeof(int32_t), 1, fin);
	count += fread(&header->biHeight, sizeof(int32_t), 1, fin);
	count += fread(&header->biPlanes, sizeof(int16_t), 1, fin);
	count += fread(&header->biBitCount, sizeof(int16_t), 1, fin);
	count += fread(&header->biCompression, sizeof(int32_t), 1, fin);
	count += fread(&header->biSizeImage, sizeof(int32_t), 1, fin);
	count += fread(&header->biXPelsPerMeter, sizeof(int32_t), 1, fin);	
	count += fread(&header->biYPelsPerMeter, sizeof(int32_t), 1, fin);
	count += fread(&header->biClrUsed, sizeof(int32_t), 1, fin);
	count += fread(&header->biClrImportant, sizeof(int32_t), 1, fin);
	return count;
}

int save_header(FILE *fout, BMPINFO *header, BMPFILEHEADER *fheader) {
	int count = 0;
	count += fwrite(&fheader->bfType, sizeof(int16_t), 1, fout);
	count += fwrite(&fheader->bfSize, sizeof(int32_t), 1, fout);
	count += fwrite(&fheader->bfReserved1, sizeof(int16_t), 1, fout);
	count += fwrite(&fheader->bfReserved2, sizeof(int16_t), 1, fout);
	count += fwrite(&fheader->bfOffBits, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biSize, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biWidth, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biHeight, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biPlanes, sizeof(int16_t), 1, fout);
	count += fwrite(&header->biBitCount, sizeof(int16_t), 1, fout);
	count += fwrite(&header->biCompression, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biSizeImage, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biXPelsPerMeter, sizeof(int32_t), 1, fout);	
	count += fwrite(&header->biYPelsPerMeter, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biClrUsed, sizeof(int32_t), 1, fout);
	count += fwrite(&header->biClrImportant, sizeof(int32_t), 1, fout);
	return count;
}

RGBQUAD **load_bmp(FILE *fin, BMPINFO *header, BMPFILEHEADER *fheader) {
	int count = read_header(fin, header, fheader);
	if (count < fields) return NULL;
	RGBQUAD **rgb = malloc(sizeof(RGBQUAD *) * header->biHeight);
	if (rgb == NULL) return NULL;
	int i, j;
	for (i = 0; i < header->biHeight; i++) {
		rgb[i] = malloc(sizeof(RGBQUAD) * header->biWidth);
		if (rgb[i] == NULL) return NULL;
	}
	for (i = 0; i < header->biHeight; i++) {
		for (j = 0; j < header->biWidth; j++) {
			rgb[i][j].rgbBlue = 0;
			rgb[i][j].rgbRed = 0;
			rgb[i][j].rgbGreen = 0;
		}
	}
	count = 0;
	for (i = header->biHeight - 1; i >= 0; i--) {
		for (j = 0; j < header->biWidth; j++) {
			count += fread(&rgb[i][j].rgbBlue, sizeof(char), 1, fin);
			count += fread(&rgb[i][j].rgbGreen, sizeof(char), 1, fin);
			count += fread(&rgb[i][j].rgbRed, sizeof(char), 1, fin);
		}
		char buf[10];
		count += fread(buf, sizeof(char), header->biWidth % 4, fin);
	}
	if (count != header->biHeight * header->biWidth * 3 + header->biHeight * (header->biWidth % 4)) return NULL;
	return rgb;
}

int save_bmp(FILE *fout, BMPINFO *header, BMPFILEHEADER *fheader, RGBQUAD **rgb) {
	int size = header_size;
	size += header->biHeight * header->biWidth * 3 + header->biHeight * (header->biWidth % 4);
	fheader->bfSize = size; 
	int count = save_header(fout, header, fheader);
	
	if (count < fields) return -1;
	count = 0;
	int i, j;
	for (i = header->biHeight - 1; i >= 0; i--) {
		for (j = 0; j < header->biWidth; j++) {
			count += fwrite(&rgb[i][j].rgbBlue, sizeof(char), 1, fout);
			count += fwrite(&rgb[i][j].rgbGreen, sizeof(char), 1, fout);
			count += fwrite(&rgb[i][j].rgbRed, sizeof(char), 1, fout);
		}
		int zero = 0;
		count += fwrite(&zero, sizeof(char), header->biWidth % 4, fout);
	}
	if (count < header->biHeight * header->biWidth * 3 + header->biHeight * (header->biWidth % 4)) return -1;
	return 0;
}

RGBQUAD **crop(RGBQUAD **rgb, int y, int x, int w, int h, BMPINFO *header) {
	int size = header->biHeight;
	header->biWidth = w;
	header->biHeight = h;

	RGBQUAD **rgb_new = malloc(sizeof(RGBQUAD *) * h);
	if (rgb_new == NULL) return NULL;

	int i, j;
	for (i = 0; i < h; i++) {
		rgb_new[i] = malloc(sizeof(RGBQUAD) * w);
		if (rgb_new[i] == NULL) return NULL;
	}
	for (i = h - 1; i >= 0; i--) {
		for (j = 0; j < w; j++) {
			rgb_new[i][j].rgbRed = rgb[i+x][j+y].rgbRed;
			rgb_new[i][j].rgbBlue = rgb[i+x][j+y].rgbBlue;
			rgb_new[i][j].rgbGreen = rgb[i+x][j+y].rgbGreen;
		}
	}

	mem_free(rgb, size);
	return rgb_new;
}

RGBQUAD **rotate(RGBQUAD **rgb, BMPINFO *header) {
	int w = header->biWidth;
	int h = header->biHeight;
	header->biWidth = h;
	header->biHeight = w;
	
	RGBQUAD **rgb_new = malloc(sizeof(RGBQUAD *) * w);
	if (rgb_new == NULL) return NULL;
	
	int i, j;
	for (i = 0; i < w; i++) {
		rgb_new[i] = malloc(sizeof(RGBQUAD) * h);
		if (rgb_new[i] == NULL) return NULL;
	}
	for (i = 0; i < w; i++) {
		for (j = 0; j < h; j++) {
			rgb_new[i][j].rgbRed = rgb[h-j-1][i].rgbRed;
			rgb_new[i][j].rgbBlue = rgb[h-j-1][i].rgbBlue;
			rgb_new[i][j].rgbGreen = rgb[h-j-1][i].rgbGreen;
		}
	}
	
	mem_free(rgb, h);
	return rgb_new;
}

void mem_free(RGBQUAD **rgb, int size) {
	for (int i = 0; i < size; i++) {
		free(rgb[i]);
	}
	free(rgb);
}