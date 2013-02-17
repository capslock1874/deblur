/*
 * =====================================================================================
 *
 *       Filename:  convertPointsToMat.c
 *
 *    Description:  转换坐标点为坐标矩阵 N*2
 *
 *        Version:  1.0
 *        Created:  2013年02月04日 00时18分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  金鹏 (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include  "functions.h"

CvMat* convertPointsToMat(CvPoint2D32f* corner , int corner_count)
{	
	CvMat* corner_mat = cvCreateMat(corner_count , 3 , CV_32FC1); 

	for( int row= 0 ;row < corner_count  ; row++ )
	{
		float* ptr = (float*)(corner_mat->data.ptr + row * corner_mat->step ) ;
		*ptr++ = corner[row].x;
		*ptr++ = corner[row].y;
		*ptr++ = 1 ;
	}
	return corner_mat ;
}


