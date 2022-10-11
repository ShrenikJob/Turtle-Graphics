#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Turtle.h"
#include "linkedList.h"
#include "effects.h"

const double PI = 3.1415926535; /* Pi constant */

int main( int argc, char* argv[] )
{
    FILE* inputFile; /* declaring the inputFile of type FILE pointer */
    LinkedList* list; /* declaring the Linkedlist */
        
    if( argc != 2 )
    {
        printf( "There must be 2 Arguments only, the executable name and the file name\n" );
    }
    else
    {
        /* read the second argument( the file name ) */
        
        inputFile = fopen( argv[1], "r" );        
        
        if( inputFile == NULL )
        {
            perror( "Error opening the file" ); 
        }
        else
        {
             /*Read and close the file */
            list = createList(); /* creates an empty linkedList*/        
            readFileCom( inputFile, list ); /* parse the FILE* to the readFileCom function */
            penDown();           
            freeLinkedList( list ); /* frees the Linked List */
            fclose( inputFile ); 
        }
        
    }

    return 0;  
}

/* prints the characters on to terminal */
void printPlot( void* draw )
{
        printf("%c", *((char*)draw));
}


/* THIS FUNCTION READS THE COMMANDS */

void readFileCom( FILE* inputFile, LinkedList* list )
{
    FILE* outputFile = fopen( "graphics.log", "a" ); /* outputting log file - append */
    int numLines = 0;
    int total  = 0; /* 1 is good, 0 is not good */
    LinkedListNode* temp = ( LinkedListNode* )malloc( sizeof( LinkedListNode ) );
    
     
    clearScreen();
    
    fprintf( outputFile, "\n" ); /* prints a new line to log file */

    while( !feof( inputFile ) )
    {
        
        Command* value = ( Command* )malloc( sizeof( Command ) );
        value->comName = ( char* )malloc( 8*sizeof( char ) );
        value->comValue = ( char* )malloc( 8*sizeof( char ) );  
        
        fscanf( inputFile, "%s %s", value->comName, value->comValue ); /* scans the command line */
        if( !feof( inputFile ) ) /* because after eof, it still continues */
        {
            numLines++;              
            strUpper( value );  /* Turns the command name to upper case */
           
             /* NEED TO ERROR CHECK */
            total = total + checkCom( value ); /* used to check is file is correct */
            
            insertLast( list, value ); /* so that its in same order when traversing through linkedList */
            temp = list->head;
            
            /*printf( "%s %s\n", list->tail->data->comName, list->tail->data->comValue );  */       
        }       
    }

    temp = list->head;
    
    /* retrieve information from LinkedList */
    if( numLines == total )
    {
        while( temp->next != NULL && list->head != NULL )
        {
            comCompare( temp->data, outputFile ) ; /* compares which command it really is and also outputs to log file */  
            temp = temp->next;  
        }

        comCompare( temp->data, outputFile ) ; /* compares the LAST COMMAND for which command it really is and also outputs to log file*/     
    }
    else
    {
        printf( "There is an error in the input file command" );
    }
    
    fprintf( outputFile, "---" ); /* prints to log file */
    setFgColour( 7 ); /* set to origianl foreground colour of white */
    setBgColour( 0 ); /* set to original background colour of black */  
    fclose( outputFile ); /* close OUTPUT FILE */
}

void strUpper( Command* value )
{
    int len = strlen( value->comName ); /* find the length of the string */
    int ii;
    int factor = 'a' - 'A'; /* the ASCII table values for 'a' minus 'A' is the factor */
    for( ii = 0; ii < len; ii++ )
    {
        if( value->comName[ ii ] >= 'a' && value->comName[ ii ] <= 'z' )
        {
            value->comName[ ii ] = value->comName[ ii ] - factor; /* turns into capital characters */ 
        } /* ELSE IS ALREADY CAPITAL */
            /* JUST INCASE NEED TO ERROR CHECK */ 
    } 
}

