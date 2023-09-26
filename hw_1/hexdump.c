#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[] )  {
    // check to make sure there are a correct amount of arguments
    if (argc != 3){
        printf("%s\n","Program requires 2 inputs");
        return 0;
    }

    // argv[1] is the fname
    // argv[2] is N
    int N = atoi(argv[2]);
    // printf("%s\n",argv[1]);
    // printf("%d\n",N);

    // get file, initialize 
    FILE * fname;
    long fsize;
    unsigned char * buffer;
    size_t result;

    //open the binary file in rb mode
    //fname = fopen ( "file-16.bin" , "rb" );
    fname = fopen ( argv[1] , "rb" );

    // check if the binary was successfuly opened
    if (fname==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size in bytes
    fseek (fname , 0 , SEEK_END);
    fsize = ftell (fname);
    rewind (fname);

    // allocate memory dynamically to contain the whole file:
    buffer = (unsigned char*) malloc (sizeof(char)*fsize);

    // check that the buffer is not empty
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,fsize,fname);

    //make sure the result size is equal to the actual file size
    if (result != fsize) {fputs ("Reading error",stderr); exit (3);}
    
    // the whole file is now loaded in the memory buffer
    // print every element from the buffer
    int index = 0;
    printf("%08x", index);
    for (int i = 0 ; i < result ; i++){
        if (index == N){
            index = 0;
            printf("\n");
            printf("%08x", i);
        }
            printf(" %02x", buffer[i]);
            index++;
    }
    printf("\n");

    // terminate
    fclose (fname);

    // free the memory that was dynamically allocated
    free (buffer);

    return 0;
}