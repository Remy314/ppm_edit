#include "img_ppm.h"
#define PIXEL_SIZE 3

int  modify_pixel(char *img,int posX, int posY,char *pixel,struct img_info info){
    if(posX <= info.width && posY <= info.width){
        int pos = info.header_size + (posX + info.width * posY)*PIXEL_SIZE;
        int j = 0;
        for (int i = pos; i<pos + PIXEL_SIZE ; i++){
            img[i] = pixel[j];
            j++;
        } 
        return 1;
    }         
    return 0;

}


int asciiToInt(char value){
    if (0x30 <= value && value <= 0x39 )
        return (int)value - 0x30;
    return -1;
}

int extract_header_info(char * img,int size_img,struct img_info *info){
    int index_nl1 = 0;
    int index_sp2 = 0;
    int index_nl3 = 0;
    int index_nl4 = 0;

    //TODO make it safe for no ppm img

    while(img[index_nl1] != '\n' ){
        index_nl1++;
        index_sp2++;
        index_nl3++;
        index_nl4++;
    }
    while(img[index_sp2] !=' '){
        index_sp2++;
        index_nl3++;
        index_nl4++;
    }
    while(img[index_nl3] != '\n'){
        index_nl3++;
        index_nl4++;
    }
    index_nl4++;
    while(img[index_nl4] != '\n'){
        index_nl4++;
    }

    unsigned int hight = 0;
    unsigned int width = 0;

    int mult = 1;
    for (int i = index_sp2-1; i > index_nl1; i-- ){
        width = width + asciiToInt(img[i])*mult;
        mult = mult*10;
    }

    mult = 1;
    for (int i = index_nl3-1; i > index_sp2; i-- ){
        hight = hight + asciiToInt(img[i])*mult;
        mult = mult*10;
    }

    info->hight = hight;
    info->width = width;
    info->header_size = index_nl4+1;
    
    return 0;

}
