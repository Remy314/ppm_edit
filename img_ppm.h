#ifndef IMG_PPM
#define IMG_PPM


struct img_info {
    int hight;
    int width;
    int header_size;
};

int modify_pixel(char *img,int posX,int posY,char *pixel,struct img_info info);

int extract_header_info(char * img,int size_img,struct img_info *info);





#endif
