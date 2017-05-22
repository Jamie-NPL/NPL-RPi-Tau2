/**
 * @file   tau2_capture.cpp
 * @author Jamie McMillan (jamie.mcmillan@npl.co.uk)
 * 		based on:
 *		Jan Jerabek (jan.jerabek@workswell.cz), Jan Moravec (jan.moravec@workswell.cz)
 * @date   May, 2017
 * @brief  This returns to standard output the camera header information and each raw pixel value.
 */

#include <pthread.h>
#include <iostream>
#include <string>
#include "CameraCenter.h"
#include "tau2_capture.h"

int main() {
	uint16_t *buffer;

	// Define start of header
	cout << string(74, '#') << endl;

	//creates a list of connected camera objects
	CameraCenter *cameras = new CameraCenter("./src/"); // Path to folder containing license file

	cout << "Number of detected cameras: " << cameras->getCameras().size() << endl;

	if (cameras->getCameras().size() == 0) {
		cout << "No camera found!" << endl;
		return -1;
	}

	//the first camera in the list
	Camera *camera1 = cameras->getCameras().at(0);

	//connect the camera
	if (camera1->Connect() != 0) {
		cout << "Error connecting camera!" << endl;
		return -1;
	}

	// Retrieve header information
	retrieveFileHeader(camera1);

	//start acquisition of the camera
	camera1->StartAcquisition();

	//get pointer to the current data
	buffer = (uint16_t *) camera1->RetreiveBuffer();

	int width = camera1->GetSettings()->GetResolutionX();
	int height = camera1->GetSettings()->GetResolutionY();

	// Define end of header
	cout << string(74, '#') << endl;

	retrievePixelValues(camera1->RetreiveBuffer(), width, height);

	//release buffer
	camera1->ReleaseBuffer();

	//stop acquisition of the camera
	camera1->StopAcquisition();

	//disconnect the camera
	camera1->Disconnect();
	return 0;
}
