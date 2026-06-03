#include <stdio.h>

int main() {
   FILE *fp;

    long total_memory;
    long available_memory;

    char label[50];

    fp = fopen("/proc/meminfo","r");

    if(fp == NULL) {
       printf("Error opening meminfo file\n");
       return 1;
    }
 
     fscanf(fp,"%s %ld",label,&total_memory);
     fscanf(fp,"%s %ld",label,&available_memory);
     fclose(fp);

     long used_memory = total_memory - available_memory;

     printf("==== Memory Status ====");
     printf("Total Memory :%ld kB\n",total_memory);
     printf("Available Memory:%ld kB\n",available_memory);
     printf("Used Memory:%ld kB\n",used_memory);

     return 0;
}
