#include<bits/stdc++.h>

using namespace std ; 


// log.debug() , log.info() , log.warn() , log.error()

// class LoggerMessage{
//     public:
//     virtual void message(string msg) = 0 ; 
// };

// class Error : public LoggerMessage {
//     public:
//     void message( string msg){
//         cout<< "[ERROR] -> "<< msg<<endl;
//     }
// };
// class Info : public LoggerMessage {
//     public:
//     void message( string msg){
//         cout<< "[INFO] -> "<< msg<<endl;
//     }
// };
// class Debug : public LoggerMessage{
//     public:
//     void message( string msg){
//         cout<< "[DEBUG] -> "<< msg<<endl;
//     }
// };
// class Warn : public LoggerMessage{
//     public:
//      void message( string msg){
//         cout<< "[WARN] -> "<< msg<<endl;
//     }
// };

// class Logger {
//     Error err ; 
//     Debug debugger ;
//     Warn warning ; 
//     Info information ; 
//     public:
//     void error(string msg){
//          err.message(msg);
//     }
//     void debug( string msg ){
//         debugger.message(msg);
//     }
//     void warn(string msg){
//         warning.message(msg);
//     }
//     void info(string msg){
//         information.message(msg);
//     }
// };

enum class LogLevel {
    DEBUG = 0,
    INFO,
    WARN,
    ERROR
};

class Logger{
    private:
    static Logger *instance ; 
    static mutex mtx ;
    ofstream logFile ; 
    LogLevel currentLevel ;

    Logger(){
        logFile.open("app.log", ios::app);
        currentLevel = LogLevel::DEBUG ;
    }
     string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO";
            case LogLevel::WARN:  return "WARN";
            case LogLevel::ERROR: return "ERROR";
        }
        return "UNKNOWN";
    }

    string getTimestamp() {
        auto now = chrono::system_clock::now();
        time_t timeNow = chrono::system_clock::to_time_t(now);
        string ts = ctime(&timeNow);
        ts.pop_back(); 
        return ts;
    }

    void logInternal(LogLevel level , const string &msg){
        if( currentLevel > level ) return ;
        lock_guard<mutex> lock(mtx);
        string logData = "[" + getTimestamp() + "]" + " [" + levelToString(level) + "] " + msg ;

        cout<< logData << endl;
        if( logFile.is_open()){
            logFile << logData <<endl;
            logFile.flush();
        }
        
    }
    public:
     static Logger& getInstance() {
        static Logger instance;
        return instance;
    }


    void setLevel(LogLevel level){
         currentLevel = level ; 
    }
    void error(const string &msg){
        logInternal(LogLevel::ERROR , msg);
    }
    void debug(const string &msg){
        logInternal(LogLevel::DEBUG , msg);
    }
    void warn(const string &msg){
        logInternal(LogLevel::WARN , msg);
    }
    void info(const string &msg){
        logInternal(LogLevel::INFO , msg);
    }
    ~Logger(){
         if( logFile.is_open()){
             logFile.close();
         }
    }
};
int main() {
 
    Logger& log = Logger::getInstance(); 

    log.debug("huihui");

     
    return 0 ; 
}