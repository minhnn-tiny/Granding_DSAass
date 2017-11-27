#include "Submit.h"



Submit::Submit(std::string id, std::string smTime, std::string folder)
	:userID(id), folderName(folder)
{
	submitTime = boost::posix_time::time_from_string(smTime);
	setSubmitID();
}
Submit::Submit()
{}
std::string Submit::getUserFolderName() const
{
	return "_" + userID;
}
std::string Submit::getSubmitFolderName() const
{
	return "Sub" + std::to_string(submitID);
}
const std::string& Submit::getUserID() const
{
	return userID;
}
int Submit::getSubmitID() const
{
	return submitID;
}
const boost::posix_time::ptime& Submit::getSubmitTime() const
{
	return submitTime;
}
const std::string& Submit::getFolderName() const
{
	return folderName;
}
void Submit::setUserID(const std::string& uid)
{
	userID = uid;
}
void Submit::setSubmitID(int id)
{
	submitID = id;
}
void Submit::setSubmitTime(const boost::posix_time::ptime& time)
{
	submitTime = time;
}
void Submit::setFolderName(const std::string& folder)
{
	folderName = folder;
}
bool Submit::operator<(Submit other)
{
	return (this->submitTime < other.submitTime);
}
bool Submit::operator>(Submit other)
{
	return (this->submitTime > other.submitTime);
}
bool Submit::operator==(Submit other)
{
	return (this->submitTime == other.submitTime);
}
bool Submit::operator<=(Submit other)
{
	return (this->submitTime <= other.submitTime);
}
bool Submit::operator>=(Submit other)
{
	return (this->submitTime >= other.submitTime);
}
Submit Submit::fromXMLFile(std::string path)
{
	if (!boost::filesystem::exists(boost::filesystem::path(path)))
		throw std::exception("File not found!");
	tinyxml2::XMLDocument doc;
	doc.LoadFile(path.c_str());
	tinyxml2::XMLElement* rootEle = doc.FirstChildElement("Upload");
	std::string folder = rootEle->FirstChildElement("FolderName")->GetText();
	std::string id = rootEle->FirstChildElement("ID")->GetText();
	std::string time = rootEle->FirstChildElement("Time")->GetText();
	return Submit(id, time, folder);
}
std::string Submit::getExecutionFilePath()
{
	std::string submitPath(serverPath + "\\" + this->getUserFolderName() + "\\" + this->getSubmitFolderName());
	submitPath += "\\" + getExecutionFileName();
	return submitPath;
}
std::string Submit::getExecutionFileName()
{
	return this->getUserFolderName() + "_" + std::to_string(this->getSubmitID()) + ".exe";
}
void Submit::copyFile()
{
	boost::filesystem::path srcPath(serverPath + "\\Unprocess\\" + this->folderName);
	boost::filesystem::path desPath(serverPath + "\\_" + this->userID);
	boost::filesystem::directory_iterator it(srcPath), eod;

	std::string xmlPath = getXMLFilePath();
	tinyxml2::XMLDocument doc;
	doc.InsertEndChild(doc.NewDeclaration());
	tinyxml2::XMLElement* rootEle = doc.NewElement("Files");


	if (!boost::filesystem::exists(desPath))
		boost::filesystem::create_directory(desPath);

	if (!boost::filesystem::exists(boost::filesystem::path(desPath.string() + "\\Sub" + std::to_string(this->submitID))))
		boost::filesystem::create_directory(boost::filesystem::path(desPath.string() + "\\Sub" + std::to_string(this->submitID)));
	BOOST_FOREACH(boost::filesystem::path const &p, std::make_pair(it, eod))
	{
		if (boost::filesystem::is_regular_file(p) && (p.extension().string() == ".cpp" || p.extension().string() == ".h"))
		{
			std::string newFileName = serverPath + "\\_" + this->userID + "\\Sub" + std::to_string(this->submitID) + "\\" + p.filename().string();
			boost::filesystem::path des(newFileName.c_str());
			boost::filesystem::copy(p, des);
			tinyxml2::XMLElement* ele = doc.NewElement("File");
			ele->SetText(p.filename().string().c_str());
			rootEle->InsertEndChild(ele);
		}
	}
	doc.InsertEndChild(rootEle);
	doc.SaveFile(xmlPath.c_str());

}
std::string Submit::getXMLFilePath()
{
	return serverPath + "\\_" + this->userID + "\\Sub" + std::to_string(this->submitID) + "\\Files.xml";
}
void Submit::setSubmitID()
{
	boost::filesystem::path submitInfoPath(serverPath + "\\" + this->getUserFolderName() + "\\UnloadInfo.xml");
	if (!boost::filesystem::exists(submitInfoPath))
	{
		tinyxml2::XMLDocument doc;
		doc.InsertFirstChild(doc.NewDeclaration());
		tinyxml2::XMLElement* ele = doc.NewElement("Count");
		ele->SetText(1);
		doc.InsertEndChild(ele);
		boost::filesystem::path xmlInfoPath(serverPath + "\\_" + userID + "\\Info.xml");
		if (!boost::filesystem::exists(boost::filesystem::path(serverPath + "\\_" + userID)))
			boost::filesystem::create_directory(boost::filesystem::path(serverPath + "\\_" + userID));
		doc.SaveFile(submitInfoPath.string().c_str());
		submitID = 1;
	}
	try
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(submitInfoPath.string().c_str());
		submitID = std::stoi(doc.FirstChildElement("Count")->GetText()) + 1;
		doc.FirstChildElement("Count")->SetText(submitID);
		doc.SaveFile(submitInfoPath.string().c_str());
	}
	catch (...)
	{
		submitID = 1;
	}


}