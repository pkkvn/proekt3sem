#ifndef SystemState_h
#define SystemState_h

#include <iostream>

template <typename T>
struct SystemState final {
    T phi, xi;
};

template <typename T>
std::ostream& operator<<(std::ostream &os, SystemState<T> const &s) {
    return os << s.phi << ' ' << s.xi;
}

template <typename T>
std::istream& operator>>(std::istream &is, SystemState<T> &s) {
    return is >> s.phi >> s.xi;
}

#endif /* SystemState_h */
