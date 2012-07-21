#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
<<<<<<< HEAD
#include <stdbool.h>

void main(void)
{
	int height,width;
=======

void main(void)
{
	int mx,my,height,width;
>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a

	width=300;
	height=300;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE,8);
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE,32);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,16);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);

	SDL_WM_SetCaption( "test", NULL);

	SDL_SetVideoMode(width,height,32,SDL_OPENGL);

	glClearColor(1,1,1,1);
	glViewport(0,0,width,height);

	//shader model
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//disable depht checking
	glDisable(GL_DEPTH_TEST);
 	
 	bool left,right;
 	left=right=false;

<<<<<<< HEAD
 	float my,mx;
=======
>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a
 	mx=width/2;
 	my=height-20;

 	SDL_Event event;
<<<<<<< HEAD
	while (1){  //sdl loop
		while ( SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){  // X button
=======
	while (1){
		while ( SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a
				return;
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE){
				//printf("%d\n", event.key.keysym.sym );
				return;
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP){
				glClearColor(0,0,1,1);
			}

			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.sym == SDLK_LEFT){
					left = true;
				}
<<<<<<< HEAD
				else if (event.key.keysym.sym == SDLK_RIGHT){
=======
				else if (event.key.keysym.sym == SDLK_RIGTH){
>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a
					right = true;
				}
			} else if (event.type == SDL_KEYUP){
				if (event.key.keysym.sym == SDLK_LEFT){
					left = false;
				}
<<<<<<< HEAD
				else if (event.key.keysym.sym == SDLK_RIGHT){
					right = false;
				}
			}
		}

		if (left==true && mx>0){
			mx-=0.5;
		}
		if (right==true && mx<width){
			mx+=0.5;
=======
				else if (event.key.keysym.sym == SDLK_RIGTH){
					right = false;
				}
			}


>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a
		}
		glClear(GL_COLOR_BUFFER_BIT);
		

		glPushMatrix(); // Start phase
 		
 		glOrtho(0,width,height,0,-1,1); //set da matrix
 /*		glColor4ub(255,0,0,255);
 		
 		glBegin(GL_QUADS); //GL_POINTS LINES STRIPS etc
 
 		glVertex2f(5,5);
 		glVertex2f(200,5);

 		glColor4ub(1,1,200,255);

 		glVertex2f(200,200);
 		glVertex2f(5,200);

 		glEnd();       // end drawing

 		glColor4ub(0,255,255,255);
 		glBegin(GL_LINES);
 		glVertex2f(10,10);
 		glVertex2f(50,50);

 		glColor4ub(1,200,1,255);
 		glVertex2f(290,290);
 		glVertex2f(240,240);
 		glEnd();
*/		
<<<<<<< HEAD
// BAR DRAWING 		//bar width near 40px & height near 20px
 		glColor4ub(0,0,0,255);
 		glBegin(GL_QUADS);

 		glVertex2f(mx-20,my-10);
 		glVertex2f(mx+20,my-10);
 		glVertex2f(mx+20,my+10);
 		glVertex2f(mx-20,my+10);
=======
// BAR DRAWING
 		int bxb,byb,bxe,bye;    //bar x begin, bar x or y end
 		//bar width near 40px & height near 20px
 		glColor4ub(0,0,0,255);
 		glBegin(GL_QUADS);

 		glVertex2f(bxb=mx-20,byb=my-10);
 		glVertex2f(bxe=m,100);
 		glVertex2f(200,250);
 		glVertex2f(100,250);
>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a

 		glEnd();




		glPopMatrix(); // end
		SDL_GL_SwapBuffers();
<<<<<<< HEAD
		SDL_Delay(1);
=======
>>>>>>> edd022e25f93a59bb2bff840aaa38ebf2b7fd31a
	}

	

	SDL_Quit();
}