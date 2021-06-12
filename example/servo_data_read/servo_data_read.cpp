/*
 * 设置舵机为阻尼模式
 * 调整参数`DAMPING_POWER`感受不同的阻尼力
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: kyle.xing@fashionstar.com.hk
 * 更新时间: 2021/06/12
 **/
#include <iostream>
#include <string>

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


int main(){
	// 打印例程信息
	cout << "Servo Data Read" << endl;
	// 设置舵机角度(限制功率)
	servo0.setAngle(0.0,  1000, 800); 

	while(true){
		// 信息查询
		uint16_t voltage = servo0.queryVoltage();
		uint16_t current = servo0.queryCurrent();
		uint16_t power = servo0.queryPower();
		uint16_t temperature = servo0.queryTemperature();

		// 打印状态信息
		cout << "voltage: " << voltage << endl;
		cout << "current: " << current << endl;
		cout << "power: " << power << endl;
		cout << "temperature: " << temperature << endl;

		// 延时1s
    	protocol.delay_ms(1000);
	}	
}