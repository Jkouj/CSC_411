#include <stdio.h>
#include <stdlib.h>

void printMask(int index, unsigned long mask, int bit_count)
{
  if(bit_count == 1)
  {
    printf("0x%08X    0x%02lX    %lu\n", index, mask, mask);
  }
  else if(bit_count == 2)
  {
    printf("0x%08X    0x%04lX    %lu\n", index, mask, mask);
  }
  else if(bit_count == 4)
  {
    printf("0x%08X    0x%08lX    %lu\n", index, mask, mask);
  }
  else
  {
    printf("0x%08X    0x%016lX    %lu\n", index, mask, mask);
  }
}

void littleEndian(unsigned long key, int bit_count, int index, unsigned char * buffer){
    unsigned long mask = 0x0000000000000000;
    for (int i = ((bit_count + index) -1); i > index; i--){
        mask = mask | buffer[i];
        mask = mask << 8;
    }
    mask = mask | buffer[index];
    if (mask == key){
        printMask(index,mask,bit_count);
    }
}

void bigEndian(unsigned long key, int bit_count, int index, unsigned char * buffer){
    unsigned long mask = 0x0000000000000000;
    for (int i = 0 ; i < bit_count-1 ; i++){
            mask = mask | buffer[index+i];
            mask = mask << 8;
        }
    mask = mask | buffer[(index+bit_count)-1];
    if (mask == key){
        printMask(index,mask,bit_count);
    }
}


int main(int argc, char *argv[] )  {
    // check to make sure there are a correct amount of arguments
    if (argc != 4){
        printf("%s\n","Program requires 3 inputs");
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

    unsigned long key = strtoul(argv[2], NULL, 10);
    char byte_count = argv[3][0];
    char end_type = argv[3][1];
    // printf("%lu\n",key);
    // printf("%c\n",byte_count);
    // printf("%c\n",end_type);

    for (int i = 0 ; i < lSize ; i += atoi(&byte_count)) {
        if (end_type == 'l'){
            littleEndian(key,atoi(&byte_count),i,buffer);
        }
        if (end_type == 'b'){
            bigEndian(key,atoi(&byte_count),i,buffer);
        }
    }
}