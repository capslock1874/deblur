/*
 * =====================================================================================
 *
 *       Filename:  deblurToolsFuns.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年02月15日 22时29分29秒
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

static const int M = 5 ;
static const int T = 20 ;

int findPairs(int start , int end , double* avgLuckiness , int* pairs , int& pairSize)
{
	//double threshold = 0.6 * *(std::max_element(avgLuckiness+start , avgLuckiness + end )) ;
	double* maxValue = max_element(avgLuckiness + start , avgLuckiness + end) ;
	double  threshold = 0.6 * *maxValue ;

	for( int i = start , pairSize = 0 ;
			i < end ;
			i++ , pairSize++ )
	{
		if(*maxValue - avgLuckiness[i] > threshold)
		{
			pairs[pairSize] = i ;
		}
	}
	return maxValue - (avgLuckiness + start) ;
}


int deterTaoOfBlurFunc(CvMat** corners , int baseImage , IplImage** frames , int* pairs , int pairSize ,  CvMat** homographies)
{
	IplImage* warpImage = cvCloneImage(frames[baseImage]);
	IplImage* diffOfImage = cvCloneImage(frames[baseImage]) ;
	IplImage* doubleDiffOfImage = cvCloneImage(frames[baseImage]) ;
	int resultTao = 0 ;
	double diffSum = 1000000 ; 
	CvScalar diff ;
	double diffTmp = 0 ;

	for( int tao = 1 ; tao <= T / 2  ; tao++ )
	{	
		for( int i = 0 ; i < pairSize ; i++ )
		{
			CvMat* homography = cvCreateMat(3 , 3 , CV_32FC1);
			cvFindHomography(corners[pairs[i]], corners[baseImage] , homography , CV_RANSAC , 1 );
			cvWarpPerspective(frames[pairs[i]] , warpImage , homography) ; 
			IplImage* bluredImage = blurFunc(homographies[baseImage - 1] , homographies[baseImage + 1] , warpImage , tao) ;
			cvSub(bluredImage , frames[baseImage] , diffOfImage) ;
			cvMul(diffOfImage , diffOfImage , doubleDiffOfImage) ;
			diff = cvAvg(doubleDiffOfImage);
			diffTmp += diff.val[0] + diff.val[1] + diff.val[2] ;
		}
		if( diffTmp < diffSum )
		{
			diffSum = diffTmp ;
			resultTao = tao ;
		}
		
	}
	cvReleaseImage(&diffOfImage) ;
	cvReleaseImage(&doubleDiffOfImage) ;

	return resultTao ; 
}


//struct calPairHomography
//{
	//CvMat** homographies ;
	//iToJHomos& pairHomographies ;

	//calPairHomography(CvMat** h ,iToJHomos& p)
		//: homographies(h) , pairHomographies(p){ } ;
	
	//void operator( )(std::pair<int,int>& elem)
	//{
		//int start = elem.first ;
		//int end = elem.second ;
		
		//CvMat* tmp = cvCreateMat(3 , 3 , CV_32FC1);
		//CvMat* result = cvCreateMat(3 , 3 , CV_32FC1);
		//cvCopy(homographies[start] , tmp) ;
		//cvCopy(homographies[start] , result) ;

		//for( int i = start; i <= end ; i++ )
		//{
			//cvMatMul(tmp , homographies[i] , result ) ;
			//cvCopy(result , tmp) ;
		//}
	
		//pairHomographies.push_back(result) ;
		
		//cvReleaseMat(&tmp);

	//}
//} ;

//void calKpairHomograpies(CvMat** homographies , luckinessPair &kPairs , iToJHomos &pairHomographies )
//{
	//int length = kPairs.size() ;

	//for_each(kPairs.begin() , kPairs.end() ,
			//calPairHomography( homographies , pairHomographies )); 
//}


//int main(int argc, char *argv[])
//{
	

//}

