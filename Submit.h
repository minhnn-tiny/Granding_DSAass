#ifndef SUBMIT_H
#define SUBMIT_H

#include <string>
#include <algorithm>
#include <fstream>
#include <boost\date_time\posix_time\posix_time.hpp>
#include <boost\foreach.hpp>
#include <boost\filesystem.hpp>

#include "tinyxml2.h"

const std::string serverPath = "F:\\ASP\\Server";
const std::string taskPath = serverPath + "\\Task.xml";
const std::string unprocess = serverPath + "\\Unprocess";
const std::string compileToolPath = "C:\\MinGW\\bin\\g++.exe";
const std::string testCaseFilePath = serverPath + "\\Testcase";

struct Submit
{
private:
	std::string userID;
	int submitID;
	boost::posix_time::ptime submitTime;
	std::string folderName;
public:
	Submit(std::string id, std::string smTime, std::string folder);
	Submit();
	std::string getUserFolderName() const;
	std::string getSubmitFolderName() const;
	std::string getExecutionFilePath();
	std::string getExecutionFileName();
	std::string getXMLFilePath();
	const std::string& getUserID() const;
	int getSubmitID() const;
	const boost::posix_time::ptime& getSubmitTime() const;
	const std::string& getFolderName() const;
	void setUserID(const std::string& uid);
	void setSubmitID(int id);
	void setSubmitTime(const boost::posix_time::ptime& ptime);
	void setFolderName(const std::string& folder);
	bool operator<(Submit other);
	bool operator>(Submit other);
	bool operator==(Submit other);
	bool operator<=(Submit other);
	bool operator>=(Submit other);
	void copyFile();
	static Submit fromXMLFile(std::string path);
	void setSubmitID();
};

#endif // !SUBMIT_H
