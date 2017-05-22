/**
 * @file   CameraCenter.h
 * @author Jan Jerabek (jan.jerabek@workswell.cz), Jan Moravec (jan.moravec@workswell.cz)
 * @copyright (c) 2016, Workswell s.r.o., All rights reserved.
 * @date   March, 2016
 * @brief  Class for searching and creating list of available WIC devices
 *
 * This is the center class for operating with WIC devices. Please, refer to WIC_SDK_Sample.cpp for example use.
 */

#ifndef CAMERACENTER_H_
#define CAMERACENTER_H_

#include "Camera.h"
#include "Authentificator.h"
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
#include <list>

class CameraCenter {
	string licenseFolderPath;
public:
	CameraCenter(string path);
	virtual ~CameraCenter();

	/**
	 * Function returns list of available WIC thermocameras.
	 * @return vector<Camera*> cameras
	 */
	vector<Camera*> getCameras(){
		return cameras;
	}

	/**
	 * Function refinds all connected cameras.
	 */
	void RefindCameras();
private:
	PvSystem *pleoraSystem;
	Authentificator *authentificator; // Object for authentification of WW camera
	Camera *camera;
	vector<Camera*> cameras;
	const PvDeviceInfo *lSelectedDI;
	vector<const PvDeviceInfo *> lDIVector;
	void OnDeviceFound(PvInterface aInterface, PvDeviceInfo aDeviceInfo);
	void createWICcams();
	int AuthentifyCamera(const PvDeviceInfo* devInfo);
};

#endif /* CAMERACENTER_H_ */
