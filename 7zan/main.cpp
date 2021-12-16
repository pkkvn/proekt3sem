#include "HeunSolver.h"
#include "PeriodicPotential.h"
#include "Printer.h"

#include <iostream>
#include <iomanip>
#include <fstream>

std::ostream& os_scientific(std::ostream &os) {
    return os << std::setprecision(8) << std::scientific;
}

struct Base {
    virtual void shout() const = 0;
};

struct DerivedA: Base {
    virtual void shout() const {
        std::cout << "DerivedA" << std::endl;
    }
};

struct DerivedB: Base {
    virtual void shout() const {
        std::cout << "DerivedB" << std::endl;
    }
};

int main(int argc, const char * argv[]) {
    PeriodicPotentialFactory ppf(1.f, 0.05f);
    SystemState<float> initial_state{1.f,1.f};
    float dt = 1.e-4;
    size_t iteration_size = 12'400'000;
    size_t skip_size = 1'000;


    {
        std::ofstream fos("./heun.txt");
        fos << os_scientific;
        Printer heun_printer(
                              initial_state,
                              HeunSolver(ppf.get_phifunction(),ppf.get_xifunction()),
                              ppf.get_energyfunction(),
                              dt,
                              iteration_size,
                              skip_size,
                              fos
        );
        heun_printer.run();
    }

    {
        std::ofstream fos("./cmps_heun.txt");
        fos << os_scientific;
        Printer heun_printer(
                              initial_state,
                              CompensatedHeunSolver(ppf.get_phifunction(),ppf.get_xifunction(),0.f,0.f,0.f,0.f),
                              ppf.get_energyfunction(),
                              dt,
                              iteration_size,
                              skip_size,
                              fos
        );
        heun_printer.run();
    }

    {
        PeriodicPotentialFactory dbl_ppf(1.,1.);
        std::ofstream fos("./dbl_heun.txt");
        fos << os_scientific;
        Printer heun_printer(
                              SystemState<double>{0.,0.5},
                              HeunSolver(dbl_ppf.get_phifunction(),dbl_ppf.get_xifunction()),
                              dbl_ppf.get_energyfunction(),
                              1.e-4,
                              iteration_size,
                              skip_size,
                              fos
        );
        heun_printer.run();
    }
    return 0;
}
