#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  FILE *fp;
  int line = 1;
  char *substring;
  int pos = 0;
  int found = 0;
  char temp[512];
  char *splitted;
  int word_index = 0;

  /* Check if correct number of arguments is provided */
  if(argc < 3 || argc > 3){
    printf("Usage: %s <file> <string>\n", argv[0]);
    exit(1);
  }

  /* Check if correct extension of the file is provided */
  if(strstr(argv[1], ".txt") == NULL){
    printf("Search can only be applied to txt files\n");
    return(0);
  }
  
  /* Open the file */
  if((fp = fopen(argv[1], "r")) == NULL){
    printf("Error\n");
    return(0);
  }

  /* Loop through all lines */
  while(fgets(temp, 512, fp) != NULL){
    /* Split line into words using space as a delimiter */
    splitted = strtok(temp, " ");
    word_index = 0;

    /* Loop through all words on current line */
    while((splitted != NULL)){
      /* Check for word containing a phraze we need */
      substring = strstr(splitted, argv[2]);

      if(substring != NULL){
        pos = (strlen(temp) - strlen(substring)) + (word_index * (strlen(substring) + 1));
        printf("%d:%d %s\n", line, pos, argv[2]);
        found = 1;
      }

      splitted = strtok(NULL, " ");
      word_index++;
    }
    
    line++;
  }

  /* Display error if no words were found */
  if(!found){
    printf("No matches\n");
  }
  
  /* Close the stream */
  if(fp){
    fclose(fp);
  }
  
  return(0);
}
