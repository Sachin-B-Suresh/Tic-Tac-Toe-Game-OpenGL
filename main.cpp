#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int board[3][3];	    // board for game play
int turn;               // current move
int result;
bool over;

void delay(unsigned int msec){
    clock_t goal=msec+clock();
    while(goal>clock());
}

void Intialize(){
	turn=1;
	over=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)
			board[i][j]=0;
	}
}

void DrawCircle(float cx, float cy, float r, int num_segments){
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle
        float x = r * cosf(theta);                                      //calculate the x component
        float y = r * sinf(theta);                                      //calculate the y component
        glVertex2f(x + cx, y + cy);                                     //output vertex
    }
    glEnd();
}

void DrawXO(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]==1){
				glBegin(GL_LINES);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			else if(board[i][j]==2){
				DrawCircle(50 + j*100 , 100 + i*100 , 25 , 15);
			}
		}
	}
}

void DrawLeftStickMan(int posx1, int posy1, int posx2, int posy2){
    int cx=-75;
    int cy=50;
    int num_segments=50;
    int r=25;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);       //get the current angle
        float x = r * cosf(theta);                                              //calculate the x component
        float y = r * sinf(theta);                                              //calculate the y component
        glVertex2f(2*x + 2*cx, 2*y + 2*cy);                                     //output vertex
    }
    glEnd();

    // BACKBONE
    glBegin(GL_LINES);
    glVertex2f(-150,50);
    glVertex2f(-150,-75);
    glEnd();
    //RIGHT-LEG
    glBegin(GL_LINES);
    glVertex2f(-150,-75);
    glVertex2f(-115,-200);
    glEnd();
    //LEFT-LEG
    glBegin(GL_LINES);
    glVertex2f(-150,-75);
    glVertex2f(-185,-200);
    glEnd();
    //RIGHT-HAND
    glBegin(GL_LINES);
    glVertex2f(-150,0);
    glVertex2f(-50 + posx1,50 + posy1);
    glEnd();
    //LEFT-HAND
    glBegin(GL_LINES);
    glVertex2f(-150,0);
    glVertex2f(-250 + posx2,50 + posy2);
    glEnd();
    //LEFT-EYE
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(-175,110);
    glEnd();
    //RIGHT-EYE
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(-125,110);
    glEnd();
    //MOUTH
     if(result==1){
       int cx=-75;
        int cy=55;
        int num_segments=48;
        int r=20;
        glBegin(GL_LINE_LOOP);
        for (int i = -18; i < -5; i++){
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);       //get the current angle
            float x = r * cosf(theta);                                              //calculate the x component
            float y = r * sinf(theta);                                              //calculate the y component
            glVertex2f(2*x + 2*cx, 2*y + 2*cy);                                     //output vertex
        }
        glEnd();
    }
    else if(result==2){
        int cx=-75;
        int cy=15;
        int num_segments=50;
        int r=25;
        glBegin(GL_LINE_STRIP);
        for (int i = 8; i <18; i++){
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);       //get the current angle
            float x = r * cosf(theta);                                              //calculate the x component
            float y = r * sinf(theta);                                              //calculate the y component
            glVertex2f(2*x + 2*cx, 2*y + 2*cy);                                     //output vertex
        }
        glEnd();
    }
    else{
        glBegin(GL_LINE_LOOP);
        glVertex2f(-170,75);
        glVertex2f(-130,75);
        glEnd();
    }
}

void DrawRightStickMan(int posx1, int posy1, int posx2, int posy2){
    int cx=225;
    int cy=50;
    int num_segments=50;
    int r=25;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <num_segments; i++){
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);       //get the current angle
        float x = r * cosf(theta);                                              //calculate the x component
        float y = r * sinf(theta);                                              //calculate the y component
        glVertex2f(2*x + 2*cx, 2*y + 2*cy);                                     //output vertex
    }
    glEnd();

    //BACKBONE
    glBegin(GL_LINES);
    glVertex2f(450,50);
    glVertex2f(450,-75);
    glEnd();

    //RIGHT-LEG
    glBegin(GL_LINES);
    glVertex2f(450,-75);
    glVertex2f(485,-200);
    glEnd();

    //LEFT-LEG
    glBegin(GL_LINES);
    glVertex2f(450,-75);
    glVertex2f(415,-200);
    glEnd();

     //RIGHT-HAND
    glBegin(GL_LINES);
    glVertex2f(450,0);
    glVertex2f(550 + posx2,50 + posy2);
    glEnd();

    //LEFT-HAND
    glBegin(GL_LINES);
    glVertex2f(450,0);
    glVertex2f(350 + posx1,50 + posy1);
    glEnd();

       //LEFT-EYE
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(425,110);
    glEnd();
    //RIGHT-EYE
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(475,110);
    glEnd();
    //MOUTH
    if(result==2){
       int cx=225;
        int cy=55;
        int num_segments=48;
        int r=20;
        glBegin(GL_LINE_LOOP);
        for (int i = -18; i < -5; i++){
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);       //get the current angle
            float x = r * cosf(theta);                                              //calculate the x component
            float y = r * sinf(theta);                                              //calculate the y component
            glVertex2f(2*x + 2*cx, 2*y + 2*cy);                                     //output vertex
        }
        glEnd();
    }
    else if(result==1){
         int cx=225;
        int cy=15;
        int num_segments=50;
        int r=25;
        glBegin(GL_LINE_STRIP);
        for (int i = 8; i <18; i++){
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);       //get the current angle
            float x = r * cosf(theta);                                              //calculate the x component
            float y = r * sinf(theta);                                              //calculate the y component
            glVertex2f(2*x + 2*cx, 2*y + 2*cy);                                     //output vertex
        }
        glEnd();
    }
    else if (result==0){
        glBegin(GL_LINE_LOOP);
    glVertex2f(430,75);
    glVertex2f(470,75);
    glEnd();
    }


}


