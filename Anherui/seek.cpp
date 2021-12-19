#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
using namespace std;
using namespace cv;
int iLowH = 28, iHighH = 71, iLowS = 57, iHighS = 219, iLowV = 0, iHighV = 255,p=0;
 void color(Mat frame,int *m);
int main(int argc, char** argv)
{
    VideoCapture cap(0);
    if(!cap.isOpened())
    {
        cout<< "failed" <<endl;
        return 0;
    }
    while(1)
    {
        Mat frame;
        cap >> frame;
        if(frame.empty())
        {
            cout<< "frame off" <<endl;
            break;
        }
        Mat imgHSV, imgThresholded, imgCanny, element;
        color(frame, &p);
        waitKey(30);
    }
    cap.release();
}
void color(Mat frame,int *m)
{
    Mat imgHSV, imgThresholded, imgCanny, element;
    int cnt=0;
    resize(frame, frame, Size(320,240), 0, 0, INTER_AREA);
	vector<vector<Point>> contours;
	vector<Vec4i>hierchy;
    // //createTrackbar
    // namedWindow("Color",WINDOW_NORMAL);
    // namedWindow("video",WINDOW_NORMAL);
    // createTrackbar("LowH", "Color", &iLowH, 180); //Hue(0 - 179);
    // createTrackbar("HighH", "Color", &iHighH, 180); 
    // createTrackbar("LowS", "Color", &iLowS, 255); //Sarturation(0 - 255);
    // createTrackbar("HighS", "Color", &iHighS, 255); 
    // createTrackbar("LowV", "Color", &iLowV, 255); //Value(0 - 255);
    // createTrackbar("HighV", "Color", &iHighV, 255);
    //cvtColor
    cvtColor(frame, imgHSV, COLOR_BGR2HSV);
    inRange(imgHSV, Scalar(iLowH,iLowS,iLowV), Scalar(iHighH,iHighS,iHighV), imgThresholded);
	element = getStructuringElement(MORPH_RECT, Size(3,3));
    morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
    morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
    GaussianBlur(imgThresholded, imgThresholded, Size(5, 5), 3, 3);
    findContours(imgThresholded, contours, hierchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());//这里用RETR_EXTERNAL显示最外层轮廓，而TREE显示所有轮廓,背景像素要是黑色
	 for(int i=0;i<contours.size();i++)  
    {  
        //contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数  
        for(int j=0;j<contours[i].size();j++)   
        {  
            //绘制出contours向量内所有的像素点
            if(contours[i].size()>100)
            {
                cnt++;
               cout<<"5"<<endl;
                drawContours(frame,contours,i,Scalar(255),1,8,hierchy);  
                if(cnt>0)
                {
                    *m=1;
                }
                else
                {
                    *m=0;
                }   
            }
            else
            {
               cout<<"4"<<endl; 
            }   

        }
        //输出hierarchy向量内容  
        // char ch[256];  
        // sprintf(ch,"%d",i);  
        // string str=ch;  
        // cout<<"向量hierarchy的第" <<str<<" 个元素内容为："<<endl<<hierarchy[i]<<endl<<endl;  
  
        //绘制轮廓  
    
    }  //findContours(imgThresholded, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	imshow("Color", imgThresholded);
    imshow("video", frame);
    
}