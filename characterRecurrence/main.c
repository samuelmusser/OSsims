#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//int to keep track of size of symbol array
int size;

//stores the objects read in from file
struct character {
    int  occurences;
    char  findMe[10];
};

//a comparator to decide whether to store
//(returns 1 if object has been read before, 0 if it is new)
int addMe(char symbol[], struct character stored)
{

    //compares char[] of symbol
    if (memcmp(symbol, stored.findMe, 10) == 0) {
        return 1;
    } else {
        return 0;
    }
}

//a comparator for qsort (descending order, for possible future implementation)
int comparator(const void *x, const void *y)
{

    int s = ((struct character *)x)->occurences;
    int r = ((struct character *)y)->occurences;

    return (r-s);
}

//creates a loop that reads all objects from file and stores them
void readNstore(struct character c[])
{

    //creates char array for temp storage
    char temp[10];

    //int to tell whether or not element was added
    int added;

    //loops through file and reads data until end of file (returns -1)
    while (scanf("%s", temp) != -1) {

        //reset added identifier
        added = 0;

        if (size == 0) {                           //base case
            size+=1;
            for (int z = 0; z < 10; z++) {
                c[size - 1].findMe[z] = temp[z]; //copies array
            }
            c[size - 1].occurences = 1;
        }

        else {
            for (int i = 0; i < size; i++) {
                if (addMe(temp, c[i]) == 1) {
                    c[i].occurences +=1;                 //increases occurence
                    break;
                } else if (i == (size - 1)) {
                    for (int m = 0; m < 10; m++) {
                        c[size + 1].findMe[m] = temp[m]; //copies array
                    }
                    c[size + 1].occurences = 1;
                    added = 1;
                } else { } //do nothing as else statement because both cover options
            }
            if (added) {
                size+=1;
            }
        }
    }
}

//output the objects with their count in order of most occuring and sort them
void printOutput(struct character c[])
{

    //qsort((void *)c, size, sizeof(int), comparator);  Use? TBD. Buggy.

    int max = 0;

    for (int ll = 0;  ll < size; ll++) {
        if(max < c[ll].occurences) {
            max = c[ll].occurences;
        }
    }

    while(max > 0) {
        for (int d = 0; d < size; d++) {
            if(c[d].occurences == max) {
                printf("%s->%d \n", c[d].findMe, c[d].occurences);
            }
        }
        max-=1;
    }
}

//executes project with file intake and calls methods to return output
int main(int argc, char *argv[])
{
    //initiates large array of objects for presumably large storage of information
    struct character bank[200000];
    size = 0;

    //reads through the input file and stores them
    readNstore(bank);

    //outputs the stored values and their occurences as specificed in assignment
    printOutput(bank);

    return 0;
}
