/***************************************************************************
* Author: Eric Romero
* Class: COSC 4590
* Date: 
* Final Project
*
* Purpose: The purpose of this project is to determine the pin number from an
* thermal image of a very recently used access point.
* 
* ToDo:
* Display keys in ASCII, comment and document
*
* Sources:  http://docs.opencv.org/
****************************************************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector> 
#include <stdexcept>
#include <stdio.h>
#include <sstream>

using namespace cv;
using namespace std;

bool checkimg(Mat img);
void display(Mat img);
Mat inputImage();
Mat createROIs(Mat img, Mat rois[]);
void processImage(Mat img);
void processPIN(Mat img);
/****************************************************************************
* Function: main
* This function calls the inputImage function which returns a mat. That mat
* is then processed by the processImage function. The post processed image is
* then displayed. It then waits on user input to quit.
****************************************************************************/
int main(){
	system("clear");
	char quit;
	bool done = false;
	Mat img = inputImage();

	processPIN(img);
	processImage(img); //make high intensities red and everything else black
	display(img); //display image
	
	do{
		cout << "\nReady to quit(q)?  ";
		cin  >> quit;
		if(quit == 'q'){
			done = true;
		}
	}while(!done);
	
	return 0;
}

/****************************************************************************
* Function: processPIN
* This function creats 9 rois by 
****************************************************************************/
void processPIN(Mat img){
	Mat rois[10];

	double numRows = img.rows / 4.0; //set number of roi rows	 (l/4)
	double numCols = img.cols / 3.0; //set number of roi columns (w/3)
							//Rect(x, y, w, h)	
	
	rois[1] = img(Rect(0, 0, numCols, numRows)); //start from the upper left most point (x, y) of the image.
	rois[2] = img(Rect(numCols, 0, numCols, numRows)); //The image is traversed now by column/3 and row/4.
	rois[3] = img(Rect(numCols*2, 0, numCols, numRows)); //This creates 3 X 4  matrix of the entire image.
	rois[4] = img(Rect(0, numRows, numCols, numRows)); //The same amount of pixels inside of each element
	rois[5] = img(Rect(numCols, numRows, numCols, numRows)); //are used for the width and height of the rectangle.
	rois[6] = img(Rect(numCols*2, numRows, numCols, numRows)); 	//	[1][2][3]
	rois[7] = img(Rect(0, numRows*2, numCols, numRows));		//	[4][5][6] 	
	rois[8] = img(Rect(numCols, numRows*2, numCols, numRows));	//	[7][8][9]
	rois[9] = img(Rect(numCols*2, numRows*2, numCols, numRows));//	[*][0][#]	
	rois[0] = img(Rect(numCols, numRows*3, numCols, numRows)); //zero is is in the center column and in the 4th row.
	
	Scalar roiMeans[10];
	for(int i = 0; i < 10; i++){
		roiMeans[i] = mean(rois[i]); //calculate the mean values of rois
	}
	
	Scalar imgfull = mean(img); //create full image scalar
	double redLimit = Scalar(imgfull)[2]; //set threshold to full image mean intensity
	double redIntens = 0;
	
	//all of the variable within the threshold will be stored in this array, 
	//intensity values that did not enter the threshold will be collected as 0.
	double Array[10]; //raw intensity values collected from pictures
	double Intens[10]; //create Intensity array to store Intensity value
	
	for(int i = 0; i < 10; i++){
		redIntens = Scalar(roiMeans[i])[2]; //variable for the red intesity value in each roi
		
		if(redIntens > redLimit){ //threshold for roi red intensity mean value
			cout << "\n   " << i << " key pressed, mean intensity: " << redIntens << endl;
			Array[i] = redIntens; //store intensity value if it is above threshold
		}else{
			Array[i] = 0; //replace values below the threshold with 0
		}
		Intens[i] = Array[i]; //create copy of raw data to be sorted
	}
	
	//sort intensity value from greatest to least and only keep non zero values
	for(int i = 0; i < 10; i++){
		for (int x = 0; x < 10; x++){
			if(Intens[x] < Intens[x + 1]){
				double temp = Intens[x];
				Intens[x] = Intens[x + 1];
				Intens[x + 1] = temp;
			}
		}
	}
	//sort intensity value from greatest to least and only keep non zero values
	
	int j = 0;
	int code[4]; //create code array to store button press value
	for(int i = 0; i < 10; i++){
		//where the intensity value matches the raw collected intesity values index
		if(Intens[j] == Array[i] && j < 4){ 
			code[j] = i; //collect the index value
			j++; //next potential pin number
			//reset i to traverse the filtered intesity values from the beginning of the array
			i = -1; //to start over from zero
		}
	}

	cout << "\n The most likely PINs are: \n\n";
	do{	
		cout << "   ";
		for(int i = 3; i != -1; i--){
			cout << code[i] << " "; //output pin number
		}
		cout << endl;
	}while(prev_permutation(code, code + 4)); //output previous permuation of code

/*/////////////////////////////////////////////////////////////////////////////////////////////////	
	int y;
	for(int i = 0; i < 10; i++){
		if(code[y] == i){
			cout << "[" << i << "][" << i + 1 << "][3]\n";
			cout << "[4][5][6]\n";
			cout << "[7][8][9]\n";
			cout << "[*][0][#]\n";
			y++;
			i = 0;
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////*/

}

