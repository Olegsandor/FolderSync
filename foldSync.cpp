#include "foldSync.h"

void foldSync::sync() 
{
	for (auto i : syncPath) {
		copyFiles((fs::path)i);
		deleteOthers((fs::path)i);
	}
}

foldSync::foldSync(std::vector<std::string> paths)
{
	if (getType(paths[0]) != fs::file_type::directory)
		throw std::invalid_argument("First path in a cfg file should be an existing folder \nWrong path: " + paths[0]);
	if (*(paths[0].end() - 1) == '\\')
		paths[0].pop_back();
	mainPath = paths[0];
	paths.erase(paths.begin());
	for (auto p : paths) {
		if (getType(p) != fs::file_type::directory && getType(p) != fs::file_type::not_found)
			throw std::invalid_argument("All paths in a cfg file shouldn't be an existing file \nWrong path: " + p);
		if (*(p.end() - 1) == '\\')
			p.pop_back();
		syncPath.insert(p);
	}
	if (syncPath.find(mainPath) != syncPath.end())
		throw std::invalid_argument("First path in a cfg file should be unique");
}

fs::file_type foldSync::getType(fs::path p)
{
	switch (fs::status(p).type()) {
	case fs::file_type::not_found:
		return fs::file_type::not_found;
	case fs::file_type::directory:
		return fs::file_type::directory;
	default:
		return fs::file_type::regular;
	}
}

fs::path foldSync::subPath(fs::path p, fs::path here) {
	if (here == "")
		here = mainPath;
	return p.string().substr(here.string().size() + 1);
}

foldSync* foldSync::copyFiles(fs::path toSync) {
	if (getType(toSync) == fs::file_type::not_found)
		create_directories(toSync);
	for (auto p : fs::recursive_directory_iterator(mainPath)) 
	{
		fs::path copyTo = toSync;
		copyTo /= subPath((fs::path)p);
		if(fs::status(p).type() != fs::status(copyTo).type()){
			if (is_directory(copyTo))
				remove_all(copyTo);
			else
				remove(copyTo);
		}
		else {
			if (getType(p) == fs::file_type::regular && filesAreEqual(p, copyTo)) {
				continue;
			}
		}
		copy((fs::path)p, copyTo, fs::copy_options::overwrite_existing);
	}
	return this;
}

foldSync* foldSync::deleteOthers(fs::path toSync) {
	for (auto p = fs::recursive_directory_iterator(toSync); p != fs::recursive_directory_iterator(); ++p)
	{
		fs::path shouldExist = mainPath;
		shouldExist /= subPath((fs::path)*p, toSync);
		if (!exists(shouldExist)) {
			fs::path pathToDelete = (fs::path)*p;
			if (p.depth())
				p.pop();
			else
				p = fs::recursive_directory_iterator(toSync);
			if (is_directory(pathToDelete))
				remove_all(pathToDelete);
			else
				remove(pathToDelete);
		}
	}
	return this;
}

// some func to compare files
bool filesAreEqual(fs::path first, fs::path second) {
	return false;
}
