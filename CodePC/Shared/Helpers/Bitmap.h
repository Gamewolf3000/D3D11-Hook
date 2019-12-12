#include <Windows.h>
#include <iostream>
using namespace std;

template <class T>
void printBlock(T block[64])
{
	cout << endl;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			cout << block[y*8+x] << '\t';
		}
		cout << endl;
	}
}

unsigned char* LoadBitmapFileRGBA(char* filename, BITMAPINFOHEADER *bitmapInfoHeader);

bool SaveBMPFile(TCHAR *filename, HBITMAP bitmap, HDC bitmapDC, int width, int height);