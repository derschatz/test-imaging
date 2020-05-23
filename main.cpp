#include <cstdlib>
#include <iostream>

#include <windows.h>
#include <stdio.h>

#include "CImg.h"
#include "resources/guicon.h"
#include "resources/imagehelper.h"

/// ---- include your own files here


/// ----

using namespace std;
using namespace cimg_library;
using namespace imaging;

int main(int argc, char *argv[])
{
	// Open a console and bind I/O to it
	RedirectIOToConsole();

	cout << "Loading input image...\n";
    ImageHelper *helper = new ImageHelper();

    // input image
    unsigned char *image;
	int width;
	int height;
	int channel;

	helper->getImageInfo("assets/lena.bmp", width, height, channel);
	image = new unsigned char[width * height * channel];
	helper->loadImage("assets/lena.bmp", &image);

	helper->showImage(image, width, height, channel);
	cout << "Input image width:" << width << " height:" << height << endl;

    /// ---- Add your code here



    // set channel=1 or 3 to save image as grayscale or RGB, respectively
    // save your images as Bitmap
    //helper->saveImage("output1.bmp", ptr, width, height, channel);

    /// ----

    cout << "END\n";
    system("PAUSE");

    delete helper;
    delete[] image;

    return EXIT_SUCCESS;
}
