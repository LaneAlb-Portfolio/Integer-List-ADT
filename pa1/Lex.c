/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa1
* Lex.c
* Take two command arguments which specify and input and output file
*/
#include"List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h> /* gives strcmp -> Lab Assign (3) */

int main(int argc, char* argv[]){
    FILE* in; /* file handle for input */
    FILE* out; /* file handle for output */
    List otpt = newList();
    int lines = 0;
    int i = 0;
    char ch;
    //string array
    char* line = NULL;
    char** strarr = NULL;
    /* Ensure proper number of arguments */
    if( argc != 3 ){
        printf("Usage: %d %s <input file> <output file>\n", argc,argv[0]);
        exit(EXIT_FAILURE);
    }
    /* open input file for reading */
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Error: Unable to read from input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    /* open output file for writing */
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Error: Unable to write to out file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    /* get max lines of the input file */
    for(ch = getc(in); ch != EOF; ch = getc(in)){
        if (ch == '\n'){
            lines++;
        }
    }
    /* Allocate memory for array and word*/
    strarr = malloc(lines * lines * sizeof(char *));
    line = malloc(lines * sizeof(char *));
    /* Ensure memory was properly allocated */
    if (line == NULL || strarr == NULL){
        printf("Error: Memory not allocated for strings from File\n");
        return(EXIT_FAILURE);
    }
    /* Rewind file for parsing strings */
    rewind(in);
    while(fgets(line, 100, in) != NULL){
        strarr[i] = malloc( (strlen(line)+1) * sizeof(char *));
        strcpy(strarr[i], line);
        i++;
    }

    /* Sorting Variables */
    int comp = -1; //set below 0 for starting insertion sorting
    int pcmp = 0;
    int fi = 0;
    int bi = 0;
    char* words = NULL;
    prepend(otpt, 0); //List has just '0' in it to start off comparisons
    moveFront(otpt);
    /* Lex sort the input */
    for (i = 1; i < lines; i++){
        words = strarr[i];
        fi = front(otpt);
        bi = back(otpt);
        while(comp != 0){
            comp = strcmp(strarr[get(otpt)], words);
            if (comp > 0){ //array < words, words before array[]
                if ( pcmp < 0 ){ //printf(" Before "); 
                    insertBefore(otpt, i); 
                    break;
                }
                if (get(otpt) == fi ){ //printf(" Prepend "); 
                    prepend(otpt, i); 
                    break;
                }
                movePrev(otpt);
            }
            if (comp < 0 ){ //array > words, words after array[]
                if ( pcmp > 0 ){ //printf(" After "); 
                    insertAfter(otpt, i); 
                    break;
                }
                if (get(otpt) == bi ){ //printf(" Append "); 
                    append(otpt, i); 
                    break;
                }
                moveNext(otpt);
            }
            if (comp == 0) { insertBefore(otpt, i);}
            pcmp = comp;
        }
        moveFront(otpt);
    }
    /* Print to output file */
    for(moveFront(otpt); index(otpt)>=0; moveNext(otpt)){
      fprintf(out, "%s", strarr[get(otpt)]);
    }
    /* Free all Memory allocated */
    for (int x = 0; x < lines+1; x++){
        free(strarr[x]);
    }
    free(strarr);
    free(line);
    fclose(in);
    fclose(out);
    freeList(&otpt);
    return(EXIT_SUCCESS);
}