/**
 * @file   CameraSerialSettings.h
 * @author Jan Jerabek (jan.jerabek@workswell.cz), Jan Moravec (jan.moravec@workswell.cz)
 * @copyright (c) 2016, Workswell s.r.o., All rights reserved.
 * @date   March, 2016
 * @brief Class for WIC thermocamera setting.
 *
 * Class uses eBUS SDK from Pleora and implements all necessary function for WIC thermocamera control.
 * When new Camera.cpp instance is created, the method SetDefault() prepares the WIC device for standard use.
 * Basic camera setting is presented in WIC_SDK_Sample.cpp.
 *
 */

#ifndef CAMERASERIALSETTINGS_H_
#define CAMERASERIALSETTINGS_H_

#include <PvDeviceSerialPort.h>
#include <PvDeviceAdapter.h>
#include <vector>

class CameraSerialSettings {
	friend class Camera;
public:
	CameraSerialSettings(PvDevice *device, PvDeviceSerial port);
	virtual ~CameraSerialSettings();

	//**********************************************************************************************************************
	// ENUMS
	//**********************************************************************************************************************

	/**Enum of available argument types for methods SetParameter() and GetParameter().*/
	enum class ArgumentType {
		Int16, Int32, ByteArray
	};
	/**Enum of possible WIC camera resolutions.*/
	enum class Resolution {
		Resolution_640,
		Resolution_336,
		Resolution_324,
		Resolution_168,
		Resolution_162,
		Resolution_160
	};
	/**Enum for selecting radiometry command for methods SetParameter() and GetParameter().*/
	enum class RadiometryCommand
    {
        ResolutionCommand,
        ModeCommand
    };
	/**WIC camera response statuses. When command to camera is send, this is the available answers.*/
	enum class ResponseStatuses
    {
        CAM_OK, /** All fine*/
        CAM_RANGE_ERROR,
        CAM_CHECKSUM_ERROR,
        CAM_UNDEFINED_PROCESS_ERROR,
        CAM_UNDEFINED_FUNCTION_ERROR,
        CAM_TIMEOUT_ERROR,
        CAM_BYTE_COUNT_ERROR,
        CAM_FEATURE_NOT_ENABLED,
        WRITE_ONLY,
        READ_ONLY,
        UNKNOWN_ERROR
    };
	/**Enum for all possible camera commands.*/
	enum class FunctionCodes : uint8_t
    {
		NO_OP = 0x00,
        SET_DEFAULT = 0x01,
        CAMERA_RESET = 0x02,
        RESTORE_FACTORY_DEFAULTS = 0x03,
        SERIAL_NUMBER = 0x04,
        GET_REVISION = 0x05,
        BAUD_RATE = 0x07, //?
        GAIN_MODE = 0x0A,
        FFC_MODE_SELECT = 0x0B,
        DO_FFC = 0x0C,
        FFC_PERIOD = 0x0D,
        FFC_TEMP_DELTA = 0x0E,
        VIDEO_MODE = 0x0F,
        VIDEO_PALETTE = 0x10,
        VIDEO_ORIENTATION = 0x11,
        DIGITAL_OUTPUT_MODE = 0x12, //?
        AGC_TYPE = 0x13,
        CONTRAST = 0x14,
        BRIGHTNESS = 0x15,
        BRIGHTNESS_BIAS = 0x18,
        SPOT_METER_MODE = 0x1F,
        READ_SENSOR = 0x20,
        EXTERNAL_SYNC = 0x21, //?
        ISOTHERM = 0x22,
        ISOTHERM_THRESHOLDS = 0x23,
        TEST_PATTERN = 0x25,
        VIDEO_COLOR_MODE = 0x26,
        GET_SPOT_METER = 0x2A,
        SPOT_DISPLAY = 0x2B,
        DDE_GAIN = 0x2C,
        FFC_WARN_TIME = 0x3C, //?
        AGC_FILTER = 0x3E,
        PLATEAU_LEVEL = 0x3F,
        SHUTTER_TEMP = 0x4D,
        AGC_MIDPOINT = 0x55,
        CAMERA_PART = 0x66,
        MAX_AGC_GAIN = 0x6A,
        VIDEO_STANDARD = 0x72,
        DDE_THRESHOLD = 0xE2,
        SPATIAL_THRESHOLD = 0xE3,
        LENS_RESPONSE_PARAMS = 0xE5,
        RADIOMETRY = 0x8E,
        SHUTTER_POSITION = 0x79
    };

	/**Enum for speed of camera.*/
	enum class CameraSpeed
    {
		_9Hz,
		_30Hz,
		_60Hz
    };

