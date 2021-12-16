#ifndef EulerSolver_h
#define EulerSolver_h

#include "SystemState.h"
#include <utility>

template <typename PhiFunction_t, typename XiFunction_t>
class EulerSolver final {
private:
    PhiFunction_t const phi_f;
    XiFunction_t const xi_f;
public:
    EulerSolver(PhiFunction_t phi_f, XiFunction_t xi_f):
        xi_f(std::forward<XiFunction_t>(xi_f)),
        phi_f(std::forward<PhiFunction_t>(phi_f)) { }
    
    template <typename T>
    SystemState<T> operator()(SystemState<T> const &s, T t, T dt) const {
        return SystemState<T> {
            s.phi + phi_f(s,t) * dt,
            s.xi + xi_f(s,t) * dt
        };
    }
};

#endif /* EulerSolver_h */
