/*
	GNU GPL v3
	(C) Tomas Kovacik [nail at nodomain dot sk]
	https://github.com/tomaskovacik/

	library for bluetooth modules based on OVC3860 chip by omnivision technologies

	supports SW and HW serial

	to enable SW serial uncomen USE_SW_SERIAL
	to enable debug output set DEBUG to 1, this is using HW Serial (hardcoded)

  based on 2 pdfs:
  https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/OVC3860_based_modules/BLK-MD-SPK-B_AT_Command_set_original.pdf
  https://github.com/tomaskovacik/kicad-library/blob/master/library/datasheet/OVC3860_based_modules/OVC3860_AT_Command_Application_Notes.pdf

  some commands did not work for me (P*,MM,MN...)
  (file BLK-MD-SPK-B_AT_Command_set_original.pdf is marked in header as -B but description is mentioning -A version of module, maybe
  this is why some commands did not work)

  PSKey confguration implemented: used to change name,pin,UART baudrate (this one is problematic currently, works with original soft in one from milion tryes....)

*/

#ifndef OVC3860_h
#define OVC3860_h
#include <Arduino.h>

#define USE_SW_SERIAL

#define DEBUG

#define USE_PSKCONFIG

//cmds definitions:
#define OVC3860_PAIRING_INIT "CA" /* discoverable for 2 minutes */
#define OVC3860_PAIRING_EXIT "CB"
#define OVC3860_CONNECT_HSHF "CC"
#define OVC3860_DISCONNECT_HSHF "CD"
#define OVC3860_CALL_ANSWARE "CE"
#define OVC3860_CALL_REJECT "CF"
#define OVC3860_CALL_HANGUP "CG"
#define OVC3860_CALL_REDIAL "CH"
#define OVC3860_VOICE_CALL_START "CI"
#define OVC3860_VOICE_CALL_CANCEL "CJ"
#define OVC3860_MIC_TOGGLE "CM"
#define OVC3860_TRANSFER_AUDIO_TO_SPEAKER "CO" // to secod BT device??? 
#define OVC3860_RELEASE_REJECT_CALL "CQ"
#define OVC3860_RELEASE_ACCEPT_CALL "CR"
#define OVC3860_HOLD_ACCEPT_CALL "CS"
#define OVC3860_CONFERENCE_CALL "CT"
#define OVC3860_PAIRING_DELETE_THEN_INIT "CV"
#define OVC3860_CALL_DIAL_NUMBER "CW"
#define OVC3860_SEND_DTMF "CX"
#define OVC3860_QUERY_HFP_STATUS "CY"
#define OVC3860_RESET "CZ"
#define OVC3860_MUSIC_TOGGLE_PLAY_PAUSE "MA"
#define OVC3860_MUSIC_STOP "MC"
#define OVC3860_MUSIC_NEXT_TRACK "MD"
#define OVC3860_MUSIC_PREVIOUS_TRACK "ME"
#define OVC3860_QUERY_CONFIGURATION "MF"
#define OVC3860_AUTOCONN_ENABLE "MG"
#define OVC3860_AUTOCONN_DISABLE "MH"
#define OVC3860_AV_SOURCE_CONNECT "MI"
#define OVC3860_AV_SOURCE_DISCONNECT "MJ"
#define OVC3860_CHANGE_LOCAL_NAME "MM"
#define OVC3860_CHANGE_PIN "MN"
#define OVC3860_QUERY_AVRCP_STATUS "MO"
#define OVC3860_AUTO_ANSWER_ENABLE "MP"
#define OVC3860_AUTO_ANSWER_DISABLE "MQ"
#define OVC3860_MUSIC_START_FF "MR"
#define OVC3860_MUSIC_START_RWD "MS"
#define OVC3860_MUSIC_STOP_FF_RWD "MT"
#define OVC3860_QUERY_A2DP_STATUS "MV"
#define OVC3860_WRITE_TO_MEMORY "MW"
#define OVC3860_READ_FROM_MEMORY "MX"
#define OVC3860_QUERY_VERSION "MY"
#define OVC3860_SWITCH_DEVICES "MZ"
#define OVC3860_PB_SYNC_BY_SIM "PA"
#define OVC3860_PB_SYNC_BY_PHONE "PB"
#define OVC3860_PB_READ_NEXT_ITEM "PC"
#define OVC3860_PB_READ_PREVIOUS_ITEM "PD"
#define OVC3860_PB_SYNC_BY_DIALED "PH"
#define OVC3860_PB_SYNC_BY_RECEIVED "PI"
#define OVC3860_PB_SYNC_BY_MISSED "PJ"
#define OVC3860_PB_SYNC_BY_LAST_CALL "PK"
#define OVC3860_GET_LOCAL_LAST_DIALED_LIST "PL"
#define OVC3860_GET_LOCAL_LAST_RECEIVED_LIST "PM"
#define OVC3860_GET_LOCAL_LAST_MISSED_LIST "PN"
#define OVC3860_DIAL_LAST_RECEIVED_CALL "PO"
#define OVC3860_CLEAR_LOCAL_CALL_HISTORY "PR"
#define OVC3860_SPP_DATA_TRANSMIT "ST"
#define OVC3860_SET_CLOCKDEBUG_MODE "VC"
#define OVC3860_VOLUME_DOWN "VD"
#define OVC3860_ENTER_TEST_MODE "VE"
#define OVC3860_SET_FIXED_FREQUENCY "VF"
#define OVC3860_EMC_TEST_MODE "VG"
#define OVC3860_SET_RF_REGISTER "VH"
#define OVC3860_INQUIRY_START "VI"
#define OVC3860_INQUIRY_STOP "VJ"
#define OVC3860_VOLUME_UP "VU"
#define OVC3860_SHUTDOWN_MODULE "VX"

