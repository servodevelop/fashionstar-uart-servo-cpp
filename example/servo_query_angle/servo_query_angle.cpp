/*
 * 舵机角度回读实验
 * 用手掰动舵机, 角度回读并将角度读数通过SPI发送
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2021/06/12
 **/
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
#define DAMPING_POWER 800 		// 阻尼模式的功率

using namespace std;
using namespace fsuservo;

// 创建协议对象
FSUS_Protocol protocol(SERVO_PORT_NAME, FSUS_DEFAULT_BAUDRATE);
// 创建一个舵机对象
FSUS_Servo servo0(SERVO_ID, &protocol);

int main(){
	// 打印例程信息
	cout << "Query Servo Angle" << endl;
	// 设置舵机为阻尼模式
	servo0.setDamping(DAMPING_POWER);

	while(true){
		// 查询(更新)舵机角度
		servo0.queryRawAngle();
		// 输出查询信息
		cout << "Servo Angle: " <<  servo0.curRawAngle << endl;
		// 延时1s
		protocol.delay_ms(1000);
	}
	
}