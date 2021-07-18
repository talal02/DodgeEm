//============================================================================
// Name        : TALAL AHMED
// Author      : Hassan Mustafa
// Version     : 2019
// Copyright   : (c)--Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================
#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
int RANDOM;                    //USED RANDOM TO START ENEMY CAR AT ANY 3 Random Positions
float bx,by,cx=310,cy=15;             //Postion (CO-ORDINATES) FOR ENEMY CARS 
int life = 3, score = 0,level=1,FOOD_X[8],FOOD_Y[8];  //LIFE, SCORE AND LEVEL DECLERATION + Arrays For x and y axis across whole canvas to print food
float x = 450, y = 545; //Position of Players Car
float width,height,radius; 
int H_S[10];
float* color;
int highscore[10];
bool PAUSE=true,MENU=true,HELP,ARENA,FOOD_CHECK[8][8],HS,Print,check;
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void FOODAXIS(){
	int food_check_x = 40, food_check_y = 30;       //X_AXIS & Y_AXIS WHERE TO PRINT FOOD
		for(int i = 0; i<8 ; i++){
		    FOOD_X[i]=food_check_x;
		    FOOD_Y[i]=food_check_y;
		    if(food_check_x == 250){
		    food_check_x = 530;                   //LOOP TO UPDATE FOOD POSITION ON X_AXIS & Y_AXIS
		    }else{                             
		    food_check_x += 70;
		    }
		    if(food_check_y == 210){
		    food_check_y = 380;
		    }else{
		    food_check_y += 60;
		    }
		}
}
void Highscore(int &score, int highscore[])
{
	if(Print||level==5){    
    int temp;
    for(int i = 0; i<10; i++){
    if (score > highscore[i])
    {        //checking highscores and replacing undercertain condition-
        highscore[i] = score;
	check = true;
	break;
	}
	}
	if(check){
        for (int i = 0; i < 10; i++){
	    if(highscore[i+1]>highscore[i]){
            	temp = highscore[i];
            	highscore[i] = highscore[i+1];
            	highscore[i+1]=temp;
        	}
	     }
	}
	Print = false;
	if(level==5){
		level++;
		}
    }
}

