#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include"static.cpp"

/* narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
*/
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
	y = SCREEN_HEIGHT - y - 1;
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	y = SCREEN_HEIGHT - y - 1;
	dest.x = x  - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};

// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	if ((x >= 0) && (x < SCREEN_WIDTH) && (y >= 0) && (y < SCREEN_HEIGHT)) {
		y = SCREEN_HEIGHT - y - 1;
		int bpp = surface->format->BytesPerPixel;
		Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
		*(Uint32*)p = color;
	}	
};

// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};

void DrawLine_dot(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		if (x % 2 == 0 && y % 2 == 0) {
			DrawPixel(screen, x, y, color);
		}
		
		x += dx;
		y += dy;
	};
};

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor, int thickness) {                 
	int i;
	for (i = 0; i < thickness; i++)
	{
		DrawLine(screen, x + i, y, k, 0, 1, outlineColor);
		DrawLine(screen, x + l - 1 - i, y, k, 0, 1, outlineColor);
		DrawLine(screen, x, y + i, l, 1, 0, outlineColor);
		DrawLine(screen, x, y + k - 1 - i, l, 1, 0, outlineColor);
	}
	/*
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + 1, y, k, 0, 1, outlineColor);

	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 2, y, k, 0, 1, outlineColor);

	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + 1, l, 1, 0, outlineColor);

	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 2, l, 1, 0, outlineColor);
	*/
	//for(i = y + 1; i < y + k - 1; i++)
	//	DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};

void DrawRectangle_dot(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor, int thickness) {
	int i;
	for (i = 0; i < thickness; i++)
	{
		DrawLine_dot(screen, x + i, y, k, 0, 1, outlineColor);
		DrawLine_dot(screen, x + l - 1 - i, y, k, 0, 1, outlineColor);
		DrawLine_dot(screen, x, y + i, l, 1, 0, outlineColor);
		DrawLine_dot(screen, x, y + k - 1 - i, l, 1, 0, outlineColor);
	}
};

////////////////////////////////////

double Count_radius(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


void Adjust_cam_to_horse(int horse_y, int &cam_y) {
	if		(horse_y - cam_y > SCREEN_HEIGHT - CAM_ADJUST_HEIGHT)	{ cam_y += CAM_ADJUST_SPEED; }
	else if (horse_y - cam_y < CAM_ADJUST_HEIGHT				)	{ cam_y -= CAM_ADJUST_SPEED; }
}

void Adjust_cam_to_horse_x(int horse_x, int& cam_x) {
	cam_x = horse_x - HORSE_START_POS_X;
}

void Draw_obstacles(SDL_Surface *screen, Uint32 color1, Uint32 color2, int distance, int cam_y, obstacle obs_arr[], star star_arr[], fairy fairy_arr[], SDL_Surface *star_img, SDL_Surface *fairy_img ) {
for (int i = 0; i < OBSTACLE_NUM; i++)
{
	if ((obs_arr[i].left_x < distance + SCREEN_WIDTH) &&
		(obs_arr[i].right_x > distance) &&
		(obs_arr[i].left_y < SCREEN_HEIGHT + cam_y) &&
		(obs_arr[i].right_y > cam_y))
	{
		int width = obs_arr[i].right_x - obs_arr[i].left_x;
		int height = obs_arr[i].right_y - obs_arr[i].left_y;
		DrawRectangle(screen, obs_arr[i].left_x - distance, obs_arr[i].left_y - cam_y, width, height, color1, color2, 3);
		//DrawRectangle_dot(screen, obs_arr[i].left_x - distance - 1, obs_arr[i].left_y - cam_y - 1, width + 2, height + 2, color1, color2, 2);
	}
}
for (int i = 0; i < STAR_NUM; i++)
{
	if ((star_arr[i].hid == 1) &&
		(star_arr[i].x < distance + SCREEN_WIDTH) &&
		(star_arr[i].x > distance) &&
		(star_arr[i].hid == 1))
	{
		DrawSurface(screen, star_img, star_arr[i].x - distance, star_arr[i].y - cam_y);
		//DrawRectangle_dot(screen, obs_arr[i].left_x - distance - 1, obs_arr[i].left_y - cam_y - 1, width + 2, height + 2, color1, color2, 2);
	}
}
for (int i = 0; i < FAIRY_NUM; i++)
{
	if ((fairy_arr[i].hid == 1) &&
		(fairy_arr[i].x < distance + SCREEN_WIDTH) &&
		(fairy_arr[i].x > distance) &&
		(fairy_arr[i].hid == 1))
	{
		DrawSurface(screen, fairy_img, fairy_arr[i].x - distance, fairy_arr[i].y - cam_y);
		//DrawRectangle_dot(screen, obs_arr[i].left_x - distance - 1, obs_arr[i].left_y - cam_y - 1, width + 2, height + 2, color1, color2, 2);
	}
}
}

void Adjust_player_vars(animal& player, double delta, double distance) {
	if (player.state != 2) {
		if (distance > 1) {
			player.speed += log(log(distance)) / 100;
		}
		player.vec_time += delta * VEC_TIME_MLTP;
		double old_vec = player.vec;
		if (player.vec > VEC_MAX_DESC)
		{
			player.vec -= VEC_MLTP * player.vec_time * player.vec_time;
		}
		if (player.vec * old_vec <= 0) { player.vec_time = delta; }
		player.y += player.vec;
		if (player.vec < -0.05) { player.state = 4; }
	}
	else if (player.state == 2) {
		player.jump = 0;
		if (player.state_time > 0) { player.state_time -= delta; }
		else { player.state = 1; player.speed /= HORSE_BURST_MLTP; }
	}
}

void Check_surfaces(animal& player, obstacle obs_arr[], double distance) {
	/*
	if (player.y <= GROUND_HEIGHT + HORSE_SMALL_HEIGHT / 2 && player.vec <= 0)
	{
		player.y = GROUND_HEIGHT + HORSE_SMALL_HEIGHT / 2;
		player.vec = 0;
		player.vec_time = 0;
	}
	*/
	if (player.state != 2) {
		for (int i = 0; i < OBSTACLE_NUM; i++)
		{
			int coll_h = (obs_arr[i].right_y - obs_arr[i].left_y) / 2;
			if (distance + HORSE_SMALL_WIDTH > obs_arr[i].left_x &&
				distance + HORSE_LEGS_END < obs_arr[i].right_x &&
				player.y - HORSE_SMALL_HEIGHT / 2 <= obs_arr[i].right_y &&
				player.y + HORSE_SMALL_HEIGHT / 2 >  obs_arr[i].left_y + coll_h &&
				player.vec <= 0)
			{
				player.y = obs_arr[i].right_y + HORSE_SMALL_HEIGHT / 2;
				player.vec = 0;
				player.vec_time = 0;
				player.state = 1;
				player.jump = 0;
				player.burst = 0;
			}
			else if (distance + HORSE_SMALL_WIDTH > obs_arr[i].left_x &&
				distance + HORSE_LEGS_END < obs_arr[i].right_x &&
				player.y - HORSE_SMALL_HEIGHT / 2 < obs_arr[i].right_y - coll_h &&
				player.y + HORSE_SMALL_HEIGHT >= obs_arr[i].left_y &&
				player.vec > 0)
			{
				player.y = obs_arr[i].left_y - HORSE_SMALL_HEIGHT / 2;
				player.vec = 0;
				player.vec_time = 0;
				player.state = 1;
				player.jump = 0;
				player.burst = 0;
			}
		}
	}
}

int  Check_collisions(animal& player, obstacle obs_arr[], star star_arr[], fairy fairy_arr[], double distance, double &points, int &star_p, int &fairy_p, int &popup, double &popup_t, blast &expl) {
	int result = 1;
	int coll_w;
	if (player.y <= 0) { result = 2; return result; }
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		coll_w = obs_arr[i].right_x - obs_arr[i].left_x;
		if ((distance + HORSE_SMALL_WIDTH + HORSE_COLL_RANGE_H		> obs_arr[i].left_x) &&
			(distance + HORSE_SMALL_WIDTH + HORSE_COLL_RANGE_H		< obs_arr[i].left_x + coll_w / 2) &&
			(player.y + HORSE_SMALL_HEIGHT / 2 - HORSE_COLL_RANGE_V > obs_arr[i].left_y) &&
			(player.y - HORSE_SMALL_HEIGHT / 2 + HORSE_COLL_RANGE_V < obs_arr[i].right_y))
		{
			result = 2; // 2 - player collided with obstacle
			expl.x = distance + HORSE_SMALL_WIDTH / 2;
			expl.y = player.y;
			expl.time = 0.5;
			expl.id = 1;
			return result;
		}
	}
	for (int i = 0; i < STAR_NUM; i++)
	{
		if (star_arr[i].hid == 1 && Count_radius(distance + HORSE_LEGS_END + HORSE_SMALL_WIDTH / 2, player.y, star_arr[i].x, star_arr[i].y) < STAR_COLL_RAD)
		{
			if (player.state == 2) {
				// POINTS ++ //
				points += star_p;
				popup = star_p;
				popup_t = 2;
				star_p += 100;
				star_arr[i].hid = 2;
				expl.x = star_arr[i].x;
				expl.y = star_arr[i].y;
				expl.time = 0.5;
				expl.id = 2;
				result = 3;
				return result;
			}
			else {
				result = 4;
				return result;
			}
		}
	}
	for (int i = 0; i < FAIRY_NUM; i++)
	{
		if (fairy_arr[i].hid == 1 && Count_radius(distance + HORSE_LEGS_END + HORSE_SMALL_WIDTH / 2, player.y, fairy_arr[i].x, fairy_arr[i].y) < FAIRY_COLL_RAD)
		{
			// POINTS ++ //
			points += fairy_p;
			popup = fairy_p;
			popup_t = 2;
			fairy_p += 10;
			fairy_arr[i].hid = 2;
			result = 5;
			return result;
		}
	}
	return result;
}

void Traverse_for_star(FILE* config_star) {
	for (;;) {
		if (fgetc(config_star) == ASCII_HASHTAG) { break; }
	}
	fgetc(config_star);
}

void Traverse_for_fairy(FILE* config_fairy) {
	for (;;) {
		if (fgetc(config_fairy) == ASCII_HASHTAG) { break; }
	}
	for (;;) {
		if (fgetc(config_fairy) == ASCII_HASHTAG) { break; }
	}
	fgetc(config_fairy);
}

int Randomize(int min, int max) {
	return rand() % (max - min) + min;
}

int File_to_int(FILE *configfile) {
	int num = 0;
	int in;
	for (;;)
	{
		in = fgetc(configfile);
		if (in < ASCII_ZERO || in > ASCII_NINE) { break; }
		num *= 10;
		num += in - ASCII_ZERO;
	}
	return num;
}

void Create_obstacle(int distance, obstacle &obs, FILE *configfile, int &loop) {
	int in = fgetc(configfile);
	if (in == ASCII_SLASH)
	{
		obs.left_x  = File_to_int(configfile) + loop;
		obs.left_y  = File_to_int(configfile);
		obs.right_x = File_to_int(configfile) + loop;
		obs.right_y = File_to_int(configfile);
		in = fgetc(configfile);
	}
	else
	{
		rewind(configfile);
		loop = distance;
		/*
		obs.left_x = Randomize(distance + SCREEN_WIDTH, distance + SCREEN_WIDTH * 2);
		obs.left_y = Randomize(GROUND_HEIGHT, GROUND_HEIGHT + SCREEN_HEIGHT);
		obs.right_x = obs.left_x + Randomize(OBS_RAND_WIDTH_MIN, OBS_RAND_WIDTH_MAX);
		obs.right_y = obs.left_y + Randomize(OBS_RAND_HEIGHT_MIN, OBS_RAND_HEIGHT_MAX);
		*/
	}
}

void Create_star(int distance, star &star, FILE* config_star, int& loop) {
	int in = fgetc(config_star);
	if (in == ASCII_SLASH)
	{
		star.x = File_to_int(config_star) + loop;
		star.y = File_to_int(config_star);
		in = fgetc(config_star);
		if (rand() % 100 > 66) { star.hid = 1; }
		else { star.hid = 2; }
	}
	else
	{
		rewind(config_star);
		Traverse_for_star(config_star);
	}
}

void Create_fairy(int distance, fairy &fairy, FILE* config_fairy, int& loop) {
	int in = fgetc(config_fairy);
	if (in == ASCII_SLASH)
	{
		fairy.x = File_to_int(config_fairy) + loop;
		fairy.y = File_to_int(config_fairy);
		in = fgetc(config_fairy);
		if (rand() % 100 > 66) { fairy.hid = 1; }
		else { fairy.hid = 2; }
	}
	else
	{
		rewind(config_fairy);
		Traverse_for_fairy(config_fairy);
	}
}

void Update_obstacles(int distance, obstacle obs_arr[],star star_arr[],fairy fairy_arr[], FILE *configfile, FILE *config_star, FILE *config_fairy, int &loop, int &star_p, int &fairy_p) {
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		if (obs_arr[i].right_x < distance) {
			Create_obstacle(distance, obs_arr[i], configfile, loop);
		}
	}
	for (int i = 0; i < STAR_NUM; i++)
	{
		if (star_arr[i].x < distance) {
			if (star_arr[i].hid == 1) { star_p = 100; }
			Create_star(distance, star_arr[i], config_star, loop);

		}
	}
	for (int i = 0; i < FAIRY_NUM; i++)
	{
		if (fairy_arr[i].x < distance) {
			if (fairy_arr[i].hid == 1) { fairy_p = 10; }
			Create_fairy(distance, fairy_arr[i], config_fairy, loop);
		}
	}
}

