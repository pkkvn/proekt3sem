#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <complex>
#include <algorithm>

using namespace std;



int main()
{
    double v_n = 0, v_p = 0, x_p = 0, x_n = 0, t_p = 0, t_n = 0, x_tmp = 0, v_tmp = 0, E = 0;


    /*double dt = 0.00001;
    double t = 0, t0 = 600;
    double gamma = 0.1;
    double t_last = 0;
    double w0 = 1;
    int i = 0;
    int F = 1;
    v_p = 1;*/

    remove("text2.txt");
    ofstream file;
    file.open("text2.txt");

    for (double w = 0.001; w <= 2; w += 0.001){
        vector <double> a;
        double dt = 0.01;
        double t = 0, t0 = 600;
        double gamma = 0.1;
        double t_last = 0;
        double w0 = 1;
        int i = 0;
        int F = 1;
        v_p = 1;

            while(t < t0){
                v_tmp = v_p + (F * std::cos(w * t_p) - (2 * gamma * v_p + w0 * w0 * x_p)) * dt;
                x_tmp = x_p + v_p * dt;

                x_n = x_p + dt * (v_p + v_tmp) / 2;
                v_n = v_p + dt * (F * std::cos(w * t_p) + F * std::cos(w * (t_p + dt)) - (2 * gamma * v_p + w0 * w0 * x_p + 2 * gamma * v_tmp + w0 * w0 * x_tmp)) / 2;
                t_n = t_p + dt;
                E = 1-cos(x_p)+(0.5*v_p*v_p)/(w*w);


                if (i%1000 == 0 && i != 0){
                    a.push_back(x_p);
                    //file << t << " " << v_p << " " << x_p  <<'\n';
                    //cout<<t<<" "<<v_p<<" "<<x_p<<" "<<E<<'\n';
                    }
                /*if(x_p < 0 && x_n > 0){
                    cout<< t-t_last <<'\n';
                    t_last = t;
                }*/

                x_p = x_n;
                v_p = v_n;
                t_p = t_n;
                t += dt;
                i++;
            }
        //cout << w << " " << *std::max_element(a.begin(), a.end()) << '\n';
        file << w << '\t' << *max_element(a.begin(), a.end())  <<'\n';

    }

    return 0;
}
