#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> 


int main(void) {
  char delimit[]=" \t\r\n\v\f";
  
  do{
    char s[100];
    char command[100];
    printf("%s> ", getcwd(s, 100));
    fgets(command, 100, stdin);
    char * arg1 = strtok(command, delimit);
    char temp[100];
    char temp2[100];
    strcpy(temp, &command[strlen(arg1) + 1]);
    
    if(strcmp(arg1, "dir") == 0){ //All items in a directory
      struct dirent *de;
  
      DIR *dr = opendir("."); //opendir() returns a pointer of DIR type. 
  
      if (dr == NULL) {
        printf("Could not open current directory" );
        return 0;
      }

      while ((de = readdir(dr)) != NULL){ //for readdir()
       printf("%s\n", de->d_name); 
      }
  
      closedir(dr);
    }
    else if(strcmp(arg1, "pwd") == 0){ //current directory path
      char s[100];
      printf("%s\n", getcwd(s, 100));
    }
    else if(strcmp(arg1, "cd") == 0){ //change directory
      char * arg2 = strtok(temp, delimit);
      chdir(arg2);      
    }
    else if(strcmp(arg1, "del") == 0){ //delete file
      char * arg2 = strtok(temp, delimit);

      if (remove(arg2) == 0){
        printf("Deleted successfully\n");
      }
      else{
        printf("Unable to delete the file\n");
      }      
    }
    else if(strcmp(arg1, "type") == 0){
      char * arg2 = strtok(temp, delimit);
      FILE *fp;
      fp = fopen(arg2, "r");
      
      
      if (NULL == fp) {
        printf("The file can't be opened or can't be found\n");
        
      }
      else{
        char sourceLine[1000];

        while (fgets(sourceLine, 1000, fp) != NULL) {
          printf("%s", sourceLine);
        }
        printf("\n");
        fclose(fp);
      }
      
    }
    else if(strcmp(arg1, "copy") == 0){
      FILE *fp;
      FILE *fp2;
      char * arg2 = strtok(temp, delimit); 
      char *token = arg2;
      char *arg3;
    
      fp = fopen(arg2, "r");

      arg3 = basename(arg2);
      
      if (fp == NULL) {
        printf("Could not open source file\n");
       }
      else{
        if (fopen(arg3, "r") == NULL) {
          fp2 = fopen(arg3, "w");
          char sourceLine[1000];
          size_t n;

          while ((n = fread(sourceLine, sizeof(char), sizeof(sourceLine), fp)) > 0) {
            fwrite(sourceLine, sizeof(char), n, fp2);
          }
          fclose(fp);
          fclose(fp2);
          printf("File successfully created\n");
          } else {
            printf("File already exists in directory\n");
          }
        
      }
      
    }
    else if(strcmp(arg1, "ren") == 0){
      char * arg2 = strtok(temp, delimit); 
      strcpy(temp2, &command[strlen(arg1) + strlen(arg2) + 1]);
      char * arg3 = strtok(temp2, delimit);
      if (rename(arg2, arg3) == 0) {
        printf("File renamed successfully\n");
      } else {
        printf("Error renaming file\n");
      }
    
    }
    

    else{
      //break;
      printf("Unrecognized command\n");
    }
    
    
    
  }while(1 > 0);
  
  return 0;
}