void High_Scores(int high){
	if(score==0&&level==1){	
	string SCORE;
	ifstream FILE;
   	FILE.open("HS.txt");
	int i = 0;	
	while(getline(FILE,SCORE)){
		     highscore[i] = stoi(SCORE);
			i++;
		}
	}	
	Highscore(score,highscore);
    	ofstream file;
    	file.open("HS.txt");
    	for(int i=0;i<10;i++){
        file << highscore[i]<<endl;
   	}
    	file.close();
  	ifstream file1;
   	file1.open("HS.txt");
    	for(int i=0;i<10;i++) {
	        H_S[i] = highscore[i]; 
    	}
	glutTimerFunc(100,High_Scores,0);  
}
void MYDISPLAY(){
	if(level == 1){
	glClearColor(1.0, 0.9 ,1.0, 0.0 );   //BACKGROUND FOR LEVEL 1
	glClear (GL_COLOR_BUFFER_BIT); 
	}else if(level == 2){
	glClearColor(0.8, 1.0 ,0.8, 0.0 ); 	//BACKGROUND FOR LEVEL 2
	glClear (GL_COLOR_BUFFER_BIT);	
	}else if(level == 3){
	glClearColor(1.0, 0.9 ,0.9, 0.0 );      //BACKGROUND FOR LEVEL 3                 
	glClear (GL_COLOR_BUFFER_BIT);                       //Update the colors	
	}else if(level == 4){
	glClearColor(0.9, 0.9 ,1.0, 0.0 );     //BACKGROUND FOR LEVEL 4
	glClear (GL_COLOR_BUFFER_BIT);	
	}else if(level >= 5){
	glClearColor(0.9, 0.9 ,1.0, 0.0 );    
	glClear (GL_COLOR_BUFFER_BIT); 	
	}  

	if(MENU){
		   DrawString(100,600,"TALAL - AHMED",colors[GREEN_YELLOW]);
		   DrawString(100,570,"19I-0727",colors[GREEN]);
		   DrawString(100,540,"CS-F",colors[YELLOW_GREEN]);
		   DrawString(220,520,"-----WELCOME TO DODGE 'EM------",colors[BLUE]);
		   DrawString(250,420,"___Press (S) - START THE  GAME",colors[LIME_GREEN]); //PRINTING THE WHOLE MENU 
		   DrawString(250,380,"___Press (P) - PAUSE THE  GAME",colors[RED]);
		   DrawString(250,340,"___Press (R) - RESET THE  GAME",colors[TEAL]);
		   DrawString(250,300,"___Press (H) - GUIDE TO   GAME",colors[ROYAL_BLUE]);
		   DrawString(250,260,"___Press (A) - PRINT HIGH SCORES",colors[YELLOW]);
		   DrawString(250,220,"___Press (E) - EXIT  THE  GAME",colors[BLACK]);
		   if(level == 2&&life>0){
			DrawString(450,100,"LEVEL @ 1 COMPLETED!!!",colors[BLACK]);
			DrawString(450,50,"PRESS(S) - TO START LEVEL 2",colors[BLACK]);   //Printing Level Completion
			}
		   if(level == 3&&life>0){
			DrawString(450,100,"LEVEL @ 2 COMPLETED!!!",colors[BLACK]);
			DrawString(450,50,"PRESS(S) - TO START LEVEL 3",colors[BLACK]);   
			}
		   if(level == 4&&life>0){
			DrawString(450,100,"LEVEL @ 3 COMPLETED!!!",colors[BLACK]);
			DrawString(450,50,"PRESS(S) - TO START LEVEL 4",colors[BLACK]);   
			}
		   if(level >= 5&&life>0){
			string SCORE = to_string(score); 
			DrawString(450,150,"Your Score : "+SCORE,colors[NAVY]);                    //IF PLAYER WON 
			DrawString(450,100,"YOU WON!!!",colors[BLACK]);
			DrawString(450,50,"PRESS(R) - TO RESET THE GAME",colors[BLACK]);   
			}
		   if(life==-1||life==0){
			DrawString(450,100,"GAME_OVER !!!",colors[BLACK]);                              //GAME OVER
			DrawString(450,50,"PRESS(R) - TO RESET THE GAME",colors[TEAL]);
			}
		glutSwapBuffers();
	}
	if(HELP){
	   	   DrawString(60,600,"Game starts with two cars -- One Yours and Second one of enemy --",colors[ROYAL_BLUE]);
		   DrawString(60,570,"Player Control His Car with Arrow Keys -- LEFT,RIGHT,UP,DOWN --",colors[ROYAL_BLUE]);
		   DrawString(60,540,"Opponent's Car is Moving AntiClockWise & Player's Car ClockWise",colors[ROYAL_BLUE]);
		   DrawString(60,510,"You Can Press -- P -- At Any Moment To Pause The Game",colors[ROYAL_BLUE]);
		   DrawString(60,480,"You Can Press -- S -- At Any Moment To Start The Game",colors[ROYAL_BLUE]);
		   DrawString(60,450,"Collect Maximum Rewards and Score Maximum",colors[ROYAL_BLUE]);               //PRINTING THE HELP/GUIDE MENU
		   DrawString(60,420,"This Game Has 4 Levels In Total",colors[RED]);
		   DrawString(60,390,"Level 1 : Opponent Car is Less Active & Normal Speed",colors[RED]);
		   DrawString(60,360,"Level 2 : Opponent Car is Active & Normal Speed",colors[RED]);
		   DrawString(60,330,"Level 3 : Opponent Car is Active & DOUBLE Speed",colors[RED]);
		   DrawString(60,300,"Level 4 : TWO Opponent Cars are Active & Normal Speed",colors[RED]);
		   DrawString(60,270,"USE -- SPACE_BAR -- To Speed Up Your Car",colors[ROYAL_BLUE]);
		   DrawString(60,240,"Press (B) - BACK_TO_MENU",colors[RED]);
		   DrawString(300,50,"DODGE 'EM ATARI-2600",colors[BLACK]);
		   DrawString(300,650,"GAME__GUIDE",colors[BLACK]);
		   int hx = 60, hy = 170, hbx = 300 , hby = 170;    //Special Int declaration to show my cars in help Menu 
		   width = 15; 
		   height = 10;
		   color = colors[DARK_SEA_GREEN]; 
		   radius = 4.0;                //SHOWING PLAYERS CAR
		   DrawRoundRect(hx,hy,width,height,color,radius); // bottom left tyre
		   DrawRoundRect(hx+width*3,hy,width,height,color,radius); // bottom right tyre
		   DrawRoundRect(hx+width*3,hy+height*4,width,height,color,radius); // top right tyre
		   DrawRoundRect(hx,hy+height*4,width,height,color,radius); // top left tyre
		   DrawRoundRect(hx,hy+height*2, width, height, color, radius/2); // body left rect
		   DrawRoundRect(hx+width,hy+height, width*2, height*3, color, radius/2); // body center rect
		   DrawRoundRect(hx+width*3,hy+height*2, width, height, color, radius/2); // body right rect
		   color = colors[STEEL_BLUE]; 		//SHOWING ENEMYS CAR
		   DrawRoundRect(hbx,hby,width,height,color,radius); // bottom left tyre
		   DrawRoundRect(hbx+width*3,hby,width,height,color,radius); // bottom right tyre
		   DrawRoundRect(hbx+width*3,hby+height*4,width,height,color,radius); // top right tyre
		   DrawRoundRect(hbx,hby+height*4,width,height,color,radius); // top left tyre
		   DrawRoundRect(hbx, hby+height*2, width, height, color, radius/2); // body left rect
		   DrawRoundRect(hbx+width, hby+height, width*2, height*3, color, radius/2); // body center rect
		   DrawRoundRect(hbx+width*3, hby+height*2, width, height, color, radius/2); // body right rect
		   DrawSquare(500,210,30,colors[RED]);
		   DrawSquare(500,180,30,colors[BLUE]);        //SHOWING FOOD IN HELP MENU
		   DrawCircle(545,225,15,colors[BLACK]);
		   DrawCircle(545,195,15,colors[GREEN]);	
		   DrawString(50,140,"User's car",colors[ROYAL_BLUE]);
		   DrawString(290,140,"Enemy's car",colors[ROYAL_BLUE]);
		   DrawString(480,140,"-- Food --",colors[ROYAL_BLUE]);	
		glutSwapBuffers();
	}
	if(HS){
		for(int i = 0, yax = 550, Count = 1;i<10;i++,yax-=40,Count++){
			string HighScr = to_string(H_S[i]);              //Loop to print Highscores
			string COUNT = to_string(Count);
		DrawString(360,yax,HighScr,colors[ROYAL_BLUE]);
		DrawString(335,yax,COUNT+".",colors[RED]);
		DrawSquare(310,yax,15,colors[GREEN]);
		DrawSquare(290,yax,15,colors[RED]);
		DrawSquare(400,yax,15,colors[BLACK]);
		DrawSquare(420,yax,15,colors[BLUE]);
		}	      
		DrawString(280,600,"-- HIGH_SCORES --",colors[TEAL]);
		DrawString(280,50,"DODGE `EM BY TALAL",colors[TEAL]);
		 glutSwapBuffers();
	}
	if(MENU == false && ARENA == true){
	     //DRAWING FOOD AND CHECKING CONDITIONS
		
		for(int i = 0; i<8 ; i++){
		    for(int j = 0; j<8 ; j++){
			if(FOOD_CHECK[i][j] == false){
			   if(FOOD_X[i]<x-10){                          //checking Car and Food-Coordinates
				DrawSquare(FOOD_X[i],FOOD_Y[j],15,colors[RED]);     
			   }else if(FOOD_X[i]>x+20){ 						 
				DrawCircle(FOOD_X[i],FOOD_Y[j],8,colors[GREEN]);
		 	   }else if(FOOD_Y[j]>y+20){
				DrawSquare(FOOD_X[i],FOOD_Y[j],15,colors[BLUE]);
			   }else if(FOOD_Y[j]<y-10){
				DrawCircle(FOOD_X[i],FOOD_Y[j],8,colors[BLACK]);
			   }
			else{
				FOOD_CHECK[i][j] = true;          //If car touches the food coordiantes
				score++;                         //increment in score and Boolen == true
			    }
			}
		   }
		}
	        	
	//DRAWING PLAYER'S CAR//
	width = 10; 
	height = 8;
	color = colors[DARK_SEA_GREEN]; 
	radius = 3.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x,y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width,y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3,y+height*2, width, height, color, radius/2); // body right rect
	if(level == 4){
	//Drawing Second Bot's Car
	color = colors[STEEL_BLUE]; 
	DrawRoundRect(cx,cy,width,height,color,radius); // bottom left tyre
	DrawRoundRect(cx+width*3,cy,width,height,color,radius); // bottom right tyre
	DrawRoundRect(cx+width*3,cy+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(cx,cy+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(cx,cy+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(cx+width,cy+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(cx+width*3,cy+height*2, width, height, color, radius/2); // body right rect	
	}
	// DRAWING BOTS'S CAR//
	color = colors[STEEL_BLUE]; 
	DrawRoundRect(bx,by,width,height,color,radius); // bottom left tyre
	DrawRoundRect(bx+width*3,by,width,height,color,radius); // bottom right tyre
	DrawRoundRect(bx+width*3,by+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(bx,by+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(bx, by+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(bx+width, by+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(bx+width*3, by+height*2, width, height, color, radius/2); // body right rect
	//PRINTING SCORE, LIFES and Levels	
	string SCORE = to_string(score);
	DrawString(450,650,"SCORE : " + SCORE,colors[BLUE]);
	string LIFE = to_string(life);
	DrawString(250,650,"LIVES : " + LIFE,colors[RED]);
	string LEVEL = to_string(level);
	DrawString(360,290,"LEVEL : " + LEVEL,colors[RED]);
	if(level >= 2)
	DrawString(20,670,"MODE : ACTIVE",colors[BLACK]);
	else
	DrawString(20,670,"MODE : LESS-ACTIVE",colors[BLACK]);
	if(level == 3)
	DrawString(20,640,"SPEED : DOUBLE-(2X)",colors[ROYAL_BLUE]);
	else
	DrawString(20,640,"SPEED : NORMAL",colors[ROYAL_BLUE]);	
	//DRAWING ARENA WITH FUNCTION DRAWRECTANLE//	
	int gap_turn = 60;
	int sx = 20;
	int sy = 0;
	int swidth = 800/2 - gap_turn/2; // half width
	int sheight = 10;
	float *scolor = colors[YELLOW];
	DrawRectangle(sx, sy, swidth-40, sheight, scolor); // bottom left
	DrawRectangle(sx + 60, sy + 60,swidth-100, sheight, scolor); // 2nd bottom left
	DrawRectangle(sx + 130, sy + 120,swidth-170, sheight, scolor); // 3rd bottom left
	DrawRectangle(sx + 200, sy + 180,swidth-240, sheight, scolor); // 4th bottom left
	DrawRectangle(sx + 280, sy + 240,swidth-255, sheight, scolor); // 5th bottom left
	DrawRectangle(sx + swidth+60, sy, swidth-40, sheight, scolor); // bottom right
	DrawRectangle(sx + swidth+60, sy + 60, swidth-100, sheight, scolor); //2nd bottom right
	DrawRectangle(sx + swidth+60, sy + 120, swidth-170, sheight, scolor); //3rd bottom right
	DrawRectangle(sx + swidth+60, sy + 180, swidth-240, sheight, scolor); //4th bottom right
	DrawRectangle(sx+swidth+gap_turn-50, sy + 240, swidth-270, sheight, scolor); //5th bottom right
	DrawRectangle(sx*2+swidth*2, sy+sheight, sheight, swidth-2*gap_turn, scolor); // right down
	DrawRectangle(sx*2+swidth*2-70, sy+sheight+50, sheight, swidth-170, scolor); //2nd right down
	DrawRectangle(sx*2+swidth*2-140, sy+sheight+110, sheight, swidth-230, scolor); //3rd right down
	DrawRectangle(sx*2+swidth*2-210, sy+sheight+170, sheight, swidth-290, scolor); //4th right down
	DrawRectangle(sx*2+swidth*2-290, sy+sheight+235, sheight, swidth-325, scolor); //5th right down
        DrawRectangle(sx*2+swidth*2, sy+sheight+swidth-20, sheight, swidth-2*gap_turn-20, scolor); // right up
	DrawRectangle(sx*2+swidth*2-70, sy+sheight+swidth-20, sheight, swidth-190, scolor); //2nd right up
	DrawRectangle(sx*2+swidth*2-140, sy+sheight+swidth-20, sheight, swidth-250, scolor); //3rd right up
	DrawRectangle(sx*2+swidth*2-210, sy+sheight+swidth-20, sheight, swidth-310, scolor); //4th right up
	DrawRectangle(sx*2+swidth*2-290, sy+sheight+swidth-30, sheight, swidth-410, scolor); //5th right up
	DrawRectangle(sx+swidth+60, sy+590, swidth-40, sheight, scolor); // top right
	DrawRectangle(sx+swidth+60, sy+530, swidth-100, sheight, scolor); //2nd top right
	DrawRectangle(sx+swidth+60, sy+470, swidth-170, sheight, scolor); //3rd top right
	DrawRectangle(sx+swidth+60, sy+410, swidth-240, sheight, scolor); //4th top right
	DrawRectangle(sx+swidth+gap_turn-50, sy+345, swidth-270, sheight, scolor); //5th top right
	DrawRectangle(sx, sy+590, swidth-40, sheight, scolor); // top left
	DrawRectangle(sx+60, sy+530, swidth-100, sheight, scolor); //2nd top left
	DrawRectangle(sx+130, sy+470, swidth-170, sheight, scolor); //3rd top left
	DrawRectangle(sx+200, sy+410, swidth-240, sheight, scolor); //4th top left
	DrawRectangle(sx+280, sy+345, swidth-265, sheight, scolor); //5th top left
	DrawRectangle(sx-sheight, sy+sheight+swidth-20, sheight, swidth-2*gap_turn-20, scolor); // left up
	DrawRectangle(sx-sheight*2+80, sy+sheight+swidth-20, sheight, swidth-190,scolor); //2nd left up
	DrawRectangle(sx-sheight*2+150, sy+sheight+swidth-20, sheight, swidth-250,scolor); //3rd left up
	DrawRectangle(sx-sheight*2+220, sy+sheight+swidth-20, sheight, swidth-310,scolor); //4th left up
	DrawRectangle(sx-sheight*2+300, sy+sheight+swidth-30, sheight, swidth-410,scolor); //5th left up
	DrawRectangle(sx-sheight, sy+sheight, sheight, swidth-2*gap_turn, scolor); // left down
	DrawRectangle(sx-sheight*2+80, sy+sheight+50, sheight, swidth-170, scolor); //2nd left down
	DrawRectangle(sx-sheight*2+150, sy+sheight+110, sheight, swidth-230, scolor); //3rd left down
	DrawRectangle(sx-sheight*2+220, sy+sheight+170, sheight, swidth-290, scolor); //4th left down
	DrawRectangle(sx-sheight*2+300, sy+sheight+235, sheight, swidth-325, scolor); //5th left down
	glutSwapBuffers();
	}
}
void ENEMYONEMOVEMENT(int b){
	//ENEMY CAR POSITIONING (FIRST ENEMY CAR)
	/*These are Bools to check Car is present in which road/track*/
	bool track_1 = false,track_2 = false,track_3 = false,track_4 = false;
	if((y==135)||(y==425)||(x==170)||(x==585)){
	   track_3 = true;
	}
	if((y==75)||(y==485)||(x==100)||(x==655)){
	   track_2 = true;
	}
	if((y==15)||(y==545)||(x==30)||(x==725)){
	  track_1 = true;
	}
	if((y==195)||(y==365)||(x==240)||(x==515)){
	  track_4 = true;
	}
	if(track_1||track_2||track_3||track_4){ 
	   if(track_1){  		//Car present on outermost road
		if(bx == 380){  	//if enemy car is on any other road
		   if(by==75){  	//it will follow follwing conditions to reach 
			by -= 60;
		   }else if(by==135){ 
			by -= 60;
		   }else if(by==195){
			by -= 60;
		   }else if(by==365){
			by += 60;
		   }else if(by==425){
			by += 60;
		   }else if(by==485){
			by += 60;
		   }
	       }
	       if(level>=2){
		if(by == 285){  	
		   if(bx==515){  	//FOR LEFT AND RIGHT GAPS 
			bx += 70;
		   }else if(bx==585){ 
			bx += 70;
		   }else if(bx==655){
			bx += 70;
		   }else if(bx==100){
			bx -= 70;
		   }else if(bx==170){
			bx -= 70;
		   }else if(bx==240){
			bx -= 70;
		   }
	       }
	}	
	}else if(track_2){
		if(bx == 380){                  //Car Present On second Road 
		   if(by==135){ 
			by -= 60;
		   }else if(by==195){
			by -= 60;
		   }else if(by==365){
			by += 60;
		   }else if(by==425){
			by += 60;
		   }else if(by==15){
			by += 60;
		   }else if(by==545){
			by -= 60;
		   }
	       }
	      if(level>=2){
		if(by == 285){  	
		   if(bx==515){  	//FOR LEFT AND RIGHT GAPS 
			bx += 70;
		   }else if(bx==585){ 
			bx += 70;
		   }else if(bx==725){
			bx -= 70;
		   }else if(bx==30){
			bx += 70;
		   }else if(bx==170){
			bx -= 70;
		   }else if(bx==240){
			bx -= 70;
		   }
	       }
	}	
	}else if(track_3){                       //Car Present on third Road
		if(bx == 380){
		   if(by==75){ 
			by += 60;
		   }else if(by==195){
			by -= 60;
		   }else if(by==365){
			by += 60;
		   }else if(by==485){
			by -= 60;
		   }else if(by==15){
			by += 60;
		   }else if(by==545){
			by -= 60;
		   }
	       }
	     if(level>=2){
		if(by == 285){  	
		   if(bx==515){  	//FOR LEFT AND RIGHT GAPS 
			bx += 70;
		   }else if(bx==655){ 
			bx -= 70;
		   }else if(bx==725){
			bx -= 70;
		   }else if(bx==30){
			bx += 70;
		   }else if(bx==100){
			bx += 70;
		   }else if(bx==240){
			bx -= 70;
		   }
	       }
	}	
	}else if(track_4){                      //Car Present On fourth Road
		if(bx == 380){
		   if(by==75){ 
			by += 60;
		   }else if(by==135){
			by += 60;
		   }else if(by==425){
			by -= 60;
		   }else if(by==485){
			by -= 60;
		   }else if(by==15){
			by += 60;
		   }else if(by==545){
			by -= 60;
		   }
	       }
	    if(level>=2){
		if(by == 285){  	
		   if(bx==585){  	//FOR LEFT AND RIGHT GAPS 
			bx -= 70;
		   }else if(bx==655){ 
			bx -= 70;
		   }else if(bx==725){
			bx -= 70;
		   }else if(bx==30){
			bx += 70;
		   }else if(bx==100){
			bx += 70;
		   }else if(bx==170){
			bx += 70;
		   }
	       }
	}	
	  }
} 
	glutPostRedisplay();
	glutTimerFunc(100,ENEMYONEMOVEMENT,0);    
}
void ENEMYTWOMOVEMENT(int q){
	if(level == 4){
	//ENEMY CAR POSITIONING (SECOND ENEMY CAR)
	/*These are Bools to check Car is present in which road/track*/
	bool track_1 = false,track_2 = false,track_3 = false,track_4 = false;
	if((y==135)||(y==425)||(x==170)||(x==585)){
	   track_3 = true;
	}
	if((y==75)||(y==485)||(x==100)||(x==655)){
	   track_2 = true;
	}
	if((y==15)||(y==545)||(x==30)||(x==725)){
	  track_1 = true;
	}
	if((y==195)||(y==365)||(x==240)||(x==515)){
	  track_4 = true;
	}
	if(track_1||track_2||track_3||track_4){ 
	   if(track_1){  		//Car present on outermost road
		if(cx == 380){  	//if enemy car is on any other road
		   if(cy==75){  	//it will follow follwing conditions to reach 
			cy -= 60;
		   }else if(cy==135){ 
			cy -= 60;
		   }else if(cy==195){
			cy -= 60;
		   }else if(cy==365){
			cy += 60;
		   }else if(cy==425){
			cy += 60;
		   }else if(cy==485){
			cy += 60;
		   }
	       }
		if(cy == 290){  	
		   if(cx==515){  	//FOR LEFT AND RIGHT GAPS 
			cx += 70;
		   }else if(cx==585){ 
			cx += 70;
		   }else if(cx==655){
			cx += 70;
		   }else if(cx==100){
			cx -= 70;
		   }else if(cx==170){
			cx -= 70;
		   }else if(cx==240){
			cx -= 70;
		   }
	}	
	}else if(track_2){
		if(cx == 380){                  //Car Present On second Road 
		   if(cy==135){ 
			cy -= 60;
		   }else if(cy==195){
			cy -= 60;
		   }else if(cy==365){
			cy += 60;
		   }else if(cy==425){
			cy += 60;
		   }else if(cy==15){
			cy += 60;
		   }else if(cy==545){
			cy -= 60;
		   }
	       }
		if(cy == 290){  	
		   if(cx==515){  	//FOR LEFT AND RIGHT GAPS 
			cx += 70;
		   }else if(cx==585){ 
			cx += 70;
		   }else if(cx==725){
			cx -= 70;
		   }else if(cx==30){
			cx += 70;
		   }else if(cx==170){
			cx -= 70;
		   }else if(cx==240){
			cx -= 70;
		   }
	}	
	}else if(track_3){                       //Car Present on third Road
		if(cx == 380){
		   if(cy==75){ 
			cy += 60;
		   }else if(cy==195){
			cy -= 60;
		   }else if(cy==365){
			cy += 60;
		   }else if(cy==485){
			cy -= 60;
		   }else if(cy==15){
			cy += 60;
		   }else if(cy==545){
			cy -= 60;
		   }
	       }
		if(cy == 290){  	
		   if(cx==515){  	//FOR LEFT AND RIGHT GAPS 
			cx += 70;
		   }else if(cx==655){ 
			cx -= 70;
		   }else if(cx==725){
			cx -= 70;
		   }else if(cx==30){
			cx += 70;
		   }else if(cx==100){
			cx += 70;
		   }else if(cx==240){
			cx -= 70;
		   }
	}	
	}else if(track_4){                      //Car Present On fourth Road
		if(cx == 380){
		   if(cy==75){ 
			cy += 60;
		   }else if(cy==135){
			cy += 60;
		   }else if(cy==425){
			cy -= 60;
		   }else if(cy==485){
			cy -= 60;
		   }else if(cy==15){
			cy += 60;
		   }else if(cy==545){
			cy -= 60;
		   }
	       }
		if(cy == 290){  	
		   if(cx==585){  	//FOR LEFT AND RIGHT GAPS 
			cx -= 70;
		   }else if(cx==655){ 
			cx -= 70;
		   }else if(cx==725){
			cx -= 70;
		   }else if(cx==30){
			cx += 70;
		   }else if(cx==100){
			cx += 70;
		   }else if(cx==170){
			cx += 70;
		   }
	           }	
	      }
        }
	}
	glutPostRedisplay();
	glutTimerFunc(100,ENEMYTWOMOVEMENT,0);    
}
void CHECKLIVESANDLEVELS(int a){
	
	int count = 0;
	for(int i = 0; i<8 ; i++){
	    for(int j = 0; j<8 ; j++){		//count to check weather all the food is eaten or not 
		 if(FOOD_CHECK[i][j] == true){   //everytime count is set to zero for fine calculation till 64 food is eaten
			count++;
			}	
		}
	}
	if(count == 64){
		for(int i = 0; i<8 ; i++){
	 	   for(int j = 0; j<8 ; j++){
			 FOOD_CHECK[i][j] = false;           //if all food is eaten
			}                    
		}
		x = 450, y = 545;                   //setting players and enemys position back
	   	RANDOM = 1+rand()%3;                  //setting all the food back
	  	if(RANDOM == 3){
		bx = 30, by =230;
	   	}else if(RANDOM==2){
		bx = 310, by = 545;
		}else{
		bx = 310, by = 545;
		}
		level++;                           //Increment in level
		if(level==4){
		if(RANDOM == 1){
		cx = 310, cy =545; 	
		}else if(RANDOM==2){
		cx = 30, cy = 230;
		}else{
		bx = 310, by = 15;
		}
		}		
		MENU = true;
		ARENA = false;
		PAUSE = true;
	}
	if(life==0){
		MENU = true;
		ARENA = false;
		Print = true;
		PAUSE = true;
		life--;
	}
	glutPostRedisplay();
	glutTimerFunc(100,CHECKLIVESANDLEVELS,0);
}
void COLLISION(int c){
	if((x>=bx-30&&x<=bx+30&&y>=by-30&&y<=by+30)||((x>=cx-30&&x<=cx+30&&y>=cy-30&&y<=cy+30)&&(level==4))){
	   life--;                               //Collision detection Happening here
	   x = 450, y = 545;                          //This condition shows when car will touch/srike enemy's car 
	   RANDOM = 1+rand()%3;                       //Setting position of players and enemys car back 
	   if(RANDOM == 1){				//Decrement in life
		bx = 310, by =545;
	   }else if(RANDOM == 3){
		bx = 30, by = 230;
	   }else{
		bx = 310, by = 15;
	   }
	if(level==4){
	  if(RANDOM == 2){
	     cx = 30, cy = 230;
	  }else if(RANDOM == 3){
	     cx = 310, cy =545;}
	}else{
	     cx = 310, cy = 15;
	}
	for(int i = 0; i<8 ; i++){
	 	   for(int j = 0; j<8 ; j++){
			 FOOD_CHECK[i][j] = false;              //Setting all the food back
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(100,COLLISION,0);

}
void NonPrintableKeys(int key ,int xx,int yy) {
	if(y>=280&&y<=300){    	
	if (key == GLUT_KEY_LEFT) {            //When Left key is pressed take Car to other tracks
    	x  -= 70;
	if(x<30||(x<500&&x>400)){           //Collision detection with boundries
	x += 70;
	}
	}
	else if(key == GLUT_KEY_RIGHT) {
        x += 70;			//When Left key is pressed take Car to other tracks
	if(x>730||(x>240&&x<350)){
	x -= 70;			    //Collision detection with boundries
	}
	}
}
	if(x>=370&&x<=390){
	if (key == GLUT_KEY_UP) {
        y += 60;			//When Left key is pressed take Car to other tracks
	if(y>550||(y>200&&y<350)){
	y -= 60;			    //Collision detection with boundries
	}	
	}
    else if (key == GLUT_KEY_DOWN) {
	y -= 60;			//When Left key is pressed take Car to other tracks
	if(y<10||(y>260&&y<350)){
	y += 60;			    //Collision detection with boundries
	}
	}
	}
    glutPostRedisplay();
}
void PrintableKeys(unsigned char key, int xp, int yp) {
if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if(key == 'e' || key == 'E'){
		exit(1);	//exiting the program  when E is prssed
	}	
	if(key == 'S' || key == 's'){
		PAUSE = false;         //S to start game
		MENU = false;        
		ARENA = true;
		cout<<"GAME STARTED!\n";
	}
	if(key == 'H' || key == 'h'){
		cout<<"GUIDE_PRINTED!!!\n";
		HELP = true;             //Displaying the guide when H is pressed
		MENU = false;
	}
	if(key == 'A' || key == 'a'){
		cout<<"***HIGH SCORES***\n";
		HS = true;
		MENU = false;
	}
	if(key == 'R' || key == 'r'){
		cout<<"RESET_THE_GAME!!!\n";
		life = 3,score = 0,level=1;
		x=450,y=545;	
		RANDOM = 1+rand()%2;
    		if(RANDOM == 2){
		bx = 30, by = 230;
		}else if(RANDOM == 3){
		bx = 310, by = 545;             //Reseting the game
		}else{
		bx =  310, by = 15;
		}                               //Lives back to 3, score back to 0, level back to 1
		PAUSE = true;                   //Setting positions of players and bots car back
		ARENA = false;			//Setting alll the food back to original position
		MENU = true;
		for(int i = 0; i<8 ; i++){
	 	   for(int j = 0; j<8 ; j++){
			 FOOD_CHECK[i][j] = false;
			}
		}
		
		}
	
	if(key == 'P' || key == 'p'){
		PAUSE = true;                   //To pause the game at any moment
		
	}
	if(key == 'B' || key == 'b'){
		MENU = true;            //Back to menu whereever user is 
		HELP = false;
		ARENA = false;	
		PAUSE = true;
		HS = false;
	}
	if(key == 32 ){		// Space--Bar Condition (2x the speed) of car
	 if((y==545&&x<725&&x>=30)||(y==485&&x<655&&x>=100)||(y==425&&x<585&&x>=170)||(y==365&&x<515&&x>=240)){
	     if(x==720||x==650||x==580||x==510)        //Detecting Boundry collision 
	   	x += 5;
	     else
		x += 10;
	}else if((x==725&&y>15)||(x==655&&y>75)||(x==585&&y>135)||(x==515&&y>195)){
	   if(y==20||y==80||y==140||y==200)		//Detecting Boundry collision
		y -= 5;
	   else
	   	y -= 10;
	}else if((y==15&&x>30)||(y==75&&x>100)||(y==135&&x>170)||(y==195&&x>240)){
		  if(x==35||x==105||x==175||x==245)	//Detecting Boundry collision
	   		x -= 5;
		  else
			x -= 10;
	}else if((x==30&&y<545)||(x==100&&y<485)||(x==170&&y<425)||(x==240&&y<365)){
		if(y==540||y==480||y==420||y==360)	//Detecting Boundry collision
			y += 5;
		else
	   		y += 10;
	}
	}
	glutPostRedisplay();
}
void Timer(int m) {
	// implement your functionality here
	if(PAUSE==false){   //boolean to Pause the car functioning
	if(level!=3){   //Level 1,2 and 4 will have normal speed 
	if((y==545&&x<725&&x>=30)||(y==485&&x<655&&x>=100)||(y==425&&x<585&&x>=170)||(y==365&&x<515&&x>=240)){
	   x += 5;
	}else if((x==725&&y>15)||(x==655&&y>75)||(x==585&&y>135)||(x==515&&y>195)){
	   y -= 5;
	}else if((y==15&&x>30)||(y==75&&x>100)||(y==135&&x>170)||(y==195&&x>240)){
	   x -= 5;
	}else if((x==30&&y<545)||(x==100&&y<485)||(x==170&&y<425)||(x==240&&y<365)){
	   y += 5;
	}
	if((by==545&&bx<=725&&bx>30)||(by==485&&bx<=655&&bx>100)||(by==425&&bx<=585&&bx>170)||(by==365&&bx<=515&&bx>240)){
	   bx -= 5;
	}else if((bx==30&&by>15)||(bx==100&&by>75)||(bx==170&&by>135)||(bx==240&&by>195)){
	   by -= 5;
	}else if((by==15&&bx<725)||(by==75&&bx<655)||(by==135&&bx<585)||(by==195&&bx<515)){
	   bx += 5;
	}else if((bx==725&&by<545)||(bx==655&&by<485)||(bx==585&&by<425)||(bx==515&&by<365)){
	   by += 5;
	}
	if(level >= 4){	
	if((cy==545&&cx<=725&&cx>30)||(cy==485&&cx<=655&&cx>100)||(cy==425&&cx<=585&&cx>170)||(cy==365&&cx<=515&&cx>240)){
	   cx -= 5;
	}else if((cx==30&&cy>15)||(cx==100&&cy>75)||(cx==170&&cy>135)||(cx==240&&cy>195)){
	   cy -= 5;
	}else if((cy==15&&cx<725)||(cy==75&&cx<655)||(cy==135&&cx<585)||(cy==195&&cx<515)){
	   cx += 5;
	}else if((cx==725&&cy<545)||(cx==655&&cy<485)||(cx==585&&cy<425)||(cx==515&&cy<365)){
	   cy += 5;
	}
	}
	}else if(level==3){	//Level 3 will have double speed 
	if((by==545&&bx<=725&&bx>30)||(by==485&&bx<=655&&bx>100)||(by==425&&bx<=585&&bx>170)||(by==365&&bx<=515&&bx>240)){
	     if(bx==35||bx==105||bx==175||bx==245)  //Detection of boundries
		bx -= 5;
	     else	   
		bx -= 10;
	}else if((bx==30&&by>15)||(bx==100&&by>75)||(bx==170&&by>135)||(bx==240&&by>195)){
		if(by==20||by==80||by==140||by==200)	  //Detection of boundries
		by -= 5;
		else
		by -= 10;
	}else if((by==15&&bx<725)||(by==75&&bx<655)||(by==135&&bx<585)||(by==195&&bx<515)){
	      if(bx==720||bx==650||bx==580||bx==510)	//Detection of boundries
		bx += 5;
	      else	   
		bx += 10;
	}else if((bx==725&&by<545)||(bx==655&&by<485)||(bx==585&&by<425)||(bx==515&&by<365)){
		if(by==540||by==480||by==420||by==360)	//Detection of boundries	
		by += 5;
		else	   
		by += 10;
	}
	if((y==545&&x<725&&x>=30)||(y==485&&x<655&&x>=100)||(y==425&&x<585&&x>=170)||(y==365&&x<515&&x>=240)){
	   x += 5;
	}else if((x==725&&y>15)||(x==655&&y>75)||(x==585&&y>135)||(x==515&&y>195)){
	   y -= 5;
	}else if((y==15&&x>30)||(y==75&&x>100)||(y==135&&x>170)||(y==195&&x>240)){
	   x -= 5;
	}else if((x==30&&y<545)||(x==100&&y<485)||(x==170&&y<425)||(x==240&&y<365)){
	   y += 5;
	}
	}
	}	
	glutPostRedisplay();
	glutTimerFunc(100.0, Timer, 0);
        }
void MousePressedAndMoved(int x, int y) {

	glutPostRedisplay();

}
void MouseMoved(int x, int y) {
	
	glutPostRedisplay();
}
void MouseClicked(int button, int state, int x1, int y1) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
int main(int argc, char*argv[]) {
	int width = 800, height = 700; // I have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	RANDOM = 1+rand()%(3);
	if(RANDOM == 3){
	bx = 30, by = 230;
	}else if(RANDOM==2){
	bx = 310, by = 545;
	}else{
	bx = 310, by = 15;
	}
   	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("DODGE 'EM"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	 // tell library which function to call for drawing Canvas.
	FOODAXIS();	
	glutDisplayFunc(MYDISPLAY);
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters	
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters	 
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);  //Movement of cars
	glutTimerFunc(1000.0,CHECKLIVESANDLEVELS,0);   //Life and levels check
	glutTimerFunc(1000.0,ENEMYONEMOVEMENT,0);  //Enemy movement inside and outside 
	glutTimerFunc(1000.0,ENEMYTWOMOVEMENT,0);  //Enemy (TWO) movement inside and outside
	glutTimerFunc(1000.0,COLLISION,0);   //COLLISION DETECTION
	glutTimerFunc(1000,High_Scores,0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