	/**Enum for radiometric parameter setting.*/
	enum class RadiometricParameters
    {
        NONE,
        RAD_EMISSIVITY, 		/**Emissivity*/
        RAD_TBKG_X100, 			/**Background temperature*/
        RAD_TRANSMISSION_WIN,
        RAD_TREFL_X100,			/**Reflected temperature*/
        RAD_TATM_X100			/**Atmospheric temperature*/
    };
	/**Enum for camera digital output mode setting. Default is digital CMOS.*/
	enum class DigitalOutputModes
    {
        XPMode,
        LVDSMode,
        CMOSBitDepth,
        LVDSBitDepth,
        NONE
    };
	/**Enum for WIC camera range mode setting. Default is Low.*/
	enum class RangeModes
    {
        Low,
		Middle,
		High
    };
	/**Enum for Flat Field Correction setting. Default is Auto.*/
	enum class FFCModes
    {
        Manual,
        Auto,
        External
    };
	/**Enum of available camera test patterns.*/
	enum class TestPatterns
    {
        Off,
        Ramp14b,
        BigVertical,
        HorizontalShade,
        FactoryUse,
        ColorBars,
        RampWithSteps
    };
	/**Enum of available camera XP BUS Modes. Default is CMOS.*/
	enum class XPBusModes
    {
        Disabled,
        BT656,
        CMOS
    };
	/**Enum of LVDS Modes.*/
	enum class LVDSModes
	{
		Disabled,
		Enabled
	};
	/**Enum for setting the digital output depth. Default is 14 bit.*/
	enum class DigitalOutputDepth
    {
        Bits14b,
		Bits8b,
		Bit8bBayer,
		Bit16bYCbCr
    };
	/**Enum for selecting the sensor measurement for methods SetParameter() and GetParameter().*/
	enum class SensorTemp
	{
		Sensor,
		Housing
	};
	/**Enum for selecting usage of palettes.*/
	enum class Palettes
    {
        WhiteHot = 0,
        BlackHot,
        Fusion,
        RainBow,
        Globow,
        Ironbow1,
        Ironbow2,
        Sepia,
        Color1,
        Color2,
        Icefire,
        Rain,
        RedHot,
        GreenHot
    };
	/**Enum for analog video gain control.*/
	enum class AGCTypes
    {
        PlateauHistogram,
        OnceBright,
        AutoBright,
        Manual,
        NotDefined,
        LinearAGC
    };
	/**Enum for selecting isotherm treshold units.*/
	enum class ThresholdUnits
    {
        degC,
        percentage
    };
	/**Enum for selecting video color mode.*/
	enum class VideoColorModes
    {
        Monochrome,
        Color
    };
	/**Enum for selecting standard of video mode.*/
	enum class VideoStandards
    {
        NTSC30Hz = 0x00,
        PAL25Hz = 0x01,
        NTSC60Hz = 0x03,
        PAL50Hz = 0x04
    };
	/**Enum for analog video in-picture indicators.*/
	enum class SpotDisplayModes
    {
        Off,
        Numeric,
        Thermometer,
        Both
    };
	/**Enum for the unit of SpotDisplayModes*/
	enum class SpotMeterModes
    {
        Off,
        Fahrenheit,
        Celsius
    };
	/**Enum for external FFC mode selection*/
	enum class ExternalSyncModes
    {
        Disabled,
        Master,
        Slave
    };

	/**
	 * @brief This function sets the WIC device to default setting.
	 * The default mode is CMOS 14bit RAW data. This setting is optimal (and mostly necessary) for temperature measurement functions.
	 * In this mode, each pixel of camera image is represented by 2 bytes (uint16_t).
	 * If you want to use test patterns, palettes and other interpreted data, the bit depth could differ.
	 * @return 0 = success, -1 = error
	 */
	int SetDefault(void);

	//**********************************************************************************************************************
	// CAMERA ACTIONS
	//**********************************************************************************************************************

	/**
	 * Test function for camera communication. If communication is fine, returns 0.
	 * @return 0 = success, -1 = error in communication
	 */
	int DoNothing();
	/**
	 * Makes WIC camera to perform Flat Field Correction (FFC). It can make the image clearer and temperature measurement more precise.
	 */
	void DoFFC();
	/**
	 * Set camera to default settings (Only camera, not WIC device).
	 */
	void DoSetDefaults(void);
	/**
	 * Resets camera (warning, communication will be lost).
	 */
	void DoCameraReset(void);
	/**
	 * Resets WIC camera to factory defaults.
	 */
	void DoRestoreFactoryDefaults(void);
	//void SetPTPOff(void);
	//bool SetPTPOn(int ActionDeviceKey, int ActionGroupKey, int ActionGroupMask);

