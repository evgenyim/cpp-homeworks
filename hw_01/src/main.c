#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
	if (argc < 1) {
		printf("Wrong input\n");
		return -1;
	}
	if (strcmp(argv[1], "crop-rotate") == 0) {
		if (argc < 8) {
			printf("Wrong input\n");
			return -1;
		}
		int check = 0;
		FILE *fin = fopen(argv[2], "r");
		if (fin == NULL) return -1;
		FILE *fout = fopen(argv[3], "wb");
		if (fout == NULL) return -1;
		BMPINFO header;
		BMPFILEHEADER fheader;
		RGBQUAD **rgb;

		rgb = load_bmp(fin, &header, &fheader);
		if (rgb == NULL) return -1;
		int x, y, w, h;
		x = atoi(argv[4]);
		y = atoi(argv[5]);
		w = atoi(argv[6]);
		h = atoi(argv[7]);
		if (x + w > header.biWidth || y + h > header.biHeight) {
			printf("Wrong input\n");
			return -1;
		}
		rgb = crop(rgb, x, y, w, h, &header);
		if (rgb == NULL) return -1;
		rgb = rotate(rgb, &header);
		if (rgb == NULL) return -1;
		check = save_bmp(fout, &header, &fheader, rgb);
		if (check == -1) return -1;
		mem_free(rgb, header.biHeight);
		fclose(fin);
		fclose(fout);
	}
}