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
	CvMat** homographies = getHomographies(frames , frameSize);
	CvMat** luckMats = calLuckMats(homographies , frames[0]->height , frames[0]->width , frameSize);
	double *avgLuckiness = new double[frameSize] ;

	for( int i = 0; i < frameSize ; i++ )
	{
		avgLuckiness[i] = (cvAvg(luckMats[i])).val[0] ;
		P(avgLuckiness[i]);
	}
    
	vector<pair<int,int> > kPairs ;
	findKPairs(avgLuckiness , frameSize , kPairs) ;
	for(vector<pair<int , int> >::iterator it = kPairs.begin() ; it != kPairs.end() ; it++ )
	{
		cout << (*it).first << "  " << (*it).second << endl ;
	}
	releaseMats(&luckMats , frameSize);	


}