	//**********************************************************************************************************************
	// GETTERS AND SETTERS
	//**********************************************************************************************************************

	/**
	 * @brief Getter for PvDevice. This describes the WIC connected device.
	 * @return PvDevice that is currently in use
	 */
	PvDevice *GetPvDevice(void);
	/**
	 * @brief Setter for PvDevice. This describes the WIC connected device.
	 * @param dev PvDevice that should be use
	 */
	void SetPvDevice(PvDevice *dev);

	/**
	 * @brief Getter for Serial port of PvDevice in use.
	 * @return PvDeviceSerial that is currently in use
	 */
	PvDeviceSerial GetPvDeviceSerial(void);
	/**
	 * @brief Setter for PvDeviceSerial.
	 * @param devSerial PvDeviceSerial that should be use
	 */
	void  SetPvDeviceSerial(PvDeviceSerial devSerial);

	/**
	 * @brief Function checks current range mode.
	 * Range mode describes the quality and range of pixel data measurement.
	 * RangeModes::Low = temperature between approximately -25 - +150 degree Celsius.
	 * RangeModes::Middle = temperature between approximately -40 - +500 degree Celsius.
	 * RangeModes::High = temperature between approximately +400 - +1500 degree Celsius.
	 * @return Current range mode
	 */
	RangeModes GetRangeMode(void);
	/**
	 * @brief Function sets the camera range mode.
	 * Range mode describes the quality and range of pixel data measurement.
	 * RangeModes::Low = temperature between approximately -25 - +150 degree Celsius.
	 * RangeModes::Middle = temperature between approximately -40 - +500 degree Celsius.
	 * RangeModes::High = temperature between approximately +400 - +1500 degree Celsius.
	 * High temperature filter has to be placed in front of camera when RangeModes::High is set.
	 * @param range Range mode to be set
	 */
	void SetRangeMode(RangeModes range);

	/**
	 * @brief Function checks whether high temperature mode is available for current lens.
	 * This parameter depends on selected lens.
	 * For proper measurement it is necessary to place a high temperature filter in front of the camera.
	 * @return True if High temperature mode is available
	 */
	bool GetHighRangeLensAvailable(void);

	/**
	 * @brief Function checks the camera FFC mode in current use.
	 * Flat Field Correction (FFC) is used for calibrating the camera. It can make the image and the measurement better.
	 * You can perform the FFC manually with DoFFC() function.
	 * @return Current FFC mode in use
	 */
	FFCModes GetFFCMode(void);
	/**
	 * @brief Function checks the camera FFC mode in current use.
	 * Flat Field Correction (FFC) is used for calibrating the camera. It can make the image and the measurement better.
	 * @param mode FFC mode to be set
	 */
	void SetFFCMode(FFCModes mode);

	/**
	 * @brief Function checks the XP Bus mode in current use.
	 * XP Bus mode is the protocol by which the digital data is transfered. It should be set to CMOS, which is also the default value.
	 * @return Current XP Bus mode
	 */
	XPBusModes GetXPBusMode(void);
	/**
	 * @brief Function sets the XP Bus mode for WIC device.
	 * Warning, do not use, if you are sure what you are doing. Default should be CMOS.
	 * @param mode XP Bus mode to be set
	 */
	void SetXPBusMode(XPBusModes mode);

	/**
	 * @brief Function gets the current LVDS mode.
	 * Warning, the WIC device is set to use CMOS mode.
	 * @return Current LVDS mode
	 */
	LVDSModes GetLVDSMode(void);
	/**
	 * @brief Function sets the LVDS mode.
	 * Warning, the WIC device is set to use CMOS mode.
	 * @param mode LVDS mode to be set
	 */
	void SetLVDSMode(LVDSModes mode);

	/**
	 * @brief Function gets the CMOS bit depth.
	 * The default bit depth should be 14 bit. That is the most precise data for measurement and image from camera.
	 * If you use 8 bit, the function for temperature calculation will not work.
	 * 8 bit depth (or 16bit YCbCr) could be useful for interpreted image with palettes or test pattern.
	 * @return Current CMOS bit depth
	 */
	DigitalOutputDepth GetCMOSBitDepth(void);
	/**
	 * @brief Function sets the CMOS bit depth.
	 * @param depth CMOS bit depth to be set
	 */
	void SetCMOSBitDepth(DigitalOutputDepth depth);

