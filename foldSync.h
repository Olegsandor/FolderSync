#pragma once
#include <string>
#include <vector>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

class foldSync
{
private:
	fs::path mainPath; //First path
	std::set<fs::path> syncPath; // all except for first
public:
	void sync();
	foldSync() {};
	foldSync(std::vector<std::string> paths);
private:
	fs::file_type getType(fs::path p);
	fs::path subPath(fs::path p, fs::path here = "");
	foldSync* copyFiles(fs::path toSync);
	foldSync* deleteOthers(fs::path toSync);
};

bool filesAreEqual(fs::path first, fs::path second);
