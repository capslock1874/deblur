#include  "errmsg.h"
#include  "functions.h"

long myErrno = 0 ;

const char* myErrmsg[] ={
	/*0*/	"No error" ,
	/*1*/	"Open file error" ,
	/*2*/	"Grab frame error" ,
	/*3*/	"argument error"
} ;

void perrmsg(const char* info)
{
	if( info )
	{
		printf("%s : %s\n" , info , myErrmsg[myErrno]) ;
		return ;
	}
	printf("Error : %s\n" , myErrmsg[myErrno]) ;
}
