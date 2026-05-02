#include <iostream>

int main() {
    //always keeps the same aspect ratio as in development
    double devViewportWidthPixels = 1920;
    double devViewportHeightPixels = 1080;
    double newViewportWidthPixels = 2000;
    double newViewportHeightPixels = newViewportWidthPixels * (double)(devViewportHeightPixels / devViewportWidthPixels);
    std::cout << "new viewport height pixels: " << newViewportHeightPixels << std::endl;
    
    double screenPercentToOneMetre = 10;
    double devPixelsToOneMetre = devViewportWidthPixels / screenPercentToOneMetre;
    std::cout << "dev pixels to one metre: " << devPixelsToOneMetre << std::endl;
    
    double newPixelsToOneMetre = newViewportWidthPixels / screenPercentToOneMetre;
    std::cout << "new pixels to one metre: " << newPixelsToOneMetre << std::endl;
    
    double newViewportWidthMetric = newViewportWidthPixels / newPixelsToOneMetre;
    std::cout << "new viewport width metric: " << newViewportWidthMetric << std::endl;
    
    double newViewportHeightMetric = newViewportHeightPixels / newPixelsToOneMetre;
    std::cout << "new viewport height metric: " << newViewportHeightMetric << std::endl;
    
    double originalImageWidthPixels = 256;
    double originalImageHeightPixels = 256;
    
    double imageWidthPixels = originalImageWidthPixels - (originalImageWidthPixels * ((devViewportWidthPixels - newViewportWidthPixels) / devViewportWidthPixels));
    std::cout << "pre-rounding new image width pixels: " << imageWidthPixels << std::endl;
    if(imageWidthPixels - (int)imageWidthPixels > 0.5)
        imageWidthPixels = (int)imageWidthPixels + 1;
    else
        imageWidthPixels = (int)imageWidthPixels;
    std::cout << "new image width pixels: " << imageWidthPixels << std::endl;
    
    //only allow square textures, and since the aspect ratio is the same, give height the same value
    double imageHeightPixels = imageWidthPixels;
    
    double imageWidthMetric = (double)imageWidthPixels / newPixelsToOneMetre;
    std::cout << "image width metric: " << imageWidthMetric << std::endl;
    
    double imageHeightMetric = imageWidthMetric;
    
    //x and y positions are basically the same
    
    double newViewportXMetric = 2.1;
    double newViewportYMetric = 5.0;
    
    double imageXMetric = 1.0;
    double imageYMetric = 4.1;
    
    bool imageRendered = false;
    
    //store width and height in pixels all the time, as well, since those are small values unlikely to change much
    
    if(((imageXMetric + imageWidthMetric) >= newViewportXMetric) && (imageXMetric < (newViewportXMetric + newViewportWidthMetric))) {
        if(((imageYMetric + imageHeightMetric) >= newViewportYMetric) && (imageYMetric < (newViewportYMetric + newViewportHeightMetric))) {
            imageRendered = true;
        }
    }
    std::cout << "imageRendered: " << imageRendered << std::endl;
    
    if(imageRendered) {
        double imageXPixels = imageXMetric - newViewportXMetric;
        imageXPixels = imageXPixels * newPixelsToOneMetre;
        int finalImageXPixels = imageXPixels;
        double imageYPixels = imageYMetric - newViewportYMetric;
        imageYPixels = imageYPixels * newPixelsToOneMetre;
        int finalImageYPixels = imageYPixels;
        
        std::cout << "image x pixels: " << finalImageXPixels << std::endl;
        std::cout << "image y pixels: " << finalImageYPixels << std::endl;
    }
    return 0;
}