void DrawString(void *font,const char s[],float x,float y){
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++){
		glutBitmapCharacter(font,s[i]);
	}
}

void DrawLines(){
	glBegin(GL_LINES);
	glColor3f(0,0,0);

    //Vertical
	glVertex2f(100,50);
	glVertex2f(100,350);
	glVertex2f(200,350);
	glVertex2f(200,50);

    //Horizontal
	glVertex2f(0,150);
	glVertex2f(300,150);
	glVertex2f(0,250);
	glVertex2f(300,250);
	glEnd();
}

bool CheckWinner(){
	int i, j;
	// horizontal check
	for(i=0;i<3;i++){
		for(j=1;j<3;j++){
			if(board[i][0]!=0 && board[i][0]==board[i][j]){
				if(j==2){
					return true;
				}
			}
			else
				break;
		}
	}
	// vertical check
	for(i=0;i<3;i++){
		for(j=1;j<3;j++){
			if(board[0][i]!=0 && board[0][i]==board[j][i]){
				if(j==2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2])
	|| (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
		return true;
	return false;
}

bool CheckIfDraw(){
	int i, j;
	bool draw;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(board[i][j]==0)
				return false;
		}
	}
	return true;
}

void Display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.75, 1, .80, 1);
	glColor3f(0, 0, 0);
	glLineWidth(5.0);
	if(over== false){
        if(turn == 1)
            DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 380);
        else
            DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 380);
    }
    DrawString(GLUT_BITMAP_HELVETICA_18, " ", 100, 380);
	DrawLines();
	DrawXO();
	if(over==false){
        if(turn==1){
	    glColor3f(1, 0, 0);
        DrawLeftStickMan(0,0,0,0);
        glColor3f(0, 0, 0);
        DrawRightStickMan(0,0,0,0);
        }
        else{
            glColor3f(0, 0, 0);
            DrawLeftStickMan(0,0,0,0);
            glColor3f(1, 0, 0);
            DrawRightStickMan(0,0,0,0);
        }
	}
	else{
            if(result==0){
                glColor3f(0, 0, 0);
                DrawLeftStickMan(0,0,0,0);
                DrawRightStickMan(0,0,0,0);
            }
            else if(result==1){
                glColor3f(1, 0, 0);
                DrawLeftStickMan(0,0,0,0);
                glColor3f(0, 0, 0);
                DrawRightStickMan(0,0,0,0);
            }
            else{
                glColor3f(0, 0, 0);
                DrawLeftStickMan(0,0,0,0);
                glColor3f(1, 0, 0);
                DrawRightStickMan(0,0,0,0);
            }
	}

	if(CheckWinner() == true){
		if(turn == 1){
			over = true;
			result = 2;
		}
		else{
			over = true;
			result = 1;
		}
	}
	else if(CheckIfDraw() == true){
		over = true;
		result = 0;
	}
	if(over == true){
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 105, 20);
		if(result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 100, -15);
		if(result == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 100, -15);
		if(result == 2)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 100, -15);
	}
	glutSwapBuffers();
}

void redraw(int posx1, int posy1, int posx2, int posy2){
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.75, 1, .80, 1);
    glLineWidth(5.0);
	if(over== false){
        if(turn == 1)
            DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 380);
        else
            DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 380);
    }
    DrawString(GLUT_BITMAP_HELVETICA_18, " ", 100, 380);
	DrawLines();
	DrawXO();
	if(over==false){
        if(turn==1){
	    glColor3f(1, 0, 0);
        DrawLeftStickMan(posx1,posy1,0,0);
        glColor3f(0, 0, 0);
        DrawRightStickMan(0,0,0,0);
        }
        else{
            glColor3f(0, 0, 0);
            DrawLeftStickMan(0,0,0,0);
            glColor3f(1, 0, 0);
            DrawRightStickMan(posx1,posy1,0,0);
        }
	}
	else{
            if(result==0){
                glColor3f(0, 0, 0);
                DrawLeftStickMan(0,0,0,0);
                DrawRightStickMan(0,0,0,0);
            }
            else if(result==1){
                glColor3f(1, 0, 0);
                DrawLeftStickMan(0,0,0,0);
                glColor3f(0, 0, 0);
                DrawRightStickMan(0,0,0,0);
            }
            else{
                glColor3f(0, 0, 0);
                DrawLeftStickMan(0,0,0,0);
                glColor3f(1, 0, 0);
                DrawRightStickMan(0,0,0,0);
            }
	}
	if(CheckWinner() == true){
		if(turn == 1){
			over = true;
			result = 2;
		}
		else{
			over = true;
			result = 1;
		}
	}
	else if(CheckIfDraw() == true){
		over = true;
		result = 0;
	}
	if(over == true){
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 105, 20);
		if(result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 100, -15);
		if(result == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 100, -15);
		if(result == 2)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 100, -15);
	}
	glutSwapBuffers();
}