	/**
	 * @brief Function gets the LVDS bit depth.
	 * @return Current LVDS bit depth
	 */
	DigitalOutputDepth GetLVDSBitDepth(void);
	/**
	 * @brief Function sets the LVDS bit depth.
	 * @param depth LVDS bit depth to be set
	 */
	void SetLVDSBitDepth(DigitalOutputDepth depth);

	/**
	 * @brief Gets the current camera image test pattern.
	 * @return Current test pattern
	 */
	TestPatterns GetTestPattern(void);
	/**
	 * @brief Sets camera image test pattern.
	 * @param pattern Test pattern to be set.
	 */
	void SetTestPattern(TestPatterns pattern);

	/**
	 * @brief Gets the current synchronization mode for FFC.
	 * @return Current FFC synchronization mode
	 */
	ExternalSyncModes GetExternalSync(void);
	/**
	 * @brief Sets the synchronization mode for FFC.
	 * @param mode FFC synchronization mode to be set
	 */
	void SetExternalSync(ExternalSyncModes mode);

	/**
	 * @brief Function gets the current FFC period in number of camera frames.
	 * If automatic mode of FFC is selected, the camera will perform FFC each X frames.
	 * You can set the number of frames when the correction is performed.
	 * @return Number of frames between FFC
	 */
	int GetFFCPeriod(void);
	/**
	 * @brief Function sets the FFC period in number of camera frames.
	 * If automatic mode of FFC is selected, the camera will perform FFC each X frames.
	 * You can set the number of frames when the correction is performed. An argument value of 0 signals
	 * that elapsed time will not be used to trigger FFC.
	 * @param period Number of frames between FFC (0 to 30,000)
	 */
	void SetFFCPeriod(uint16_t period);

	/**
	 * @brief Gets the temperature difference used to trigger automatic FFC.
	 * The specified value is converted to Celsius degrees by dividing by 10 then adding 0.1. For Set example,
	 * a value of 10 corresponds to a delta temperature of 1.1C degrees.
	 * @return Temperature difference - Range: 0 to 1000 (0.1C to 100.1C degrees)
	 */
	uint16_t GetFFCTempDelta(void);
	/**
	 * @brief Sets the temperature difference used to trigger automatic FFC
	 * The specified value is converted to Celsius degrees by dividing by 10 then adding 0.1. For Set example,
	 * a value of 10 corresponds to a delta temperature of 1.1C degree.
	 * @param delta Temperature difference - Range: 0 to 1000 (0.1C to 100.1C degrees)
	 */
	void SetFFCTempDelta(uint16_t delta);

	/**
	 * @brief Reverse video horizontally.
	 * @return True if video is reversed
	 */
	bool GetInvertVideo(void);
	/**
	 * @brief Reverse video horizontally.
	 * @param invert True if video should be reversed
	 */
	void SetInvertVideo(bool invert);

	/**
	 * @brief Reverse video vertically
	 * @return True if video is reversed
	 */
	bool GetRevertVideo(void);
	/**
	 * @brief Reverse video vertically
	 * @param revert True if video should be reversed
	 */
	void SetRevertVideo(bool revert);

	/**
	 * @brief Function gets the current palette in use.
	 * The palette are designed for image data which should be not used for temperature measurement.
	 * @return Current palette
	 */
	Palettes GetPalette(void);
	/**
	 * @brief Function sets palette.
	 * The palette are designed for image data which should be not used for temperature measurement.
	 * @param pal Palette to be set
	 */
	void SetPalette(Palettes pal);

	/**
	 * @brief Sets WIC to analog video output
	 * @return True = analog video enabled
	 */
	bool GetAnalogVideo(void);
	/**
	 * @brief Sets WIC to analog video output
	 * @param video Sets the analog video output
	 */
	void SetAnalogVideo(bool video);

	/**
	 * @brief Function returns true, if WIC camera is capable of radiometry.
	 * @return True = radiometric camera
	 */
	bool GetIsRadiometric(void);

	/**
	 * @brief Function returns true, if radiometry is activated.
	 * @return True = radiometry is active
	 */
	bool GetRadiometryMode(void);
	/**
	 * @brief Functions sets or disables the radiometry mode.
	 * @param value True = radiometry should be active
	 */
	void SetRadiometryMode(bool value);
	/**
	 * @brief Gets the AGC algorithm.
	 * @return Current AGC algorithm in use
	 */
	AGCTypes GetAGCType(void);
	/**
	 * @brief Sets the AGC algorithm.
	 * @param type AGC algorithm to be set
	 */
	void SetAGCType(AGCTypes type);

