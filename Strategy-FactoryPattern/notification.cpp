#include<bits/stdc++.h>

using namespace std ; 


enum class NotificationType {
    SMS = 0,
    PUSH 
};
class Notification {
     public:
     virtual void send(const string &msg) = 0 ;
     virtual ~Notification() = default ; 
};

class SMS : public Notification {
     public :
     void send(const string &msg) override {
         cout<<"Message through SMS : " << msg << endl;
     }
};

class PushNotify : public Notification {
     public :
     void send(const string &msg) override {
         cout <<"Message through Push notification : " << msg <<endl;
     }
};

class NotificationFactory {
     public:
     static Notification* create(const NotificationType &type){

            switch (type){
                 case NotificationType::PUSH :{
                     return new PushNotify();
                 }
                 case NotificationType::SMS :{
                     return new SMS();
                 }
                 default : {
                    throw std::runtime_error("NOTIFICATION TYPE DOESN'T EXIST");
                 }
            }
     }
};
class NotificationStrategy {
    Notification* notify ; 
    public:
    
    NotificationStrategy(const NotificationType &type){
        notify = NotificationFactory::create(type);
    }

    void setStrategy(const NotificationType &type){
         notify = NotificationFactory::create(type);
    }
    void Notify(string msg){
         notify->send(msg);
    }
};


int main(){
       NotificationStrategy strategy(NotificationType::PUSH);

       strategy.Notify("HELLEWO FRIENDS!!");
    // NotificationStrategy* notify_strategy = new NotificationStrategy( new SMS());
    //  notify_strategy->Notify("HELLO FRIENDS!!!");

    return 0;
}