#include <stdio.h>
#include "file_extractor.h"
#include "img_ppm.h"

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("error parameter\n");
        return 1;
    }
    char *path = argv[1];
    char *img = NULL;

    int file_size = extract_file(path,&img);
    if (file_size == -1){
        return 1;
    }

    struct img_info info;
    extract_header_info(img,file_size,&info);
    
    int posX,posY;
    printf("Insert the pixel position for X: ");
    fflush(stdout);
    scanf("%d",&posX);

    printf("Insert the pixel position for Y: ");
    fflush(stdout);
    scanf("%d",&posY);


    char color[3] = {200,0,0};

    modify_pixel(img,posX,posY,color ,info);
    

    int rs = store_file("output.ppm", img,file_size);
    if (rs ==-1){
        return 1;
    }
    
    return 0;
}
