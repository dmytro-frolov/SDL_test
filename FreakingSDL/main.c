#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
//#include <SDL_image/SDL_image.h>
//#include <string.h>

#include <stdbool.h>

#define BRICKS 36

bool collision(int Ax,int Ay,int Aw,int Ah,int Bx,int By,int Bw, int Bh)
{
	if (Ay+Ah < By) return false; // up
	if (Ax+Aw < Bx) return false; // left
	if (Ay > By+Bh) return false; // down
	if (Ax > Bx+Bw) return false; // rigth

	return true;
}

GLuint imload()
{
    SDL_Surface *image;
    image=IMG_Load("bar.png");
    
    SDL_DisplayFormatAlpha(image);
    
    unsigned int object(0);
    
    glGenTextures(1, &object);
    
    glBindTexture(GL_TEXTURE_2D, object);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    
    //Free surface
    SDL_FreeSurface(image);
    
    return object;
    SDL_BlitSurface(image,0,320,0);
}

struct brick {
    float x,y, width, height;
    bool alive;
} bricks[BRICKS];

int main(int argc, char* args[])
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

	glClearColor(1,1,1,255);
	glViewport(0,0,width,height);

	//shader model
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


    
    
	//disable depht checking
	glDisable(GL_DEPTH_TEST);
 	
 	bool left,right;
 	left=right=false;
    
// bar vars
 	float my,mx;
 	mx=width/2;
 	my=height-30;
    
// ball vars
    float ballx=10;
    float bally=200;
    float ballhw=30;
    float vellx=2;
    float velly=2;
    int goal=0;

// briks initialization
    char deadcount=0;
    int i,x,y;
    for (i=0,x=8,y=10;i<BRICKS;i++,x+=10+30){
        if (x>width-31){
            y+=50;
            x=8;
        } 
        bricks[i].y=y;
        bricks[i].x=x;
        bricks[i].width=30;
        bricks[i].height=30;
        bricks[i].alive=true;

    }
 /*   int flags=IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if(initted&flags != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    */
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
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE){
                glClearColor(1,1,1,255);
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
			mx-=1.5;
		}
		if (right==true && mx<width-120){
			mx+=1.5;
		}
        
// ball logic

        bally+=velly;     
        if (bally > height){
            printf("%d ",++goal);
            bally=1;
            ballx=100;
        }

        if (bally > height){
        	velly=-velly;
        }
        else if ((ballx < 0) || (ballx > width-ballhw)) {
            vellx=-vellx;
        } else
        if ( bally < 0){
            velly=-velly;
        }

        if (collision(ballx,bally,ballhw,ballhw,mx,my,120,20)==true){
        	velly=-velly;
        }
        
      
    
// brick logic 
        for (i=0;i<BRICKS;i++){
            if ( bricks[i].alive==true && collision(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, ballx, bally, ballhw, ballhw)==true){
                velly=-velly;
                bricks[i].alive=false;
                deadcount++;
                if (deadcount==BRICKS) return 0;
                break;
            }
            
        }
        
        ballx+=vellx;
        for (i=0;i<BRICKS;i++){
            if ( bricks[i].alive==true && collision(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, ballx, bally, ballhw, ballhw)==true){
                vellx=-vellx;
                bricks[i].alive=false;
                deadcount++;
                if (deadcount==BRICKS) return 0;
                break;
            }
            
        }
        
		glClear(GL_COLOR_BUFFER_BIT); // start renderig
		glPushMatrix(); // Start phase
 		glOrtho(0,width,height,0,-1,1); //set da matrix
	
// BAR DRAWING 		//bar width near 120px & height near 20px
 		glColor4ub(12,12,120,255);
 		glBegin(GL_QUADS);

 		glVertex2f(mx,my);
 		glVertex2f(mx+120,my);
 		glVertex2f(mx+120,my+20);
 		glVertex2f(mx,my+20);

 		glEnd();

        glColor4ub(128,128, 0,255);  // ball rendering
        glBegin(GL_QUADS);
        glVertex2f(ballx, bally);
        glVertex2f(ballx+ballhw, bally);
        glVertex2f(ballx+ballhw, bally+ballhw);
        glVertex2f(ballx, bally+ballhw);
        glEnd();
// bricks drawing        
        glColor4ub(0,0,0,255);
        glBegin(GL_QUADS);
        for (i=0;i<BRICKS;i++){
            if (bricks[i].alive==false) continue;
            (i%2==0)?glColor4ub(15, 200, 1, 255):glColor4ub(0, 10, 200, 255);
            glVertex2f(bricks[i].x, bricks[i].y);
            glVertex2f(bricks[i].x+bricks[i].width, bricks[i].y);
            glVertex2f(bricks[i].x+bricks[i].width, bricks[i].y+bricks[i].height);
            glVertex2f(bricks[i].x, bricks[i].y+bricks[i].height);
            
        }
        glEnd();
        

		glPopMatrix(); // end
		SDL_GL_SwapBuffers();
		SDL_Delay(4.5);
	}

	

	SDL_Quit();
    return 0;
}