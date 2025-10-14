#ifndef KEY_H
#define KEY_H

// 检测独立按键是否按下；不能判断多个按键同时按下；按键按下后只取一次有效（这不是消抖）
// 参数：按键ID（1~4）
// 返回：0-未按下，1-按键按下
int IsKeyDown(int id);

#endif