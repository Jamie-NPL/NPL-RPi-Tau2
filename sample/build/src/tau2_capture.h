/**
 * @file   tau2_capture.h
 * @author Jamie McMillan (jamie.mcmillan@npl.co.uk)
 * 		based on:
 *		Jan Jerabek (jan.jerabek@workswell.cz), Jan Moravec (jan.moravec@workswell.cz)
 * @date   May, 2017
 * @brief  This returns to standard output the camera header information and each raw pixel value.
 */

#ifndef TAU2_CAPTURE_H
#define TAU2_CAPTURE_H

void retrieveFileHeader(Camera *cam) {
	cout << "Camera part number: " << cam->GetSettings()->GetPartNumber() << endl;
	cout << "Camera resolution: " << cam->GetSettings()->GetResolutionX() << "x" << cam->GetSettings()->GetResolutionY() << endl;
	cout << "WIC model: " << cam->GetSettings()->GetModel() << endl;
	cout << "Camera manufacture: " << cam->GetSettings()->GetManufacturer() << endl;
	cout << "Camera firmware version: " << cam->GetSettings()->GetFWMajorVersion() << "-" << cam->GetSettings()->GetFWMinorVersion() << endl;
	cout << "Camera sensor temperature [°C]: " << cam->GetSettings()->GetSensorTemperature() << endl; 
	cout << "Camera housing temperature [°C]: " << cam->GetSettings()->GetHousingTemperature() << endl;
	cout << "Check for camera speed: ";

	switch(cam->GetSettings()->GetCameraSpeed()){
	case CameraSerialSettings::CameraSpeed::_9Hz:
		cout << "9Hz" << endl;
		break;
	case CameraSerialSettings::CameraSpeed::_30Hz:
		cout << "30Hz" << endl;
		break;
	case CameraSerialSettings::CameraSpeed::_60Hz:
		cout << "60Hz" << endl;
		break;
	default:
		cout << "" << endl;
		break;
	}

	if (cam->GetSettings()->GetIsRadiometric()) {
		cout << "Camera is capable of radiometry" << endl;
		if (cam->GetSettings()->GetRadiometryMode()) {
			cout << "	 -Camera is in radiometry mode" << endl;
		} else {
			cout << "	 -Camera is not in radiometry mode" << endl;
		}
	} else {
		cout << "	 -Camera is not capable of radiometry" << endl;
	}

	switch (cam->GetSettings()->GetTestPattern()) {
	case CameraSerialSettings::TestPatterns::Off:
		cout << "Test patter is off" << endl;
		break;
	default:
		cout << "Test pattern is on" << endl;
		break;
	}
	cout << "Temperature calculation values: " << endl;
	cout << "	-Emissivity: " << cam->GetSettings()->GetEmissivity() << endl;
	cout << "	-Atmospheric temperature [°C]: " << cam->GetSettings()->GetAtmospericTemperatureC() << endl;
	cout << "	-Reflected temperature [°C]: " << cam->GetSettings()->GetReflectedTemperatureC() << endl;
	cout << "	-Humidity [%]: " << cam->GetSettings()->GetHumidity() * 100.0 << endl;
	cout << "	-Object distance [m]: " << cam->GetSettings()->GetDistance() << endl;

	cout << "Performing flat field correction (click noise)..." << endl;
	cam->GetSettings()->DoFFC();
	sleep(1);
}


void retrievePixelValues(uint8_t *input_buffer, int width, int height) {
	uint16_t * in_f16 = (uint16_t *) input_buffer; // Pixel is a two-byte number
	int idx = 0;

	height=width=1; //for debugging

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			idx = y * width + x;
			uint16_t raw = in_f16[idx];
			cout << "Row: " << y << " Column: " << x << " Raw: " << raw << endl; 
		}
	}
}

#endif /* TAU2_CAPTURE */
