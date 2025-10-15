#include <REGX52.H>
#include <key.h>
#include <delay.h>

// 当前展示的模块ID
int module = 1;
#define MAX_MODULE_INDEX 4

// 软件计时器（约65毫秒后重置）int:16位
unsigned int timer_count = 0;
//int is_later(int t1, int t2)
//{
//	// 时间刻 t1 是否在 t2 之后；不考虑溢出，则只能在一分钟内保持有效
//	return t1>t2;
//}


// 流水跑马时间间隔 50~450
int wait_time_interval = 50;
// 流水灯状态
unsigned char water_light_status = 0x0f;
// 流水跑马灯上次运行的时刻
unsigned int last_light_time = 0;

// 流水灯(按下第一个键调整时间间隔)
void module1()
{
	// 调整时间
	if (IsKeyDown(1)) {
		wait_time_interval += 100;
		if (wait_time_interval > 450) {
			wait_time_interval = 50;
		}
	}
	// 时间是否过了一个间隔，是否应该“流水”一格
	if (timer_count - last_light_time < wait_time_interval)
		return;
	last_light_time = timer_count;
	// 主要逻辑
	if (water_light_status & 0x80) {
		// 1000 0000
		water_light_status <<= 1;
		water_light_status += 1;
	} else {
		water_light_status <<= 1;
	}
	P2 = ~water_light_status;
}


// 跑马灯状态
char horse_light_status = 0x01;

// 跑马灯(按第一个键调整时间间隔)
void module2()
{
	// 调整时间间隔(按键事件不应阻塞)
	if (IsKeyDown(1)) {
		wait_time_interval += 100;
		if (wait_time_interval > 450) {
			wait_time_interval = 50;
		}
	}
	// 时间是否过了一个间隔，是否应该“跑马”一次
	if (timer_count - last_light_time < wait_time_interval)
		return;
	last_light_time = timer_count;
	// 主要逻辑
	horse_light_status <<= 1;
	if (horse_light_status == 0) {
		horse_light_status = 1;
	}
	P2 = ~horse_light_status;
}


// 刷新间隔（17ms--60 fps），一亮一灭为一次刷新
int fresh_interval = 17;
// 呼吸灯亮度(0~17)，最小单位是毫秒，则最大亮度不是足够大的整数
int breathing_light = 0;
// 呼吸灯亮度变化速度（用于加亮度或减亮度）
int breathing_velocity = 1;
// 上一次呼吸灯刷新时间刻
unsigned int last_fresh_time = 0;
// 上一次呼吸灯亮度变化时间刻
unsigned int last_animate_time = 0;

// 线性呼吸灯(按第一个键调整呼吸（亮-灭-亮）时间间隔)
void module3()
{
	// 调整呼吸时间间隔
	if (wait_time_interval == 50)
		wait_time_interval = 2000;// 默认设置为2秒（实际时间受运行其他指令的影响，如控制语句的条件判断、跳转等，实测2.5秒）
	if (IsKeyDown(1)) {
		wait_time_interval += 100;
		if (wait_time_interval > 2000) {
			wait_time_interval = 500;
		}
	}
	// wait_time_interval 作为呼吸（亮-灭-亮）时间间隔，单位ms
	// 使亮度变化
	if (timer_count - last_animate_time > wait_time_interval/fresh_interval/2) {
		last_animate_time = timer_count;
		if (breathing_light>=fresh_interval)
			breathing_velocity = -1;
		if (breathing_light<=0)
			breathing_velocity = 1;
		breathing_light += breathing_velocity;
	}
	// 使灯刷新
	if (timer_count - last_fresh_time > fresh_interval-breathing_light) {
		// 保持灭一定时间，时间长度为 fresh_interval-breathing_light，再亮灯
		P2_0 = 0;
	}
	if (timer_count - last_fresh_time > fresh_interval) {
		last_fresh_time = timer_count;// 完成一次刷新
		// 保持亮一定时间，时间长度为 fresh_interval，再灭灯
		P2_0 = 0xff;
	}
}


// 二进制要显示的值
char bin_value = 0;

// 二进制显示(按下第一个键使二进制值加1)
void module4()
{
	P2 = ~bin_value;
	if (IsKeyDown(1)) {
		bin_value++;
		// 8位二进制数，溢出自动变成0
	}
}


void main()
{
	while (1) {
		// 计时器计数加一
		delay(1);
		timer_count++;
		// 模块切换
		if (IsKeyDown(2)) {
			module++;
			if (module > MAX_MODULE_INDEX) {
				module = 1;
			}
			// 每次切换重置一次全局变量
			timer_count = 0;			// 计数器清零
			wait_time_interval = 50;	// 流水、跑马、呼吸时间间隔 50~450
			water_light_status = 0x0f;	// 流水灯状态
			last_light_time = 0;		// 流水跑马灯上次运行的时刻
			horse_light_status = 0x01;	// 跑马灯状态
			fresh_interval = 17;// 刷新间隔（17ms--60 fps），一亮一灭为一次刷新
			breathing_light = 0;		// 呼吸灯亮度(0~255)
			breathing_velocity = 1;		// 呼吸灯亮度变化速度（用于加亮度或减亮度）
			last_fresh_time = 0;		// 上一次呼吸灯刷新时间刻
			last_animate_time = 0;		// 上一次呼吸灯亮度变化时间刻
			bin_value = 0;				// 二进制要显示的值
			P2 = 0xff;					// 灭灯
		}
		// 运行特定模块
		switch (module) {
		case 1:
			module1();
			break;
		case 2:
			module2();
			break;
		case 3:
			module3();
			break;
		case 4:
			module4();
			break;
		default:
			break;
		}
	}
    while(1);
}