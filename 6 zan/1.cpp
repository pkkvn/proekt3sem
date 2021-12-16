#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <complex>

using namespace std;

void disp(double alpha, std::ostream& fout){
    double w_shtr, k_shtr;
    double eps = 0.001;
    double w_prib_nac = 0;
    double k_shtr_0 = 0;
    vector<int> a;
    vector<int> b;
    for (double k_shtr = k_shtr_0; k_shtr < 3; k_shtr += 0.003){
    double w_prib_0;

        if (k_shtr > 0){
            w_prib_0 = a[a.size()-1];
        }
        else{
            w_prib_0 = 1;
        }
        int iter = 0;
        bool good;
        do {
            double F_f, F_fpr, div;

            F_f = 1 - 1/(w_prib_0*w_prib_0) - alpha/((w_prib_0 - k_shtr)*(w_prib_0 - k_shtr));
            F_fpr = 2*(1/(w_prib_0*w_prib_0*w_prib_0) + alpha/((w_prib_0 - k_shtr)*(w_prib_0 - k_shtr)*(w_prib_0 - k_shtr)));

            div = (((w_prib_0 - k_shtr)*(w_prib_0 - k_shtr)*(w_prib_0*w_prib_0 - 1) - alpha*w_prib_0*w_prib_0)*w_prib_0*(w_prib_0 - k_shtr))/(2*(w_prib_0 - k_shtr)*(w_prib_0 - k_shtr)*(w_prib_0 - k_shtr) + 2*alpha*w_prib_0*w_prib_0*w_prib_0);

            //w_shtr = w_prib_0 - (F_f)/(F_fpr);
            w_shtr = w_prib_0 - div;
            if (std :: abs(w_shtr - w_prib_0) < eps){
                good = true;
                break;
            }
            iter += 1;
            w_prib_0 = w_shtr;
            if (iter > 10000){
                good = false;

                break;
            }

        }
        while(1);{
            if (good){
                a.push_back(w_shtr);
                b.push_back(k_shtr);
                fout << k_shtr << " " << w_shtr << endl;
            }
            else{
                a.push_back(k_shtr);
                b.push_back(k_shtr);

            }
            }
        }

    cout << "Completed" << endl;
}


int main(){
    ofstream out_file;
    out_file.open("disp0.txt");
    disp(1.e-2, out_file);
    out_file.close();

    out_file.open("disp1.txt");
    disp(1.01, out_file);
    out_file.close();

}
