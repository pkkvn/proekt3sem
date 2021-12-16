#ifndef PeriodicPotential_h
#define PeriodicPotential_h

#include "SystemState.h"
#include <cmath>

template <typename T>
class PeriodicPotentialFactory final {
private:
    T omega;
    T gamma;

    class PhiFunction final {
    public:
        T operator()(SystemState<T> const &s, T t) const {
            return s.xi;
        }
    };

    class XiFunction final {
    private:
        T omega;
        T gamma;
    public:
        XiFunction(T omega, T gamma): omega(omega), gamma(gamma) { }

        T operator()(SystemState<T> const &s, T t) const {
            return -omega * omega * s.phi - 2*gamma*s.xi;
        }
    };

    class EnergyFunction final {
    private:
        T omega;
        T gamma;
    public:
        EnergyFunction(T omega, T gamma): omega(omega), gamma(gamma) { }

        T operator()(SystemState<T> const &s, T t) const {
          //  return s.xi * s.xi / static_cast<T>(2) + omega * omega * (static_cast<T>(1) - std::cos(s.phi));
          return s.xi * s.xi / static_cast<T>(2) + s.phi * s.phi / static_cast<T>(2);
        }
    };

public:
    PeriodicPotentialFactory(T omega, T gamma): omega(omega), gamma(gamma) { }

    auto get_xifunction() const {
        return XiFunction(omega, gamma);
    }

    auto get_phifunction() const {
        return PhiFunction();
    }

    auto get_energyfunction() const {
        return EnergyFunction(omega, gamma);
    }
};

#endif /* PeriodicPotential_h */
