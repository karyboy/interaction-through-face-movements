
#include <Windows.h>
#include "ktrack.h"

int cam_frame_width=320;
int cam_frame_height=240;
int screen_width=GetSystemMetrics(SM_CXSCREEN);
int screen_height=GetSystemMetrics(SM_CYSCREEN);
int sens_width=50;
int sens_height=27;
float xsens=screen_width/sens_width+2;
float ysens=screen_height/sens_height+2;
//int ski=0;
int xcent=cam_frame_width/2;
int ycent=cam_frame_height/2;
POINT lpp;

Point frame_center(){

	Point center(xcent,ycent);
	return center;

}

rectval screensize(){
	rectval r;
	r.height=screen_height;
	r.width=screen_width;
    return r;

}
rectval sens(){
    rectval r;
	r.x=xcent-sens_width/2;
	r.y=ycent-sens_height/2;
	r.height=sens_height;
	r.width=sens_width;
	return r;
}

void prevpara(int x,int y,double time){
	pp.x=x;
	pp.y=y;
	pp.time=time;
	
}

double distance(int x,int y){
	return sqrt(pow((double)(x-pp.x),2)+pow((double)(y-pp.y),2));

}

void setCenter(int x,int y){
	xcent=x;ycent=y;
}
void sendEvent(int no){

switch(no){
case 1:lclick();
	break;
default: std::cout<<"illegal event";

}


}


void lclick(){
 std::cout<<"left clicked"<<std::endl;
 mouse_event(MOUSEEVENTF_LEFTDOWN,lpp.x,lpp.y,0,0);
 mouse_event(MOUSEEVENTF_LEFTUP,lpp.x,lpp.y,0,0);
}

bool convert(Point c){
	RECT rec=getWindow();
	rectval out;
	rectval r=sens();
	GetCursorPos(&lpp);
	double tim=time(0);
	//ski++;
	/*if(ski>5){
	filing(c.x,c.y,tim);
	ski=0;
	}*/
	if(c.x>=r.x && c.x<(r.x)+r.width && c.y>=r.y && c.y<(r.y)+r.height){
		out.x=c.x-r.x;
		out.y=c.y-r.y;
		double d=distance(out.x,out.y);
		prevpara(out.x,out.y,tim);
		//cout<<out.x<<"++"<<out.y<<"++"<<d<<endl;
		//cout<<sqrt(pow((double)(lpp.x-rec.left),2)+pow((double)(lpp.y-rec.top),2))<<endl;
		if(sqrt(pow((double)(lpp.x-rec.left),2)+pow((double)(lpp.y-rec.top),2))<100){
			SetCursorPos(rec.left+5,rec.top+5);
		   // std::cout<<"asdsadasD";
		}
	    if(abs(lpp.y-screen_height)<100)
			SetCursorPos(lpp.x,screen_height-20);
		if(lpp.y<100)
			SetCursorPos(lpp.x,20);
		if(d>1.8){
		SetCursorPos(screen_width-out.x*xsens,out.y*ysens);
		}
		//cout<<"in----------"<<endl;
		return true;
	}
	else{
		
		if (c.x>xcent+sens_width/2){
			SetCursorPos(screen_width,lpp.y);
			xcent=c.x-sens_width/2;
			//cout<<"x >>>>>>>>>>>>";
		}
		if (c.x<xcent-sens_width/2){
			SetCursorPos(0,lpp.y);
			xcent=c.x+sens_width/2;
			//cout<<"x<<<<<<<<<<<<<<<<";
		}
		if (c.y>ycent+sens_height/2){
			SetCursorPos(lpp.x,screen_height);
			ycent=c.y-sens_height/2;
			//cout<<"y>>>>>>>>>>>>";
		}
		if (c.y<ycent-sens_height/2){
			SetCursorPos(lpp.x,0);
			ycent=c.y+sens_height/2;
			//cout<<"y<<<<<<<<<<<<";
		}
		
		
		std::cout<<std::endl;
		return true;
	}
		

}

RECT getWindow(){
	//cout<<"??????????";
	HWND hw=GetForegroundWindow();
	TITLEBARINFOEX tch;
	tch.cbSize=sizeof(TITLEBARINFOEX);
	SendMessage(hw,WM_GETTITLEBARINFOEX,0,LPARAM(&tch));
	RECT rec=tch.rgrect[5];
	return rec;
	
}
	


