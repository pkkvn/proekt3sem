#ifndef HeunSolver_h
#define HeunSolver_h

#include "SystemState.h"
#include <utility>

template <typename PhiFunction_t, typename XiFunction_t>
class HeunSolver final {
private:
    PhiFunction_t const phi_f;
    XiFunction_t const xi_f;
    
public:
    HeunSolver(PhiFunction_t phi_f, XiFunction_t xi_f):
        xi_f(std::forward<XiFunction_t>(xi_f)),
        phi_f(std::forward<PhiFunction_t>(phi_f)) { }
    
    template <typename T>
    SystemState<T> operator()(SystemState<T> const &s, T t, T dt) const {
        auto euler_next = SystemState<T> {
            s.phi + phi_f(s,t) * dt,
            s.xi + xi_f(s,t) * dt
        };
        
        auto full_next = SystemState<T> {
            s.phi + phi_f(euler_next,t+dt) * dt,
            s.xi + xi_f(euler_next,t+dt) * dt
        };
        
        return SystemState<T> {
            (euler_next.phi + full_next.phi) / static_cast<T>(2),
            (euler_next.xi + full_next.xi) / static_cast<T>(2)
        };
    }
};

template <typename T>
inline
T compensated_sum(T sum, T input, T &compensation) {
    auto t1 = input - compensation;
    auto t2 = sum + t1;
    compensation = (t2 - sum) - t1;
    return t2;
}

template <typename PhiFunction_t, typename XiFunction_t, typename T>
class CompensatedHeunSolver final {
private:
    PhiFunction_t const phi_f;
    XiFunction_t const xi_f;
    mutable T euler_cmps_phi;
    mutable T euler_cmps_xi;
    mutable T full_cmps_phi;
    mutable T full_cmps_xi;
    
public:
    CompensatedHeunSolver(PhiFunction_t phi_f, XiFunction_t xi_f, T euler_cmps_phi, T euler_cmps_xi, T full_cmps_phi, T full_cmps_xi):
        xi_f(std::forward<XiFunction_t>(xi_f)),
        phi_f(std::forward<PhiFunction_t>(phi_f)),
        euler_cmps_phi(euler_cmps_phi), euler_cmps_xi(euler_cmps_xi),
        full_cmps_phi(full_cmps_phi), full_cmps_xi(full_cmps_xi) { }
    
    SystemState<T> operator()(SystemState<T> const &s, T t, T dt) const {
        auto euler_next = SystemState<T> {
            compensated_sum(s.phi, phi_f(s,t) * dt, euler_cmps_phi),
            compensated_sum(s.xi, xi_f(s,t) * dt, euler_cmps_xi)
        };
        
        auto full_next = SystemState<T> {
            compensated_sum(s.phi, phi_f(euler_next,t) * dt, full_cmps_phi),
            compensated_sum(s.xi, xi_f(euler_next,t) * dt, full_cmps_xi)
        };
        
        return SystemState<T> {
            compensated_sum(euler_next.phi, full_next.phi, full_cmps_phi) / static_cast<T>(2),
            compensated_sum(euler_next.xi, full_next.xi, full_cmps_xi) / static_cast<T>(2)
        };
    }
};

#endif /* HeunSolver_h */
