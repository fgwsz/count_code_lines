#pragma once
#include<cmath>//std::floor
#include<ratio>//std::nano
#include<chrono>//std::chrono
#include<string>//std::string std::to_string
struct Timer{
    inline void start(void);
    inline void stop(void);
    inline double delta_nanoseconds(void)const;
    inline static std::string nanoseconds_to_string(double ns);
    inline std::string delta_string(void)const;
private:
    using clock=std::chrono::high_resolution_clock;
    using time_point=typename clock::time_point;
    time_point begin_,end_;
};
template<typename Period,typename TimePoint>
inline double delta(TimePoint const& begin,TimePoint const& end){
    return std::chrono::duration_cast<
        std::chrono::duration<double,Period>
    >(end-begin).count();
}
inline void Timer::start(void){
    this->begin_=Timer::clock::now();
}
inline void Timer::stop(void){
    this->end_=Timer::clock::now();
}
inline double Timer::delta_nanoseconds(void)const{
    return std::chrono::duration_cast<
        std::chrono::duration<double,std::nano>
    >(this->end_-this->begin_).count();
}
inline std::string Timer::nanoseconds_to_string(double ns){
    static constexpr double c_1ns=1;
    static constexpr double c_1us=1000*c_1ns;
    static constexpr double c_1ms=1000*c_1us;
    static constexpr double c_1s=1000*c_1ms;
    static constexpr double c_1m=60*c_1s;
    static constexpr double c_1h=60*c_1m;
    double integer=0;
    double others=0;
    if(ns>=c_1h){
        integer=std::floor(ns/c_1h);
        others=ns-integer*c_1h;
        return std::to_string(static_cast<std::size_t>(integer))+" h "
            +Timer::nanoseconds_to_string(others);
    }else if(ns>=c_1m){
        integer=std::floor(ns/c_1m);
        others=ns-integer*c_1m;
        return std::to_string(static_cast<std::size_t>(integer))+" m "
            +Timer::nanoseconds_to_string(others);
    }else if(ns>=c_1s){
        integer=std::floor(ns/c_1s);
        others=ns-integer*c_1s;
        return std::to_string(static_cast<std::size_t>(integer))+" s "
            +Timer::nanoseconds_to_string(others);
    }else if(ns>=c_1ms){
        integer=std::floor(ns/c_1ms);
        others=ns-integer*c_1ms;
        return std::to_string(static_cast<std::size_t>(integer))+" ms "
            +Timer::nanoseconds_to_string(others);
    }else if(ns>=c_1us){
        integer=std::floor(ns/c_1us);
        others=ns-integer*c_1us;
        return std::to_string(static_cast<std::size_t>(integer))+" us "
            +Timer::nanoseconds_to_string(others);
    }
    return std::to_string(static_cast<std::size_t>(ns))+" ns";
}
inline std::string Timer::delta_string(void)const{
    return Timer::nanoseconds_to_string(this->delta_nanoseconds());
}
