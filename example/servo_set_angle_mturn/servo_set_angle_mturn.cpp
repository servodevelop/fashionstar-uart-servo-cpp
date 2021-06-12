/* 
 * 设置舵机的角度(多圈模式)
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
#define DAMPING_POWER 800 		// 阻尼模式的功率

using namespace std;
using namespace fsuservo;

// 创建协议对象
FSUS_Protocol protocol(SERVO_PORT_NAME, FSUS_DEFAULT_BAUDRATE);
// 创建一个舵机对象
FSUS_Servo servo0(SERVO_ID, &protocol);

// 轨迹规划参数定义
uint16_t interval;  // 运行周期 单位ms 
uint16_t t_acc;     // 加速时间 单位ms
uint16_t t_dec;     // 减速时间 单位ms
float velocity;         // 目标转速 单位°/s

/* 等待并报告当前的角度*/
void waitAndReport(FSUS_Servo* servo){
    servo->wait();          // 等待舵机旋转到目标角度
	cout << "Real Angle = " << servo->curRawAngle << ", Target Angle = " << servo->targetRawAngle << endl;
    protocol.delay_ms(2000); // 暂停2s
}

int main(){
	// 打印例程信息
	cout << "Set Servo Angle" << endl;
    
	cout << "Set Angle = 900 deg" << endl;
    servo0.setRawAngleMTurn(900.0);  // 设置舵机的角度
    waitAndReport(&servo0);

	cout << "Set Angle = -900.0 deg" << endl;
    servo0.setRawAngleMTurn(-900.0);
    waitAndReport(&servo0);

	cout << "Set Angle = 900 deg - Set Interval = 10s" << endl;
    interval = 10000;
    t_acc = 100;
    t_dec = 100;
    servo0.setRawAngleMTurnByInterval(900, interval, t_acc, t_dec, 0);
    waitAndReport(&servo0);

	cout << "Set Angle = -900 deg - Set Velocity = 200 dps" << endl;
    velocity = 200.0;
    t_acc = 100;
    t_dec = 100;
    servo0.setRawAngleMTurnByVelocity(-900, velocity, t_acc, t_dec, 0);
    waitAndReport(&servo0);
    	
}