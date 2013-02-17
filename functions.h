#ifndef FUNCTIONS_H 
#define FUNCTIONS_H 

#include  "cv.h"
#include  "cxcore.h"
#include "highgui.h"
#include  <iostream>
#include  <cstdio>
#include <algorithm>
#include  <cstring>
#include  <vector>

CvMat** getHomographies(IplImage** frames , int size);
CvMat* convertPointsToMat(CvPoint2D32f* corners , int corner_count);
IplImage** getFramesFromVideo(const char* fileName , int& size);

CvMat* calLuckiness(CvMat* homoPre , CvMat* homoPost , int rows , int cols) ;
CvMat** calLuckMats(CvMat** homographies , int rows , int cols , int size) ;

CvMat* calWarpFunH(const float t , CvMat* homoMat) ;

void findPairs(int start , int end , double* avgLuckiness ,std:: vector<std::pair<int , int> > &kPairs);
void findKPairs(double* avgLuckiness , int size , std::vector<std::pair<int,int> > &kPairs);
//tools function 
void releaseFrames(IplImage*** frames , int& size) ;
void releaseMats(CvMat*** , int);
void displayMat(CvMat* mat) ;

#endif //FUNCTIONS_H