#define OVC3860_BAUDRATE_1200 0x00
#define OVC3860_BAUDRATE_2400 0x01
#define OVC3860_BAUDRATE_4800 0x02
#define OVC3860_BAUDRATE_9600 0x03
#define OVC3860_BAUDRATE_14400 0x04
#define OVC3860_BAUDRATE_19200 0x05
#define OVC3860_BAUDRATE_38400 0x06
#define OVC3860_BAUDRATE_57600 0x07
#define OVC3860_BAUDRATE_115200 0x08
#define OVC3860_BAUDRATE_230400 0x09
#define OVC3860_BAUDRATE_460800 0x0A
#define OVC3860_BAUDRATE_921600 0x0B

#define OVC3860_PSKEY_ADDR_NAME 0x01c7
#define OVC3860_PSKEY_ADDR_PIN 0x01BF
#define OVC3860_PSKEY_ADDR_LOCAL_BTADDR 0x0018
#define OVC3860_PSKEY_ADDR_BTSYS_MODE 0x0007
#define OVC3860_PSKEY_ADDR_UART_BAUDRATE 0x0011
#define OVC3860_PSKEY_ADDR_CLASSOFDEVICE 0x0036

#define OVC3860_PSKEY_READ 0x1000
#define OVC3860_PSKEY_READ_RESPONCE 0x2000
#define OVC3860_PSKEY_WRITE 0x3000
#define OVC3860_PSKEY_WRITE_RESPONCE 0x4000
#define OVC3860_PSKEY_QUIT 0x5000

#if defined(USE_SW_SERIAL)
#if ARDUINO >= 100
#include <SoftwareSerial.h>
#else
#include <NewSoftSerial.h>
#endif
#endif


class OVC3860
{
  public:


/*
from datasheet:
HFP Status Value Description:(MG) => uint8_t HFPState
1. Ready (to be connected)
2. Connecting
3. Connected
4. Outgoing Call
5. Incoming Call
6. Ongoing Call
A2DP Status Value Description:(MU) => uint8_t A2DPState
1. Ready (to be connected)
2. Initializing
3. Signalling Active
4. Connected
5. Streaming
AVRCP Status Value Description:(ML) => uint8_t AVRCPState
1. Ready (to be connected)
2. Connecting
3. Connected
 */
    enum STATES
    {
      Ready, //HFP,A2DP.AVRCP
      Connecting, //HFP.AVRCP
      Connected, //HFP,A2DP.AVRCP
      OutgoingCall,//HFP
      IncomingCall,//HFP
      OngoingCall,//HFP
      Initializing,//A2DP
      SignallingActive,//A2DP
      Streaming,//A2DP
      Playing, //Music
      Idle, //Music = paused/stoped, call =idle;
      On, //PowerState
      Off, //PowerState
      Pairing, //BT
      ShutdownInProgress,//PowerState
      FastForwarding, //Music
      Rewinding, //Music
      ConfigError, //Audio
      CodecClosed,//Audio
      ASR_44800,//Audio
      ASR_44100,//Audio
      ASR_32000,//Audio
      ASR_16000,//Audio
      PhoneCall,
      Listening,
      PhoneHangUp,
      SPPopened,
      SPPclosed,
      Discoverable,
      Disconnected,
      ConfigMode
    };

    uint16_t BTState = Disconnected;
    uint16_t HFPState = Disconnected;
    uint16_t A2DPState = Disconnected;
    uint16_t AVRCPState = Disconnected;
    uint16_t CallState = Disconnected;
    uint16_t MusicState = Idle;
    uint16_t PowerState = Off;
    uint16_t Audio;
    uint16_t AutoAnswer=Off;
    uint16_t AutoConnect=Off;
    
