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

typedef std::vector<std::pair<int , int> > luckinessPair ;
typedef std::vector<CvMat*> iToJHomos ;
			
void findPairs(int start , int end , double* avgLuckiness ,luckinessPair &kPairs)
{
	double threshold = 0.6 * *(std::max_element(avgLuckiness+start , avgLuckiness + end )) ;

	//P(threshold * 10000) ;
	for( int i = start ; i < end ; i++ )
	{
		for( int j = i + 1; j < end ; j++ )
		{
			//P(fabs(avgLuckiness[i] - avgLuckiness[j]) * 10000) ;
			if( fabs(avgLuckiness[i] - avgLuckiness[j]) > threshold )
			{
				//P(fabs(avgLuckiness[i] - avgLuckiness[j]) - threshold) ;
				kPairs.push_back(std::make_pair<int ,int>(i , j)) ;
			}
		}
		
	}
	
}

void findKPairs(double* avgLuckiness , int size ,luckinessPair &kPairs)
{
	int start , end ;

	for( int i = 0 ; i < size ; i++ )
	{
		start = i > M ? i - M : 0 ;
		end = i + M >= size ? size : i + M + 1;

		findPairs(start  , end , avgLuckiness , kPairs) ;
	}
}

struct calPairHomography
{
	CvMat** homographies ;
	iToJHomos& pairHomographies ;

	calPairHomography(CvMat** h ,iToJHomos& p)
		: homographies(h) , pairHomographies(p){ } ;
	
	void operator( )(std::pair<int,int>& elem)
	{
		int start = elem.first ;
		int end = elem.second ;
		
		CvMat* tmp = cvCreateMat(3 , 3 , CV_32FC1);
		CvMat* result = cvCreateMat(3 , 3 , CV_32FC1);
		cvCopy(homographies[start] , tmp) ;
		cvCopy(homographies[start] , result) ;

		for( int i = start; i <= end ; i++ )
		{
			cvMatMul(tmp , homographies[i] , result ) ;
			cvCopy(result , tmp) ;
		}
	
		pairHomographies.push_back(result) ;
		
		cvReleaseMat(&tmp);

	}
} ;

void calKpairHomograpies(CvMat** homographies , luckinessPair &kPairs , iToJHomos &pairHomographies )
{
	int length = kPairs.size() ;

	for_each(kPairs.begin() , kPairs.end() ,
			calPairHomography( homographies , pairHomographies )); 
}


//int main(int argc, char *argv[])
//{
	

//}

