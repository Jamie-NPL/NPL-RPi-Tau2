/**
 * @file   Camera.h
 * @author Jan Jerabek (jan.jerabek@workswell.cz), Jan Moravec (jan.moravec@workswell.cz)
 * @copyright (c) 2016, Workswell s.r.o., All rights reserved.
 * @date   March, 2016
 * @brief Class for WIC thermocamera control
 *
 * This class controls WIC cameras. The default use is described in WIC_SDK_Sample.cpp.
 * Basically it is: Connect(), StartAcquisition(), RetrieveBuffer(), ReleaseBuffer(), StopAcquisition() and lastly Disconnect().
 *
 * Use CameraCenter.cpp class for finding available cameras.
 *
 * Use the getter GetSettings() for thermocamera settings control.
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <chrono>
#include <iostream>
#include <PvSampleUtils.h>
#include <PvDevice.h>
#include <PvDeviceGEV.h>
#include <PvDeviceU3V.h>
#include <PvSerialBridge.h>
#include <PvStream.h>
#include <PvStreamGEV.h>
#include <PvStreamU3V.h>
#include <PvBuffer.h>
#include <PvPipeline.h>
#include <list>
#include "CameraSerialSettings.h"

class CameraCenter;

class Camera {

public:
	virtual ~Camera();

	/**
	 * Connect establishes connection to the selected camera.
	 * @return success
	 */
	int Connect();
	/**
	 * StartAcquisition starts the streaming from the camera
	 */
	void StartAcquisition();
	/**
	 * RetrieveBuffer gets actual data buffer from the camera
	 * @return pointer to the data buffer
	 */
	uint8_t * RetreiveBuffer();
	/**
	 * ReleaseBuffer releases the current buffer
	 */
	void ReleaseBuffer();
	/**
	 * StopAcquisition stops streaming from the connected camera
	 */
	void StopAcquisition();
	/**
	 * Disconnect disconnects the connected camera
	 */
	void Disconnect();
	/**
	 * IsConnected gets connection status of the camera
	 * @return true if the camera is connected
	 */
	bool IsConnected();
	/**
	 * IsAcquiring gets acquisition status of the camera
	 * @return true if the camera is acquiring images
	 */
	bool IsAcquiring();
	/**
	 * GetStatus gets camera status
	 * @return camera status - Connected/Disconnected/Acquiring
	 */
	string GetStatus();
	/**
	 * @brief Function calculates the temperature of RAW pixel value.
	 * The function works for current camera setting, regardless if its radiometric or non-radiometric.
	 * The camera must be set for CMOS 14bit RAW values (default setting)
	 * @param raw Raw pixel value
	 * @return Temperature in degrees Celsius
	 */
	double CalculateTemperatureC(uint16_t raw);
	/**
	 * @brief Function calculates the temperature of RAW pixel value.
	 * The function works for current camera setting, regardless if its radiometric or non-radiometric.
	 * The camera must be set for CMOS 14bit RAW values (default setting)
	 * @param raw Raw pixel value
	 * @return Temperature in Kelvin
	 */
	double CalculateTemperatureK(uint16_t raw);

	/**
	 * Getter for Camera settings
	 * @return Current setting for WIC camera
	 */
	CameraSerialSettings *GetSettings(){
		return settings;
	}


private:
	friend class CameraCenter;
	Camera(const PvDeviceInfo*);
	Camera(const PvDeviceInfo *aDeviceInfo, string calibData);
	Camera(const PvDeviceInfo *aDeviceInfo, string calibData, string licVersion);
	Camera(const PvDeviceInfo *aDeviceInfo, string calibData, string licVersion, string serialNmr);

	void ConfigureStream();
	PvPipeline *CreatePipeline( PvDevice *aDevice, PvStream *aStream );

	PvStream *mStream;
	PvPipeline *mPipeline;
	PvDevice *physicalDevice;
	PvGenCommand *lStart;
	PvGenCommand *lStop;
	PvBuffer *lBuffer;
	PvGenParameterArray *lDeviceParams;
	const PvDeviceInfo *deviceInfo;
	CameraSerialSettings *settings;
	string calibrationData = "";
	string licenseVersion = "00";
	string cameraSerialNmr ="";
	bool acquiring;
	uint64_t cameraTime = 0;
	bool isFastCamera = true;
};

#endif /* CAMERA_H_ */
