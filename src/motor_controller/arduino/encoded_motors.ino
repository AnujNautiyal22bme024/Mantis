#include<ros.h>
#include<std_msgs/Int32.h>
#include<RMCS2303drive.h>

RMCS2303 rmcs;  
SoftwareSerial myserial(2,3); 
SoftwareSerial myserial1(5,6);

//parameter Settings "Refer datasheet for details"
byte slave_id=7;
byte slave_id1=0;
int INP_CONTROL_MODE=257;           
int PP_gain=32;
int PI_gain=16;
int VF_gain=32;
int LPR=334;
int acceleration=5000;
int speed=8000;

long int Current_position;
long int Current_Speed;

 volatile unsigned long totalPulsesLeft = 0;
 volatile unsigned long totalPulsesRight = 0;
 int motorVelocityLeft=0;
 int motorVelocityRight=0;

//  void interruptFunctionLeft();
//  void interruptFunctionRight();

 ros::NodeHandle nh;

 void callBackFunctionMotorLeft(const std_msgs::Int32 &motorVelocityLeftROS){
  motorVelocityLeft=motorVelocityLeftROS.data;
 }

  void callBackFunctionMotorRight(const std_msgs::Int32 &motorVelocityRightROS){
  motorVelocityRight=motorVelocityRightROS.data;
 }

 std_msgs::Int32 leftEncoderROS;
 ros::Publisher leftEncoderROSPublisher("left_encoder_pulses", &leftEncoderROS);

 std_msgs::Int32 rightEncoderROS;
 ros::Publisher rightEncoderROSPublisher("right_encoder_pulses", &rightEncoderROS);

 ros::Subscriber<std_msgs::Int32> leftMotorROSSubscriber("left_motor_velocity", &callBackFunctionMotorLeft);
 ros::Subscriber<std_msgs::Int32> rightMotorROSSubscriber("right_motor_velocity", &callBackFunctionMotorRight);

 void setup() {
  // left motor
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   Serial.println("RMCS-2303 Speed control mode demo\r\n\r\n");

   //rmcs.begin(&Serial1,9600);    //Uncomment if using hardware serial port for mega2560:Serial1,Serial2,Serial3 and set baudrate. Comment this line if Software serial port is in use
   rmcs.begin(&myserial,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed);    //Uncomment to write parameters to drive. Comment to ignore.
   rmcs.READ_PARAMETER(slave_id);

  //  right motor
   rmcs.Serial_selection(1);       //Serial port selection:0-Hardware serial,1-Software serial
   rmcs.Serial0(9600);             //Set baudrate for usb serial to monitor data on serial monitor
   Serial.println("RMCS-2303 Speed control mode demo\r\n\r\n");

   //rmcs.begin(&Serial1,9600);    //Uncomment if using hardware serial port for mega2560:Serial1,Serial2,Serial3 and set baudrate. Comment this line if Software serial port is in use
   rmcs.begin(&myserial1,9600);     //Uncomment if using software serial port. Comment this line if using hardware serial.
   rmcs.WRITE_PARAMETER(slave_id,INP_CONTROL_MODE,PP_gain,PI_gain,VF_gain,LPR,acceleration,speed);    //Uncomment to write parameters to drive. Comment to ignore.
   rmcs.READ_PARAMETER(slave_id);

  // nh.getHardware()->setBaud(9600);

  nh.initNode();
  nh.advertise(leftEncoderROSPublisher);
  nh.advertise(rightEncoderROSPublisher);

  nh.subscribe(leftMotorROSSubscriber);
  nh.subscribe(rightMotorROSSubscriber);

 }

 void loop(){
  nh.spinOnce();
   Serial.println("Sending speed command - 8000 RPM");
   rmcs.Speed(slave_id,motorVelocityLeft);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   rmcs.Speed(slave_id1,motorVelocityLeft);                   //Set speed within range of 0-65535 or 0-(maximum speed of base motor)
   rmcs.Enable_Digital_Mode(slave_id,0);        //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 
   rmcs.Enable_Digital_Mode(slave_id1,0);        //To enable motor in digital speed control mode. 0-fwd,1-reverse direction. 
   
   delay(3000);
   Current_Speed=rmcs.Speed_Feedback(slave_id); 
   Serial.print("Current Speed feedback : ");
   Serial.println(Current_Speed);

   delay(5000);

  leftEncoderROS.data=totalPulsesLeft;
  rightEncoderROS.data=totalPulsesRight;
  leftEncoderROSPublisher.publish(&leftEncoderROS);
  rightEncoderROSPublisher.publish(&rightEncoderROS);

  delay(10);

 }

// void interruptFunctionLeft(){
//     totalPulsesLeft = totalPulsesLeft + 1;
//  }

// void interruptFunctionRight(){
//     totalPulsesRight = totalPulsesRight + 1;
// }