	/**
	 * @brief Gets the contrast value used by oncebright, auto-bright, and manual AGC algorithms. Value 0 to 255.
	 * @return Contrast value
	 */
	uint16_t GetContrast(void);
	/**
	 * Sets the contrast value used by oncebright, auto-bright, and manual AGC algorithms.
	 * @param contrast Value 0 to 255.
	 */
	void SetContrast(uint16_t contrast);

	/**
	 * @brief Gets or sets the AGC brightness value used by the manual and auto-bright AGC algorithms.
	 * @return Range: 0 to 16383
	 */
	uint16_t GetBrightness(void);
	/**
	 * @brief Gets or sets the AGC brightness value used by the manual and auto-bright AGC algorithms.
	 * @param brightness Range: 0 to 16383
	 */
	void SetBrightness(uint16_t brightness);

	/**
	 * @brief Gets the brightness bias value used by the once-bright AGC algorithm.
	 * @return Range: -16384 to 16383
	 */
	int16_t GetBrightnessBias(void);
	/**
	 * @brief Sets the brightness bias value used by the once-bright AGC algorithm.
	 * @param brightnessBias Range: -16384 to 16383
	 */
	void SetBrightnessBias(int16_t brightnessBias);

	/**
	 * @brief Gets the isotherm mode (on/off).
	 * @return True = isotherm mode active
	 */
	bool GetIsotherm(void);
	/**
	 * @brief Sets the isotherm mode (on/off).
	 * @param isotherm True = isotherm mode active
	 */
	void SetIsotherm(bool isotherm);

	/**
	 * @brief Gets the isotherm thresholds in percent ( e.g. 97 decimal = 97%) or in degress Celsius C (e.g., 97 decimal = 97C).
	 * @return Current units
	 */
	ThresholdUnits GetIsothermThresholdUnit(void);
	/**
	 * @brief Sets the isotherm thresholds in percent ( e.g. 97 decimal = 97%) or in degress Celsius C (e.g., 97 decimal = 97C).
	 * Percent is relative to a value of 160C when in high-gain mode and 600C
	 * when in low-gain mode. For example, a value of 97% equates to 155C in
	 * high-gain mode, 582C in low-gain mode.
	 * @param unit Unit to be set
	 */
	void SetIsothermThresholdUnit(ThresholdUnits unit);

	/**
	 * @brief Gets the isotherm threshold in selected units ThresholdUnits.
	 * Thresholds must be in proper order: (Lower <= Middle <= Upper)
	 * @return Isotherm threshold
	 */
	int16_t GetIsothermThresholdLower(void);
	/**
	 * @brief Sets the isotherm threshold in selected units ThresholdUnits.
	 * Thresholds must be in proper order: (Lower <= Middle <= Upper)
	 * @param threshold
	 */
	void SetIsothermThresholdLower(int16_t treshold);
	/**
	 * @brief Gets the isotherm threshold in selected units ThresholdUnits.
	 * Thresholds must be in proper order: (Lower <= Middle <= Upper)
	 * @param threshold
	 */
	int16_t GetIsothermThresholdMiddle(void);
	/**
	 * @brief Sets the isotherm threshold in selected units ThresholdUnits.
	 * Thresholds must be in proper order: (Lower <= Middle <= Upper)
	 * @param threshold
	 */
	void SetIsothermThresholdMiddle(int16_t treshold);
	/**
	 * @brief Gets the isotherm threshold in selected units ThresholdUnits.
	 * Thresholds must be in proper order: (Lower <= Middle <= Upper)
	 * @param threshold
	 */
	int16_t GetIsothermThresholdUpper(void);
	/**
	 * @brief Sets the isotherm threshold in selected units ThresholdUnits.
	 * Thresholds must be in proper order: (Lower <= Middle <= Upper)
	 * @param threshold
	 */
	void SetIsothermThresholdUpper(int16_t treshold);

	/**
	 * @brief Gets the current video color mode.
	 * @return Current video color mode
	 */
	VideoColorModes GetVideoColorMode(void);
	/**
	 * @brief Sets the video color mode.
	 * @param mode Video color mode to be set
	 */
	void SetVideoColorMode(VideoColorModes mode);

	/**
	 * @brief Gets the spot display mode.
	 * @return Current spot display mode
	 */
	SpotDisplayModes GetSpotDisplayMode(void);
	/**
	 * @brief Sets the spot display mode.
	 * mode Spot display mode to be set
	 */
	void SetSpotDisplayMode(SpotDisplayModes mode);

