#ifndef _ICANCmd_H_
#define _ICANCmd_H_

#ifdef __cplusplus  
extern "C" { 
#endif

#define TRUE            true
#define FALSE           false
typedef bool            BOOL;
typedef char            CHAR;
typedef unsigned char   UCHAR;
typedef unsigned char   BYTE;
typedef unsigned char   *PBYTE;
typedef unsigned short  WORD;
typedef unsigned short  USHORT;
typedef int             INT;
typedef unsigned int    UINT;
typedef unsigned int    DWORD;
typedef unsigned int    *LPDWORD;
typedef unsigned long        ULONG;
typedef unsigned long long   ULONG64;
typedef void            *PVOID;
typedef void            *LPVOID;
#define __stdcall 
#define PACKED __attribute__( ( packed, aligned(1) ) )

//�ӿڿ����Ͷ���
#define ACUSB_131B              1
#define ACUSB_132B              2
#define ACPCI_251               3
#define ACPCI_252               4
#define ACPCI_254               5

#define ACNET_600               6
#define ACNET_622               7

#define LCPCIE_251              8
#define LCPCIE_252              9

#define LCPCIE_361              10
#define LCPCIE_362              11
#define LCPCIE_364              12

#define LCUSB_131B              1
#define LCUSB_132B              2
#define LCMiniPcie_431          1
#define LCMiniPcie_432          2
#define LCPCI_252               4

#define USBCAN_1CH              13
#define USBCAN_C_1CH            14
#define USBCAN_E_1CH            15
#define USBCAN_E_2CH            16
#define MPCIeCAN_1CH            17
#define MPCIeCAN_2CH            18

//�������÷���״ֵ̬
#define	CAN_RESULT_OK			1
#define CAN_RESULT_ERROR		0

//CAN������
enum CAN_ErrorCode
{	
	CAN_E_NOERROR        = 0x0000,   // û�з��ִ���
	CAN_E_OVERFLOW       = 0x0001,   // CAN�������ڲ�FIFO���
	CAN_E_ERRORALARM     = 0x0002,   // CAN���������󱨾�
	CAN_E_PASSIVE        = 0x0004,   // CAN��������������
	CAN_E_LOSE           = 0x0008,   // CAN�������ٲö�ʧ
	CAN_E_BUSERROR       = 0x0010,   // CAN���������ߴ���

	CAN_E_RCV_BUF        = 0x0020,   // dll CAN����BUF����
	CAN_E_ERR_BUF        = 0x0040,   // dll CAN������ϢBUF����

	CAN_E_DEVICEOPENED   = 0x0100,	// �豸�Ѿ���
	CAN_E_DEVICEOPEN     = 0x0200,	// ���豸����
	CAN_E_DEVICENOTOPEN  = 0x0400,	// �豸û�д�
	CAN_E_BUFFEROVERFLOW = 0x0800,	// ���������
	CAN_E_DEVICENOTEXIST = 0x1000,	// ���豸������
	CAN_E_LOADKERNELDLL  = 0x2000,	// װ�ض�̬��ʧ��
	CAN_E_CMDFAILED      = 0x4000,	// ִ������ʧ�ܴ�����
	CAN_E_BUFFERCREATE   = 0x8000,	// �ڴ治��
};	

// �����˲�����
typedef struct tagWakeup_Config
{
	DWORD	dwAccCode;						// ������
	DWORD	dwAccMask;						// ������
	DWORD	nFilter;						// �˲���ʽ(0��ʾδ�����˲�����-���յ�����CAN���Ķ�ͨ��USB��������,1��ʾ˫�˲�,2��ʾ���˲�,3-�رջ��ѹ���)
}PACKED Wakeup_Config, *PWakeup_Config;

enum ParamType
{
	PARAM_WAKEUP_CFG = 0x4000,      // ���û������ò���
};

enum libcancmd_log_level {
	_LIBUSB_LOG_LEVEL_NONE    = 0,
	_LOG_LEVEL_INFO           = 2,           // 2
	_LOG_LEVEL_WARNING        = 4,        // 4
	_LOG_LEVEL_ERROR          = 8,          // 8
	_LOG_LEVEL_CALL           = 16,           // 16
	_LIBUSB_LOG_LEVEL_ERROR   = 32,   // 32
	_LIBUSB_LOG_LEVEL_WARNING = 64, // 64
	_LIBUSB_LOG_LEVEL_INFO    = 128,   // 128
	_LIBUSB_LOG_LEVEL_DEBUG   = 256,  // 256
};

typedef void(*libcancmd_log_cb)(enum libcancmd_log_level level, const char *str);


//CAN����֡����
typedef  struct  tagCAN_DataFrame {
	UINT	uTimeFlag;                      // ʱ���ʶ,�Խ���֡��Ч
	BYTE	nSendType;                      // ����֡����,0-��������;1-���η���;2-�Է�����;3-�����Է�����
	BYTE	bRemoteFlag;                    // �Ƿ���Զ��֡
	BYTE	bExternFlag;                    // �Ƿ�����չ֡
	BYTE	nDataLen;                       // ���ݳ���
	UINT	uID;                            // ����DI
	BYTE	arryData[8];                    // ��������
}PACKED CAN_DataFrame, *PCAN_DataFrame;

//CAN��ʼ������
typedef struct tagCAN_InitConfig {
	UCHAR	bMode;	                        // ����ģʽ(0��ʾ����ģʽ,1��ʾֻ��ģʽ)
	BYTE	nBtrType;                       // λ��ʱ����ģʽ(1��ʾSJA1000,0��ʾLPC21XX)
	BYTE    dwBtr[4];						// CANλ��ʱ����
	DWORD	dwAccCode;						// ������
	DWORD	dwAccMask;						// ������
	BYTE	nFilter;						// �˲���ʽ(0��ʾδ�����˲�����,1��ʾ˫�˲�,2��ʾ���˲�)
	BYTE    dwReserved;                     // Ԥ���ֶ�
}PACKED CAN_InitConfig, *PCAN_InitConfig;

//CAN�豸��Ϣ
typedef  struct  tagCAN_DeviceInformation {
	USHORT	uHardWareVersion;               // Ӳ���汾
	USHORT	uFirmWareVersion;               // �̼��汾
	USHORT	uDriverVersion;                 // �����汾
	USHORT	uInterfaceVersion;              // �ӿڿ�汾
	USHORT	uInterruptNumber;               // �жϺ�
	BYTE	bChannelNumber;                 // �м�·CAN
	CHAR	szSerialNumber[20];             // �豸���к�
	CHAR	szHardWareType[40];             // Ӳ������
	CHAR    szDescription[20];			    // �豸����
} PACKED CAN_DeviceInformation, *PCAN_DeviceInformation; 

//CAN������Ϣ
typedef struct tagCAN_ErrorInformation {
	UINT			uErrorCode;             // ��������   
	BYTE			PassiveErrData[3];      // ������������
	BYTE			ArLostErrData;          // �ٲô�������
} PACKED CAN_ErrorInformation, *PCAN_ErrorInformation;


/**/
	 void   CAN_SetLogCb(libcancmd_log_cb cb);
	 void   CAN_SetDebug(unsigned int level);
	// ���豸
	 DWORD  CAN_DeviceOpen(DWORD dwType, DWORD dwIndex, CHAR *pDescription);
	// �ر��豸
	 DWORD  CAN_DeviceClose(DWORD dwDeviceHandle);

	// ����CAN
	 DWORD  CAN_ChannelStart(DWORD dwDeviceHandle, DWORD dwChannel, PCAN_InitConfig pInitConfig);
	// ֹͣCAN
	 DWORD  CAN_ChannelStop(DWORD dwDeviceHandle, DWORD dwChannel);

	// ��ȡ�豸��Ϣ
	 DWORD  CAN_GetDeviceInfo(DWORD dwDeviceHandle, PCAN_DeviceInformation pInfo);
	// ��ȡCAN������Ϣ
	 DWORD  CAN_GetErrorInfo(DWORD dwDeviceHandle, DWORD dwChannel, PCAN_ErrorInformation pErr);

	// ��EEPROM
	 DWORD  CAN_ReadEEPROM(DWORD dwDeviceHandle, WORD dwAddr, PBYTE pBuff, WORD nLen);
	// дEEPROM
	 DWORD  CAN_WriteEEPROM(DWORD dwDeviceHandle, WORD dwAddr, PBYTE pBuff, WORD nLen);

	// ��������
	 ULONG  CAN_ChannelSend(DWORD dwDeviceHandle, DWORD dwChannel, PCAN_DataFrame pSend, ULONG nCount);
	// �ӽ��ջ������ж�����
	 ULONG  CAN_ChannelReceive(DWORD dwDeviceHandle, DWORD dwChannel, PCAN_DataFrame pReceive, ULONG nCount, INT nWaitTime = -1);
	// ��ȡ���ջ�����֡��
	 ULONG  CAN_GetReceiveCount(DWORD dwDeviceHandle, DWORD dwChannel);
	// ��ս��ջ�����
	 DWORD  CAN_ClearReceiveBuffer(DWORD dwDeviceHandle, DWORD dwChannel);

	//���Ĵ���
	 DWORD  CAN_ReadRegister(DWORD dwDeviceHandle, DWORD dwChannel, DWORD dwAddr, PBYTE pBuff, WORD nLen);
	//д�Ĵ���
	 DWORD  CAN_WriteRegister(DWORD dwDeviceHandle, DWORD dwChannel, DWORD dwAddr, PBYTE pBuff, WORD nLen);

	// ��ȡ����
	 DWORD  CAN_GetParam(DWORD dwDeviceHandle, DWORD dwChannel, DWORD dwParamType, PVOID pData);
	// ���ò���
	 DWORD  CAN_SetParam(DWORD dwDeviceHandle, DWORD dwChannel, DWORD dwParamType, PVOID pData);

	#ifdef __cplusplus  
}
#endif

#endif //_ICANCmd_H_
