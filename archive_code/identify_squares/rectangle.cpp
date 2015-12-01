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
void load_image(Mat);
static double angel(Point, Point, Point);
static void findSquares(Mat&, vector<vector<Point> >&);
static void drawSquares(Mat&, vector<vector<Point> >&);

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

	/**************************************************************
	 * Justin's sandbox
	 *
	 **************************************************************/
	 	load_image(img);
	 /**************************************************************
	 * End Justin's sandbox
	 *
	 **************************************************************/
	
	// Mat roi1 = smallerImages.pop_back(1);
	
	Mat roi0 = img(Rect(248, 370, 59, 40));
	Mat roi1 = img(Rect(167, 125, 59, 40)); //For researched keypad "keypad3.jpg"
	Mat roi2 = img(Rect(248, 125, 59, 40)); 
	Mat roi3 = img(Rect(332, 125, 59, 40));
	Mat roi4 = img(Rect(167, 208, 59, 40)); 
	Mat roi5 = img(Rect(248, 208, 59, 40));
	Mat roi6 = img(Rect(332, 208, 59, 40));
	Mat roi7 = img(Rect(167, 291, 59, 40));
	Mat roi8 = img(Rect(248, 291, 59, 40));
	Mat roi9 = img(Rect(332, 291, 59, 40));
	
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
	
	display(img); //display image
	//modify this if you need to see a specific number or the whole image
	
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
	
	cout << "\n image0: " << img0Mean << endl;
    cout << " image1: " << img1Mean << endl;
    cout << " image2: " << img2Mean << endl;
    cout << " image3: " << img3Mean << endl;
    cout << " image4: " << img4Mean << endl;
    cout << " image5: " << img5Mean << endl;
    cout << " image6: " << img6Mean << endl;
    cout << " image7: " << img7Mean << endl;
    cout << " image8: " << img8Mean << endl;
    cout << " image9: " << img9Mean << endl;
    
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
	
	if(red > redLimit || blue < blueLimit){
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
	
	x = 0;
	sort(Intens, Intens + 4); //sort intensity value from least to greatest
	for(int i = 0; i != 10; i++){
		if(Intens[x] == Array[i]){
			code[x] = i;
			// cout << "\nX: " << x;
			x++;
			i = 0;
		}
	}

	cout << "\n\nThe most likely PINs are: \n";
	do{	
		for(int i = 0; i != 4; i++){
			cout << code[i] << " ";
		}
		cout << endl;
	}while(next_permutation(code, code + 4));
	
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

/**************************************************************
*
* Justin's sandbox
*
**************************************************************/


int thresh = 50, N = 11;

static double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

static void findSquares(Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();

    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        for( int l = 0; l < N; l++ )
        {

            if( l == 0 )
            {
                // apply Canny. 
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold
                gray = gray0 >= (l+1)*255/N;
            }

            // find contours and store them all as a list
            findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

            vector<Point> approx;


            for( size_t i = 0; i < contours.size(); i++ )
            {

                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {

                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }
}


// the function draws all the squares in the image
static void drawSquares( Mat& image, vector<vector<Point> >& squares )
{
	Rect r, c;
	Mat tempMat, tempMat2;
	char confirm;
	int width; 
	int height;
	Point tempPoint;

	for( size_t i = 0; i < squares.size(); i++ )
    {
		cout << "count: " << squares.size();

        r = boundingRect(squares[i]);
        tempMat = image(Rect(r.x, r.y, r.width, r.height));

        if(tempMat.empty()){
    	cout << "\n temp is empty" << endl; 
    	}

    	else{
    	namedWindow("Square key",CV_WINDOW_NORMAL);
    	imshow("Square key", tempMat);
    	waitKey(2000);
    	destroyWindow("Square key");
	    }

	    cout << "\n Confirm: " << endl;
	    cout << "\n Is this a key?" << endl; 
	    cin >> confirm; 

	    if(confirm == 'y'){
	    	width = r.width;
	    	height = r.height;
	    	break;
	    }
	}


    for( size_t i = 0; i < squares.size(); i++ )
    {
		cout << "count: " << squares.size();

        c = boundingRect(squares[i]);

        	cout << "\n x" << c.x << endl;
        	cout << "\n y" << c.y << endl; 

        if(c.width >= width+5 || c.width <= width+5 && c.height >= height+5 || c.height <= height+5){
        	if(c.x >= tempPoint.x + 20 || c.x <= tempPoint.x - 20 && c.y >= tempPoint.y + 20 || c.y <= tempPoint.y - 20 && c.x != 1 && c.y != 1){
        	tempMat2 = image(Rect(c.x, c.y, c.width, c.height));
        	tempPoint.x = c.x; 
        	tempPoint.y = c.y; 
        	cout << "\n tempx: " << tempPoint.x << endl;
        	cout << "\n tempy: " << tempPoint.y << endl;

        	        if(tempMat2.empty()){
			    	cout << "\n temp is empty" << endl; 
			    	}

			    	else{
			    	namedWindow("Square key",CV_WINDOW_NORMAL);
			    	imshow("Square key", tempMat2);
			    	waitKey(2000);
			    	destroyWindow("Square key");
			    	}
        	}
    	}	
    }


}


void load_image(Mat image)
{ 

    vector<vector<Point> > squares;
    findSquares(image, squares);
    drawSquares(image, squares);

}


/**************************************************************
*
* End of Justin's sandbox
* 
**************************************************************/