/****************************************************************************
* Function: processImage
* 
****************************************************************************/
void processImage(Mat img){
	int red = 0, blue = 0, green = 0;
	
	for(int y = 0; y < img.rows; y++){
		for(int x = 0; x < img.cols; x++){
			blue = img.at<Vec3b>(y,x)[0];  //insert blue channel pixels intensity values
			green = img.at<Vec3b>(y,x)[1]; //insert green channel pixels intensity values
			red = img.at<Vec3b>(y,x)[2];	//insert red channel pixels intensity values
			
			//Modify these values for imge correction
			//blue ~[5-20]) //green ~[5-20] //red ~[150-250]
			if(blue > 5 && green > 5 && red > 150){ //threshold for isolating presses
				img.at<Vec3b>(y,x)[0] = 0; 		//set all blue intensities to black
				img.at<Vec3b>(y,x)[1] = 0;  	//set all green intensities to black
				img.at<Vec3b>(y,x)[2] = 255;  	//max out all red intensities
			}else{
				img.at<Vec3b>(y,x)[0] = 0;  	//set all blue intensities to black
				img.at<Vec3b>(y,x)[1] = 0;  	//set all green intensities to black
				img.at<Vec3b>(y,x)[2] = 0;  	//set all red intensities to black
			}
			
		}  //traverse image pixel by pixel
	}
}

/****************************************************************************
* Function:inputImage
* 
****************************************************************************/
Mat inputImage(){
	cout << "\n ---Displaying Original Image--- \n";
	Mat orimg = imread("vend11.jpg", CV_LOAD_IMAGE_UNCHANGED); //imread in image
	checkimg(orimg); //check image
	Mat img = orimg.clone(); //clone image
	
	double rows = img.rows; // image size
	double cols = img.cols;
	
	cout<< "\n The image has " << cols << " columns and " << rows << " rows - " 
		<< img.size() << endl; //output file dimensions
		
	return img;
}

/****************************************************************************
* Function: checkimg
* This function tests the image file to ensure the image is loaded, if not
* it exits the program. 
****************************************************************************/
bool checkimg(Mat img){
	if (img.empty()) //check whether the image is loaded or not
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
		return 0;
	}
	return true;
}

/****************************************************************************
* Function: display
* This function takes the output image and displays the dimensions of the
* image. The function then displays the image in a window and waits for a
* new key press to destroy the window. 
****************************************************************************/
void display(Mat img){
	namedWindow("MyWindow",CV_WINDOW_NORMAL);
	imshow("MyWindow", img); 
	//display the image which is stored in the 'img' in the "MyWindow" window

	waitKey(5); //wait 5 ms
	
	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}