	/**
	 * @brief Gets the spot meter mode.
	 */
	SpotMeterModes GetSpotMeterMode(void);
	/**
	 * @brief Sets the spot meter mode.
	 */
	void SetSpotMeterMode(SpotMeterModes mode);

	/**
	 * @brief Gets the gain value for DDE in manual mode.
	 * @return DDE gain currently used
	 */
	uint16_t GetDDEGain(void);
	/**
	 * @brief Sets the gain value for DDE in manual mode.
	 * @param gain Range changed from 255 to 65535
	 */
	void SetDDEGain(uint16_t gain);

	/**
	 * @brief Gets FFC warn time.
	 * @return FFC warn time (frames)
	 */
	uint16_t GetFFCWarnTime(void);
	/**
	 * @brief Sets FFC warn time.
	 * @param time Range: 0 to 600 (frames)
	 */
	void SetFFCWarnTime(uint16_t time);

	/**
	 * @brief Gets the AGC filter value.
	 * @return Current AGC filter value
	 */
	uint16_t GetAGCFilter(void);
	/**
	 * @brief Sets the AGC filter value.
	 * @param filter Range: 0 to 255
	 */
	void SetAGCFilter(uint16_t filter);

	/**
	 * @brief Gets the plateau level for the Plateau AGC algorithm.
	 * @return Plateau level value
	 */
	uint16_t GetPlateauLevel(void);
	/**
	 * @brief Sets the plateau level for the Plateau AGC algorithm.
	 * @param level Range: 0 to 4095
	 */
	void SetPlateauLevel(uint16_t level);

	/**
	 * @brief Gets the AGC midpoint offset, a parameter used by the Plateau-Equalization and Linear AGC algorithms.
	 * @return Midpoint value
	 */
	uint16_t GetAGCMidpoint(void);
	/**
	 * @brief Gets the AGC midpoint offset, a parameter used by the Plateau-Equalization and Linear AGC algorithms.
	 * @param point Range: 0 to 255
	 */
	void SetAGCMidpoint(uint16_t point);

	/**
	 * @brief Gets the max-gain parameter for Plateau AGC.
	 * @return Current maximal gain
	 */
	uint16_t GetMaxACGGain(void);
	/**
	 * @brief Sets the max-gain parameter for Plateau AGC.
	 * @param gain Range: 0 to 255
	 */
	void SetMaxACGGain(uint16_t gain);

	/**
	 * @brief Gets the spatial threshold of the DDE filter and the DDE mode (auto or manual).
	 * @return Current spatial treshold
	 */
	uint16_t GetSpatialTreshold(void);
	/**
	 * @brief Sets the spatial threshold of the DDE filter and the DDE mode (auto or manual)
	 * @param threshold Auto Threshold range is -20 to 100 (-20 to -1 blurs the image, 1 to 100 sharpens the image)
	 */
	void SetSpatialTreshold(uint16_t threshold);

	/**
	 * @brief Function returns the camera serial number.
	 * @return Camera serial number
	 */
	int GetCameraSerialNumber(void);
	/**
	 * @brief Function returns the sensor serial number.
	 * @return Sensor serial number
	 */
	int GetSensorSerialNumber(void);
	/**
	 * @brief Function returns the camera part number
	 * @return Camera part number as string
	 */
	std::string GetCameraPartNumber(void);
	/**
	 * @brief Function returns the WIC part number
	 * @return WIC part number in string
	 */
	std::string GetPartNumber(void);
	/**
	 * @brief Function checks, if current PvDevice object is supported.
	 * @return True = is supported
	 */
	bool GetIsSupported(void);
	/**
	 * @brief Function returns the camera resolution in pixels
	 * @return X resolution, image width
	 */
	int GetResolutionX(void);
	/**
	 * @brief Function returns the camera resolution in pixel
	 * @return Y resolution, image height
	 */
	int GetResolutionY(void);
	/**
	 * @brief Function returns the camera device manufacture
	 * @return Camera manufacture in string
	 */
	std::string GetManufacturer(void);
	/**
	 * @brief Function returns WIC model name
	 * @return WIC model name in string
	 */
	std::string GetModel(void);
	/**
	 * @return Camera firmware major version
	 */
	int GetFWMajorVersion(void);
	/**
	 * @return Camera firmware minor version
	 */
	int GetFWMinorVersion(void);
	/**
	 * @return Camera software major version
	 */
	int GetSWMajorVersion(void);
	/**
	 * @return Camera software minor version
	 */
	int GetSWMinorVersion(void);

