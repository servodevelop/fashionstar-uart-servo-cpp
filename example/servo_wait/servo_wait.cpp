/* 
 * 测试wait()函数,轮询角度直到舵机旋转到目标位置
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


int main(){
	// 打印例程信息
	cout << "Test Wait" << endl;

    cout << "Set Angle = 90.0" << endl;
    servo0.setRawAngle(90.0); // 设置舵机的角度
    servo0.wait();
    protocol.delay_ms(500);
    servo0.queryRawAngle();
    cout << "Real Angle = " <<  servo0.curRawAngle << endl;
     
    protocol.delay_ms(2000);

    cout << "Set Angle = -90.0" << endl;
    servo0.setRawAngle(-90.0); // 设置舵机的角度
    servo0.wait();
    protocol.delay_ms(500);
    servo0.queryRawAngle();
    cout << "Real Angle = " <<  servo0.curRawAngle << endl;

    protocol.delay_ms(2000);
}