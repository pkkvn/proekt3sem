#include <iostream>
#include <vector>
#include <fstream>


using namespace std;


int main(){
    double x, y, xn, yn, xc, yc, dt, w;
    cin >> xc >> yc;
    xn = xc;
    yn = yc;
    dt = 0.0001;
    w = 1;
    ofstream out_file;
    out_file.open("res1.txt");
    for (int t = 0; t < 20000; t++){
        xn = xc-w*w*yc*dt;
        yn = yc + xc*dt;
        xc = xn;
        yc = yn;
        out_file << t << " " << xn << " " << yn << endl;
    }
    /*dy = x*dt;
    dx = -w*w*y*dt;*/
    out_file.close();
    out_file.open("res2.txt");
    double xn2, x20, yn2, yn22, y20, x2c, y2c, y22c;
    cin >> x20 >> y20;
    xn2 = x20;
    yn2 = y20;
    yn22 = y20;
    for (int t = 0; t < 20000; t++){
        xn2 = x2c - w*w*yn22*dt;
        yn22 = x2c*dt/2 + y2c;
        yn2 = y22c + x2c*dt/2;
        x2c = xn2;
        y2c = yn2;
        y22c = yn22;
        out_file << t << " " << xn2 << " " << yn2 << endl;
    }

}