	/**
	 * @brief Function returns current camera shutter temperature
	 * @return Shutter temperature in degrees Celsius
	 */
	double GetShutterTemperature(void);
	/**
	 * @brief Function returns camera core sensor temperature
	 * @return Camera sensor temperature in degrees Celsius
	 */
	double GetSensorTemperature(void);
	/**
	 * @brief Function returns current camera housing temperature
	 * @return Camera housing temperature in degrees Celsius
	 */
	double GetHousingTemperature(void);

	/**
	 * @brief Returns current emissivity. This values is used for temperature calculation.
	 * @return Emissivity value (0.5 - 1)
	 */
	double GetEmissivity(void);
	/**
	 * @brief Sets emissivity. This values is used for temperature calculation.
	 * @param value Emissivity value (0.5 - 1)
	 */
	void SetEmissivity(double value);

	/**
	 * @brief Returns the reflected temperature value in Kelvins. This is used for temperature calculation.
	 * @return Reflected temperature [Kelvin]
	 */
	double GetReflectedTemperatureK(void);
	/**
	 * @brief Sets the reflected temperature value in Kelvins. This is used for temperature calculation.
	 * @param value Reflected temperature [Kelvin]
	 */
	void SetReflectedTemperatureK(double value);

	/**
	 * @brief Returns the reflected temperature value in degrees Celsius. This is used for temperature calculation.
	 * @return value Reflected temperature [Celsius]
	 */
	double GetReflectedTemperatureC(void);
	/**
	 * @brief Sets the reflected temperature value in degrees Celsius. This is used for temperature calculation.
	 * @param value Reflected temperature [Celsius]
	 */
	void SetReflectedTemperatureC(double value);

	/**
	 * @brief Returns the atmospheric temperature value in Kelvins. This is used for temperature calculation.
	 * @return Atmospheric temperature [Kelvin]
	 */
	double GetAtmosphericTemperatureK(void);
	/**
	 * @brief Sets the atmospheric temperature value in Kelvins. This is used for temperature calculation.
	 * @param value Atmospheric temperature [Kelvin]
	 */
	void SetAtmosphericTemperatureK(double value);

	/**
	 * @brief Returns the atmospheric temperature value in degrees Celsius. This is used for temperature calculation.
	 * @return Atmospheric temperature [Celsius]
	 */
	double GetAtmospericTemperatureC(void);
	/**
	 * @brief Sets the atmospheric temperature value in degrees Celsius. This is used for temperature calculation.
	 * @param value Atmospheric temperature [Celsius]
	 */
	void SetAtmospericTemperatureC(double value);

	/**
	 * @brief Returns the current distance of measured object in meters. This is used for temperature calculation.
	 * @return Distance to measured object [m]
	 */
	double GetDistance(void);
	/**
	 * @brief Sets the distance of measured object in meters. This is used for temperature calculation.
	 * @param distance Distance to measured object [m]
	 */
	void SetDistance(double distance);

	/**
	 * @brief Gets the current humidity in 0 to 1 value (50% = 0.5). This is used for temperature calculation.
	 * @return Humidity [0 - 1]
	 */
	double GetHumidity(void);
	/**
	 * @brief Sets the humidity in 0 to 1 value (50% = 0.5). This is used for temperature calculation.
	 * @param humidity [0 - 1]
	 */
	void SetHumidity(double humidity);

	/**
	 * @brief Function gets current debug mode
	 * Debug mode writes special messages used for debugging or development.
	 * @return True = debug mode active
	 */
	bool GetDebugMessages();
	/**
	 * @brief Function sets debug mode
	 * Debug mode writes special messages used for debugging or development.
	 * @param set True = debug mode active
	 */
	void SetDebugMessages(bool set);

	/**
	 * @brief Function reruns vector with available lenses setting.
	 * Each lens can have different temperature calibration. For the temperature measurement to be precise, the lens should be set correctly.
	 * @return vector with available lenses setting (e.g. "019mm")
	 */
	std::vector<std::string> GetAvailibleLenses(void);
	/**
	 * @brief Function sets selected lens, if available. Each lens has different calibration data, thus it needs to be set correctly to get
	 * the best and most accurate temperature results. This operation can take several minutes.
	 * The available lenses can be acquired with the GetAvailibleLenses() function. The progress can be checked with function isSetLensReady().
	 *
	 * WARNING! Do not power off or disconnect the camera during this time! You can not communicate (get or sets properties) with WIC during this time!
	 * @param lens String with lens name (e.g. "019mm")
	 */
	void SetLens(std::string lens);
	/**
	 * Checks if function GetAvailibleLenses() finished and if the lens is ready. If the return value is false, you can not communicate with WIC camera.
	 * @return True if ready, False if not.
	 */
	bool isSetLensReady(void);
	/**
	 * @brief Function gets which lens is currently used.
	 * @return lens String with lens name (e.g. "019mm") or empty String when no lens is currently set
	 */
	std::string GetCurrentLense(void);

