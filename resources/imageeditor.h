#ifndef __IMAGEEDITOR_H__

#define __IMAGEEDITOR_H__

namespace imaging
{

class ImageEditor
{
	
public:
	ImageEditor();
	unsigned char * apply_grayscale(unsigned char * image, int width, int height, int channels);
	unsigned char * apply_denoise(unsigned char * image, int width, int height, int channels);
	unsigned char * apply_sharpening(unsigned char * image, int width, int height, int channels, float intensity);
private:
	unsigned int pixel_index(unsigned int width, unsigned int height, unsigned int w, unsigned int h, unsigned int channel);
	unsigned char get_median(unsigned char * values, unsigned int size);
	void sort(unsigned char * values, unsigned int size);
};
}; // namespace imaging

#endif
