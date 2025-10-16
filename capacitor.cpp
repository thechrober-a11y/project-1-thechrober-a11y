#include <iostream>
#include <iomanip>

using namespace std;

// Capacitor structure
struct _capacitor {
    double *time;     // time array
    double *voltage;  // voltage array
    double *current;  // current array
    double C;         // capacitance
};
typedef struct _capacitor Capacitor;

int main() {
    // Constants
    const double dt = 1e-10;           // timestep
    const double final_time = 5e-6;    // final time
    const int N = static_cast<int>(final_time / dt); // number of steps
    const double R = 1e3;              // 1 kOhm
    const double C = 100e-12;          // 100 pF
    const double I_const = 1e-2;       // constant current 0.01 A
    const double V0 = 10.0;            // constant voltage 10 V

    // Allocate for constant current simulation
    Capacitor cc;
    cc.time = new double[N];
    cc.voltage = new double[N];
    cc.current = new double[N];
    cc.C = C;

    // Initial conditions
    cc.time[0] = 0.0;
    cc.voltage[0] = 0.0;
    cc.current[0] = I_const;

    // Constant current simulation
    for (int n = 0; n < N - 1; n++) {
        cc.time[n + 1] = cc.time[n] + dt;
        cc.voltage[n + 1] = cc.voltage[n] + (cc.current[n] * dt) / cc.C;
        cc.current[n + 1] = I_const; // constant
    }

    cout << "=== Constant Current Source Simulation ===" << endl;
    cout << fixed << setprecision(6);
    for (int n = 0; n < N; n += 200) {
        cout << "t = " << setw(10) << cc.time[n]
             << " s,  V = " << setw(12) << cc.voltage[n]
             << " V,  I = " << cc.current[n] << " A" << endl;
    }

    // Allocate for constant voltage simulation
    Capacitor cv;
    cv.time = new double[N];
    cv.voltage = new double[N];
    cv.current = new double[N];
    cv.C = C;

    // Initial conditions
    cv.time[0] = 0.0;
    cv.current[0] = V0 / R;
    cv.voltage[0] = 0.0;

    // Constant voltage simulation
    for (int n = 0; n < N - 1; n++) {
        cv.time[n + 1] = cv.time[n] + dt;
        cv.current[n + 1] = cv.current[n] - (cv.current[n] * dt) / (R * cv.C);
        cv.voltage[n + 1] = cv.voltage[n] + (cv.current[n] * dt) / cv.C;
    }

    cout << "\n=== Constant Voltage Source Simulation ===" << endl;
    for (int n = 0; n < N; n += 200) {
        cout << "t = " << setw(10) << cv.time[n]
             << " s,  V = " << setw(12) << cv.voltage[n]
             << " V,  I = " << cv.current[n] << " A" << endl;
    }

    // Free memory
    delete[] cc.time;
    delete[] cc.voltage;
    delete[] cc.current;

    delete[] cv.time;
    delete[] cv.voltage;
    delete[] cv.current;

    return 0;
}

