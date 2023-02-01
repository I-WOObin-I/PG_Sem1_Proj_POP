#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480

#define HORSE_SMALL_WIDTH	96
#define HORSE_SMALL_HEIGHT	58
#define HORSE_START_POS_X	20
#define HORSE_START_POS_Y	150
#define HORSE_LEGS_END		30
#define HORSE_START_SPEED	200
#define HORSE_MAX_SPEED		500
#define	HORSE_BURST_MLTP	5
#define HORSE_BURST_TIME	0.2
#define HORSE_RET_SPEED		15
#define HORSE_COLL_RANGE_H	0
#define HORSE_COLL_RANGE_V  5
#define HORSE_START_HP		3

#define VEC_TIME_MLTP		1
#define VEC_MAX_DESC		-1
#define VEC_MLTP			1
#define VEC_JUMP			2

#define CAM_START_POS_X		0
#define CAM_START_POS_Y		0
#define CAM_ADJUST_HEIGHT	140
#define CAM_ADJUST_SPEED	2

#define GROUND_HEIGHT		0

#define OBSTACLE_NUM		5
#define OBS_RAND_WIDTH_MIN	80
#define OBS_RAND_WIDTH_MAX	800
#define OBS_RAND_HEIGHT_MIN	50
#define OBS_RAND_HEIGHT_MAX	100
#define OBS_RAND_HEIGHT_OG	800
#define OBS_RAND_DISTANCE	800

#define STAR_NUM			2
#define STAR_COLL_RAD		45
#define FAIRY_NUM			2
#define FAIRY_COLL_RAD		45

#define ASCII_ZERO			48
#define ASCII_NINE			57
#define ASCII_SLASH			47
#define ASCII_MINUS			45
#define ASCII_HASHTAG		35

struct obstacle {
	int left_x;
	int left_y;
	int right_x;
	int right_y;
};

struct star {
	int x;
	int y;
	int hid;
};

struct fairy {
	int x;
	int y;
	int hid;
};

struct animal {
	double x;
	double y;
	double speed;
	double vec;
	double vec_time;
	int state;
	int jump;
	int burst;
	double state_time;
	int hp;
};

struct blast {
	int x;
	int y;
	double time;
	int id;
};