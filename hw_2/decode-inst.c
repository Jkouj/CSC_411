#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[] )  {
    // check to make sure there are a correct amount of arguments
    if (argc != 2){
        printf("%s\n","Program requires 1 input");
        return 0;
    }
    
    // get file, initialize 
    FILE * fname;
    long lSize;
    unsigned char * buffer;
    size_t result;

    //open the binary file in rb mode
    //fname = fopen ( "file-16.bin" , "rb" );
    fname = fopen ( argv[1] , "rb" );

    // check if the binary was successfuly opened
    if (fname==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size in bytes
    fseek (fname , 0 , SEEK_END);
    lSize = ftell (fname);
    rewind (fname);

    // allocate memory dynamically to contain the whole file:
    buffer = (unsigned char*) malloc (sizeof(char)*lSize);
    // check that the buffer is not empty
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
    // copy the file into the buffer:
    result = fread (buffer,1,lSize,fname);
    //make sure the result size is equal to the actual file size
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    //printf("%x%x%x%x\n",buffer[0],buffer[1],buffer[2],buffer[3]);
    char * operator_arr [4] = {"mul","div","add","sub"};
    char * register_arr [4] = {"t0","t1","s0","s1"};

    for (int i = 0 ; i < lSize ; i++) {
        unsigned int temp = buffer[i];
        printf("%s ",operator_arr[temp>>6]);
        temp = temp << 26;
        printf("%s, ",register_arr[temp>>30]);
        temp = temp << 2;
        printf("%s, ",register_arr[temp>>30]);
        temp = temp << 2;
        printf("%s",register_arr[temp>>30]);
        printf("\n");
    }
}