void comCompare( Command* value, FILE* outputFile ) 
{
    /* START static so is preserved within the function for duration of program */

    static double curAngle = 0; /* will be in radians */
    static double x1 = 0;
    static double x2 = 0;
    static double y1 = 0;
    static double y2 = 0;
    static int FG = 7;
    static int BG = 0;
    static char pattern = '+';
    void *ptr = &pattern;

    /* END static variables */

    PlotFunc myFunction = &printPlot; /* myFunction now points to printPlot function */

    if( strcmp( value->comName, "ROTATE" ) == 0 )
    {
        curAngle = curAngle + ( atof( value->comValue )*(-1) )*(PI/180); /* converts string to a double to radians */    
                                      
        fprintf( outputFile, "ROTATE ( %.3f  )\n", curAngle ); /* prints to log file */
    }
    else if( strcmp( value->comName, "MOVE" ) == 0 )
    {
        x2 = x1 + cos( curAngle )*( atof( value->comValue ) ); /* the new x-coordinate is old x-coordinate + cos( angle )*distance  */
        y2 = y1 + sin( curAngle )*( atof( value->comValue ) ); /* same as above except for y-value and sin( angle ) */     
        
        fprintf( outputFile, "MOVE ( %.3f, %.3f)-( %.3f, %.3f)\n", x1, y1, x2, y2 ); /* prints to log file */
            
        x1 = x2; /* make x1 the new coordinate */
        y1 = y2; /* like above but for y1 */ 
        

    }
    #ifndef SimpleGraphics

    else if( strcmp( value->comName, "FG" ) == 0 )
    {
        FG = atoi( value->comValue ); /* converts String to Int */
        setFgColour( FG ); /* sets the Foreground Colour */
    }
    else if( strcmp( value->comName, "BG" ) == 0 )
    {
        BG = atoi( value->comValue ); /* converts String to int */
        setBgColour( BG ); /* converts String to int */
    }
    
    #endif

    else if( strcmp( value->comName, "PATTERN" ) == 0 )
    {
        pattern = value->comValue[0]; /* gets the first character of the String */      
    }
    else if( strcmp( value-> comName, "DRAW" ) == 0 )
    {            
        x2 = x1 + cos( curAngle )*( atof( value->comValue ) ); /* the new x-coordinate is old x-coordinate + cos( angle )*distance  */
        y2 = y1 + sin( curAngle )*( atof( value->comValue ) ); /* same as above except for y-value and sin( angle ) */
         
        /*printf("%c %d", pattern , atoi( value->comValue ) ); */
        line( x1, y1, x2 - 1, y2, myFunction, ptr ); /* parses these parameters to line function in effects.c */ 
        
        fprintf( outputFile, "DRAW ( %.3f, %.3f)-( %.3f, %.3f)\n", x1, y1, x2, y2 ); /* prints to log file */
        #ifdef DEBUG                
        fprintf( stderr, "DRAW ( %.3f, %.3f)-( %.3f, %.3f)\n", x1, y1, x2, y2 ); /* prints to stderr- DEBUG MODE */
        #endif
        x1 = x2;
        y1 = y2;
    }   
}

int checkCom( Command* value )
{
    int boolean = 0;

    if( ( strcmp( value->comName, "ROTATE" ) == 0 ) ) 
    {
        boolean = 1;                   
    }
    else if( strcmp( value->comName, "MOVE" ) == 0 )
    {
        boolean = 1;    
    }
    else if( strcmp( value->comName, "FG" ) == 0 )
    {
        boolean = 1;
    }
    else if( strcmp( value->comName, "BG" ) == 0 )
    {
        boolean = 1;
    }
    else if( strcmp( value->comName, "PATTERN" ) == 0 )
    {
        boolean = 1;
    }
    else if( strcmp( value-> comName, "DRAW" ) == 0 )
    {
        boolean = 1;        
    }

    return boolean;     
}







