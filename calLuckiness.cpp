/*
 * =====================================================================================
 *
 *       Filename:  calLuckiness.cpp
 *
 *    Description:  calculate luckiness
 *
 *        Version:  1.0
 *        Created:  2013年02月12日 22时15分23秒
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
#include <cmath>

static const int sigma = 20 ;
#define square(a) ((a) *(a))



CvMat* calLuckiness(CvMat* homoPre , CvMat* homoPost , int rows , int cols)
{
	CvMat* luckiness = cvCreateMat(rows , cols , CV_32FC1) ;
	float index[3] = { 0 , 0 ,1.0 } ;
	float homoedIndexArray[3] =  { 0 } ;
	float homoPreInvertArray[9] = { 0 } ;
	CvMat indexMat ;
	cvInitMatHeader( &indexMat , 1 , 3 , CV_32FC1 , index );
	CvMat homoedIndex = cvMat( 1 , 3 , CV_32FC1 , homoedIndexArray );
	CvMat homoPreInvert = cvMat( 3 , 3 , CV_32FC1 , homoPreInvertArray) ;
	float* ptr = NULL ;
	float pixelDisplacement , disToPost , disToPre ;
	int foo = 2 ; 
	if( homoPre )
	{

		cvInvert(homoPre , &homoPreInvert , CV_LU);
	}

	for( int i = 0 ; i < rows ; i++ )
	{
		ptr = (float*)( luckiness->data.ptr + i * luckiness->step ) ;
		index[0] = (float)i ;

		for( int j = 0; j < cols ; j++ , ptr++ )
		{
			index[1] = (float)j ;
			index[2] = 1.0 ;
			if( homoPost )
			{

				cvMatMul(&indexMat , homoPost , &homoedIndex) ;

				disToPost = square(homoedIndexArray[0] / homoedIndexArray[2] - index[0])
					+ square(homoedIndexArray[1] / homoedIndexArray[2] - index[1]) ;
			}
			else
			{
				disToPost = 0 ;
				foo = 1 ; 
			} 

			if( homoPre )
			{

				cvMatMul(&indexMat , homoPre , &homoedIndex) ;

				disToPre = square(homoedIndexArray[0] / homoedIndexArray[2] - index[0])
					+ square(homoedIndexArray[1] / homoedIndexArray[2] - index[1]) ;
			}
			else
			{
				disToPre = 0 ;
				foo = 1 ;
			}

			pixelDisplacement = exp(-1 * (disToPost + disToPre) / (foo * square(sigma)));
			
			*ptr = pixelDisplacement ; 
		}
		cvZero(&homoedIndex) ;
		cvZero(&indexMat) ;
	}
	
	return luckiness ;	
}

CvMat** calLuckMats(CvMat** homographies , int rows , int cols , int size)
{
	CvMat** luckMats = new CvMat*[size] ;
	CvMat *homoPre , *homoPost ;

	luckMats[0] = calLuckiness(NULL , homographies[0] , rows , cols) ;

	for( int i = 1 ; i < size - 1 ; i++ )
	{
		homoPre = homographies[i - 1] ;
		homoPost = homographies[i] ;
		luckMats[i] = calLuckiness(homoPre , homoPost , rows , cols) ;
	}
	
	luckMats[size-1] = calLuckiness(homographies[size-2] , NULL , rows , cols) ;

	return luckMats ;
}

//int main(int argc, char *argv[])
//{
	//float pos[] ={1 , 0 , 1 ,
				  //0 , 1 , 0 ,
				  //0 , 0 , 1 } ;
	//CvMat post = cvMat( 3 , 3 , CV_32FC1 , pos);
	//CvMat* luckinessMat = calLuckiness(&post, &post , 3 , 3) ;	
	//displayMat(luckinessMat) ;
//}