void winner(int posx1, int posy1, int posx2, int posy2){
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(.75, 1, .80, 1);
    glLineWidth(5.0);
    DrawString(GLUT_BITMAP_HELVETICA_18, " ", 100, 380);
	DrawLines();
	DrawXO();
	if(result==1){
        glColor3f(1,0,0);
        DrawLeftStickMan(posx1,posy1,posx2,posy2);
        glColor3f(0,0,0);
        DrawRightStickMan(0,0,0,0);
	}
	else if(result==2){
        glColor3f(0,0,0);
        DrawLeftStickMan(0,0,0,0);
        glColor3f(1,0,0);
        DrawRightStickMan(posx1,posy1,posx2,posy2);
	}
	if(over == true){
		DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 105, 20);
		if(result == 0)
			DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 100, -15);
		if(result == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 100, -15);
		if(result == 2)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 100, -15);

        DrawString(GLUT_BITMAP_HELVETICA_18, "Play Again??", 100, -35);
	}
	glutSwapBuffers();
}

void Reshape(int x, int y){
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-300, 600,-250, 450);
	glMatrixMode(GL_MODELVIEW);
}

void OnKeyPress(unsigned char key, int x, int y){
    if(turn==1){
        redraw(0,-50,0,0); delay(200);
        redraw(0,0,0,0); delay(200);
    }
    else{
        redraw(0,-50,0,0); delay(200);
        redraw(0,0,0,0); delay(200);
    }
    if(over==true && result==1){
            winner(0,0,0,-100); delay(250);
            winner(0,-50,0,-50); delay(250);
            winner(0,-100,0,0); delay(250);
            winner(0,-50,0,-50); delay(250);
            winner(0,0,0,-100); delay(250);
            winner(0,0,0,0); delay(250);
    }
    else if(over==true && result==2){
            winner(0,0,0,-100); delay(250);
            winner(0,-50,0,-50); delay(250);
            winner(0,-100,0,0); delay(250);
            winner(0,-50,0,-50); delay(250);
            winner(0,0,0,-100); delay(250);
            winner(0,0,0,0); delay(250);
    }
    switch(key){
        case '7':
            if(turn==1 && over==false){
                if(board[2][0]==0){
                    board[2][0]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[2][0]==0){
                    board[2][0]=2;
                    turn=1;
                }
            }
            break;
        case '8':
            if(turn==1 && over==false){
                if(board[2][1]==0){
                    board[2][1]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[2][1]==0){
                    board[2][1]=2;
                    turn=1;
                }
            }
            break;
        case '9':
            if(turn==1 && over==false){
                if(board[2][2]==0){
                    board[2][2]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[2][2]==0){
                    board[2][2]=2;
                    turn=1;
                }
            }
            break;
        case '4':
            if(turn==1 && over==false){
                if(board[1][0]==0){
                    board[1][0]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[1][0]==0){
                    board[1][0]=2;
                    turn=1;
                }
            }
            break;
        case '5':
            if(turn==1 && over==false){
                if(board[1][1]==0){
                    board[1][1]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[1][1]==0){
                    board[1][1]=2;
                    turn=1;
                }
            }
            break;
        case '6':
            if(turn==1 && over==false){
                if(board[1][2]==0){
                    board[1][2]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[1][2]==0){
                    board[1][2]=2;
                    turn=1;
                }
            }
            break;
        case '1':
            if(turn==1 && over==false){
                if(board[0][0]==0){
                    board[0][0]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[0][0]==0){
                    board[0][0]=2;
                    turn=1;
                }
            }
            break;
        case '2':
            if(turn==1 && over==false){
                if(board[0][1]==0){
                    board[0][1]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[0][1]==0){
                    board[0][1]=2;
                    turn=1;
                }
            }
            break;
        case '3':
            if(turn==1 && over==false){
                if(board[0][2]==0){
                    board[0][2]=1;
                    turn=2;
                }
            }
            else if(turn==2 && over==false){
                if(board[0][2]==0){
                    board[0][2]=2;
                    turn=1;
                }
            }
            break;

            case 'y':
                if(over==true){
                    Intialize();
                    }
                break;
            case 'n':
                exit(0);
                break;

    }                     //End of SWITCH
}

int main(int argc, char **argv){
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(340,100);
	glutInitWindowSize(850,600);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}
