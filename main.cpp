#include <cstdlib>
#include <iostream>

#include <windows.h>
#include <stdio.h>

#include "CImg.h"
#include "resources/guicon.h"
#include "resources/imagehelper.h"

/// ---- include your own files here
#include "resources/imageeditor.h"
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
	
	const char * image_name = "assets/lena.bmp";
	
	helper->getImageInfo(image_name, width, height, channel);
	image = new unsigned char[width * height * channel];	
	
	helper->loadImage(image_name, &image);
		
	helper->showImage(image, width, height, channel);
	cout << "Input image width:" << width << " height:" << height << endl;

    /// ---- Add your code here
    
    ImageEditor * editor = new ImageEditor();
    
    // Grayscale code
    const char * grayscale_image_name = "output/lena_gray.bmp";
    unsigned char *grayscale_image = editor->apply_grayscale(image, width, height, channel);
//    helper->showImage(grayscale_image, width, height, channel);
    helper->saveImage(grayscale_image_name, grayscale_image, width, height, 1);
    
	delete[] grayscale_image;
    delete[] image;
    
	// denoise code
	
	const char * noise_img_name = "assets/lena_noise.bmp";
	const char * denoised_img_name = "lena_denoise.bmp";
	
	helper->getImageInfo(noise_img_name, width, height, channel);
	image = new unsigned char[width * height * channel];	
	helper->loadImage(noise_img_name, &image);	
	helper->showImage(image, width, height, channel);
	
	unsigned char *denoised_image = editor->apply_denoise(image, width, height, channel);
	  
//	helper->showImage(denoised_image, width, height, channel);
	helper->saveImage(denoised_img_name, denoised_image, width, height, 3);
    
    delete[] denoised_image;
    delete[] image;
    
    // sharpening filter code
	
	const char * sharp_img_name10 = "lena_sharpening_filter.bmp";
	
	helper->getImageInfo(image_name, width, height, channel);
	image = new unsigned char[width * height * channel];	
	helper->loadImage(image_name, &image);
	
	unsigned char *sharp_image = editor->apply_sharpening(image, width, height, channel, 1.0);
	helper->saveImage(sharp_img_name10, sharp_image, width, height, 3);
    
    sharp_image = editor->apply_sharpening(image, width, height, channel, 0.1);
	
    delete[] sharp_image;
    
    //helper->saveImage("output1.bmp", ptr, width, height, channel);

    /// ----

    cout << "END\n";
    system("PAUSE");
	
	
	delete editor;
    delete helper;
    delete[] image;

    return EXIT_SUCCESS;
}
