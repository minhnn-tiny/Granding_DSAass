#include "Grading.h"
#include "MatrixMult.h"

using namespace std;
using namespace tinyxml2;
using namespace boost::filesystem;

// Mỗi khi file upload lên thì thêm vào File "Task.xml" - danh sách các folder có sự thay đổi
// Nếu queue trống thì lại đọc lại file Task.xml để nhận thêm task và xóa các task đó đi trong file "Task.xml"	

// Khi upload thì file sẽ được lưu vào "Trash"





int main()
{
	//MatrixMult::makeTestCase();
	Grading* gr = new Grading();
	gr->process();
	system("pause"); 
	return 0;
}
void readTask()
{
	/*
	string copyTaskPath = serverPath + "\\TaskCopy.xml";
	bool error = false;
	boost::filesystem::path src(taskPath);
	boost::filesystem::path des(copyTaskPath);
	if (!boost::filesystem::exists(src))
		return;
	while (!boost::filesystem::exists(des))
	{
		try
		{
			boost::system::error_code err;
			boost::filesystem::rename(src, des, err);
			cout << err.message() << endl;
		}
		catch (...)
		{ }
	}
	tinyxml2::XMLDocument doc;
	doc.LoadFile(copyTaskPath.c_str());
	XMLElement* ele = nullptr;
	try
	{
		ele = doc.LastChildElement("ListUpload")->FirstChildElement("Upload");
		while (ele != nullptr)
		{
			string folder = ele->FirstChildElement("FolderName")->GetText();
			string id = ele->FirstChildElement("ID")->GetText();
			int submitID = stoi(ele->FirstChildElement("SubmitID")->GetText());
			string time = ele->FirstChildElement("Time")->GetText();
			ele = ele->NextSiblingElement("Upload");
			submitList.push(new Submit(id, submitID, time, folder));
		}
		boost::filesystem::remove(copyTaskPath);
	}
	catch (exception ex)
	{
		return;
	}
	catch (const filesystem_error& ex)
	{
		cout << ex.what() << endl;
	}
	*/

	boost::filesystem::path unprocessPath(unprocess);
	boost::filesystem::directory_iterator it(unprocessPath), eod;
	BOOST_FOREACH(boost::filesystem::path const &p, std::make_pair(it, eod))
	{
		if (is_regular_file(p))
		{
			if (p.extension().string() == ".xml")
			{
				cout << p.string() << endl;
			}
		}

	}
	
}
void processFolder(Submit* s)
{
	/*
	boost::filesystem::path copyPath(serverPath + "\\Unprocess\\" + s->folderName);
	boost::filesystem::directory_iterator it(copyPath), eod;
	string targetPathStr = serverPath + "\\_" + s->userID + "\\Sub" + to_string(s->submitID + 1);
	boost::filesystem::path targetPath(targetPathStr);
	if (!boost::filesystem::exists(targetPath))
		boost::filesystem::create_directories(targetPath);
	string xmlFile = targetPathStr + "\\Pro.xml";
	std::ofstream fs(xmlFile);
	fs << "<?xml version =\"1.0\" encoding =\"UTF-8\"?>\n<ListFile>\n</ListFile>";
	fs.close();
	tinyxml2::XMLDocument doc;
	doc.LoadFile(xmlFile.c_str());
	XMLElement* rootEle = doc.FirstChildElement("ListFile");

	BOOST_FOREACH(boost::filesystem::path const &p, std::make_pair(it, eod))
	{
		if (is_regular_file(p))
		{
			boost::filesystem::path newFilePath(targetPath.string() + "\\" + p.filename().string());
			boost::filesystem::copy_file(p, newFilePath);
			XMLElement* newEle = doc.NewElement("File");
			string fileName = p.filename().string();
			newEle->SetText(fileName.c_str());
			rootEle->InsertEndChild(newEle);
		}
	
	}
	doc.SaveFile(xmlFile.c_str());
	boost::filesystem::remove_all(serverPath + "\\Unprocess\\" + s->folderName);

	compileAndRun(s);
	//boost::filesystem::remove(serverPath + "\\Unprocess\\" + s->folderName);
	*/
}
void processing()
{
	
}
string getSubmitPath(Submit s)
{
	return serverPath + "\\_" + s.getUserID() + "\\Sub" + to_string(s.getSubmitID() + 1);
}
string getCompileStr(Submit s, string compileStd)
{
	/*
	string submitPath = getSubmitPath(s);
	string compileStr = "g++ "  + compileStd + " ";
	string proFile = submitPath + "\\Pro.xml";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(proFile.c_str());
	tinyxml2::XMLElement* ele = doc.FirstChildElement("ListFile")->FirstChildElement("File");
	while (ele != nullptr)
	{
		compileStr += submitPath + "\\" + ele->GetText();
		ele = ele->NextSiblingElement("File");
	}
	compileStr += " -o " + submitPath + "\\program.exe";
	return compileStr;
	*/
	return "";
}
void compileAndRun(Submit s)
{
	/*
	string submitPath = serverPath + "\\_" + s->userID + "\\Sub" + to_string(s->submitID + 1);
	string compileStr = getCompileStr(s, "-std=c++11");
	string compile = "set PATH=%PATH%;" + compileToolPath + " && " + compileStr;
	system(compile.c_str());
	for (int i = 0; i < N_TESTCASE; ++i)
	{
		//string testFile = testCaseFilePath + "\\" + "Test" + to_string(i) + ".txt";
		

	}
	*/
}