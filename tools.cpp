/*
 * =====================================================================================
 *
 *       Filename:  tools.cpp
 *
 *    Description:  some tool function
 *
 *        Version:  1.0
 *        Created:  2013年02月13日 20时48分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  金鹏 (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include  "functions.h"
#include "errmsg.h"

void displayMat(CvMat* mat)
{
	for( int i = 0 ; i < mat->rows ; i++ )
	{
		float* ptr = (float*)(mat->data.ptr + i * mat->step) ;
		for( int j = 0 ; j < mat->cols ; j++ )
		{
			printf("%f " ,*(ptr+j));	
		}
		printf("\n");	
	}
	
}

void releaseMats(CvMat*** mats , int size )
{
	for( int i = 0 ; i < size ; i++ )
	{
		cvReleaseMat(&((*mats)[i]));
	}

	delete *mats ;
	
}

void releaseFrames(IplImage*** frames , int& size)
{
	for( int i = 0 ; i < size; i++ )
	{
		cvReleaseImage(&((*frames)[i]));
	}

	delete *frames ;
}

