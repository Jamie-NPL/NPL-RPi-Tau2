#ifndef AUTHENTIFICATOR_H_
#define AUTHENTIFICATOR_H_

#include <list>
#include <string>
#include <vector>

class Authentificator {

	std::string licenseFolderPath;
public:
	Authentificator(std::string);
	virtual ~Authentificator();
	void UpdateLicenses();
	std::vector<std::string> GetSerialNumbers();
	std::vector<std::string> GetCalibrationData();
	std::vector<std::string> GetLicenseVersions();
	std::vector<std::string> GetTimeRestrictions();
	std::vector<std::string> GetSoftwareShortcuts();
	std::vector<std::string> GetLicenseCreators();
	std::vector<std::string> GetLicenseDates();
	std::vector<std::string> GetLicenseArticles();

private:

	std::string processLine(std::string line, int startPos, int stopPos);
	std::string ExtractSerialNo(std::string decryptedSerialNo);
	std::string ExtractCalibrationData(std::string fullSerialNum);
	std::string Decrypt(std::string str);
	std::string Encrypt(std::string str);
	// Information about licenses:
	std::vector<std::string> licenseVersions; // License version (01, 05, ...)
	std::vector<std::string> serialNumbers; // Decoded serial number
	std::vector<std::string> timeRestrictions; // Time restriction, if then none (001, 005, INF, ...)
	std::vector<std::string> softwareShortcuts; // 010 = Windows Linux ARM
	std::vector<std::string> licenseCreators; // Name of license creator
	std::vector<std::string> licenseDates; // Date of license creations DD.MM.RRRR
	std::vector<std::string> licenseArticles; // Article number
	std::vector<std::string> calibrationData; // Calibration data vector
};

#endif /* AUTHENTIFICATOR_H_ */
