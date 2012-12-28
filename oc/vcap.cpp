#include "ktrack.h"
 

void main()

{   int i=0;
	String cn="haarcascade_frontalface_alt.xml";
	CascadeClassifier cd;
	vector<Rect> faces;
	bool cb=cd.load(cn);
	Point cent;
	bool lock=true;
	int nodetect_cnt=0;
	int clickdetectcnt=3;
	try
{   
    VideoCapture cap(-1); 
	cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    if(!cap.isOpened()) {
		cout<<"not found";
	}
	else{
		cout<<"yeah";
	}

	cout<<cap.get(CV_CAP_PROP_FRAME_HEIGHT)<<"_________________"<<cap.get(CV_CAP_PROP_FRAME_WIDTH)<<endl;
	 for(;;)
    {
        Mat frame;
		rectval r1=sens();
		cap >> frame; 
		
		ellipse( frame, frame_center(), Size(5,5), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
		rectangle(frame,Point(r1.x,r1.y),Point(r1.x+r1.width,r1.y+r1.height),Scalar( 255, 0, 255 ));
		cd.detectMultiScale(frame,faces);
		if(faces.size()==1){
			cout<<"face"<<endl;
			nodetect_cnt=0;
		}
		else{
			nodetect_cnt=nodetect_cnt+1;
			if(nodetect_cnt==clickdetectcnt && lock==true){
					cout<<"event sent"<<endl;
					sendEvent(1);
					nodetect_cnt=0;
			}
			cout<<nodetect_cnt<<endl;
		    cout<<"no face"<<endl;
		}
		for(int i=0 ; i<faces.size();i++){
		
		Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
		cent=center;
		if(lock==true)
		convert(center);
	    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
		ellipse( frame, center, Size( 5, 5), 0, 0, 360, Scalar( 50, 205, 50 ), 2, 8, 0 );
	 	}
		imshow("edges", frame);
		int c=waitKey(20);
		if(c==99)
			setCenter(cent.x,cent.y);
		if(c==27)
		break;
		if(c==108)
			lock=false;
		if(c==107)
			lock=true;
		//cout<<c;
       
   }
}
catch( cv::Exception& e )
{
    cout<< "---------"<<e.what();
}

	int a;
	std::cin>>a;
}