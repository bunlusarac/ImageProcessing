/*
 *	BitmapReadWrite.cpp - function definitions for bitmap image IO
 *  -------------------
 *	Includes function definitions for reading and writing bitmap images from/to disk
 *  and utility functions for summarizing header info and more.
 */

#include <stdio.h>
#include <stdlib.h>
#include "BitmapReadWrite.h"

//Bypass MSVC warnings about safe file IO functions.
#pragma warning(disable : 4996)

//Hint compiler for struct packing of size of 1 bytes
#pragma pack(1)

/*
 *	bitCountToNColor - determine number of colors in a bitmap image
 *  -------------
 *	Map a bitmap images bitcount to number of colors in the image.
 *  Returns 0 if bitcount is greater than 24.
 */
unsigned int bitCountToNColor(unsigned int bitCount) {
	unsigned int nColors;

	switch (bitCount) {
	case 1:
		nColors = 2;
		break;
	case 4:
		nColors = 16;
		break;
	case 8:
		nColors = 256;
		break;
	case 16:
		nColors = 65536;
		break;
	default:
		nColors = 0; //If bitcount is 24 or higher there will be no color palette
		break;
	}

	return nColors;
}

/*
 *	ReadImage - read bitmap image from disk
 *  -------------
 *	Read bitmap image from the given path and return pointer for it.
 */
BitmapImage* ReadImage(const char* fileName) {
	//Get the file and info header data from the image
	BitmapFileHeader bitmapFileHeader;
	BitmapInfoHeader bitmapInfoHeader;

	FILE* imageFilePointer;
	
	imageFilePointer = fopen(fileName, "rb");

	if (imageFilePointer == NULL) {
		printf("File is not found or an error occured while reading the file in specified path.");
		return NULL;
	}

	fread(
		&bitmapFileHeader,
		sizeof(BitmapFileHeader),
		1,
		imageFilePointer);

	fread(
		&bitmapInfoHeader,
		sizeof(BitmapInfoHeader),
		1,
		imageFilePointer
	);

	//Copy all of image data to the memory
	BitmapImage* bitmapImage = (BitmapImage*) malloc(bitmapFileHeader.bfSize);
	
	if (bitmapImage == NULL) {
		printf("Not enough memory available for reading the bitmap file.");
		return NULL;
	}

	bitmapImage->bitmapFileHeader = bitmapFileHeader;
	bitmapImage->bitmapInfoHeader = bitmapInfoHeader;

	//Set up palette before reading imagedata
	unsigned int nColors = bitCountToNColor(bitmapInfoHeader.biBitCount);

	//If there is a color palette, read it from the bitmap file and allocate it
	if (nColors != 0) {
		//sizeof(BitmapRGBTriplet) = 4 bytes, thus 4 bytes per color. 1 triplet per color
		bitmapImage->bitmapColorPalette = (BitmapRGBTriplet*) malloc(4 * nColors); 

		if (bitmapImage->bitmapColorPalette == NULL) {
			printf("Memory could not be allocated for color palette. Please check available memory and try again.");
			return NULL;
		}

		fread(bitmapImage->bitmapColorPalette, 4 * nColors, 1, imageFilePointer);
	}

	//calculate image size in bytes
	unsigned int rowSize = (((bitmapInfoHeader.biWidth * bitmapInfoHeader.biBitCount) + 31) / 32) * 4;
	unsigned int wholeSize = rowSize * bitmapInfoHeader.biHeight;

	//Allocate space and read image pixeldata
	bitmapImage->bitmapImageData = (BYTE*) malloc(wholeSize);

	if (bitmapImage->bitmapImageData == NULL) {
		printf("Memory could not be allocated for image data. Please check available memory and try again.");
		return NULL;
	}

	fread(bitmapImage->bitmapImageData, wholeSize, 1, imageFilePointer);
	
	//Close the filestream
	fclose(imageFilePointer);
	return bitmapImage;
}

/*
 *	WriteImage - write bitmap image to disk
 *  -------------
 *	Writes the given bitmap image to the given path.
 */
void WriteImage(BitmapImage* bitmapImage, const char* fileName) {
	FILE* imageFilePointer = fopen(fileName, "wb");
	
	if (imageFilePointer == NULL) {
		printf("The specified file could not be found or could not be read.");
		return;
	}
	
	//Write info and file headers
	fwrite(&(bitmapImage->bitmapFileHeader), sizeof(BitmapFileHeader), 1, imageFilePointer);
	fwrite(&(bitmapImage->bitmapInfoHeader), sizeof(BitmapInfoHeader), 1, imageFilePointer);

	//Determine number of colors in the image
	unsigned int nColors = bitCountToNColor(bitmapImage->bitmapInfoHeader.biBitCount);

	//If 0, it means bitcount is > 24 bits and these kind of images don't have a palette
	if (nColors != 0) {
		//Write color palette, 4-byte triplet for each color in the image
		fwrite(bitmapImage->bitmapColorPalette, 4 * nColors, 1, imageFilePointer);
	}

	//Determine rowsize and wholesize, then write pixeldata to the file
	unsigned int rowSize = ((((bitmapImage->bitmapInfoHeader.biWidth) * (bitmapImage->bitmapInfoHeader.biBitCount)) + 31) / 32) * 4;
	unsigned int wholeSize = rowSize * (bitmapImage->bitmapInfoHeader.biHeight);

	fwrite(bitmapImage->bitmapImageData, wholeSize, 1, imageFilePointer);
	fclose(imageFilePointer);
}

/*
 *	SummarizeInfo - summarize all bitmap image metadata
 *  -------------
 *	Prints all data stored in given image's info and file header.
 */
void SummarizeInfo(BitmapImage* bitmapImage, const char* fileName)
{
	printf("--------Info about %s  image file--------\n", fileName);
	printf("bfType value		:%c%c\n", bitmapImage->bitmapFileHeader.bfType1, bitmapImage->bitmapFileHeader.bfType2);
	printf("bfsize			:%d\n",		bitmapImage->bitmapFileHeader.bfSize);
	printf("bfreserved1		:%d\n",		bitmapImage->bitmapFileHeader.bfReserved1);
	printf("bfreserved2		:%d\n",		bitmapImage->bitmapFileHeader.bfReserved2);
	printf("bfOffbits		:%d\n",		bitmapImage->bitmapFileHeader.bfOffBits);
	printf("bisize			:%d\n",		bitmapImage->bitmapInfoHeader.biSize);
	printf("Width			:%d\n",		bitmapImage->bitmapInfoHeader.biWidth);
	printf("Height			:%d\n",		bitmapImage->bitmapInfoHeader.biHeight);
	printf("biplane			:%d\n",		bitmapImage->bitmapInfoHeader.biPlanes);
	printf("bibitcount		:%d\n",		bitmapImage->bitmapInfoHeader.biBitCount);
	printf("Compression		:%d\n",		bitmapImage->bitmapInfoHeader.biCompression);
	printf("bisizeimage		:%d\n",		bitmapImage->bitmapInfoHeader.biSizeImage);
	printf("bix			:%d\n",			bitmapImage->bitmapInfoHeader.biXPelsPerMeter);
	printf("biy			:%d\n",			bitmapImage->bitmapInfoHeader.biYPelsPerMeter);
	printf("bi color used		:%d\n", bitmapImage->bitmapInfoHeader.biClrImportant);
	printf("bi color imp.		:%d\n", bitmapImage->bitmapInfoHeader.biClrUsed);
}