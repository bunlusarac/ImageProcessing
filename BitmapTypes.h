/*
 *	BitmapTypes.cpp - type definitions for all bitmap operations
 *  -------------------
 *	Includes type definitions for bitmap image format sections and
 *  and atomic integral typedefs for ease of understanding.
 */

#pragma once
#pragma pack(1)

typedef unsigned char	BYTE;	//1-byte type definition
typedef unsigned short	WORD;	//2-byte type definition
typedef unsigned int	DWORD;	//4-byte type definition
typedef int				LONG;	//4-byte type definition

/*
	BitmapFileHeader is the struct type that
	holds information about type, size and layout
	of the file. (14 bytes)
*/
typedef struct {
	BYTE	bfType1;		//Character B for distinction	
	BYTE	bfType2;		//Character M for distinction
	LONG	bfSize;			//Size of file in bytes (somehow only works with LONG)
	WORD	bfReserved1;	//Unused (mostly 0, depends on software that generated image)
	WORD	bfReserved2;	//Unused (mostly 0, depends on software that generated image)
	DWORD	bfOffBits;		//Offset to start of image/pixel data
} BitmapFileHeader;

/*
	BitmapInfoHeader is the struct type that
	holds information about dimension and color
	format.
*/
typedef struct {
	DWORD	biSize;				//Header size (bytes) (min value=40)
	LONG	biWidth;			//Image width (px)
	LONG	biHeight;			//Image height (px)
	WORD	biPlanes;			//Number of color planes (must be 1)
	WORD	biBitCount;			//Bits per pixel (1,2,4,8,16,...)
	DWORD	biCompression;		//Compression type (uncompressed if 0)
	DWORD	biSizeImage;		//Image size (bytes) (can be 0 for uncompressed images)
	LONG	biXPelsPerMeter;	//Preferred resolution in pixels per meter - X axis (0 by default)
	LONG	biYPelsPerMeter;	//Preferred resolution in pixels per meter - Y axis (0 by default)
	DWORD	biClrUsed;			//Number color map entries that are actually used (number of colors)
	DWORD	biClrImportant;		//Number of significant colors (0 means all colors are important)
} BitmapInfoHeader;

/*	biCompression 
	-------------
	0 -> no compression
	1 -> 8-bit run length encoding
	2 -> 4-bit run length encoding
	3 -> RGB bitmap with mask
*/

/*
	BitmapRGBTriplet is the struct type that
	holds RGB color information for a single
	picture element (pixel).
*/
typedef struct {
	BYTE red;
	BYTE green;
	BYTE blue;
	BYTE reserved;
} BitmapRGBTriplet;

/*
	BitmapImage is the struct type for the
	whole bitmap image format.
*/
typedef struct {
	BitmapFileHeader	bitmapFileHeader;
	BitmapInfoHeader	bitmapInfoHeader;
	BitmapRGBTriplet*	bitmapColorPalette;
	BYTE*				bitmapImageData; //pointer to pixel data and color table info
} BitmapImage;