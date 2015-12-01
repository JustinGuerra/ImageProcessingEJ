/***************************************************************************
* Authors: Eric Romero & Justin Guerra
* Class: COSC 4590 Image Processing
* Date: 11/30/2015
* Image Processing Final Project
*
* Purpose: The purpose of this project is to determine the pin number from an
* thermal image of a recently used access point.
*
* Sources:  http://docs.opencv.org/
*			https://cseweb.ucsd.edu/~kmowery/papers/thermal.pdf
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

	display(img); //display image before processing
	processImage(img); //keeps red intensities and turns everything else black
	processPIN(img); //Identifies the PIN
	display(img); //display image after processing
	
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
* This function creats 9 ROIs by dividing the image into 12 sections.
* This function then collects the mean intesity values of the ROIs and full image
* After it sets the mean value of the full image as the threshold for a press
* Then, it creates two identical arrays in order to compare them (data and intens).
* It sorts the intens array and leaves the data array alone
* The it compares the values within the two arrays and if the intesity values
* match between data and intens arrays it keeps the index value from the data 
* array and identifies that index value as a possible number in the code.
* Lastly, it outputs the permuations of the code.
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
	rois[0] = img(Rect(numCols, numRows*3, numCols, numRows)); //zero is in the center (2nd) column and in the 4th row.
	
	Scalar roiMeans[10]; //Scalar for multi channel images
	for(int i = 0; i < 10; i++){
		roiMeans[i] = mean(rois[i]); //calculate the mean values of rois and collect them
	}
	
	Scalar imgfull = mean(img); //create full image scalar
	double redLimit = Scalar(imgfull)[2]; //set threshold to full image mean intensity
	double redIntens = 0;
	//all of the variable within the threshold will be stored in this data array, 
	//intensity values that did not enter the threshold will be collected as 0.
	double data[10]; //raw intensity values collected from pictures
	double intens[10]; //create duplicate array to store Intensity value
	
	for(int i = 0; i < 10; i++){
		redIntens = Scalar(roiMeans[i])[2]; //variable for the red intesity value in each roi
		
		if(redIntens > redLimit){ //threshold for roi red intensity mean value
			cout << "\n   " << i << " key pressed, mean intensity: " << redIntens << endl;
			data[i] = redIntens; //store intensity value if it is above threshold
		}else{
			data[i] = 0; //replace values below the threshold with 0
		}
		intens[i] = data[i]; //create copy of raw data to be sorted
	}

	sort(intens, intens + 10);
	//sort intensity value from least to greatest
	
	int j = 9, c = 0; //start at the end of the intens array
	int code[4]; //create code array to store button press value
	for(int i = 0; i < 10; i++){
		//where the intensity value matches the raw collected intesity values index
		if(intens[j] == data[i]){ 
			code[c] = i; //collect the index value
			i = -1; 
			//reset i to traverse the filtered intesity values from the beginning of the array
			j--; //next lowest intesity value
			c++; //next code value
		}
	}

	cout << "\n The most likely PINs are: \n\n";
	do{	
		cout << "   ";
		for(int i = 3; i != -1; i--){
			cout << code[i] << " "; //output pin number
		}
		cout << endl;
	}while(prev_permutation(code, code + 4)); //output permuation pin number

}

/****************************************************************************
* Function: processImage
* This function corrects the image by changing every color that is not red
* to black.
****************************************************************************/
void processImage(Mat img){
	int red = 0, blue = 0, green = 0;
	//Modify these values for image correction
	//red ~[100-250] //blue ~[5-20]) //green ~[5-20]
	int usrRed = 100, usrBlue = 5, usrGreen = 5;
	//red is the most relevant
	for(int y = 0; y < img.rows; y++){
		for(int x = 0; x < img.cols; x++){
			blue = img.at<Vec3b>(y,x)[0];  //insert blue channel pixels intensity values
			green = img.at<Vec3b>(y,x)[1]; //insert green channel pixels intensity values
			red = img.at<Vec3b>(y,x)[2];   //insert red channel pixels intensity values
			
			if(blue > usrBlue && green > usrGreen && red > usrRed){ //threshold for isolating presses
				img.at<Vec3b>(y,x)[0] = 0; 	//set all blue intensities to black
				img.at<Vec3b>(y,x)[1] = 0;  //set all green intensities to black
				img.at<Vec3b>(y,x)[2] = 255;//max out all red intensities
			}else{
				img.at<Vec3b>(y,x)[0] = 0;  //set all blue intensities to black
				img.at<Vec3b>(y,x)[1] = 0;  //set all green intensities to black
				img.at<Vec3b>(y,x)[2] = 0;  //set all red intensities to black
			}
		}  //traverse image pixel by pixel
	}
	
}

/****************************************************************************
* Function:inputImage
* This function inputs the image and outputs the images size in cols and rows
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

	waitKey(2000); //wait
	
	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}