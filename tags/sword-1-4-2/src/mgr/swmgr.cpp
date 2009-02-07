/******************************************************************************
 *  swmgr.cpp   - implementaion of class SWMgr used to interact with an install
 *				base of sword modules.
 *
 * $Id: swmgr.cpp,v 1.6 1999/06/05 23:32:02 scribe Exp $
 *
 * Copyright 1998 CrossWire Bible Society (http://www.crosswire.org)
 *	CrossWire Bible Society
 *	P. O. Box 2528
 *	Tempe, AZ  85280-2528
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef __GNUC__
#include <io.h>
#else
#include <unistd.h>
#include <unixstr.h>
#endif
#include <sys/stat.h>


#include <swmgr.h>
#include <rawtext.h>
#include <rawgbf.h>
#include <rawcom.h>
#include <hrefcom.h>
#include <rawld.h>
#include <utilfuns.h>
#include <gbfplain.h>
#include <gbfstrongs.h>
#include <gbffootnotes.h>
#include <rawfiles.h>


void SWMgr::init() {
	configPath  = 0;
	prefixPath  = 0;
	configType  = 0;
	myconfig    = 0;
	mysysconfig = 0;

	optionFilters.insert(FilterMap::value_type("GBFStrongs", new GBFStrongs()));
	optionFilters.insert(FilterMap::value_type("GBFFootnotes", new GBFFootnotes()));
	gbfplain = new GBFPlain();
}


SWMgr::SWMgr(SWConfig *iconfig, SWConfig *isysconfig, bool autoload) {

	init();
	
	if (iconfig) {
		config   = iconfig;
		myconfig = 0;
	}
	else config = 0;
	if (isysconfig) {
		sysconfig   = isysconfig;
		mysysconfig = 0;
	}
	else sysconfig = 0;

	if (autoload)
		Load();
}


SWMgr::SWMgr(const char *iConfigPath, bool autoload) {

	string path;
	
	init();
	
	path = iConfigPath;
	path += "/";
	if (existsFile(path.c_str(), "mods.conf")) {
		stdstr(&prefixPath, path.c_str());
		path += "mods.conf";
		stdstr(&configPath, path.c_str());
	}
	else {
		if (existsDir(path.c_str(), "mods.d")) {
			stdstr(&prefixPath, path.c_str());
			path += "mods.d";
			stdstr(&configPath, path.c_str());
			configType = 1;
		}
	}

	config = 0;
	sysconfig = 0;

	if (autoload && configPath)
		Load();
}


SWMgr::~SWMgr() {

	DeleteMods();

	if (gbfplain)
		delete gbfplain;

	for (FilterMap::iterator it = optionFilters.begin(); it != optionFilters.end(); it++)
		delete (*it).second;			
			
	if (myconfig)
		delete myconfig;

	if (prefixPath)
		delete [] prefixPath;

	if (configPath)
		delete [] configPath;
}


char SWMgr::existsFile(const char *ipath, const char *ifileName)
{
	string path = ipath;
	path += "/";
	int fd;
	string filePath = path + ifileName;
	if ((fd = ::open(filePath.c_str(), O_RDONLY)) > 0) {
		::close(fd);
		return 1;
	}
	return 0;
}


char SWMgr::existsDir(const char *ipath, const char *idirName)
{
	DIR *dir;
	string path = ipath;
	path += "/";
	string filePath = path + idirName;
	if ((dir = opendir(filePath.c_str()))) {
		closedir(dir);
		return 1;
	}
	return 0;
}


void SWMgr::findConfig() {
	string path;
	ConfigEntMap::iterator entry;
	int fd;

	char *envsworddir = getenv ("SWORD_PATH");
	char *envhomedir  = getenv ("HOME");

	configType = 0;

	// check working directory

	if (existsFile(".", "mods.conf")) {
		stdstr(&prefixPath, "./");
		stdstr(&configPath, "./mods.conf");
		return;
	}
	if (existsDir(".", "mods.d")) {
		stdstr(&prefixPath, "./");
		stdstr(&configPath, "./mods.d");
		configType = 1;
		return;
	}


	// check environment variable SWORD_PATH

	if (envsworddir != NULL) {
		path = envsworddir;
		path += "/";
		if (existsFile(path.c_str(), "mods.conf")) {
			stdstr(&prefixPath, path.c_str());
			path += "mods.conf";
			stdstr(&configPath, path.c_str());
			return;
		}
		if (existsDir(path.c_str(), "mods.d")) {
			stdstr(&prefixPath, path.c_str());
			path += "mods.d";
			stdstr(&configPath, path.c_str());
			configType = 1;
			return;
		}
	}


	// check ~/.sword/

	if (envhomedir != NULL) {
		path = envhomedir;
		path += "/.sword/";
		if (existsFile(path.c_str(), "mods.conf")) {
			stdstr(&prefixPath, "");
			path += "mods.conf";
			stdstr(&configPath, path.c_str());
			return;
		}
		if (existsDir(path.c_str(), "mods.d")) {
			stdstr(&prefixPath, "");
			path += "mods.d";
			stdstr(&configPath, path.c_str());
			configType = 1;
			return;
		}
	}


	if ((fd = ::open("/etc/sword.conf", O_RDONLY)) > 0) {
		::close(fd);
		SWConfig etcconf("/etc/sword.conf");
		if ((entry = etcconf.Sections["Install"].find("DataPath")) != etcconf.Sections["Install"].end()) {
			path = (*entry).second + "/";

			if (existsFile(path.c_str(), "mods.conf")) {
				stdstr(&prefixPath, path.c_str());
				path += "mods.conf";
				stdstr(&configPath, path.c_str());
				return;
			}
			if (existsDir(path.c_str(), "mods.d")) {
				stdstr(&prefixPath, path.c_str());
				path += "mods.d";
				stdstr(&configPath, path.c_str());
				configType = 1;
				return;
			}
		}
	}
}


void SWMgr::loadConfigDir(const char *ipath)
{
   DIR *dir;
   struct dirent *ent;
   string newmodfile;
 
	if ((dir = opendir(ipath))) {
		rewinddir(dir);
		while ((ent = readdir(dir))) {
			if ((strcmp(ent->d_name, ".")) && (strcmp(ent->d_name, ".."))) {
				newmodfile = ipath;
				newmodfile += "/";
				newmodfile += ent->d_name;
				if (config) {
					SWConfig tmpConfig(newmodfile.c_str());
					*config += tmpConfig;
				}
				else	config = myconfig = new SWConfig(newmodfile.c_str());
			}
		}
		closedir(dir);
		if (!config) {	// if no .conf file exist yet, create a default
			newmodfile = ipath;
			newmodfile += "/globals.conf";
			config = myconfig = new SWConfig(newmodfile.c_str());
		}
	}
}


void SWMgr::Load() {
	if (!config) {	// If we weren't passed a config object at construction, find a config file
		if (!configPath)	// If we weren't passed a config path at construction...
			findConfig();
		if (configPath) {
			if (configType)
				loadConfigDir(configPath);
			else	config = myconfig = new SWConfig(configPath);
		}
	}

	if (config) {
		SectionMap::iterator Sectloop, Sectend;
		ConfigEntMap::iterator Entryloop, Entryend;

		DeleteMods();

		for (Sectloop = config->Sections.lower_bound("Globals"), Sectend = config->Sections.upper_bound("Globals"); Sectloop != Sectend; Sectloop++) {		// scan thru all 'Globals' sections
			for (Entryloop = (*Sectloop).second.lower_bound("AutoInstall"), Entryend = (*Sectloop).second.upper_bound("AutoInstall"); Entryloop != Entryend; Entryloop++)	// scan thru all AutoInstall entries
				InstallScan((*Entryloop).second.c_str());		// Scan AutoInstall entry directory for new modules and install
		}		
		if (configType) {	// force reload on config object because we may have installed new modules
			delete myconfig;
			config = myconfig = 0;
			loadConfigDir(configPath);
		}
		else	config->Load();


		CreateMods();
	}
	else {
		SWLog::systemlog->LogError("SWMgr: Can't find 'mods.conf' or 'mods.d'.  Try setting:\n\tSWORD_PATH=<directory containing mods.conf>\n\tOr see the README file for a full description of setup options (%s)", configPath);
		exit(-1);
	}
}


SWModule *SWMgr::CreateMod(string name, string driver, ConfigEntMap &section)
{
	string description, datapath, misc1;
	ConfigEntMap::iterator entry;
	SWModule *newmod = 0;

	description = ((entry = section.find("Description")) != section.end()) ? (*entry).second : (string)"";
	datapath = prefixPath;
	datapath += "/";
	datapath += ((entry = section.find("DataPath")) != section.end()) ? (*entry).second : (string)"";
	
	if (!stricmp(driver.c_str(), "RawText")) {
		newmod = new RawText(datapath.c_str(), name.c_str(), description.c_str());
	}
	
	if (!stricmp(driver.c_str(), "RawGBF")) {
		newmod = new RawGBF(datapath.c_str(), name.c_str(), description.c_str());
	}

	if (!stricmp(driver.c_str(), "RawCom")) {
		newmod = new RawCom(datapath.c_str(), name.c_str(), description.c_str());
	}
				
	if (!stricmp(driver.c_str(), "RawFiles")) {
		newmod = new RawFiles(datapath.c_str(), name.c_str(), description.c_str());
	}
				
	if (!stricmp(driver.c_str(), "HREFCom")) {
		misc1 = ((entry = section.find("Prefix")) != section.end()) ? (*entry).second : (string)"";
		newmod = new HREFCom(datapath.c_str(), misc1.c_str(), name.c_str(), description.c_str());
	}
				
	if (!stricmp(driver.c_str(), "RawLD"))
		newmod = new RawLD(datapath.c_str(), name.c_str(), description.c_str());

	return newmod;
}


void SWMgr::AddGlobalOptions(SWModule *module, ConfigEntMap &section, ConfigEntMap::iterator start, ConfigEntMap::iterator end)
{
	for (;start != end; start++) {
		FilterMap::iterator it;
		it = optionFilters.find((*start).second);
		if (it != optionFilters.end()) {
			module->AddOptionFilter((*it).second);	// add filter to module and option as a valid option
			OptionsList::iterator loop;
			for (loop = options.begin(); loop != options.end(); loop++) {
				if (!strcmp((*loop).c_str(), (*it).second->getOptionName()))
					break;
			}
			if (loop == options.end())	// if we have not yet included the option
				options.push_back((*it).second->getOptionName());
		}
	}
}


void SWMgr::AddLocalOptions(SWModule *module, ConfigEntMap &section, ConfigEntMap::iterator start, ConfigEntMap::iterator end)
{
	for (;start != end; start++) {
		printf("%s:%s\n", module->Name(), (*start).second.c_str());
	}
}


void SWMgr::AddRenderFilters(SWModule *module, ConfigEntMap &section)
{
	string sourceformat;
	ConfigEntMap::iterator entry;

	sourceformat = ((entry = section.find("SourceType")) != section.end()) ? (*entry).second : (string)"";
	// Temporary: To support old module types
	if (sourceformat.empty()) {
		try {
			if (dynamic_cast<RawGBF *>(module))
				sourceformat = "GBF";
		}
		catch ( ... ) {}
	}

// process module	- eg. follows
//	if (!stricmp(sourceformat.c_str(), "GBF")) {
//		module->AddRenderFilter(gbftortf);
//	}

}


void SWMgr::AddStripFilters(SWModule *module, ConfigEntMap &section)
{
	string sourceformat;
	ConfigEntMap::iterator entry;

	sourceformat = ((entry = section.find("SourceType")) != section.end()) ? (*entry).second : (string)"";
	// Temporary: To support old module types
	if (sourceformat.empty()) {
		try {
			if (dynamic_cast<RawGBF *>(module))
				sourceformat = "GBF";
		}
		catch ( ... ) {}
	}
	
	if (!stricmp(sourceformat.c_str(), "GBF")) {
		module->AddStripFilter(gbfplain);
	}
}


void SWMgr::CreateMods() {
	SectionMap::iterator it;
	ConfigEntMap::iterator start;
	ConfigEntMap::iterator end;
	ConfigEntMap::iterator entry;
	SWModule *newmod;
	string driver, misc1;
	for (it = config->Sections.begin(); it != config->Sections.end(); it++) {
		ConfigEntMap &section = (*it).second;
		newmod = 0;
		
		driver = ((entry = section.find("ModDrv")) != section.end()) ? (*entry).second : (string)"";
		if (!driver.empty()) {
			newmod = CreateMod((*it).first, driver, section);
			if (newmod) {
				start = (*it).second.lower_bound("GlobalOptionFilter");
				end   = (*it).second.upper_bound("GlobalOptionFilter");
				AddGlobalOptions(newmod, section, start, end);

				start = (*it).second.lower_bound("LocalOptionFilter");
				end   = (*it).second.upper_bound("LocalOptionFilter");
				AddLocalOptions(newmod, section, start, end);

				AddStripFilters(newmod, section);
				AddRenderFilters(newmod, section);
				
				Modules.insert(ModMap::value_type(newmod->Name(), newmod));
			}
		}
	}
}


void SWMgr::DeleteMods() {

	ModMap::iterator it;

	for (it = Modules.begin(); it != Modules.end(); it++)
		delete (*it).second;

	Modules.erase(Modules.begin(), Modules.end());
}


void SWMgr::InstallScan(const char *dirname)
{
   DIR *dir;
   struct dirent *ent;
   int conffd = 0;
   string newmodfile;
   string targetName;
 
	if ((dir = opendir(dirname))) {
		rewinddir(dir);
		while ((ent = readdir(dir))) {
			if ((strcmp(ent->d_name, ".")) && (strcmp(ent->d_name, ".."))) {
				newmodfile = dirname;
				newmodfile += "/";
				newmodfile += ent->d_name;
				if (configType) {
					if (config > 0)
						close(conffd);
					targetName = configPath;
					targetName += "/";
					targetName += ent->d_name;
					conffd = open(targetName.c_str(), O_WRONLY|O_CREAT, S_IREAD|S_IWRITE);
				}
				else {
					if (conffd < 1) {
						conffd = open(config->filename.c_str(), O_WRONLY|O_APPEND);
						if (conffd > 0)
							lseek(conffd, 0L, SEEK_END);
					}
				}
				AddModToConfig(conffd, newmodfile.c_str());
				unlink(newmodfile.c_str());
			}
		}
		if (conffd > 0)
			close(conffd);
		closedir(dir);
	}
}


char SWMgr::AddModToConfig(int conffd, const char *fname)
{
	int modfd;
	char ch;

	SWLog::systemlog->LogTimedInformation("Found new module [%s]. Installing...", fname);
	modfd = open(fname, O_RDONLY);
	ch = '\n';
	write(conffd, &ch, 1);
	while (read(modfd, &ch, 1) == 1)
		write(conffd, &ch, 1);
	ch = '\n';
	write(conffd, &ch, 1);
	close(modfd);
	return 0;
}


void SWMgr::setGlobalOption(const char *option, const char *value)
{
	for (FilterMap::iterator it = optionFilters.begin(); it != optionFilters.end(); it++) {
		if (!stricmp(option, (*it).second->getOptionName()))
			(*it).second->setOptionValue(value);
	}
}


const char *SWMgr::getGlobalOption(const char *option)
{
	for (FilterMap::iterator it = optionFilters.begin(); it != optionFilters.end(); it++) {
		if (!stricmp(option, (*it).second->getOptionName()))
			return (*it).second->getOptionValue();
	}
	return 0;
}


const char *SWMgr::getGlobalOptionTip(const char *option)
{
	for (FilterMap::iterator it = optionFilters.begin(); it != optionFilters.end(); it++) {
		if (!stricmp(option, (*it).second->getOptionName()))
			return (*it).second->getOptionTip();
	}
	return 0;
}


OptionsList SWMgr::getGlobalOptions()
{
	return options;
}


OptionsList SWMgr::getGlobalOptionValues(const char *option)
{
	OptionsList options;
	for (FilterMap::iterator it = optionFilters.begin(); it != optionFilters.end(); it++) {
		if (!stricmp(option, (*it).second->getOptionName())) {
			options = (*it).second->getOptionValues();
			break;	// just find the first one.  All option filters with the same option name should expect the same values
		}
	}
	return options;
}

