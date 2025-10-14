#include <key.h>
#include <REGX52.H>

// 上一次按键检测是否是按下状态
static int is_key1_down = 0;
static int is_key2_down = 0;
static int is_key3_down = 0;
static int is_key4_down = 0;

int IsKeyDown(int id)
{
	// 按键1
	// 按键第一次物理导通
	if (is_key1_down==0) {
		if (id==1 && !P3_1) {
			is_key1_down = 1;
			return 1;
		}
	} else {
		// 按键已导通，检测是否已经放开
		if (id==1 && P3_1) {
			is_key1_down = 0;
			return 0;
		}
	}
	
	// 按键2
	if (is_key2_down==0) {
		if (id==2 && !P3_0) {
			is_key2_down = 1;
			return 1;
		}
	} else {
		if (id==2 && P3_0) {
			is_key2_down = 0;
			return 0;
		}
	}
	
	// 按键3
	if (is_key3_down==0) {
		if (id==3 && !P3_2) {
			is_key3_down = 1;
			return 1;
		}
	} else {
		if (id==3 && P3_2) {
			is_key3_down = 0;
			return 0;
		}
	}
	
	// 按键4
	if (is_key4_down==0) {
		if (id==4 && !P3_3) {
			is_key4_down = 1;
			return 1;
		}
	} else {
		if (id==4 && P3_3) {
			is_key4_down = 0;
			return 0;
		}
	}
	return 0;
}