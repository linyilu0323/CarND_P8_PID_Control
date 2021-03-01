#ifndef PID_H
#define PID_H

#include <vector>
#include <iostream>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the average total squared error.
   * @output: 1/n * sum(cte^2)
   */
  double TotalError();

  /**
   * Update the PID gain, given index value (0=P, 1=I, 2=D)
   * @param delta is the desired change for the gain
   */
  void UpdateGain(int idx, double delta);

  /**
   * Twiddle algorithm for optimizing PID gains
   */
  void Twiddle();

  /**
  * PID Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;
  double prev_cte;

  // for twiddle
  int iterations;
  double sum_squared_err;
  std::vector<double> delta_gain;
  double best_err;


//private:


};

#endif  // PID_H
