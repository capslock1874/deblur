#ifndef FUNCTIONS_H 
#define FUNCTIONS_H 

#include  "cv.h"
#include  "cxcore.h"
#include "highgui.h"
#include  <iostream>
#include  <cstdio>
#include <algorithm>
#include  <limits.h>
#include  <cstring>
#include  <vector>
using namespace std ;

CvMat** getHomographies(IplImage** frames , int size , CvMat** corners);
CvMat* convertPointsToMat(CvPoint2D32f* corners , int corner_count);
IplImage** getFramesFromVideo(const char* fileName , int& size);
int deterTaoOfBlurFunc(CvMat** corners , int baseImage , IplImage** frames ,
		int* pairs , int pairSize ,  CvMat** homographies);
CvMat* calLuckiness(CvMat* homoPre , CvMat* homoPost , int rows , int cols) ;
CvMat** calLuckMats(CvMat** homographies , int rows , int cols , int size) ;
IplImage* blurFunc(CvMat* preHomography , CvMat* homography , IplImage* latent , int tao);
CvMat* calWarpFunH(const float t , CvMat* homoMat) ;

int findPairs(int start , int end , double* avgLuckiness , int* pairs , int& pairSize);
//tools function 
void releaseFrames(IplImage*** frames , int& size) ;
void releaseMats(CvMat*** , int);
void displayMat(CvMat* mat) ;

#endif //FUNCTIONS_H
