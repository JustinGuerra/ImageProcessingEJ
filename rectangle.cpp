/***************************************************************************
* Author: Eric Romero
* Class: COSC 4590
* Date: 
* Final Project
*
* Purpose: 
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
void orig(Mat img);
/****************************************************************************
* Function: main
* 
****************************************************************************/
int main(){
	system("clear");
	char quit;
	bool done = false;
	
	cout << "\n---Displaying original image--- \n";
	Mat orimg = imread("keypad5.jpg", CV_LOAD_IMAGE_UNCHANGED); //imread in image
	checkimg(orimg); //check image
	Mat img = orimg.clone(); //clone image
	
	double rows = img.rows; // image size
	double cols = img.cols;
	
	cout<< "\nThe image has " << cols << " columns and " << rows << " rows - " 
		<< img.size() << endl;
					//Rect(x, y, w, h)
	// Mat roi0 = img(Rect(298, 315, 100, 85));
	// Mat roi1 = img(Rect(200, 45, 100, 85)); //For painted on keypad "keypad2.jpg"
	// Mat roi2 = img(Rect(298, 45, 100, 85)); //For spray painted on only keypad "keypad.jpg"
	// Mat roi3 = img(Rect(398, 45, 100, 85));
	// Mat roi4 = img(Rect(200, 135, 100, 85)); 
	// Mat roi5 = img(Rect(298, 135, 100, 85));
	// Mat roi6 = img(Rect(398, 135, 100, 85));
	// Mat roi7 = img(Rect(200, 225, 100, 85));
	// Mat roi8 = img(Rect(298, 225, 100, 85));
	// Mat roi9 = img(Rect(398, 225, 100, 85));
	
	// Size smaller(59, 40);
	// Mat smallerImages;
	// Rect rect;
	// for(int y = 0; y < rows; y += smaller.height){
		// for (int j = 0; j < cols; j += smaller.width){
			// rect = Rect(j, y, smaller.width, smaller.height);
			// smallerImages.push_back(Mat(img, rect));
		// }
	// }
	
	// Mat roi1 = smallerImages.pop_back(1);
	
	double s1 = img.cols / 3.0;
	double s2 = img.rows / 4.0;
	
	// cout << "\nSide 1: " << s1 << endl;
	
	Mat rois[10];
	
	Mat roi0 = img(Rect(s1, s2*3, s1, s2));
	Mat roi1 = img(Rect(0, 0, s1, s2));
	Mat roi2 = img(Rect(s1, 0, s1, s2));
	Mat roi3 = img(Rect(s1*2, 0, s1, s2));
	Mat roi4 = img(Rect(0, s2, s1, s2));
	Mat roi5 = img(Rect(s1, s2, s1, s2));
	Mat roi6 = img(Rect(s1*2, s2, s1, s2));
	Mat roi7 = img(Rect(0, s2*2, s1, s2));
	Mat roi8 = img(Rect(s1, s2*2, s1, s2));
	Mat roi9 = img(Rect(s1*2, s2*2, s1, s2));
	
	rois[0] = roi0;
	rois[1] = roi1;
	rois[2] = roi2;
	rois[3] = roi3;
	rois[4] = roi4;
	rois[5] = roi5;
	rois[6] = roi6;
	rois[7] = roi7;
	rois[8] = roi8;
	rois[9] = roi9;
	
	int blue1 = 0;
	int green1 = 0;
	
	for(int i = 0; i < 11; i++){
		
		for(int y = 0; y < rois[i].rows; y++){
			for(int x = 0; x < rois[i].cols; x++){
				blue1 = rois[i].at<Vec3b>(y,x)[0]; //insert blue channel pixels intensity values
				green1 = rois[i].at<Vec3b>(y,x)[1]; //insert green channel pixels intensity values
				
				if(blue1 > 0 && green1 > 0){ //threshold
					rois[i].at<Vec3b>(y,x)[0] = 0; //if blue is less than 20, increase to 255
					rois[i].at<Vec3b>(y,x)[1] = 0;
				}
				
			}  //traverse image change all black to blue
		}
		i++;
	}
	
	// Mat roi0 = img(Rect(248, 370, 59, 40));
	// Mat roi1 = img(Rect(167, 125, 59, 40)); //For researched keypad "keypad3.jpg"
	// Mat roi2 = img(Rect(248, 125, 59, 40)); 
	// Mat roi3 = img(Rect(332, 125, 59, 40));
	// Mat roi4 = img(Rect(167, 208, 59, 40)); 
	// Mat roi5 = img(Rect(248, 208, 59, 40));
	// Mat roi6 = img(Rect(332, 208, 59, 40));
	// Mat roi7 = img(Rect(167, 291, 59, 40));
	// Mat roi8 = img(Rect(248, 291, 59, 40));
	// Mat roi9 = img(Rect(332, 291, 59, 40));
	
	// Mat roi0 = img(Rect(235, 320, 120, 50));
	// Mat roi1 = img(Rect(100, 150, 120, 50)); //For phone keypad "keypad4.jpg"
	// Mat roi2 = img(Rect(240, 145, 120, 50));
	// Mat roi3 = img(Rect(375, 140, 120, 50));
	// Mat roi4 = img(Rect(100, 205, 120, 50));
	// Mat roi5 = img(Rect(235, 200, 120, 50));
	// Mat roi6 = img(Rect(385, 195, 120, 50));
	// Mat roi7 = img(Rect(95, 260, 120, 50));
	// Mat roi8 = img(Rect(235, 255, 120, 50));
	// Mat roi9 = img(Rect(385, 250, 120, 50));
	
	display(roi8); //display image
	//modify this if you nee	d to see a specific number or the whole image
	
	Scalar img0Mean = mean(roi0);
    Scalar img1Mean = mean(roi1);
    Scalar img2Mean = mean(roi2);
    Scalar img3Mean = mean(roi3);
    Scalar img4Mean = mean(roi4);
    Scalar img5Mean = mean(roi5);
    Scalar img6Mean = mean(roi6);
    Scalar img7Mean = mean(roi7);
    Scalar img8Mean = mean(roi8);
    Scalar img9Mean = mean(roi9);
	Scalar imgfull = mean(img);
	
	cout << "\n Full Image: " << imgfull << endl;
	
	cout << "\n roi: " << img0Mean << endl;
    cout << " roi1: " << img1Mean << endl;
    cout << " roi2: " << img2Mean << endl;
    cout << " roi3: " << img3Mean << endl;
    cout << " roi4: " << img4Mean << endl;
    cout << " roi5: " << img5Mean << endl;
    cout << " roi6: " << img6Mean << endl;
    cout << " roi7: " << img7Mean << endl;
    cout << " roi8: " << img8Mean << endl;
    cout << " roi9: " << img9Mean << endl;
    
	double redZero = 0;
	double redOne = 0;
	double redTwo = 0;
	double redThree = 0;
	double redFour = 0;
	double redFive = 0;
	double redSix = 0;
	double redSeven = 0;
	double redEight = 0;
	double redNine = 0;
	double redLimit = 130.000;
	double blueLimit = 100.000;
	
	double red = Scalar(img0Mean)[2];
	double green = Scalar(img0Mean)[1];
	double blue = Scalar(img0Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nZero has been pressed\n";
		redZero = red;
	}
	
	red = Scalar(img1Mean)[2]; //pull red Intensity value from Scalar
	green = Scalar(img1Mean)[1]; //pull green Intensity value from Scalar
	blue = Scalar(img1Mean)[0]; //pull blue Intensity value from Scalar
	
	if(red > redLimit || blue < blueLimit){ //Threshold for intensity mean
		cout << "\nOne has been pressed\n";
		redOne = red; //Store the Red intensity value
	}
	//This process is repeated for each rectangle image
	red = Scalar(img2Mean)[2];
	green = Scalar(img2Mean)[1];
	blue = Scalar(img2Mean)[0];
	
	if(red > redLimit || blue < blueLimit){ //Threshold for intensity mean
		cout << "\nTwo has been pressed\n";
		redTwo = red; //Store the Red 
	}
	
	red = Scalar(img3Mean)[2];
	green = Scalar(img3Mean)[1];
	blue = Scalar(img3Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nThree has been pressed\n";
		redThree = red;
	}

	red = Scalar(img4Mean)[2];
	green = Scalar(img4Mean)[1];
	blue = Scalar(img4Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nFour has been pressed\n";
		redFour = red;
	}
	
	red = Scalar(img5Mean)[2];
	green = Scalar(img5Mean)[1];
	blue = Scalar(img5Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nFive has been pressed\n";
		redFive = red;
	}
	
	red = Scalar(img6Mean)[2];
	green = Scalar(img6Mean)[1];
	blue = Scalar(img6Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nSix has been pressed\n";
		redSix = red;
	}
	
	red = Scalar(img7Mean)[2];
	green = Scalar(img7Mean)[1];
	blue = Scalar(img7Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nSeven has been pressed\n";
		redSeven = red;
	}
	
	red = Scalar(img8Mean)[2];
	green = Scalar(img8Mean)[1];
	blue = Scalar(img8Mean)[0];
	
	if(red > redLimit){
		cout << "\nEight has been pressed\n";
		redEight = red;
	}
	
	red = Scalar(img9Mean)[2];
	green = Scalar(img9Mean)[1];
	blue = Scalar(img9Mean)[0];
	
	if(red > redLimit || blue < blueLimit){
		cout << "\nNine has been pressed\n";
		redNine = red;
	}
	

	//all of the variable within the threshold will be stored in this array, 
	//intensity values that did not enter the threshold will be collected as 0.
	double Array[10] = {redZero, redOne, redTwo, redThree, redFour, redFive, redSix, redSeven,
						redEight, redNine}; //raw values collected from pictures
	int code[4] = {0,0,0,0}; //create code array to store button press value
	double Intens[4] = {0,0,0,0}; //create Intensity array to store Intensity value
	int x = 0; //code index and intensity index number we want these to be equal
	int j = 0; //code index and intensity index number we want these to be equal
	double temp;
	int count = 0; //prevent more than 4 numbers in code
	
	cout << endl;
	for(int i = 0; i != 10; i++){ //for loop to calculate code
		if(Array[i] > 0){ //If The intensity of red is greater than 0
			code[x] = i; //store index number of value i into code array
			Intens[x] = Array[i]; //store the intensity that was not zero into new array
			cout << "\nIntens: " << Intens[x]; //output possible keys intensity values
			cout << "\nCode: " << code[x]; //output possible code number
			x++;
		}
	}
	
	sort(Intens, Intens + 4); //sort intensity value from least to greatest
	
	for(int i = 0; i != 10; i++){
		//where the intensity value matches the raw collected intesity values index
		if(Intens[j] == Array[i]){ 
			code[j] = i; //collect the index value
			// cout << "\nX: " << j;
			j++;
			//reset i to traverse the raw collected intesity values from the beginning of the array
			i = 0; 
		}
	}

	cout << "\n\nThe most likely PINs are: \n";
	do{	
		for(int i = 0; i != 4; i++){
			cout << code[i] << " "; //output pin number
		}
		cout << endl;
	}while(next_permutation(code, code + 4)); //output next permuation of code
	
	do{
		cout << "\n\nReady to quit(q)?  ";
		cin  >> quit;
		if(quit == 'q'){
			done = true;
		}
	}while(!done);
	
	return 0;
}

/****************************************************************************
* Function: orig
* This function takes the original image and displays it.
****************************************************************************/
void orig(Mat img){
	display(img);
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
		return -1;
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