    uint8_t volume;

    String CallerID;
    uint8_t BT_ADDR[6];
    String BT_NAME;
    String BT_PIN;

#if defined(USE_SW_SERIAL)
#if ARDUINO >= 100
    OVC3860(SoftwareSerial *ser, uint8_t resetPin);
#else
    OVC3860(NewSoftSerial  *ser, uint8_t resetPin);
#endif
#else
    OVC3860(HardwareSerial *ser, uint8_t resetPin);
#endif
    void begin(uint32_t baudrate = 115200);
    ~OVC3860();

    uint8_t sendData(String cmd);
    uint8_t getNextEventFromBT();
    uint8_t sendRawData(uint8_t _size, uint8_t data[]);
    
    uint8_t pairingInit();
    uint8_t pairingExit();
    uint8_t connectHSHF();
    uint8_t disconnectHSHF();
    uint8_t callAnswer();
    uint8_t callReject();
    uint8_t callHangUp();
    uint8_t callRedial();
    uint8_t voiceDialStart();
    uint8_t voiceDialEnd();
    uint8_t micToggle();
    uint8_t transferAudio();
    uint8_t callReleaseReject();
    uint8_t callReleaseAccept();
    uint8_t callHoldAccept();
    uint8_t callConference();
    uint8_t pairingDeleteThenInit();
    uint8_t callDialNumber(String number);
    uint8_t sendDTMF(char c);
    uint8_t queryHFPStatus();
    uint8_t reset();
    uint8_t musicTogglePlayPause();
    uint8_t musicStop();
    uint8_t musicNextTrack();
    uint8_t musicPreviousTrack();
    uint8_t queryConfiguration();
    uint8_t autoconnEnable();
    uint8_t autoconnDisable();
    uint8_t connectA2DP();
    uint8_t disconnectA2DP();
    uint8_t changeLocalName(String name = ""); //without parameter module should return actual name, did not work for me
    uint8_t changePin(String pin = ""); //without parameter module should return actual pin, did not work for me
    uint8_t queryAvrcpStatus();
    uint8_t autoAnswerEnable();
    uint8_t autoAnswerDisable();
    uint8_t musicStartFF();
    uint8_t musicStartRWD();
    uint8_t musicStopFFRWD();
    uint8_t queryA2DPStatus();
    uint8_t writeToMemory(String data);
    uint8_t readFromMemory(String addr);
    uint8_t switchDevices();
    uint8_t queryVersion();
    uint8_t pbSyncBySim();
    uint8_t pbSyncByPhone();
    uint8_t pbReadNextItem();
    uint8_t pbReadPreviousItem();
    uint8_t pbSyncByDialer();
    uint8_t pbSyncByReceiver();
    uint8_t pbSyncByMissed();
    uint8_t pbSyncByLastCall();
    uint8_t getLocalLastDialedList();
    uint8_t getLocalLastReceivedList();
    uint8_t getLocalLastMissedList();
    uint8_t dialLastReceivedCall();
    uint8_t clearLocalCallHistory();
    uint8_t sppDataTransmit();
    uint8_t setClockdebugMode();
    uint8_t volumeDown();
    uint8_t enterTestMode();
    uint8_t setFixedFrequency();
    uint8_t emcTestMode();
    uint8_t setRFRegister();
    uint8_t inquiryStart();
    uint8_t inquiryStop();
    uint8_t volumeUp();
    uint8_t shutdown();
    uint8_t enterConfigMode();
    uint8_t quitConfigMode();
    uint8_t readName();
    uint8_t writeName(String NewName);
    uint8_t readAllPSK();
    uint8_t readPin();
    uint8_t writePin(String NewPin);
    uint8_t readBaudRate();
    uint8_t writeBaudRate(uint8_t NewBaudRate = OVC3860_BAUDRATE_115200);
    uint8_t readSysBTMode();
    uint8_t writeSysBTMode(uint8_t mode);
    uint8_t readClassOfDevice();
    uint8_t writeClassOfDevice();
    uint8_t readBTAddress();
    void resetModule();

  private:
    uint32_t _baudrate;
    uint8_t _reset;
    uint8_t decodeReceivedString(String receivedString);
    uint8_t decodeReceivedDataArray(uint8_t data[]);
#if defined DEBUG 
    void DBG(String text);
#endif
    void resetHigh();
    void resetLow();


#if  defined(USE_SW_SERIAL)
#if ARDUINO >= 100
    SoftwareSerial *btSerial;
#else
    NewSoftSerial  *btSerial;
#endif
#else
    HardwareSerial *btSerial;
#endif
};


#endif

