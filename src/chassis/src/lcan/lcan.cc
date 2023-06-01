#include "lcan.h"
namespace cyber_c3
{
  namespace can_bridge
  {

    lcan::lcan(bool simulink = false)
    {
      /* 打开can设备 */
      printf("laikeusbcan open ...\n");
      if (simulink == false)
      {
        dwDeviceHandle_ = CAN_DeviceOpen(dwType_, dwChannel_, 0);
        // while ((dwDeviceHandle_ = CAN_DeviceOpen(dwType_, dwChannel_, 0)) == 0)
        // {
        //   printf("laikeusbcan0 open deivce0 error\n");
        //   usleep(1000 * 1000);
        // }
        printf("laikeusbcan open deivce success!\n");
        /* CAN 通道配置*/
        CAN_InitConfig config0;
        config0.dwAccCode = 0;          // 验收码
        config0.dwAccMask = 0xffffffff; // 屏蔽码
        config0.nFilter =
            0;                   // 滤波方式(0表示未设置滤波功能,1表示双滤波,2表示单滤波)
        config0.bMode = 0;       // 工作模式(0表示正常模式,1表示只听模式)
        config0.nBtrType = 1;    // 位定时参数模式(1表示SJA1000,0表示LPC21XX)
        config0.dwBtr[0] = 0x00; // BTR0
        config0.dwBtr[1] = 0x1C; // BTR1
        config0.dwBtr[2] = 0;
        config0.dwBtr[3] = 0;
        CAN_ChannelStart(dwDeviceHandle_, dwChannel_, &config0);
        // while (CAN_ChannelStart(dwDeviceHandle_, dwChannel_, &config0) !=
        //        CAN_RESULT_OK)
        // {
        //   printf("mPciCAN Start CAN 0 error\n");
        // }
      }
    };

    int lcan::Read(cyberc3::basic::can &can_data)
    {
      int reclen = 0; // 接收到的数据长度
      CAN_DataFrame rec[1];
      CAN_ErrorInformation err;
      reclen =
          CAN_ChannelReceive(dwDeviceHandle_, dwChannel_, rec, __countof(rec), 10);
      if (reclen != 0)
      {
        for (int num = 0; num < reclen; num++)
        {
          can_data.id = int(rec[num].uID);
          can_data.len = rec[num].nDataLen;
          for (size_t i = 0; i < can_data.len; i++)
          {
            can_data.data[i] = rec[num].arryData[i];
          }
        }
      }
      else
      {
        if (CAN_GetErrorInfo(dwDeviceHandle_, dwChannel_, &err) ==
            CAN_RESULT_OK)
        { // 必须调用CAN_GetErrorInfo函数
        }
        else
        {
          // CAN卡没有收到CAN报文
        }
      }
    }

    void lcan::Write(const cyberc3::basic::can &can_data)
    {
      std::lock_guard<std::mutex> lock(write_mutex);
      CAN_DataFrame candata_send[1];
      candata_send[0].nSendType = 0;
      candata_send[0].bRemoteFlag = 0;
      candata_send[0].bExternFlag = 0;
      candata_send[0].uID = can_data.id;
      candata_send[0].nDataLen = can_data.len;
      for (int i = 0; i < int(can_data.len); i++)
      {
        candata_send[0].arryData[i] = can_data.data[i];
      }
      CAN_ChannelSend(dwDeviceHandle_, dwChannel_, candata_send, 1);
    }

    void lcan::Close()
    {
      CAN_ChannelStop(dwDeviceHandle_, 0);
      usleep(10 * 1000);
      CAN_DeviceClose(dwDeviceHandle_);
    };
  } // namespace can_bridge
} // namespace cyber_c3