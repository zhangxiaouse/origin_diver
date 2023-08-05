#pragma once
namespace cyberc3 {
namespace feedback {
    class speed {
    private:
        /* data */
    public:
        double speed_cmps = 0.0;
        double feedback_time = 0;
        char direction = 0;
        char speed_driver_error_code = 0;
        bool speed_driver_is_auto = false;
        bool inter_lock_status = false;
    };
}  // namespace feedback
}  // namespace cyberc3