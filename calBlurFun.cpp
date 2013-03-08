/*
 * =====================================================================================
 *
 *       Filename:  calBlurFun.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年02月13日 22时00分01秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  金鹏 (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include  "functions.h"
#include  "errmsg.h"

extern long myErrno ;

static const double T = 20 ;


static CvMat* calWarpFunH(const double t , CvMat* homoMat) 
{
	float identityMatArray[9] = { 1 , 0 , 0 ,
							   0 , 1 , 0 ,
							   0 , 0 , 1 } ;

	CvMat identityMat = cvMat( 3 , 3 , CV_32FC1 , identityMatArray );
	CvMat* warpMat = cvCreateMat(3 , 3 , CV_32FC1);

	cvAddWeighted( &identityMat , (T - t) / T , homoMat , t / T , 0 , warpMat);
	return warpMat ;
}

IplImage* blurFunc(CvMat* preHomography , CvMat* homography , IplImage* latent , int tao)
{
	if( !preHomography || !homography || !latent || tao < 1 )
	{
		myErrno = ERR_ARGUMENT ;
		perrmsg(NULL);
		return NULL ;
	}
	CvMat* preHomographyInvert = cvCreateMat(3 , 3 , CV_32FC1) ;
	CvSize imageSize = cvGetSize(latent) ;
	IplImage* preSum = cvCreateImage( imageSize , latent->depth , latent->nChannels);
	IplImage* sum = cvCreateImage( imageSize , latent->depth , latent->nChannels);
	IplImage* tmp = cvCreateImage( imageSize , latent->depth , latent->nChannels);
	IplImage* preHomoFrame = cvCreateImage( imageSize , latent->depth , latent->nChannels);
	IplImage* postHomoFrame = cvCreateImage( imageSize , latent->depth , latent->nChannels);
	IplImage* result  = cvCreateImage( imageSize , latent->depth , latent->nChannels);

	CvMat* preWarpMat , *postWarpMat ;

	cvZero(sum) ;
	cvZero(preSum) ;
	cvZero(tmp) ;
	cvZero(preHomoFrame) ;
	cvZero(postHomoFrame) ;
	cvInvert(preHomography , preHomographyInvert);
	//cvNamedWindow("win1") ;
	//cvNamedWindow("win2") ;
	for( double d = 1 ; d <= tao ; d++ )
	{
		preWarpMat = calWarpFunH( d , preHomographyInvert ) ;
		postWarpMat = calWarpFunH( d , homography ) ;
		cvWarpPerspective(latent , preHomoFrame , preWarpMat) ;
		cvWarpPerspective(latent , postHomoFrame , postWarpMat) ;

		//cvShowImage("win1" , preHomoFrame) ;
		cvAdd(preHomoFrame , postHomoFrame , tmp);
		cvAdd(tmp , preSum , sum) ;
		//cvShowImage("win2" , sum) ;
		//cvWaitKey(0) ;
		cvCopy(sum , preSum) ;
	}

	cvAdd(preSum , latent , sum) ;

	cvConvertScale(sum , result , 1.0 / ( 2 * tao + 1 )) ;
	//cvConvertScale(sum , result , 0.5) ;

	cvReleaseMat(&preHomographyInvert);
	cvReleaseImage(&preSum) ;
	cvReleaseImage(&tmp) ;
	cvReleaseImage(&preHomoFrame) ;
	cvReleaseImage(&postHomoFrame) ;
	cvReleaseImage(&sum) ;

	return result ;
}



//int main(int argc, char *argv[])
//{

	//float homoMatArray[9] = { 1 , 0 , 0 ,
						   //0 , 1 , 0 ,
						   //0 , 0 , 1 } ;

	//CvMat homoMat = cvMat( 3 , 3 , CV_32FC1 , homoMatArray);
	//IplImage* a = cvLoadImage("./images/1.jpeg");
	//IplImage* b = cvLoadImage("./images/2.jpeg");

	//IplImage* res = blurFunc(&homoMat , &homoMat ,a , 4) ;
	//cvNamedWindow("win");
	//cvShowImage("win" , res);
	//cvWaitKey(0);
	//cvDestroyWindow("win");
	//cvReleaseImage(&res) ;
//}

