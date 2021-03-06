#include "SDL2/SDL.h"
#include "math.h"
#include <stdio.h>
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

	SDL_CreateWindowAndRenderer(10, 10, SDL_WINDOW_RESIZABLE, &window, &renderer);
	
	int arista = 50;
	double cubo[arista*12][4];

	int ang_x = 0, ang_y = 0;
	double theta_x, theta_y;

	int width, height;

	int max_x = 0, max_y = 0,
		min_x = 0, min_y = 0;

	int vert[8] = {0, 150, 200, 299, 300, 349, 550, 599};

	int pos_x = 0, pos_y = 0;
	int mov_x = 1, mov_y = 1;

	int color_x = 0, color_y = 0;
	int dec_c_x = 0, dec_c_y = 0;

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
  			cubo[i + 50 * 0][0]  = i+20; cubo[i + 50 * 0][1]  = 20;   cubo[i + 50 * 0][2]  = 20;   cubo[i + 50 * 0][3]  = 1;
  			cubo[i + 50 * 1][0]  = 20;   cubo[i + 50 * 1][1]  = i+20; cubo[i + 50 * 1][2]  = 20;   cubo[i + 50 * 1][3]  = 1;
  			cubo[i + 50 * 2][0]  = 20;   cubo[i + 50 * 2][1]  = 20;   cubo[i + 50 * 2][2]  = i+20; cubo[i + 50 * 2][3]  = 1;
  			cubo[i + 50 * 3][0]  = i+20; cubo[i + 50 * 3][1]  = 70;   cubo[i + 50 * 3][2]  = 20;   cubo[i + 50 * 3][3]  = 1;
  			cubo[i + 50 * 4][0]  = 70;   cubo[i + 50 * 4][1]  = i+20; cubo[i + 50 * 4][2]  = 20;   cubo[i + 50 * 4][3]  = 1;
  			cubo[i + 50 * 5][0]  = 70;   cubo[i + 50 * 5][1]  = 20;   cubo[i + 50 * 5][2]  = i+20; cubo[i + 50 * 5][3]  = 1;
  			cubo[i + 50 * 6][0]  = i+20; cubo[i + 50 * 6][1]  = 20;   cubo[i + 50 * 6][2]  = 70;   cubo[i + 50 * 6][3]  = 1;
  			cubo[i + 50 * 7][0]  = 20;   cubo[i + 50 * 7][1]  = i+20; cubo[i + 50 * 7][2]  = 70;   cubo[i + 50 * 7][3]  = 1;
			cubo[i + 50 * 8][0]  = 20;   cubo[i + 50 * 8][1]  = 70;   cubo[i + 50 * 8][2]  = i+20; cubo[i + 50 * 8][3]  = 1;
			cubo[i + 50 * 9][0]  = i+20; cubo[i + 50 * 9][1]  = 70;   cubo[i + 50 * 9][2]  = 70;   cubo[i + 50 * 9][3]  = 1;
			cubo[i + 50 * 10][0] = 70;   cubo[i + 50 * 10][1] = i+20; cubo[i + 50 * 10][2] = 70;   cubo[i + 50 * 10][3] = 1;
			cubo[i + 50 * 11][0] = 70;   cubo[i + 50 * 11][1] = 70;   cubo[i + 50 * 11][2] = i+20; cubo[i + 50 * 11][3] = 1;
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

		deOri[0][0] = 1;
		deOri[0][3] = pos_x;
		deOri[1][1] = 1;
		deOri[1][3] = pos_y;
		deOri[2][2] = 1;
		deOri[2][3] = 30;
		deOri[3][3] = 1;


		theta_x = (2.0 * pi * ang_x) / 360.0;
		theta_y = (2.0 * pi * ang_y) / 360.0;

		rotX[0][0] =  1;
		rotX[1][1] =  cos(theta_x);
		rotX[1][2] = -sin(theta_x);
		rotX[2][1] =  sin(theta_x);
		rotX[2][2] =  cos(theta_x);
		rotX[3][3] =  1;

		rotY[0][0] =  cos(theta_y);
		rotY[0][2] =  sin(theta_y);
		rotY[1][1] =  1;
		rotY[2][0] = -sin(theta_y);
		rotY[2][2] =  cos(theta_y);
		rotY[3][3] =  1;

		ang_x += mov_x;
		ang_y += mov_y;

		multMat(rotX, aOri);
		multMat(rotY, rotX);
		multMat(deOri, rotY);
		multMat(persMat, deOri);

		if ((pos_x - 1) % 256 == 255) { dec_c_x = !dec_c_x; }
		if ((pos_y - 1) % 256 == 255) { dec_c_y = !dec_c_y; }

		color_x = pos_x % 256;
		color_x = dec_c_x ? 256 - color_x : color_x;
		color_y = pos_y % 256;
		color_y = dec_c_y ? 256 - color_y : color_y;

		for (int i = 0; i < arista * 12; i++) {
			rot(persMat, cubo[i]);
			SDL_SetRenderDrawColor(renderer, color_x, color_y, cubo[i][2], 0x88);
			SDL_RenderDrawPoint(renderer, cubo[i][0], cubo[i][1]);
		}

		SDL_GetWindowSize(window, &width, &height);

		max_x = cubo[0][1];
		max_y = max_x; min_x = max_x; min_y = max_x;

		for (int i = 0; i < 8; i++) {
			max_x = max_x < cubo[vert[i]][0] ? cubo[vert[i]][0] : max_x;
			max_y = max_y < cubo[vert[i]][1] ? cubo[vert[i]][1] : max_y;
			min_x = min_x > cubo[vert[i]][0] ? cubo[vert[i]][0] : min_x;
			min_y = min_y > cubo[vert[i]][1] ? cubo[vert[i]][1] : min_y;
		}

		if (max_x >= width)
			mov_x = -1;
		if (min_x == 0)
			mov_x =  1;
		if (max_y >= height)
			mov_y = -1;
		if (min_y == 0)
			mov_y =  1;
		pos_x += mov_x;
		pos_y += mov_y;

        SDL_RenderPresent(renderer);
		SDL_Delay(16);
    }


	SDL_Quit();
	return 0;
}
