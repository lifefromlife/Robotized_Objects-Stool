#include <ros.h>                //ros 라이브러리
#include <std_msgs/Float64.h>   //Float64.h 라이브러리 
#include <std_msgs/String.h>    //String 라이브러리 

ros::NodeHandle nh;    //rosserial 할 때 필수로 입력해두기

std_msgs::Float64 Sensor1;  //센서1은 초음파센서1를 임의로 붙임
std_msgs::Float64 Sensor2;  //센서2는 초음파센서2를 임의로 붙임  
std_msgs::String str_msg;   //String 꼴로 전달-> 즉 문자임

ros::Publisher sensor1("sensor1", &Sensor1);   //센서1에 대해서 rosserial로 값 전달 
ros::Publisher sensor2("sensor2", &Sensor2);   //센서2에 대해서 rosserial로 값 전달
ros::Publisher height("height", &str_msg);     //height에 대해서 rosserial로 값 전달

char child[13] = "child";     //child 14개 인덱스 배열  
char adult[13] = "adult";     //adult 14개 인덱스 배열

const int trigPin[2] = {50,58};   //opencr 보드 50,58 연결
const int echoPin[2] = {51,59};   //opencr 보드 51,59 연결

long duration[2]={0,0};           //duration[2] 0,0 인덱스 배열 형성 
float distance[2]={0,0};          //distance[2] 0,0 인덱스 배열 형성 

float Distance_sensing(int i) {         //Distance_sensing(int i)라는 함수를 만들어서 Distance_sensing(i) 값을 입력하면 작동되게 함.
  
  digitalWrite(trigPin[i], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin[i], LOW);
  duration[i] = pulseIn(echoPin[i], HIGH);
  return duration[i] * 0.034 / 2;           //이 부분은 통으로 가져다 쓰기

}

void setup() {
  nh.initNode();
  nh.advertise(sensor1);
  nh.advertise(sensor2);
  nh.advertise(height);
  pinMode(trigPin[0], OUTPUT);              //trigPin[0]  
  pinMode(echoPin[0], INPUT);               //echoPin[0]
  pinMode(trigPin[1], OUTPUT);              //trigPin[1] 
  pinMode(echoPin[1], INPUT);               //echoPin[1] --> 초음파 센서 1번 2번 지정  
  Serial.begin(57600);
}

void loop() {

  Sensor1.data = Distance_sensing(0);    
  Sensor2.data = Distance_sensing(1);

  if (Sensor2.data<20){              //초음파 센서2의 거리가 20보다 작으면 즉, 앞에 물체가 감지가 되면 adult라는 str_msg.data를 만들고
    str_msg.data = adult;            //height.publish로 str_msg를 전달한다. 
    height.publish( &str_msg );
  }
  else if(Sensor1.data<20){          //초음파 센서1 거리가 20보다 작으면 즉, 앞에 물체가 감지가 되면 child라는 str_msg.data를 만들고
    str_msg.data = child;            //height라는 이름으로 str_msg를 전달한다. 나중에 rospy.Subscriber("height", Int64, self.callback과 같은 함수명)으로 받을 수 있다.
    height.publish( &str_msg );
  }

  sensor1.publish(&Sensor1);         //Sensor1에 대한 값도 sensor1이라는 이름으로 publish  나중에 rospy.Subscriber("sensor1", Int64, self.callback과 같은 함수명)으로 받을 수 있다.
  sensor2.publish(&Sensor2);         //Sensor2에 대한 값도 sensor2라는 이름으로 publish 나중에  rospy.Subscriber("sensor2", Int64, self.callback과 같은 함수명)으로 받을 수 있다.
  
  nh.spinOnce();                    //void loop 마지막에 nh.spinOnce();를 붙여준다 
  delay(100);                       //delay는 100 주면 됨
}
