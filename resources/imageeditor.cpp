#include "imageeditor.h"

namespace imaging
{

ImageEditor::ImageEditor()
{
}

unsigned char * ImageEditor::apply_grayscale(unsigned char * image, int width, int height, int channels)
{
	// Grayscale Formula: L = R * 299/1000 + G * 587/1000 + B * 114/1000
	// https://pillow.readthedocs.io/en/3.2.x/reference/Image.html#PIL.Image.Image.convert
	
	unsigned char * gray_image = new unsigned char[width * height * channels];
	
	for (unsigned int pixel = 0, max_pixel = width * height; pixel < max_pixel; ++pixel){
		
		unsigned int red_shift = 0; // (0 * max_pixel) always zero;
		unsigned int green_shift = (1 * max_pixel);
		unsigned int blue_shift = (2 * max_pixel);
		
		unsigned char red_pixel_value = image[pixel + red_shift] * 299/1000;  
		unsigned char green_pixel_value = image[pixel + green_shift] * 587/1000;
		unsigned char blue_pixel_value = image[pixel + blue_shift] * 114/1000;
		
		unsigned char gray_value = red_pixel_value + green_pixel_value + blue_pixel_value;
		
		gray_image[pixel + red_shift] = gray_value;
		gray_image[pixel + green_shift] = gray_value;
		gray_image[pixel  + blue_shift] = gray_value;
	}
	
	return gray_image;
}

unsigned char * ImageEditor::apply_denoise(unsigned char * image, int width, int height, int channels)
{
	unsigned char * denoised_image = new unsigned char[width * height * channels];
	
	// copy pixels from first row
	for (unsigned int h = 0; h < height; ++h) {
		unsigned int r = pixel_index(width, height, 0, h, 0);
		unsigned int g = pixel_index(width, height, 0, h, 1);
		unsigned int b = pixel_index(width, height, 0, h, 2);
		 
		denoised_image[r] = image[r];
		denoised_image[g] = image[g];
		denoised_image[b] = image[b];
	}
	
	// copy pixels from last row
	for (unsigned int h = 0; h < height; ++h) {
		unsigned int r = pixel_index(width, height, width-1, h, 0);
		unsigned int g = pixel_index(width, height, width-1, h, 1);
		unsigned int b = pixel_index(width, height, width-1, h, 2);
		 
		denoised_image[r] = image[r];
		denoised_image[g] = image[g];
		denoised_image[b] = image[b];
	}
	
	// copy pixels from first column
	for (unsigned int w = 0; w < width; ++w) {
		unsigned int r = pixel_index(width, height, w, 0, 0);
		unsigned int g = pixel_index(width, height, w, 0, 1);
		unsigned int b = pixel_index(width, height, w, 0, 2);
		 
		denoised_image[r] = image[r];
		denoised_image[g] = image[g];
		denoised_image[b] = image[b];
	}
	
	// copy pixels from last column
	for (unsigned int w = 0; w < width; ++w) {
		unsigned int r = pixel_index(width, height, w, height-1, 0);
		unsigned int g = pixel_index(width, height, w, height-1, 1);
		unsigned int b = pixel_index(width, height, w, height-1, 2);
		 
		denoised_image[r] = image[r];
		denoised_image[g] = image[g];
		denoised_image[b] = image[b];
	}
	
	for (unsigned int w = 1; w < width-1; ++w) {
		for (unsigned int h = 1; h < height-1; ++h) {
			for (unsigned int c = 0; c < channels; ++c) {
				
				unsigned char * neighborhood = new unsigned char[9];
				
				neighborhood[0] = image[pixel_index(width, height, w-1, h-1, c)]; 
	            neighborhood[1] = image[pixel_index(width, height, w-1, h, c)];
	            neighborhood[2] = image[pixel_index(width, height, w-1, h+1, c)];
	            neighborhood[3] = image[pixel_index(width, height, w, h-1, c)];
				neighborhood[4] = image[pixel_index(width, height, w, h, c)];	            
	            neighborhood[5] = image[pixel_index(width, height, w, h+1, c)];
	            neighborhood[6] = image[pixel_index(width, height, w+1, h-1, c)];
	            neighborhood[7] = image[pixel_index(width, height, w+1, h, c)];
	            neighborhood[8] = image[pixel_index(width, height, w+1, h+1, c)];
	            
	            denoised_image[pixel_index(width, height, w, h, c)] = get_median(neighborhood, 9);
			}
		}
	}
	
	return denoised_image;
}

unsigned int ImageEditor::pixel_index(unsigned int width, unsigned int height, unsigned int w, unsigned int h, unsigned int channel) {
	return ((w * width) + h) + (channel * width * height);	
}

unsigned char ImageEditor::get_median(unsigned char * values, unsigned int size) {
	// sort values
	sort(values, size);
	if (size % 2 == 0) {
		unsigned int mid = size/2;
		return (values[mid] + values[mid-1]) / 2;
	} else {
		return values[size/2];
	}
}

void ImageEditor::sort(unsigned char * values, unsigned int size) {
    // One by one move boundary of unsorted subarray  
    for (unsigned int i = 0; i < size-1; i++) {  
        // Find the minimum element in unsorted array  
        unsigned int min_idx = i;  
        for (unsigned int j = i+1; j < size; j++)  {
        	if (values[j] < values[min_idx])  {
        		min_idx = j; 
			}
		}
  
        // Swap the found minimum element with the first element
		unsigned char tmp = values[min_idx];
		values[min_idx] = values[i];
        values[i];
    }  
}  

unsigned char * ImageEditor::apply_sharpen(unsigned char * image, int width, int height, int channels, float intensity)
{
}

}; // namespace imaging
