#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {

  PID::Kp = Kp_;
  PID::Ki = Ki_;
  PID::Kd = Kd_;

  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
  prev_cte = 0.0;

  // for twiddle
  //iterations = 0;
  sum_squared_err = 0;
  delta_gain = {0.1*Kp, 0.1*Ki, 0.1*Kd};
  best_err = 1e6;

}

void PID::UpdateError(double cte) {

  p_error = cte;
  i_error += cte;
  d_error = cte - prev_cte;
  prev_cte = cte;

  iterations += 1;
  sum_squared_err += cte * cte;

}

double PID::TotalError(){
    return sum_squared_err/iterations;
}

void PID::UpdateGain(int idx, double delta){
    switch(idx) {
        case 0: Kp += delta; break;
        case 1: Ki += delta; break;
        case 2: Kd += delta; break;
    }
}

void PID::Twiddle(){
    double err;

    for (int i = 0; i < 3; ++i){
        UpdateGain(i, delta_gain[i]);
        err = TotalError();

        if (err < best_err){
            best_err = err;
            delta_gain[i] *= 1.1;
        }

        else {
            UpdateGain(i, -2*delta_gain[i]);
            err = TotalError();

            if (err < best_err){
                best_err = err;
                delta_gain[i] *= 1.1;
            }
            else{
                UpdateGain(i, delta_gain[i]);
                delta_gain[i] *= 0.9;
            }
        }
        std::cout << "Finished tuning idx=" << i << " parameter" << std::endl;
    }
}
