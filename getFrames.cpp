#include "functions.h"
#include "errmsg.h"

extern long myErrno ;

IplImage** getFramesFromVideo(const char* fileName , int& size)
{
	int numFrames = 0 ;
	IplImage** frames = NULL ;
	IplImage* tmp = NULL ;
	CvCapture *capture = cvCaptureFromAVI(fileName) ;
	size = 0 ;

	if( !capture )
	{
		myErrno = ERR_OPEN_FILE ;
		perrmsg("Can't open the file") ;

		return NULL ;
	}

	cvQueryFrame(capture) ;
	numFrames = (int)cvGetCaptureProperty(capture , CV_CAP_PROP_FRAME_COUNT) ;	
	
	frames = new IplImage*[numFrames+1] ;
	
	while(cvGrabFrame(capture))
	{
		tmp = cvRetrieveFrame(capture) ;
		frames[size++] = cvCloneImage(tmp);
	}
	cvReleaseCapture(&capture);
	
	return frames ;
}

//int main(int argc, char *argv[])
//{
	//int size = 0 ;
	//IplImage** frames = getFramesFromVideo("1.avi" , size);
	//cvNamedWindow("win");
	//cvShowImage("win",frames[9]);
	//P(size);
	//cvWaitKey(0);
	//releaseFrames(&frames , size);
//}
