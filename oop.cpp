#include<iostream>

using namespace std;

//父類別：車
class Car{
    private: //會被子類別繼承，但無法存取！！！
        int speed;
    protected: // 可以被子類別繼承，存取！！！
        string color;
    public:
        Car() : speed(0) {} // 建構子，將speed初始化為0

        int getSpeed(){ return speed; }
        void setSpeed(int s) {speed = s;}

};

// 子類別：車的外觀
class DetailOfCar : public Car {
    public:
        void setColor(string c) { // 此為detail獨有之方法，若要使用必須建立detail物件
            color = c;
            cout<<"Car color: "<<color <<endl;
        }

};

int main(){
    Car mycar;
/*---------------建構子初始化及基本行為操作-----------------------------------------------------------------------------*/
    int speed = mycar.getSpeed();
    cout<<"Initial speed = "<<speed<<endl; // 初始值

    mycar.setSpeed(100);
    speed = mycar.getSpeed();
    cout<<"After asigned = "<<speed<<endl; // 設定後
/*---------------繼承(inheritance) : 子類別可繼承父類別之資料及行為-------------------------------------------------------*/
    cout<<"----------------------------繼承(inheritance)----------------------------------------------------"<<endl;
    DetailOfCar mycar1;
    mycar1.setColor("black");
    mycar1.setSpeed(50);
    cout<<"繼承getSpeed成功-> speed = " <<mycar1.getSpeed() <<endl;




}