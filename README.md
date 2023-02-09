# Robotized_Stool
Collaborative Human-Robot Interaction Design for Robotic Library



### 의자 경로
```
/home/kist/catkin_ws/src/icsr/scripts 
```
경로에 설정하였습니다.

```
cd ~/catkin_ws/src/icsr/scripts
```
후에 수정 가능

```
sudo nano jjmaster.py
```

혹은

```
sudo gedit jjmaster.py
```

jjmaster.py 파일 외에 github에서  받으시는 파일이면 stool.py로 실행해주세요.

### 의자 구동 방식

1. 터틀봇을 의자에 탑재 (이 때 의자는 거꾸로 뒤집은 상태에서 터틀봇을 해당 위치에 맞게 배치하고 다시 뒤집음) 
2. 터틀봇을 가만히 놔두고 의자를 터틀봇 위로 바로 씌워버리려고 하면 라즈베리파이랑 openCR, LDS-01 라이다 센서가 부딪힐 수 있기 때문에 1번 방식대로 해주세요. 

##### 새 터미널
```
roscore
```
##### 새 터미널
```
ssh ubuntu@172.16.0.112  
```
(키리랩 노트북으로 하고 와이파이는 LVL로 함.)
```
ssh ubuntu@192.168.0.26  
```
(연구실 노트북으로 하고 와이파이는 bog로 함.)
비밀번호: turtlebot
혹시 이 ip가 달라질 수 있어서 원격 제어가 안될 수도 있는데 
이러면 ip를 다시 확인해봐야 합니다. -> 

1. 모니터 HDMI 선을 연결 (노파심에 ... 라즈베리파이3는 HDMI인데 라즈베리파이4는 HDMI Mini임. 출력 포트 위치는 동일하니 3과 4를 비교해보면서 적응하면 될 듯 합니다.)
2. 전원선을 연결 
3. 모니터에 화면 뜨면 로그인 (id: ubuntu, pw: turtlebot)
4. ifconfig로 터틀봇 ip 확인 
5. 혹시 노트북 ip도 바뀌었으면 master ip도 변경 해주어야 함 . sudo nano ~/.bashrc로 

```
roslaunch turtlebot3_bringup turtlebot3_robot.launch
```

##### 새 터미널 
```
rosrun icsr jjmaster.py
```
(별다른 메세지 안나오는데 그게 정상임)

##### 새 터미널 
```
rostopic pub -1 /height std_msgs/String "test1"
```
임의로 rostopic으로 1번만 data 신호를 보낸다는 뜻.
test1 같은 경우 data.data=="데이터값"의 형태로 들어가는데 
이 신호는 ROS 통신으로 키높이 장치, 블루투스 앱 등으로 전달할 수 있습니다. 

--------------------------------------------------------------------------------------------------------

미니어처 의자는 단순 아두이노 주행입니다. 
아두이노 나노보드로 구동 방식은 아두이노에서 보드만 Arduino Nano로 바꾸면 됩니다.

서보모터를 써서 별도로 모터 드라이버는 필요가 없지만, 양쪽 모터의 속력이 미묘하게 달라 직선 주행으로 가려면 반복적인 작업을 통하여 바꿔야 합니다.

(최대한 작게 만드느라 부품들을 간소화하였습니다. IMU를 쓰면 같은 속도로 이동하겠지만 속도가 잘 안나올거.)

버튼의 경우 libraries.zip 별도의 라이브러리를 사용했습니다. 
