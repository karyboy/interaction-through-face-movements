#include "ktrack.h"
#include "voce.h"

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
	bool quit=false;
	
	try
{   
    VideoCapture cap(-1); 
	cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    if(!cap.isOpened()) {
		std::cout<<"not found";
	}
	else{
		voce::init("./lib", false, true, "./grammar", "digits");
		std::cout<<"yeah";
	}

	std::cout<<cap.get(CV_CAP_PROP_FRAME_HEIGHT)<<"_________________"<<cap.get(CV_CAP_PROP_FRAME_WIDTH)<<std::endl;

	 for(;;)
    {   
		//std::cout<<"yahan aaya ";
		
	    Mat frame;
		rectval r1=sens();
		cap >> frame; 
		
		ellipse( frame, frame_center(), Size(5,5), 0, 0, 360, Scalar( 255, 0, 255 ), 2, 8, 0 );
		rectangle(frame,Point(r1.x,r1.y),Point(r1.x+r1.width,r1.y+r1.height),Scalar( 255, 0, 255 ));
		cd.detectMultiScale(frame,faces);
	
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
		if (voce::getRecognizerQueueSize() > 0)
		{
			std::string s = voce::popRecognizedString();

			if (std::string::npos != s.rfind("stop"))
			{
				quit = true;
				break;
			}
			std::string aopen="click",areset="reset";
			if(aopen.compare(s)==0){
			    sendEvent(1);
			}
			if(areset.compare(s)==0)
				setCenter(cent.x,cent.y);
				
			std::cout << "You said: " << s << std::endl;
			//voce::synthesize(s);
		}
		//if(c==99)
			
		if(c==27)
		break;
		if(c==108)
			lock=false;
		if(c==107)
			lock=true;
		//cout<<c;
       
   }
	 voce::destroy();
  
}
catch( cv::Exception& e )
{
    std::cout<< "---------"<<e.what();
}

	//int a;
	//std::cin>>a;
}