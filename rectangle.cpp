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
	Mat orimg = imread("keypad4.jpg", CV_LOAD_IMAGE_UNCHANGED); //imread in image
	checkimg(orimg); //check image
	Mat img = orimg.clone(); //clone image
	
	double rows = img.rows; // image size
	double cols = img.cols;
	
	cout<< "\nThe image has " << cols << " columns and " << rows << " rows - " 
		<< img.size() << endl;
					//Rect(x, y, w, h)
	// Mat roi1 = img(Rect(200, 45, 100, 85)); //For painted on keypad "keypad2.jpg"
	// Mat roi2 = img(Rect(298, 45, 100, 85)); //For spray painted on only keypad "keypad.jpg"
	// Mat roi3 = img(Rect(398, 45, 100, 85));
	// Mat roi4 = img(Rect(200, 135, 100, 85));
	// Mat roi5 = img(Rect(298, 135, 100, 85));
	// Mat roi6 = img(Rect(398, 135, 100, 85));
	// Mat roi7 = img(Rect(200, 225, 100, 85));
	// Mat roi8 = img(Rect(298, 225, 100, 85));
	// Mat roi9 = img(Rect(398, 225, 100, 85));
	// Mat roi0 = img(Rect(298, 315, 100, 85));
	
	Mat roi1 = img(Rect(110, 150, 110, 50)); //For phone keypad "keypad4.jpg"
	Mat roi2 = img(Rect(235, 145, 110, 50));
	Mat roi3 = img(Rect(370, 140, 110, 50));
	Mat roi4 = img(Rect(110, 205, 110, 50));
	Mat roi5 = img(Rect(235, 200, 110, 50));
	Mat roi6 = img(Rect(385, 195, 110, 50));
	Mat roi7 = img(Rect(110, 265, 110, 50));
	Mat roi8 = img(Rect(235, 260, 110, 50));
	Mat roi9 = img(Rect(380, 255, 110, 50));
	Mat roi0 = img(Rect(235, 325, 110, 50));
	
	display(img); //display image
	//modify this is you need to see a specific number or the whole image
	
    Scalar img1Mean = mean(roi1);
    Scalar img2Mean = mean(roi2);
    Scalar img3Mean = mean(roi3);
    Scalar img4Mean = mean(roi4);
    Scalar img5Mean = mean(roi5);
    Scalar img6Mean = mean(roi6);
    Scalar img7Mean = mean(roi7);
    Scalar img8Mean = mean(roi8);
    Scalar img9Mean = mean(roi9);
    Scalar img0Mean = mean(roi0);
	
    cout << "\n image1: " << img1Mean << endl;
    cout << " image2: " << img2Mean << endl;
    cout << " image3: " << img3Mean << endl;
    cout << " image4: " << img4Mean << endl;
    cout << " image5: " << img5Mean << endl;
    cout << " image6: " << img6Mean << endl;
    cout << " image7: " << img7Mean << endl;
    cout << " image8: " << img8Mean << endl;
    cout << " image9: " << img9Mean << endl;
    cout << " image0: " << img0Mean << endl;
	
	double redOne = 0;
	double redTwo = 0;
	double redThree = 0;
	double redFour = 0;
	double redFive = 0;
	double redSix = 0;
	double redSeven = 0;
	double redEight = 0;
	double redNine = 0;
	double redZero = 0;
	
	double red = Scalar(img1Mean)[2]; //pull red Intensity value from Scalar
	double green = Scalar(img1Mean)[1]; //pull green Intensity value from Scalar
	double blue = Scalar(img1Mean)[0]; //pull blue Intensity value from Scalar
	
	if(red > 130.000 || blue < 100.000){ //Threshold for intensity mean
		cout << "\nOne has been pressed\n";
		redOne = red; //Store the Red intensity value
	}
	//This process is repeated for each rectangle image
	red = Scalar(img2Mean)[2];
	green = Scalar(img2Mean)[1];
	blue = Scalar(img2Mean)[0];
	
	if(red > 130.000 || blue < 100.000){ //Threshold for intensity mean
		cout << "\nTwo has been pressed\n";
		redTwo = red; //Store the Red 
	}
	
	red = Scalar(img3Mean)[2];
	green = Scalar(img3Mean)[1];
	blue = Scalar(img3Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nThree has been pressed\n";
		redThree = red;
	}

	red = Scalar(img4Mean)[2];
	green = Scalar(img4Mean)[1];
	blue = Scalar(img4Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nFour has been pressed\n";
		redFour = red;
	}
	
	red = Scalar(img5Mean)[2];
	green = Scalar(img5Mean)[1];
	blue = Scalar(img5Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nFive has been pressed\n";
		redFive = red;
	}
	
	red = Scalar(img6Mean)[2];
	green = Scalar(img6Mean)[1];
	blue = Scalar(img6Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nSix has been pressed\n";
		redSix = red;
	}
	
	red = Scalar(img7Mean)[2];
	green = Scalar(img7Mean)[1];
	blue = Scalar(img7Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nSeven has been pressed\n";
		redSeven = red;
	}
	
	red = Scalar(img8Mean)[2];
	green = Scalar(img8Mean)[1];
	blue = Scalar(img8Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nEight has been pressed\n";
		redEight = red;
	}
	
	red = Scalar(img9Mean)[2];
	green = Scalar(img9Mean)[1];
	blue = Scalar(img9Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nNine has been pressed\n";
		redNine = red;
	}
	
	red = Scalar(img0Mean)[2];
	green = Scalar(img0Mean)[1];
	blue = Scalar(img0Mean)[0];
	
	if(red > 130.000 || blue < 100.000){
		cout << "\nZero has been pressed\n";
		redZero = red;
	}
	//all of the variable within the threshold will be stored in this array, 
	//intensity values that did not enter the threshold will be collected as 0.
	double Array[10] = {redZero, redOne, redTwo, redThree, redFour, redFive, redSix, redSeven,
						redEight, redNine}; //raw values collected from pictures
	int Code[4] = {0,0,0,0}; //create code array to store button press value
	double Intens[4] = {0,0,0,0}; //create Intensity array to store Intensity value
	int x = 0; //code index and intensity index number we want these to be equal
	double temp;
	int count = 0; //prevent more than 4 numbers in code
	
	cout << endl;
	for(int i = 0; i != 10; i++){ //for loop to calculate code
		if(Array[i] > 0){ //If The intensity of red is greater than 0
			Code[x] = i; //store index number of value i into code array
			Intens[x] = Array[i]; //store the intensity that was not zero into new array
			//output possible keys intensity values
			cout << "\nIntens: " << Intens[x];
			cout << "\nCode: " << Code[x];
			
			//sort code based on lowest to highest intensity
			if(count < 4 && Intens[x] < Intens[x - 1]){ 
				//create temp variable to store higher intensity value index number
				temp = Code[x - 1]; 
				Code[x - 1] = Code[x]; //set lower intensity index value to higher value  
				Code[x] = temp; //set higher intensity value to lower intensity value
				count++;
			}
			
			x++;
		}
		// if(Array[i] == Intens[x] || Array[i] == Intens[x + 1] || Array[i] == Intens[x + 2] || Array[i] == Intens[x + 3]){
			// Code[x] = i + 1;
		// }
	}
	
	// for(int i = 0; i < 10; i++){
		
	// }
		
	sort(Intens, Intens + 4); //sort intensity value from least to greatest
	cout << "\nThe Intensities are: ";
	for(int i = 0; i != 4; i++){
		cout << Intens[i] << " ";
	}

	cout << "\nThe numbers pressed are: ";
	for(int i = 0; i != 4; i++){
		cout << Code[i] << " ";
	}
	
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