#pragma once

#include "../candevice/canbridge_interface.h"
#include "../tracer/data/basic/can.h"
#include "lcan_common.h"
#include <mutex>
#define __countof(a) (sizeof(a) / sizeof(a[0]))

namespace cyber_c3
{
  namespace can_bridge
  {
    class lcan : public interface
    {
    public:
      lcan(bool);
      ~lcan(){};
      int Read(cyberc3::basic::can &can_data) override;
      void Write(const cyberc3::basic::can &can_data) override;
      void Close() override;

    private:
      std::mutex write_mutex;
      DWORD dwDeviceHandle_;
      DWORD dwChannel_ = 0;
      DWORD dwType_ = LCUSB_132B;
    };

  } // namespace can_bridge
} // namespace cyber_c3