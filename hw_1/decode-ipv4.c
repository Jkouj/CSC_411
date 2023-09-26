#include <stdio.h>
#include <stdlib.h>


void printIP(unsigned int ip){
    unsigned int temp = 0x000000FF;
    printf("%d.%d.%d.%d\n", ip >> 24, (ip >> 16)&temp, (ip >> 8)&temp, ip&temp);
}

void printRange(unsigned int ip, unsigned int mask){
    unsigned int rangeMax = ((ip | ~mask) - 1);
    unsigned int rangeMin = ((ip & mask) + 1);
    unsigned int temp = 0x000000FF;
    printf("%s","Usable IP range: ");
    printf("%d.%d.%d.%d", rangeMin >> 24, (rangeMin >> 16)&temp, (rangeMin >> 8)&temp, rangeMin&temp);
    printf("%s"," - ");
    printf("%d.%d.%d.%d\n", rangeMax >> 24, (rangeMax >> 16)&temp, (rangeMax >> 8)&temp, rangeMax&temp);
}

void printAll(unsigned int ip, unsigned int mask){
    //printIP
    printf("%s","IP address:      ");
    printIP(ip);
    //printNetwork
    printf("%s","Network address: ");
    printIP(ip & mask);
    //printRange
    printRange(ip, mask);
    //printSubnet
    printf("%s","Subnet mask:     ");
    printIP(mask);


}

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
    
    for (int i = 0 ; i < lSize ; i += 5){
        unsigned int ip = (((((buffer[i] << 8) | buffer[i+1]) << 8) | buffer[i+2]) << 8) | buffer[i+3];
        unsigned int mask = 0xFFFFFFFF << (32 - buffer[i+4]);
        printAll(ip, mask);
        printf("\n");
        //printf("ip: %x (%d)\tmask: %x (%d)",ip,ip,mask,mask);
    }



    // terminate
    fclose (fname);
    // free the memory that was dynamically allocated
    free (buffer);
    // return
    return 0;
}



// the whole file is now loaded in the memory buffer
    // the IP address is the first 4 values
    // the following value is the # of bits in the subnet mask (N)
    // the subnet mask is N ones, followed by 0's until it reaches 32 bits
    // the Network Address is the bit-wise operator & of the IP and subnet mask