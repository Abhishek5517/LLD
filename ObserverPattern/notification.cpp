#include<bits/stdc++.h>

using namespace std ; 

enum class NotificationType {
    PUSH = 0,
    SMS
};

class Notification {
     public : 
     virtual void send(const string& msg) = 0 ;
     virtual ~Notification() = default ;
};

class PushNotification : public Notification{
    public :
    void send(const string& msg) override {
        cout<< "Push message sent : "<< msg <<endl;
    }
};

class SMSNotification : public Notification{
    public :
    void send(const string& msg) override {
        cout<< "SMS sent : "<< msg <<endl;
    }
};

class NotificationFactory {
    public:
    static Notification* create(const NotificationType &type){
        
          switch (type){
               case NotificationType::PUSH :{
                  return new PushNotification();
               }
               case NotificationType::SMS :{
                  return new SMSNotification();
               }
               default :{
                 throw std::runtime_error("NOT A VALID TYPE OF NOTIFICATION");
               }
          }
    }

};

class Observer {
     Notification* notify ; 
     public:
     Observer(const NotificationType &type) {
         notify = NotificationFactory::create(type);
     }   
     void Notify(const string &msg){
         notify->send(msg);
     }
};


template<typename T>
class Counter {
     int count ; 
     set<T*> o ; 
     public :
     Counter( int n ){
         count = n ; 
     }
     void subcribe(T* u){
         o.insert(u);
     }
     void incr(){
         count++;
         for( auto &u : o){
              u->Notify(to_string(count));
         }
     }
     void unsubscribe(T* u){
         o.erase(u);
     }
};

int main(){
    Observer o1(NotificationType::PUSH);
    Observer o2(NotificationType::SMS) ;

    Counter<Observer> cnt(0);
    cnt.subcribe(&o1);
    cnt.subcribe(&o2);
    cnt.incr();
    cnt.incr();
    return 0 ; 
}