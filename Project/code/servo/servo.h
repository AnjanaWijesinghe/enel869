/** @file */

//! Setup servo timer
//! \param ccr2 CCR2 to set the duty cycle
void setup_servo_timer(int ccr2);
//! Set servo value.
//! Limits the new value to within the range.
//! \param  val new value
//! \param max_val maximum servo value
//! \param min_val minimum servo value
int set_servo_val(int val, int max_val, int min_val);
//! Increase servo value.
//! Limits the new value to within the range.
//! \param inc_val Number to increae by
//! \param curr_val current value of servo
//! \param max_val maximum servo value
//! \param min_val minimum servo value
int increase_servo_val(int inc_val, int curr_val, int max_val, int min_val);
//! Decrease servo value.
//! Limits the new value to within the range.
//! \param dec_val Number to decreae by
//! \param curr_val current value of servo
//! \param max_val maximum servo value
//! \param min_val minimum servo value
int decrease_servo_val(int dec_val, int curr_val, int max_val, int min_val);
//! Custom servo value set.
//! Limits the new value to within the range.
//! \param new_val New servo value
//! \param curr_val current value of servo
//! \param max_val maximum servo value
//! \param min_val minimum servo value
int custom_servo_val(int new_val, int curr_val, int max_val, int min_val);