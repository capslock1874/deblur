/*
 * =====================================================================================
 *
 *       Filename:  testForTlk.cpp
 *
 *    Description:  从视频帧序列得到相应得单一性矩阵 
 *
 *        Version:  1.0
 *        Created:  2013年02月02日 09时54分29秒
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


extern long myErrno ;

static const int MAX_CORNERS = 500 ;


static void releaseImageArray(IplImage** array , int size)
{
	for( int i = 0 ; i < size  ; i++ )
	{
		cvReleaseImage(&array[i]);
	}
	delete array ;
	
}

CvMat** getHomographies(IplImage** frames , int size) /* 传入到图片必须是灰度图 */
{
	IplImage** grayFrames = frames ;

	if(frames == NULL || frames[0]->nChannels != 1 || size <= 0 )
	{
		grayFrames = new IplImage*[size] ;
		CvSize imgSize = cvGetSize(frames[0]);
		//cvNamedWindow("win");
		for( int i = 0 ; i < size ; i++ )
		{
			grayFrames[i] = cvCreateImage(imgSize , IPL_DEPTH_8U , 1);
			cvCvtColor(frames[i] , grayFrames[i] , CV_RGB2GRAY) ;
			//cvShowImage("win" , grayFrames[i]);
			//cvWaitKey(333);
			//P(i);
		}	
	}
	

	CvMat** homographies = new CvMat*[size] ;
	IplImage *imgA , *imgB ;

	imgA = grayFrames[0] ;

//	P(grayFrames[0]->depth);
//	P(grayFrames[0]->nChannels);

	CvSize img_size = cvGetSize(imgA);
	int win_size = 10 ;

	IplImage *eig_image = cvCreateImage(img_size , IPL_DEPTH_32F , 1) ;
	IplImage *tmp_image = cvCreateImage(img_size , IPL_DEPTH_32F , 1) ;

	int corner_count = MAX_CORNERS ; 
	CvPoint2D32f *cornersA = new CvPoint2D32f[corner_count];
	cvGoodFeaturesToTrack(
			imgA ,
			eig_image ,
			tmp_image ,
			cornersA ,
			&corner_count ,
			0.01 ,
			5.0 ,
			0 ,
			3 ,
			0 ,
			0.04
			);

	cvFindCornerSubPix(
			imgA , 
			cornersA ,
			corner_count ,
			cvSize(win_size , win_size) ,
			cvSize(-1 , -1) ,
			cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS , 20 ,  0.03 ) 
			) ;

	char features_found[MAX_CORNERS] ;
	float features_error[MAX_CORNERS] ;

	CvSize pyr_sz = cvSize(imgA->width + 8 , imgA->height / 3);

	IplImage* pyrA = cvCreateImage(pyr_sz , IPL_DEPTH_32F , 1) ;
	IplImage* pyrB = cvCreateImage(pyr_sz , IPL_DEPTH_32F , 1) ;

	CvPoint2D32f* cornersB = new CvPoint2D32f[MAX_CORNERS] ;

	for( int i = 1; i < size ; i++ )
	{
		imgB = grayFrames[i];
		cvCalcOpticalFlowPyrLK(
				imgA ,
				imgB ,
				pyrA ,
				pyrB ,
				cornersA ,
				cornersB ,
				corner_count , 
				cvSize(win_size , win_size) ,
				5 ,
				features_found ,
				features_error ,
				cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS , 20 , 0.3) ,
				0
				);

		//for( int i = 0; i < corner_count ; i++ )
		//{
			//if(features_found[i] == 0 || features_error[i] > 550){
				//printf("Error is %f \n" , features_error[i]) ;
				//continue ;
			//}
			////printf("Got it\n") ;

			//cvLine(imgA , cvPointFrom32f(cornersA[i]) , cvPointFrom32f(cornersB[i]) ,CV_RGB(255,0,0) , 2) ;
		//}

		CvMat* cornersAMat = convertPointsToMat(cornersA , corner_count) ;
		CvMat* cornersBMat = convertPointsToMat(cornersB , corner_count) ;
		CvMat* cornersAMat_ = cvCreateMat(corner_count , 3 , CV_32FC1) ;
		CvMat* cornersBMat_ = cvCreateMat(corner_count , 3 , CV_32FC1) ;
		cvConvertPointsHomogenious(cornersAMat , cornersAMat_) ;
		cvConvertPointsHomogenious(cornersBMat , cornersBMat_) ;

		CvMat* homography = cvCreateMat(3 , 3 , CV_32FC1);
		cvFindHomography(cornersAMat_ , cornersBMat_ , homography , CV_RANSAC , 1 );

		homographies[i-1] = homography ;
		
		imgA = imgB ;

		//for( int i = 0 ; i < 3 ; i++ )
		//{
			//float* ptr = (float*)(homographies[i]->data.ptr + i * homographies[i]->step) ;
			//for(int j = 0 ; j < 3 ; j++)
				//printf("%f " , *ptr++) ;
			//printf("\n");
		//}

	}

	//cvNamedWindow("win1");
	//cvShowImage("win1" , imgA);
	//cvNamedWindow("win2");
	//cvShowImage("win2" , imgB);
	//cvWaitKey();
	//cvDestroyWindow("win1");
	//cvDestroyWindow("win2");
	releaseImageArray(grayFrames , size) ;

	return homographies ;
}

//int main(int argc, char *argv[])
//{
	//IplImage *imgA = cvLoadImage("./images/scene_l.bmp" , CV_LOAD_IMAGE_GRAYSCALE);
	//IplImage *imgB = cvLoadImage("./images/scene_r.bmp" , CV_LOAD_IMAGE_GRAYSCALE);

	//IplImage* src[3] = {imgA , imgB , imgB} ;

	//CvMat** h = getHomographies(src , 3);

	//for( int i = 1 ; i < 3; i++ )
	//{
		//cvReleaseMat(&h[i]);
	//}
	

	//return 0 ;

//}