void New_game(animal &player, double &distance, double &worldTime, double &delta,int &loop, obstacle obs_arr[], star star_arr[], fairy fairy_arr[], FILE *configfile, FILE *config_star, FILE *config_fairy) {
	distance = 0;
	worldTime = 0;
	delta = 0;
	loop = 0;
	player.x = HORSE_SMALL_WIDTH / 2 + HORSE_START_POS_X;
	player.y = GROUND_HEIGHT + HORSE_SMALL_HEIGHT / 2;
	player.vec = 0;
	player.vec_time = 0;
	player.state = 1;
	player.state_time = 0;
	player.speed = HORSE_START_SPEED;
	
	for (int i = 0; i < OBSTACLE_NUM; i++)
	{
		obs_arr[i].right_x = 0;
	}
	for (int i = 0; i < STAR_NUM; i++)
	{
		star_arr[i].x = 0;
		star_arr[i].hid = 1;
	}
	for (int i = 0; i < FAIRY_NUM; i++)
	{
		fairy_arr[i].x = 0;
		fairy_arr[i].hid = 1;
	}
	rewind(configfile);
	rewind(config_star);
	Traverse_for_star(config_star);
	rewind(config_fairy);
	Traverse_for_fairy(config_fairy);
}

// main ////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	int t1, t2, quit, frames, rc, controls_type;
	double delta, worldTime, fpsTimer, fps, distance;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *horse;
	SDL_Surface *eti;
	SDL_Surface *star_img;
	SDL_Surface *fairy_img;
	SDL_Surface *background;
	SDL_Surface *burst;
	SDL_Texture *scrtex;
	SDL_Window	*window;
	SDL_Renderer *renderer;
	srand(time(NULL));

	FILE *configfile;
	FILE *config_star;
	FILE *config_fairy;
	FILE *leaderboard;
	FILE *leaderboard_save;
	int loop = 0;
	configfile = fopen("lvlconfig.txt", "r");
	config_star = fopen("lvlconfig.txt", "r");
	config_fairy = fopen("lvlconfig.txt", "r");

	if(configfile == NULL || config_star == NULL || config_fairy == NULL) {
		SDL_Quit();
		return 1;
	}
	Traverse_for_fairy(config_fairy);
	Traverse_for_star(config_star);

	/* okno konsoli nie jest widoczne, jeøeli chcemy zobaczyÊ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniÊ na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	*/
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}

	/* tryb pe≥noekranowy / fullscreen mode
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	*/	                                 
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy≥πczenie widocznoúci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	horse = SDL_LoadBMP("./img/horse_small.bmp");
	if(horse == NULL) {
		printf("SDL_LoadBMP(hirse_small.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horse2;
	horse2 = SDL_LoadBMP("./img/horse_small2.bmp");
	if (horse2 == NULL) {
		printf("SDL_LoadBMP(hirse_small.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horse3;
	horse3 = SDL_LoadBMP("./img/horse_small3.bmp");
	if (horse3 == NULL) {
		printf("SDL_LoadBMP(hirse_small.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horsej;
	horsej = SDL_LoadBMP("./img/horse_smallj.bmp");
	if (horsej == NULL) {
		printf("SDL_LoadBMP(horsej.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horseb;
	horseb = SDL_LoadBMP("./img/horse_smallb.bmp");
	if (horseb == NULL) {
		printf("SDL_LoadBMP(horseb.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horsef;
	horsef = SDL_LoadBMP("./img/horse_smallf.bmp");
	if (horsef == NULL) {
		printf("SDL_LoadBMP(horsef.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horsee;
	horsee = SDL_LoadBMP("./img/horse_smalle.bmp");
	if (horsee == NULL) {
		printf("SDL_LoadBMP(horsee.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* star_b;
	star_b = SDL_LoadBMP("./img/star_b.bmp");
	if (star_b == NULL) {
		printf("SDL_LoadBMP(star_b.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	star_img = SDL_LoadBMP("./img/star.bmp");
	if (star_img == NULL) {
		printf("SDL_LoadBMP(star.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	fairy_img = SDL_LoadBMP("./img/fairy.bmp");
	if (fairy_img == NULL) {
		printf("SDL_LoadBMP(star.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	burst = SDL_LoadBMP("./img/burst.bmp");
	if (burst == NULL) {
		printf("SDL_LoadBMP(burst.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	eti = SDL_LoadBMP("./img/eti.bmp");
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	background = SDL_LoadBMP("./img/background.bmp");
	if (background == NULL) {
		printf("SDL_LoadBMP(background.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface *menu_bg;
	menu_bg = SDL_LoadBMP("./img/menu_bg.bmp");
	if (menu_bg == NULL) {
		printf("SDL_LoadBMP(menu_bg.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* horse_big;
	horse_big = SDL_LoadBMP("./img/horse_big.bmp");
	if (horse_big == NULL) {
		printf("SDL_LoadBMP(horse_big.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* logo;
	logo = SDL_LoadBMP("./img/logo.bmp");
	if (logo == NULL) {
		printf("SDL_LoadBMP(logo.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	SDL_Surface* heart;
	heart = SDL_LoadBMP("./img/heart.bmp");
	if (heart == NULL) {
		printf("SDL_LoadBMP(heart.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	controls_type = 2;

	animal player;
	player.x = HORSE_SMALL_WIDTH / 2 + HORSE_START_POS_X;
	player.y = HORSE_START_POS_Y;
	player.vec = 0;
	player.vec_time = 0;
	player.state = 1;
	player.state_time = 0;
	player.speed = HORSE_START_SPEED;
	player.hp = HORSE_START_HP;
	
	int cam_x = CAM_START_POS_X;
	int cam_y = CAM_START_POS_Y;

	obstacle obs_arr[OBSTACLE_NUM];
	for (int i = 0; i < OBSTACLE_NUM; i++) {
		obs_arr[i].right_x = 0;
	}
	star star_arr[STAR_NUM];
	for (int i = 0; i < STAR_NUM; i++) {
		star_arr[i].x = 0;
		star_arr[i].hid = 1;
	}
	fairy fairy_arr[FAIRY_NUM];
	for (int i = 0; i < FAIRY_NUM; i++) {
		fairy_arr[i].x = 0;
		fairy_arr[i].hid = 1;
	}
	double coll_id = 1;
	double points = 0;
	int game_part = 1;
	delta = 0;
	char c;
	int points_int;
	int leaderboard_page = 0;

	int star_p = 100;
	int fairy_p = 10;
	int popup = 0;
	double popup_t = 0;
	blast expl;
	expl.id = 1;
	expl.time = 0;
	expl.x = 0;
	expl.y = 0;
	/////////////////////////////////////////////////////////////////////////////////////////
	while(!quit) {

		t2 = SDL_GetTicks();
		delta = (t2 - t1) * 0.001;
		t1 = t2;
		/* w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplyna≥ od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		*/
		SDL_FillRect(screen, NULL, czarny);

		if (game_part == 1) {
			DrawSurface(screen, menu_bg, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			DrawSurface(screen, horse_big, 100, 200);
			DrawSurface(screen, logo, SCREEN_WIDTH / 2, 400);
			sprintf(text, "N - nowa gra  ##  ESC - wyjdz");
			DrawString(screen, 200, 50, text, charset);
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if		(event.key.keysym.sym == SDLK_n) {
						game_part = 2;
						New_game(player, distance, worldTime, delta, loop, obs_arr, star_arr, fairy_arr, configfile, config_star, config_fairy);
					}
					else if (event.key.keysym.sym == SDLK_ESCAPE) { quit = 1; }
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		if (game_part == 2) {

			worldTime += delta;

			if (controls_type == 2) { distance += player.speed * delta; }
			points += player.speed * delta / 100;

			DrawSurface(screen, background, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

			if (player.state == 2) { DrawSurface(screen, burst, player.x, player.y - cam_y); DrawSurface(screen, horseb, player.x - cam_x, player.y - cam_y);
			}
			if(player.state == 3) { DrawSurface(screen, horsej, player.x - cam_x, player.y - cam_y); }
			if (player.state == 1) {
				if		(((int)distance / 20) % 3 == 0) { DrawSurface(screen, horse, player.x - cam_x, player.y - cam_y); }
				else if (((int)distance / 20) % 3 == 1) { DrawSurface(screen, horse3, player.x - cam_x, player.y - cam_y); }
				else if (((int)distance / 20) % 3 == 2) { DrawSurface(screen, horse2, player.x - cam_x, player.y - cam_y); }
			}
			if( player.state == 4) { DrawSurface(screen, horsef, player.x - cam_x, player.y - cam_y);  }
			

			Draw_obstacles(screen, zielony, zielony, distance, cam_y, obs_arr, star_arr, fairy_arr, star_img, fairy_img);
			for (int i = 0; i < player.hp; i++)
			{
				DrawSurface(screen, heart, 60 + i * 60, 430);
			}

			if (popup_t > 0) {
				sprintf(text, "+ %.0li", popup);
				DrawString(screen, 500, 100, text, charset);
				popup_t -= delta;
			}

			if (expl.time > 0) {
				if (expl.id == 1) {
					DrawSurface(screen, horsee, player.x - cam_x, player.y - cam_y);
				}
				if (expl.id == 2) {
					DrawSurface(screen, star_b, expl.x - distance - cam_x, expl.y - cam_y);
				}
				expl.time -= delta;
			}

			fpsTimer += delta;
			if(fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};
		

			sprintf(text, "casz: %.0lf", worldTime);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 10, text, charset);
			sprintf(text, "Punkty: %.0lf", points);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 26, text, charset);

			if (controls_type == 1) {
				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE)	quit = 1;
						else if (event.key.keysym.sym == SDLK_UP) { player.y += HORSE_RET_SPEED; }
						else if (event.key.keysym.sym == SDLK_DOWN) { player.y -= HORSE_RET_SPEED; }
						else if (event.key.keysym.sym == SDLK_RIGHT) { player.x += HORSE_RET_SPEED; distance += HORSE_RET_SPEED; }
						else if (event.key.keysym.sym == SDLK_LEFT) { player.x -= HORSE_RET_SPEED; distance -= HORSE_RET_SPEED; }
						else if (event.key.keysym.sym == SDLK_d) { controls_type = 2; }
						else if (event.key.keysym.sym == SDLK_n) { player.hp = HORSE_START_HP;  points = 0; New_game(player, distance, worldTime, delta, loop, obs_arr, star_arr, fairy_arr, configfile, config_star, config_fairy); }
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};
			}
			if (player.state != 2 && controls_type == 2) {
				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE)	quit = 1;
						else if (event.key.keysym.sym == SDLK_z) {
							if (player.jump < 1)
							{
								player.jump = 1;
								if (player.state == 1) { player.jump = 0; }
								player.vec = VEC_JUMP;
								player.vec_time = 0;
								player.state = 3;
							}
							
						
						}
						else if (event.key.keysym.sym == SDLK_d) { controls_type = 1; }
						else if (event.key.keysym.sym == SDLK_n) { player.hp = HORSE_START_HP;  points = 0;  New_game(player, distance, worldTime, delta, loop, obs_arr, star_arr, fairy_arr, configfile, config_star, config_fairy); }
						else if (event.key.keysym.sym == SDLK_x) {
							if (player.burst < 1)
							{
								player.vec = 0;
								player.vec_time = 0;
								player.state = 2;
								player.speed *= HORSE_BURST_MLTP;
								player.state_time = HORSE_BURST_TIME;
								player.burst = 1;
							}
							
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};
			}

			coll_id = Check_collisions(player, obs_arr, star_arr, fairy_arr, distance, points, star_p, fairy_p, popup, popup_t, expl);
			if (coll_id == 2 || coll_id == 4) { game_part = 3; player.hp--; New_game(player, distance, worldTime, delta, loop, obs_arr, star_arr, fairy_arr, configfile, config_star, config_fairy); }
			if (player.hp <= 0) { game_part = 1; player.hp = HORSE_START_HP; points = 0; }
			if (controls_type == 2) {
				Check_surfaces(player, obs_arr, distance);
				Adjust_player_vars(player, delta, distance);
			}
			if (controls_type == 1) {
				Adjust_cam_to_horse_x(player.x, cam_x);
			}
			Adjust_cam_to_horse(player.y, cam_y);
			Update_obstacles(distance, obs_arr, star_arr, fairy_arr, configfile, config_star, config_fairy, loop, star_p, fairy_p);
			frames++;

		} // end if ( game_part ) //
		if (game_part == 3) {
			sprintf(text, "N - nowa gra  ##  ESC - wyjdz");
			DrawString(screen, 200, 50, text, charset);
			sprintf(text, "G - graj dalej");
			DrawString(screen, 250, 400, text, charset);
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_n) {
						game_part = 2;
						points = 0;
						player.hp = HORSE_START_HP;
						New_game(player, distance, worldTime, delta, loop, obs_arr, star_arr, fairy_arr, configfile, config_star, config_fairy);
					}
					else if (event.key.keysym.sym == SDLK_ESCAPE) { quit = 1; }
					else if (event.key.keysym.sym == SDLK_g) { game_part = 2; }
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		
		
		
		
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		
		
	};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	};
