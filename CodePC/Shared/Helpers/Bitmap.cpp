#include "Bitmap.h"

unsigned char* LoadBitmapFileRGBA(char* filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
	FILE *filePtr;
	BITMAPFILEHEADER bitmapFileHeader;
	unsigned char* bitmapImage;
	unsigned char* flippedBitmapImage;
	int imageIdx = 0;
	unsigned char tempRGB;

	//open filename in read binary mode
	fopen_s(&filePtr, filename,"rb");
	if (filePtr == NULL)
		return NULL;

	//read the bitmap file header
	fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

	//verify that this is a bmp file by check bitmap id
	if(bitmapFileHeader.bfType != 0x4D42)
	{
		fclose(filePtr);
		return NULL;
	}

	//read the bitmap info header
	fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

	//move file point to the begging of bitmap data
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	//allocate enough memory for the bitmap image data
	bitmapImage = new unsigned char[bitmapInfoHeader->biSizeImage];

	//allocate memory for final RGBA values
	size_t memSize = bitmapInfoHeader->biWidth * bitmapInfoHeader->biHeight * 4;
	flippedBitmapImage = new unsigned char[memSize];

	//verify memory allocation
	if (!bitmapImage || !flippedBitmapImage)
	{
		free(bitmapImage);
		free(flippedBitmapImage);
		fclose(filePtr);
		return NULL;
	}

	//read in the bitmap image data
	fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr);

	//make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}

	//swap the r and b values to get RGB (bitmap is BGR)
	for (imageIdx = 0;imageIdx < (int)bitmapInfoHeader->biSizeImage;imageIdx+=3)
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	//flip image and set alpha channel data
	for(int y = 0; y < bitmapInfoHeader->biHeight; y++)
	{
		unsigned char* src = &bitmapImage[(bitmapInfoHeader->biHeight - 1 - y) * bitmapInfoHeader->biWidth * 3];
		unsigned char* dst = &flippedBitmapImage[bitmapInfoHeader->biWidth * y * 4];
		for(int x = 0; x < bitmapInfoHeader->biWidth; x++)
		{
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = 255; //full alpha

			dst += 4;
			src += 3;
		}
	}

	delete [] bitmapImage;

	//close file and return bitmap iamge data
	fclose(filePtr);
	return flippedBitmapImage;
}

inline int GetFilePointer(HANDLE FileHandle){
	return SetFilePointer(FileHandle, 0, 0, FILE_CURRENT);
}

bool SaveBMPFile(TCHAR* filename, HBITMAP bitmap, HDC bitmapDC, int width, int height)
{
	bool Success=0;
	HDC SurfDC=NULL;
	HBITMAP OffscrBmp=NULL;
	HDC OffscrDC=NULL;
	LPBITMAPINFO lpbi=NULL;
	LPVOID lpvBits=NULL;
	HANDLE BmpFile=INVALID_HANDLE_VALUE;
	BITMAPFILEHEADER bmfh;
	if ((OffscrBmp = CreateCompatibleBitmap(bitmapDC, width, height)) == NULL)
		return 0;
	if ((OffscrDC = CreateCompatibleDC(bitmapDC)) == NULL)
		return 0;
	HBITMAP OldBmp = (HBITMAP)SelectObject(OffscrDC, OffscrBmp);
	BitBlt(OffscrDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
	if ((lpbi = (LPBITMAPINFO)(new char[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)])) == NULL) 
		return 0;
	ZeroMemory(&lpbi->bmiHeader, sizeof(BITMAPINFOHEADER));
	lpbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	SelectObject(OffscrDC, OldBmp);
	if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, NULL, lpbi, DIB_RGB_COLORS))
		return 0;
	if ((lpvBits = new char[lpbi->bmiHeader.biSizeImage]) == NULL)
		return 0;
	if (!GetDIBits(OffscrDC, OffscrBmp, 0, height, lpvBits, lpbi, DIB_RGB_COLORS))
		return 0;
	if ((BmpFile = CreateFile(filename,
						GENERIC_WRITE,
						0, NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL)) == INVALID_HANDLE_VALUE)
		return 0;
	DWORD Written;
	bmfh.bfType = 19778;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh)) 
		return 0; 
	if (!WriteFile(BmpFile, &lpbi->bmiHeader, sizeof(BITMAPINFOHEADER), &Written, NULL)) 
		return 0;
	if (Written < sizeof(BITMAPINFOHEADER)) 
		return 0;
	int PalEntries;
	if (lpbi->bmiHeader.biCompression == BI_BITFIELDS) 
		PalEntries = 3;
	else PalEntries = (lpbi->bmiHeader.biBitCount <= 8) ?
					  (int)(1 << lpbi->bmiHeader.biBitCount) : 0;
	if(lpbi->bmiHeader.biClrUsed) 
	PalEntries = lpbi->bmiHeader.biClrUsed;
	if(PalEntries){
	if (!WriteFile(BmpFile, &lpbi->bmiColors, PalEntries * sizeof(RGBQUAD), &Written, NULL)) 
		return 0;
		if (Written < PalEntries * sizeof(RGBQUAD)) 
			return 0;
	}
	bmfh.bfOffBits = GetFilePointer(BmpFile);
	if (!WriteFile(BmpFile, lpvBits, lpbi->bmiHeader.biSizeImage, &Written, NULL)) 
		return 0;
	if (Written < lpbi->bmiHeader.biSizeImage) 
		return 0;
	bmfh.bfSize = GetFilePointer(BmpFile);
	SetFilePointer(BmpFile, 0, 0, FILE_BEGIN);
	if (!WriteFile(BmpFile, &bmfh, sizeof(bmfh), &Written, NULL))
		return 0;
	if (Written < sizeof(bmfh)) 
		return 0;
	return 1;
}
