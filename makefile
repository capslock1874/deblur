opencvLib = `pkg-config opencv --libs  --cflags`
objs = main.o getHomographies.o convertPointsToMat.o getFrames.o errmsg.o calLuckiness.o tools.o \
	   deblurToolsFuns.o

deblur: $(objs) 
	g++ -o deblur $(objs) $(opencvLib) 

main.o: functions.h errmsg.h
	g++ -c -o main.o deblur.cpp $(opencvLib)

getHomographies.o: getHomographies.cpp functions.h
	g++ -c getHomographies.cpp $(opencvLib) 

convertPointsToMat.o: functions.h convertPointsToMat.cpp
	g++ -c convertPointsToMat.cpp $(opencvLib) 

getFrames.o: functions.h errmsg.h getFrames.cpp errmsg.cpp
	g++ -c getFrames.cpp $(opencvLib)

errmsg.o: functions.h errmsg.h
	g++ -c errmsg.cpp $(opencvLib)

calLuckiness.o: functions.h errmsg.h
	g++ -c calLuckiness.cpp $(opencvLib)

tools.o: functions.h errmsg.h
	g++ -c tools.cpp $(opencvLib)

deblurToolsFuns.o: functions.h errmsg.h
	g++ -c deblurToolsFuns.cpp $(opencvLib)

clean :
	rm *.o 
