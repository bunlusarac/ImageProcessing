/*
 *	BitmapReadWrite.h - header file for BitmapReadWrite.cpp
 *  -------------------
 *	Includes function prototype declarations for BitmapReadWrite.cpp
 *  and inclusion of bitmap struct type definitions.
 */

#pragma once
#include "BitmapTypes.h"

BitmapImage* ReadImage(const char* fileName);
void SummarizeInfo(BitmapImage* bitmapImage, const char* fname);
void WriteImage(BitmapImage* bitmapImage, const char* fileName);
unsigned int bitCountToNColor(unsigned int bitCount);