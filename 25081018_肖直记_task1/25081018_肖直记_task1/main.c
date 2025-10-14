#include <REGX52.H>
#include <key.h>
#include <delay.h>

// 当前展示的模块ID
int module = 1;
#define MAX_MODULE_INDEX 4

// 软件计时器（约65毫秒后重置）int:16位
int timer_count = 0;
bool is_later(int t1, int t2)
{
	// 时间刻 t1 是否在 t2 之后，不考虑溢出，则只能在一分钟内保持有效
	return t1>t2;
}


// 流水跑马时间间隔 50~450
int wait_time_interval = 50;
// 流水灯状态
char water_light_status = 0x0f;

// 流水灯
void module1()
{
	// 调整时间
//	if (IsKeyDown(1)) {
//		wait_time_interval += 100;
//		if (wait_time_interval > 450) {
//			wait_time_interval = 50;
//		}
//	}
}


// 跑马灯状态
char horse_light_status = 0x01;

// 跑马灯(按第一个键调整时间间隔)
void module2()
{
	int i = 0;
	while (i<3) {
		i++;
		delay(wait_time_interval/3);
		// 调整时间
		if (IsKeyDown(3)) {
			wait_time_interval += 100;
			if (wait_time_interval > 450) {
				wait_time_interval = 50;
			}
		}
	}
	horse_light_status <<= 1;
	if (horse_light_status == 0) {
		horse_light_status = 1;
	}
	P2 = ~horse_light_status;
}


// 线性呼吸灯
void module3()
{
}


// 二进制要显示的值
char bin_value = 0;

// 二进制显示
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
		timer_count++;
		// 模块切换
		if (IsKeyDown(2)) {
			module++;
			if (module > MAX_MODULE_INDEX) {
				module = 1;
			}
			// 每次切换重置一次全局变量
			bin_value = 0;
			horse_light_status = 0x01;
			water_light_status = 0x0f;
			wait_time_interval = 50;
			P2 = 0xff;
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