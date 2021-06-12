/*
 * 测试舵机轮式模式
 * 提示: 拓展板上电之后, 记得按下Arduino的RESET按键
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2021/06/12
 */

#include <iostream>

#include "CSerialPort/SerialPort.h"
#include "FashionStar/UServo/FashionStar_UartServoProtocol.h"
#include "FashionStar/UServo/FashionStar_UartServo.h"

// 串口总线舵机配置
// 设置串口总线Servo转接板的端口号
#ifdef _WIN32
#define SERVO_PORT_NAME "COM8" 	        // Windows下端口号名称 COM{}
#else
#define SERVO_PORT_NAME "/dev/ttyUSB0" 	// Linux下端口号名称 /dev/ttyUSB{}
#endif
#define SERVO_ID 0 				        // 舵机ID号

using namespace std;
using namespace fsuservo;

// 创建协议对象
FSUS_Protocol protocol(SERVO_PORT_NAME, FSUS_DEFAULT_BAUDRATE);
// 创建一个舵机对象
FSUS_Servo servo0(SERVO_ID, &protocol);

/* 轮子持续旋转指令与停止指令测试 */
void testWheelRunAndStop(){
    servo0.wheelRun(FSUS_CCW); // 轮子持续旋转, 方向为逆时针
    protocol.delay_ms(2000);            // 等待2s
    servo0.wheelStop();
    protocol.delay_ms(2000);            // 等待2s
    servo0.wheelRun(FSUS_CW); // 轮子持续旋转
    protocol.delay_ms(2000);            // 等待2s
    servo0.wheelStop();
    protocol.delay_ms(2000);            // 等待2s
}

/* 测试轮子旋转特定的时间 */
void testWheelRunNTime(){
    servo0.wheelRunNTime(FSUS_CW, 5000); // 轮子持续旋转5s(顺时针)
    protocol.delay_ms(5000);                         
    servo0.wheelRunNTime(FSUS_CCW, 5000); // 轮子持续旋转5s(逆时针)
    protocol.delay_ms(5000);
}

/* 测试轮子旋转特定的圈数 */
void testWheelRunNCircle(){
    uint16_t nCircle = 2; // 旋转圈数
    uint16_t delayMsEstimate = (uint16_t)(360.0 * nCircle / servo0.speed * 1000); // 估计旋转的时间
    servo0.wheelRunNCircle(FSUS_CW, 2); // 轮子持续旋转2圈(顺时针)
    protocol.delay_ms(delayMsEstimate);             // 等到轮子旋转到特定的位置 

    servo0.wheelRunNCircle(FSUS_CCW, 2);// 轮子持续旋转2圈(逆时针)
    protocol.delay_ms(delayMsEstimate);             // 等到轮子旋转到特定的位置}
}


int main(){
	// 打印例程信息
	cout << "Test Wait" << endl;

    // 测试持续旋转与停止
    // testRunAndStop();

    // 测试旋转特定的时间
    // testWheelRunNTime();
    
    // 测试旋转特定的圈数
    testWheelRunNCircle();
}