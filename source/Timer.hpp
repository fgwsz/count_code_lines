#pragma once
#include<cmath>//std::floor
#include<ratio>//std::ratio
#include<chrono>//std::chrono
#include<string>//std::string std::to_string
struct Timer{
    void start(void);
    void stop(void);
    double delta_nanoseconds(void)const;
    double delta_microseconds(void)const;
    double delta_milliseconds(void)const;
    double delta_seconds(void)const;
    double delta_minutes(void)const;
    double delta_hours(void)const;
    std::string delta_string(void)const;
private:
    using clock=std::chrono::high_resolution_clock;
    using time_point=typename clock::time_point;
    time_point begin_,end_;
};
namespace detail{
template<typename Period,typename TimePoint>
double delta(TimePoint const& begin,TimePoint const& end){
    return std::chrono::duration_cast<
        std::chrono::duration<double,Period>
    >(end-begin).count();
}
std::string nanoseconds_to_string(double ns){
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
            +detail::nanoseconds_to_string(others);
    }else if(ns>=c_1m){
        integer=std::floor(ns/c_1m);
        others=ns-integer*c_1m;
        return std::to_string(static_cast<std::size_t>(integer))+" m "
            +detail::nanoseconds_to_string(others);
    }else if(ns>=c_1s){
        integer=std::floor(ns/c_1s);
        others=ns-integer*c_1s;
        return std::to_string(static_cast<std::size_t>(integer))+" s "
            +detail::nanoseconds_to_string(others);
    }else if(ns>=c_1ms){
        integer=std::floor(ns/c_1ms);
        others=ns-integer*c_1ms;
        return std::to_string(static_cast<std::size_t>(integer))+" ms "
            +detail::nanoseconds_to_string(others);
    }else if(ns>=c_1us){
        integer=std::floor(ns/c_1us);
        others=ns-integer*c_1us;
        return std::to_string(static_cast<std::size_t>(integer))+" us "
            +detail::nanoseconds_to_string(others);
    }
    return std::to_string(static_cast<std::size_t>(ns))+" ns";
}
}//namespace detail
void Timer::start(void){
    this->begin_=Timer::clock::now();
}
void Timer::stop(void){
    this->end_=Timer::clock::now();
}
double Timer::delta_nanoseconds(void)const{
    return detail::delta<std::nano,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_microseconds(void)const{
    return detail::delta<std::micro,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_milliseconds(void)const{
    return detail::delta<std::milli,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_seconds(void)const{
    return detail::delta<std::ratio<1>,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_minutes(void)const{
    return detail::delta<std::ratio<60>,typename Timer::time_point>
        (this->begin_,this->end_);
}
double Timer::delta_hours(void)const{
    return
        detail::delta<std::ratio<3600>,typename Timer::time_point>
        (this->begin_,this->end_);
}
std::string Timer::delta_string(void)const{
    return detail::nanoseconds_to_string(this->delta_nanoseconds());
}
