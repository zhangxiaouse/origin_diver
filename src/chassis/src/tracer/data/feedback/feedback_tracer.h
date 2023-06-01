#pragma once

namespace cyberc3
{
    namespace feedback
    {
        class tracer
        {
        private:
            /* data */
        public:
            signed int left_speed = 0;
            signed int right_speed = 0;
            signed int speed = 0;
            signed int steer = 0;
            signed int left_odom = 0;
            signed int right_odom = 0;
        };

    } // namespace feedback
} // namespace cyberc3