/*
 * =====================================================================================
 *
 *       Filename:  deblur.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013年02月12日 17时41分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  金鹏 ()
 *   Organization:
 *
 * =====================================================================================
 */

#include "functions.h"
#include "errmsg.h"


int main(int argc, char *argv[])
{
	using namespace std ;

	int frameSize = 0 ;
	IplImage** frames = getFramesFromVideo("1.avi" , frameSize);
	//IplImage* first = cvLoadImage("./images/1.jpeg");
	//IplImage* second = cvLoadImage("./images/1.jpeg");
	//IplImage* second2 = cvLoadImage("./images/1.jpeg");
	//frames[0] = first ;
	//frames[1] = second ;
	//frames[2] = second2 ;
	//frameSize = 3 ; 
	CvMat** corners = new CvMat*[frameSize] ;
	CvMat** homographies = getHomographies(frames , frameSize , corners);
	CvMat** luckMats = calLuckMats(homographies , frames[0]->height , frames[0]->width , frameSize);
	double *avgLuckiness = new double[frameSize] ;
	for( int i = 0; i < frameSize ; i++ )
	{
		avgLuckiness[i] = (cvAvg(luckMats[i])).val[0] ;
		P(avgLuckiness[i]);
	}
	int* pairs = new int[frameSize] ;
	int pairSize = 0 ; 
	int baseImageNum = findPairs( 0 , frameSize , avgLuckiness , pairs , pairSize) ;
	int tao = deterTaoOfBlurFunc(corners , baseImageNum , frames , pairs , pairSize , homographies ); 
	P(baseImageNum) ;
	P(tao);
	releaseMats(&luckMats , frameSize);	


}



