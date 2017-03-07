//Cathal McKenna 15324261
//UNIX Programming Assignment 1
//Variation = head and even

//program by default prints the first ten lines of the input
//from either stdin or a file argument to the program
//all features working
//program can output a chosen number of lines
//or output all the even lines or a chosen number of even lines

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int DEFAULT_NUMBER_OF_LINES = 10;

void printHelp(void);

int main(int argc,char* argv[]){
    int opt,numberOfLines;
    int nflag = 0;
    int vflag = 0;
    int hflag = 0;
    int eflag = 0;
    int fileFlag = 0;
    FILE *file;
    char* input;

    while((opt = getopt(argc, argv,"n:Vhe")) != -1){	//check for arguments
        switch(opt){
            case 'n':
                numberOfLines = atoi(optarg);
                nflag = 1;
                break;

            case 'V':
                vflag = 1;
                break;

            case 'h':
                hflag = 1;
                break;

            case 'e':
                eflag = 1;
                break;

            case '?':
                printf("error unrecognised argument\n");
                return 0;
                break;
        }
    }
    if(vflag){      //if V print info and exit
        printf("\nCathal McKenna\n"
                       "15324261\n"
                       "cathal.mc-kenna@ucdconnect.ie\n\n");
        return 0;
    }
    if(hflag){      //if h print help and exit
        printHelp();
        return 0;
    }
    if(optind < argc){      //if there are extra args, it will be the file name
        for(int index = optind; index < argc; index++){
            input = argv[index];
        }
        fileFlag = 1;
    }
    if(fileFlag){       //if there is a file, attempt to open it
        file = fopen(input, "r");
        if (file == NULL) {     //if file not found, error and exit
            printf("Error: file not found\n");
            return 0;
        }
    }
    else{
        file = stdin;       //if no file read from stdin
    }
    char line[100];
    int i = 1;
    while(fgets(line,100,file)){
        if(!eflag && nflag){        //given just number of lines
            if(i <= numberOfLines){
                printf("%d:%s",i,line);
                i++;
            }
        }
        else if(eflag && nflag){        //given even and number of lines
            if(i <= numberOfLines * 2){
                if(i %2 ==0){
                    printf("%d:%s",i,line);
                }
                i++;
            }
        }
        else if(eflag && !nflag){       //just given even
            if(i <= DEFAULT_NUMBER_OF_LINES * 2){
                if(i %2 ==0){
                    printf("%d:%s",i,line);
                }
                i++;
            }
        }
        else{       //given no args
            if(i <= DEFAULT_NUMBER_OF_LINES){       //prints the default number of lines
                printf("%d:%s",i,line);
                i++;
            }
        }
    }

    return 0;
}

void printHelp(void){       //function used to print help
    printf("usage: { head } [OPTION ] . . . [ FILE ]\n"
                   "options:\n"
                   "-V output version info\n"
                   "-h display help and exit\n"
                   "-e print even lines\n"
                   "-n [NUMLINES] print n lines\n");
    return;
}