	/**
	 * @brief Function gets camera speed
	 * @return speed of camera i.e 9Hz, 30Hz, 60Hz
	 */
	CameraSpeed GetCameraSpeed(void);

private:
	ResponseStatuses GetParameter(FunctionCodes functionCodes, void *value, RadiometricParameters radioparam = RadiometricParameters::NONE, DigitalOutputModes digioutmode = DigitalOutputModes::NONE);
	ResponseStatuses SetParameter(FunctionCodes functionCodes, void *value, RadiometricParameters radioparam = RadiometricParameters::NONE, DigitalOutputModes digioutmode = DigitalOutputModes::NONE);
	unsigned char *prepareMessage(unsigned char function, unsigned short byte_count, unsigned char args[]);
	int switchSFFC1(void);
	int switchSFFC2(void);
	unsigned char *sendMessage(unsigned char *message, unsigned short byte_count, int sleepUS);

	//**********************************************************************************************************************
	// Values and variables
	//**********************************************************************************************************************

	PvDevice *device = NULL; //* Camera device descriptor
	PvDeviceSerial port; //* Camera device descriptor
    bool isRadiometric = false; //* Is camera radiometric
    bool radiometryMode = false; //* Is camera in radiometric mode / is in standard mode
    bool radiometryHigh = false; //* Is camera in radiometry high resolution / low resolution
    std::string cameraPartNumber = ""; //* Camera part number
    std::string partNumber = ""; //* Device part number
    bool isSupported = false; //* Is device supported
	SensorTemp sensorTemp = SensorTemp::Sensor; //* Command select
    RadiometryCommand radiometryCommand = RadiometryCommand::ModeCommand; //* Command select
    bool debugMessages = false;  //* Sets the debug messages on/off
    bool SetLensReady = true;
	RangeModes actualRange = RangeModes::Low;

	//**********************************************************************************************************************
	// FORMULAS
	//**********************************************************************************************************************

	uint16_t TempToRaw(double temperature);
	double calibrateTemperatureC(double temp);
	double RawToTemp(uint16_t RAW);
	void RecalculateConstants();


	//**********************************************************************************************************************
	// Radiometry functions
	//**********************************************************************************************************************

	void SetRadEmissivityTemp(double value);
	double GetRadEmissivityTemp();
	void SetRadReflectedTemp(double value);
	double GetRadReflectedTemp();
	void SetRadAtmosphericTemp(double value);
	double GetRadAtmosphericTemp();
	void SetRadiometricParameters();
	bool CheckIsRadimetric(void);
	int changeSFFCLens(void);
	/**
	 * brief Function checks, if radiometry is in High or Low mode.
	 * return True = radiometry in High mode
	 */
	bool GetRadiometryHighResolutionMode(void);
	/**
	 * brief Function sets the radiometry mode to High or Low.
	 * High mode give more accurate values, but is limited to +350 degrees Celsius.
	 * param mode True = radiometry in High mode
	 */
	void SetRadiometryHighResolutionMode(bool mode);

	//**********************************************************************************************************************
	// Other functions
	//**********************************************************************************************************************

	//GainModes GetGainMode(void);
	void SetGainMode(RangeModes gain);
	int CheckPartNumber(void);
	void SetPartNumber(Resolution resolution, bool fastSpeed);
	ResponseStatuses GetResponse(uint8_t *outbuffer);
	std::string ResponseToString(CameraSerialSettings::ResponseStatuses resp);
    uint16_t CalculateCRC(void *buf, int len);
    void setCalibrationData(std::string data, std::string licenseVersion, std::string serialNmr);
    int CheckCameraSffc(void);
	/**
	 * @brief Gets the current analog video standard.
	 * @return Current analog video standard
	 */
	VideoStandards GetVideoStandard(void);
	/**
	 * @brief Sets the current analog video standard.
	 * @param standard Analog standard to be set
	 */
	void SetVideoStandards(VideoStandards standard);
	/**
	 * @brief Function checks, if WIC camera is fast speed.
	 * @return True = 30 Hz, False = 9Hz
	 */
	bool GetIsFastVideoSpeed(void);
};

#endif /* CAMERASERIALSETTINGS_H_ */
