/*
* Lane Albrecht, ltalbrec
* 2021 Winter CSE 101 pa1
* Lex.c
* Take two command arguments which specify and input and output file
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h> /* gives strcmp -> Lab Assign (3) */
#include"List.h"

int main(int argc, char* argv[]){
    FILE* in; /* file handle for input */
    FILE* out; /* file handle for output */
    List otpt = newList();
    int lines;
    int i = 0;
    char ch;
    char word[256];
    char array[256][256];

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
    for(ch = getc(in); ch != EOF; ch = getc(in)){
        if (ch == '\n'){
            lines++;
        }
    }

    /* open output file for writing */
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Error: Unable to write to out file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    rewind(in);
    while( fscanf(in, " %s", word) != EOF ){
        strcpy(array[i], word);
        i++;
    }

    /* Sorting Variables */
    int comp;
    int pcmp = 0;
    int fi = 0;
    int bi = 0;
    prepend(otpt, 0); //List has just '0' in it to start off comparisons
    moveFront(otpt);
    char* words;
    /* Lex sort the input */
    for (i = 1; i < lines; i++){
        words = array[i];
        fi = front(otpt);
        bi = back(otpt);
        while(comp != 0){
            comp = strcmp(array[get(otpt)], words);
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

    /* Print to Out File */
    for(moveFront(otpt); index(otpt)>=0; moveNext(otpt)){
      fprintf(out, "%s\n", array[get(otpt)]);
    }
    /* close input and output files */
    fclose(in);
    fclose(out);
    return(EXIT_SUCCESS);
}