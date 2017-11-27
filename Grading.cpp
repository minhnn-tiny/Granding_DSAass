#include "Grading.h"

using namespace std;
using namespace boost::filesystem;
using namespace tinyxml2;

Grading::Grading()
{
	submitList = new SubmitList();
}
void Grading::process()
{
	while (true)
	{
		readTask();
		while (!submitList->empty())
		{
			cout << submitList->nextTask().getUserID() << endl;
			compileAndRun(submitList->nextTask());
			submitList->remove();
		}
	}
}
void Grading::readTask()
{
	
	string processFolder = serverPath + "\\Unprocess";
	boost::filesystem::path unprocessPath(unprocess);
	if (!boost::filesystem::exists(unprocessPath))
		return;
	boost::filesystem::directory_iterator it(unprocessPath), eod;
	BOOST_FOREACH(boost::filesystem::path const &p, std::make_pair(it, eod))
	{
		if (is_regular_file(p))
			if (p.extension().string() == ".xml")
			{
				path newFilePath(unprocessPath.string() + "\\NewFile.xml");
				while (!exists(newFilePath))
				{
					try
					{
						rename(p, newFilePath);
					}
					catch (const exception& ex)
					{}
					catch (...)
					{}
				}
				Submit newSubmit = Submit::fromXMLFile(newFilePath.string());
				newSubmit.copyFile();
				submitList->add(newSubmit);
				boost::filesystem::remove(newFilePath);
				boost::filesystem::remove_all(serverPath + "\\Unprocess\\" + newSubmit.getFolderName());
			}
	}
}
void Grading::processFolder(Submit s)
{

}
std::string Grading::getCompileStr(Submit t, std::string compileStd)
{
	string compile = "set PATH=%PATH%;" + compileToolPath + " && " + " g++ " + compileStd + " ";
	path submitPath(serverPath + "\\" + t.getUserFolderName() + "\\" + t.getSubmitFolderName());
	string xmlPath = t.getXMLFilePath();
	tinyxml2::XMLDocument doc;
	doc.LoadFile(xmlPath.c_str());
	XMLElement* ele = doc.FirstChildElement("Files")->FirstChildElement("File");

	while (ele != nullptr)
	{
		compile += submitPath.string() + "\\" + std::string(ele->GetText()) + " ";
		ele = ele->NextSiblingElement("File");
	}
	compile += "-o " + t.getExecutionFilePath();
	return compile;
}
void Grading::compileAndRun(Submit s)
{
	string timeout = "20";
	string compileStr = getCompileStr(s, "-std=c++11");
	
	system(compileStr.c_str());
	for (int i = 0; i < N_TESTCASE; ++i)
	{
		string testcasePath = "<\"" + testCaseFilePath + "\\Test" + to_string(i + 1) + "\\input1.txt\"";
		string outputPath = ">\"" + serverPath + "\\_" + s.getUserID() + "\\" + s.getSubmitFolderName() + "\\output.txt\"";
		string run = s.getExecutionFilePath() + " " + testcasePath + " " + outputPath + " && timeout /t " +
			timeout + " && taskkill /im " + s.getExecutionFileName() + " /f";
		system(run.c_str());
	}
}
bool Grading::compare(std::string path, std::string path2)
{
	return true;
}