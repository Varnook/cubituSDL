#include "SDL.h"
#include "math.h"
#define _USE_MATH_DEFINES
double pi = M_PI;

void multMat(double A[4][4], double B[4][4]) {
	double res[4][4] = {0};

	for (int i = 0; i < 4; i++)
		for (int j = 0;  j < 4; j++)
			for (int k = 0; k < 4; k++)
				res[i][j] += A[i][k] * B[k][j];

	for (int i = 0; i < 4; i++)
		for (int j = 0;  j < 4; j++)
			A[i][j] = res[i][j];
}

void rot(double mat[4][4], double vec[4]) {
	double res[4] = {0};

	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++)
			res[i] += mat[i][j] * vec[j];
	
	for (int i = 0; i < 4; i++)
		vec[i] = res[i];
}

int main (int argc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	
	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);
	
	int arista = 50;
	double cubo[arista*12][4];

	int ang = 0;
	double theta;
	
	double persMat[4][4];

	double aOri[4][4];

	double deOri[4][4];

	double rotX[4][4];

	double rotY[4][4];

	while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

		for (int i = 0; i < arista; i++) {
			cubo[i + 50 * 0][0] = i+20; cubo[i + 50 * 0][1] = 20; cubo[i + 50 * 0][2] = 20; 	 cubo[i + 50 * 0][3] = 1;
			cubo[i + 50 * 1][0] = 20; cubo[i + 50 * 1][1] = i+20; cubo[i + 50 * 1][2] = 20;      cubo[i + 50 * 1][3] = 1;
			cubo[i + 50 * 2][0] = 20; cubo[i + 50 * 2][1] = 20; cubo[i + 50 * 2][2] = i+20;      cubo[i + 50 * 2][3] = 1;
			cubo[i + 50 * 3][0] = i+20; cubo[i + 50 * 3][1] = 70; cubo[i + 50 * 3][2] = 20;      cubo[i + 50 * 3][3] = 1;
			cubo[i + 50 * 4][0] = 70; cubo[i + 50 * 4][1] = i+20; cubo[i + 50 * 4][2] = 20;      cubo[i + 50 * 4][3] = 1;
			cubo[i + 50 * 5][0] = 70; cubo[i + 50 * 5][1] = 20; cubo[i + 50 * 5][2] = i+20;      cubo[i + 50 * 5][3] = 1;
			cubo[i + 50 * 6][0] = i+20; cubo[i + 50 * 6][1] = 20; cubo[i + 50 * 6][2] = 70;      cubo[i + 50 * 6][3] = 1;
			cubo[i + 50 * 7][0] = 20; cubo[i + 50 * 7][1] = i+20; cubo[i + 50 * 7][2] = 70;      cubo[i + 50 * 7][3] = 1;
			cubo[i + 50 * 8][0] = 20; cubo[i + 50 * 8][1] = 70; cubo[i + 50 * 8][2] = i+20;      cubo[i + 50 * 8][3] = 1;
			cubo[i + 50 * 9][0] = i+20; cubo[i + 50 * 9][1] = 70; cubo[i + 50 * 9][2] = 70;      cubo[i + 50 * 9][3] = 1;
			cubo[i + 50 * 10][0] = 70; cubo[i + 50 * 10][1] = i+20; cubo[i + 50 * 10][2] = 70;   cubo[i + 50 * 10][3] =1;
			cubo[i + 50 * 11][0] = 70; cubo[i + 50 * 11][1] = 70; cubo[i + 50 * 11][2] = i+20;   cubo[i + 50 * 11][3] =1;
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				persMat[i][j] = 0;
				aOri[i][j] = 0;
				deOri[i][j] = 0;
				rotX[i][j] = 0;
				rotY[i][j] = 0;
			}
		}
				

		persMat[0][0] = atan(pi/2.0);
		persMat[1][1] = atan(pi/2.0);
		persMat[2][2] = -90.0 / 70.0;
		persMat[2][3] = -1600.0 / 70.0;
		persMat[3][2] = -1;

		aOri[0][0] = 1;
		aOri[0][3] = -45;
		aOri[1][1] = 1;
		aOri[1][3] = -45;
		aOri[2][2] = 1;
		aOri[2][3] = -45;
		aOri[3][3] = 1;

		deOri[0][0] =   1;
		deOri[0][3] = 100;
		deOri[1][1] =   1;
		deOri[1][3] = 100;
		deOri[2][2] =   1;
		deOri[2][3] =  30;
		deOri[3][3] =   1;

		theta = (2.0 * pi * ang) / 360.0;

		rotX[0][0] =  1;
		rotX[1][1] =  cos(theta);
		rotX[1][2] = -sin(theta);
		rotX[2][1] =  sin(theta);
		rotX[2][2] =  cos(theta);
		rotX[3][3] =  1;

		rotY[0][0] =  cos(theta);
		rotY[0][2] =  sin(theta);
		rotY[1][1] =  1;
		rotY[2][0] = -sin(theta);
		rotY[2][2] =  cos(theta);
		rotY[3][3] =  1;

		ang++;
		ang %= 360;

		multMat(rotX, aOri);
		multMat(rotY, rotX);
		multMat(deOri, rotY);
		multMat(persMat, deOri);


		for (int i = 0; i < arista * 12; i++) {
			rot(persMat, cubo[i]);
			int light = cubo[i][0] + cubo[i][1] + cubo[i][2];
			SDL_SetRenderDrawColor(renderer, 0x01 * light, 0x01 * light, 0x01 * light, 0xFF);
			SDL_RenderDrawPoint(renderer, cubo[i][0], cubo[i][1]);
		}

        SDL_RenderPresent(renderer);
		SDL_Delay(16);
    }


	SDL_Quit();
	return 0;
}
