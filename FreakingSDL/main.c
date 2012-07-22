#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdbool.h>

bool collision

int main()
{
	int height,width;
    float delay=1;
    
	width=720;
	height=480;
    
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

 	float my,mx;
 	mx=width/2;
 	my=height-30;
    
// ball vars
    float ballx=100;
    float bally=30;
    float ballhw=30;
    float vellx=2;
    float velly=2;
    int goal=0;
    
 	SDL_Event event;
	while (1){  //sdl loop
// logic 
		while ( SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){  // X button
				return 0;
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE){
				//printf("%d\n", event.key.keysym.sym );
				return 0;
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP){
				delay+=0.1;
			}
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN){
                delay-=0.1;

			}
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.sym == SDLK_LEFT){
					left = true;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT){
					right = true;
				}
			} else if (event.type == SDL_KEYUP){
				if (event.key.keysym.sym == SDLK_LEFT){
					left = false;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT){
					right = false;
				}
			}
		}

        
// bar logic
		if (left==true && mx>0){
			mx-=0.5;
		}
		if (right==true && mx<width-120){
			mx+=0.5;
		}
        
// ball logic
        ballx+=vellx;
        bally+=velly;
        if (bally == my+ballhw && (ballx > mx && ballx < mx+120)){
            velly=-velly;
            printf("bingo");
        }
        else
            
            if (bally > height){
                printf("%d ",++goal);
                bally=1;
                ballx=100;
            }
        else
        if ((ballx < 0) || (ballx > width-ballhw)) {
            vellx=-vellx;
        } else
        if ( bally < 0){
            velly=-velly;
        }

        
		glClear(GL_COLOR_BUFFER_BIT); // start renderig


		glPushMatrix(); // Start phase
 		
 		glOrtho(0,width,height,0,-1,1); //set da matrix
	
// BAR DRAWING 		//bar width near 40px & height near 20px
 		glColor4ub(0,0,0,255);
 		glBegin(GL_QUADS);

 		glVertex2f(mx,my);
 		glVertex2f(mx+120,my);
 		glVertex2f(mx+120,my+20);
 		glVertex2f(mx,my+20);

 		glEnd();

        glColor4ub(128,128, 0,255);
        glBegin(GL_QUADS);
        glVertex2f(ballx, bally);
        glVertex2f(ballx+ballhw, bally);
        glVertex2f(ballx+ballhw, bally+ballhw);
        glVertex2f(ballx, bally+ballhw);
        glEnd();

		glPopMatrix(); // end
		SDL_GL_SwapBuffers();
		SDL_Delay(1.1);
	}

	

	SDL_Quit();
    return 0;
}