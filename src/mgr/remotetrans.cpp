/*****************************************************************************
 *
 *  remotetrans.cpp -	
 *
 * $Id$
 *
 * Copyright 2004-2013 CrossWire Bible Society (http://www.crosswire.org)
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


 

#include <remotetrans.h>
#include <filemgr.h>

#include <fcntl.h>
#include <dirent.h>
#include <swlog.h>

extern "C" {
#include <ftpparse.h>
}

using std::vector;


SWORD_NAMESPACE_START


namespace {

void removeTrailingSlash(SWBuf &buf) {
	int len = buf.size();
	if ((buf[len-1] == '/')
	 || (buf[len-1] == '\\'))
		buf.size(len-1);
}

};


void StatusReporter::preStatus(long totalBytes, long completedBytes, const char *message) {
}

void StatusReporter::statusUpdate(double dtTotal, double dlNow) {
}


RemoteTransport::RemoteTransport(const char *host, StatusReporter *statusReporter) {
	this->statusReporter = statusReporter;
	this->host = host;
	u = "ftp";
	p = "installmgr@user.com";
	term = false;
}


RemoteTransport::~RemoteTransport() {
}


// override this method in your real transport class
char RemoteTransport::getURL(const char *destPath, const char *sourceURL, SWBuf *destBuf) {
	char retVal = 0;
	return retVal;
}


vector<struct DirEntry> RemoteTransport::getDirList(const char *dirURL) {

	vector<struct DirEntry> dirList;
	
	SWBuf dirBuf;
	if (!getURL("", dirURL, &dirBuf)) {
		char *start = dirBuf.getRawData();
		char *end = start;
		while (start < (dirBuf.getRawData()+dirBuf.size())) {
			struct ftpparse item;
			bool looking = true;
			for (end = start; *end; end++) {
				if (looking) {
					if ((*end == 10) || (*end == 13)) {
						*end = 0;
						looking = false;
					}
				}
				else if ((*end != 10) && (*end != 13))
					break;
			}
			SWLog::getSystemLog()->logWarning("getDirList: parsing item %s(%d)\n", start, end-start);
			int status = ftpparse(&item, start, end - start);
			// in ftpparse.h, there is a warning that name is not necessarily null terminated
			SWBuf name;
			name.append(item.name, item.namelen);
			SWLog::getSystemLog()->logWarning("getDirList: got item %s\n", name.c_str());
			if (status && name != "." && name != "..") {
				struct DirEntry i;
				i.name = name;
				i.size = item.size;
				i.isDirectory = (item.flagtrycwd == 1);
				dirList.push_back(i);
			}
			start = end;
		}
	}
	else {
		SWLog::getSystemLog()->logWarning("getDirList: failed to get dir %s\n", dirURL);
	}
	return dirList;
}


int RemoteTransport::copyDirectory(const char *urlPrefix, const char *dir, const char *dest, const char *suffix) {
	unsigned int i;
	int retVal = 0;
	
	SWBuf url = SWBuf(urlPrefix) + SWBuf(dir);
	removeTrailingSlash(url);
	url += '/';
	
	SWLog::getSystemLog()->logWarning("NetTransport: getting dir %s\n", url.c_str());
	vector<struct DirEntry> dirList = getDirList(url.c_str());

	if (!dirList.size()) {
		SWLog::getSystemLog()->logWarning("NetTransport: failed to read dir %s\n", url.c_str());
		return -1;
	}
				
	long totalBytes = 0;
	for (i = 0; i < dirList.size(); i++)
		totalBytes += dirList[i].size;
	long completedBytes = 0;
	for (i = 0; i < dirList.size(); i++) {
		struct DirEntry &dirEntry = dirList[i];
		SWBuf buffer = (SWBuf)dest;
		removeTrailingSlash(buffer);
		buffer += "/";
		buffer += dirEntry.name;
		if (!strcmp(&buffer.c_str()[buffer.length()-strlen(suffix)], suffix)) {
			SWBuf buffer2 = "Downloading (";
			buffer2.appendFormatted("%d", i+1);
			buffer2 += " of ";
			buffer2.appendFormatted("%d", dirList.size());
			buffer2 += "): ";
			buffer2 += dirEntry.name;
			if (statusReporter)
				statusReporter->preStatus(totalBytes, completedBytes, buffer2.c_str());
			FileMgr::createParent(buffer.c_str());	// make sure parent directory exists
			SWTRY {
				SWBuf url = (SWBuf)urlPrefix + (SWBuf)dir;
				removeTrailingSlash(url);
				url += "/";
				url += dirEntry.name; //dont forget the final slash
				if (!dirEntry.isDirectory) {
					if (getURL(buffer.c_str(), url.c_str())) {
						SWLog::getSystemLog()->logWarning("copyDirectory: failed to get file %s\n", url.c_str());
						return -2;
					}
					completedBytes += dirEntry.size;
				}
				else {
					SWBuf subdir = (SWBuf)dir;
					removeTrailingSlash(subdir);
					subdir += (SWBuf)"/" + dirEntry.name;
					if (copyDirectory(urlPrefix, subdir, buffer.c_str(), suffix)) {
						SWLog::getSystemLog()->logWarning("copyDirectory: failed to get file %s\n", subdir.c_str());
						return -2;
					}
				}
			}
			SWCATCH (...) {}
			if (term) {
				retVal = -3;
				break;
			}
		}
	}
	return retVal;
}


SWORD_NAMESPACE_END
