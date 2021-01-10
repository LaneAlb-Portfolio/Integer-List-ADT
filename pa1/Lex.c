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
    char word[15]; //dunno what this needs to be
    char array[10][15];
    if( argc != 3 ){
        printf("Usage: %d %s <input file> <output file>\n", argc,argv[0]);
        exit(EXIT_FAILURE);
    }
    /* open input file for reading */
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    for(ch = getc(in); ch != EOF; ch = getc(in)){
        if (ch == '\n'){
            lines++;
        }
    }
    printf("It's %d long", lines);
    printf("\nOpening outfile.. \n");
    // How to allocate specific amount of memory for array
    /* open output file for writing */
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    printf("\nWriting to outfile.. \n");
    rewind(in);
    while( fscanf(in, " %s", word) != EOF ){
        strcpy(array[i], word);
        i++;
    }
    printf("\n array print\n");
    for (i = 0; i < lines; i++){
        printf("%s ", array[i]);
    }
    /* Populate list based off array contents and indices*/
    printf("\n List Creation, Arry index reset\n");
    int comp;
    int pcmp = 0;
    int fi = 0;
    int bi = 0;
    prepend(otpt, 0); //List has just '0' in it to start off comparisons
    moveFront(otpt);
    char* words;
    /* Can prob do this in double for loop; with outside starting at i = 0 and inside i=1*/
    for (i = 1; i < lines; i++){
        words = array[i];
        fi = front(otpt);
        bi = back(otpt);
        while(comp != 0){
            comp = strcmp(array[get(otpt)], words);
            if (comp > 0){ //array < words, words before array[]
                if ( pcmp < 0 ){ printf(" iBefore "); insertBefore(otpt, i); break;}
                if (get(otpt) == fi ){ printf(" Prepend "); prepend(otpt, i); break;}
                movePrev(otpt);
                }
            if (comp < 0 ){ //array > words, words after array[]
                if ( pcmp > 0 ){ printf(" iAfter "); insertAfter(otpt, i); break;}
                if (get(otpt) == bi ){ printf(" Append "); append(otpt, i); break;}
                moveNext(otpt);
            }
            if (comp == 0) {printf(" Identical "); insertBefore(otpt, i);}
            pcmp = comp;
        }
        printf(" While Exit ");
        moveFront(otpt);
    }
    printf("\n");
    printList(stdout, otpt);
    printList(out, otpt);

    /* close input and output files */
    fclose(in);
    fclose(out);
    return(EXIT_SUCCESS);
}
/* Quit if 2 command arguments are not present */
// I think this uses scanf

/* Count number of lines in Input File to create an array of same length */
/* Populate array with each line in the Input File */

/* Create a list that will lexicographic (alphabetic) sort the array */
/* The list will have the indices of the array elements rather than the data */

/* Tips: Use Insertion Sort as a guide, inserting 1 by 1 to do this */
/* Don't directly use Insertion Sort */

/*Print List to the Output File*/
/* Order should be -> five four one three two */