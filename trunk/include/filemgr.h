/******************************************************************************
*  filemgr.h   - definition of class FileMgr used for pooling file handles
*
* $Id$
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

#ifndef FILEMGR_H
#define FILEMGR_H

#include <sys/stat.h>
#include <fcntl.h>

#include <defs.h>
#include <swbuf.h>
#include <swcacher.h>

SWORD_NAMESPACE_START

#ifndef O_BINARY
#define O_BINARY 0
#endif

class SWDLLEXPORT FileMgr;

/**
* This class represents one file. It works with the FileMgr object.
*/
class SWDLLEXPORT FileDesc {

	friend class FileMgr;

	long offset;
	int fd;			// -77 closed;
	FileMgr *parent;
	FileDesc *next;

	FileDesc(FileMgr * parent, const char *path, int mode, int perms, bool tryDowngrade);
	virtual ~FileDesc();

public:
	/** @return File handle.
	*/
	int getFd();
	/** Path to file.
	*/
	char *path;
	/** File access mode.
	*/
	int mode;
	/** File permissions.
	*/
	int perms;
	/**
	*/
	bool tryDowngrade;
};

/**
*	This class ist used make file access operations easier.
* It keeps a list of all open files internally and closes them
* when the destructor is called.
*/
class FileMgr : public SWCacher {

	friend class FileDesc;
	friend class __staticsystemFileMgr;

	FileDesc *files;
	int sysOpen(FileDesc * file);
protected:
	static FileMgr *systemFileMgr;
public:

	/** Maximum number of open files set in the constructor.
	* determines the max number of real system files that
	* filemgr will open.  Adjust for tuning.
	*/
	int maxFiles;
	
	static FileMgr *getSystemFileMgr();
	static void setSystemFileMgr(FileMgr *newFileMgr);

	/** Constructor.
	* @param maxFiles The number of files that this FileMgr may open in parallel, if necessary.
	*/
	FileMgr(int maxFiles = 35);

	/**
	* Destructor. Clean things up. Will close all files opened by this FileMgr object.
	*/
	~FileMgr();

	/** Open a file and return a FileDesc for it.
	* The file itself will only be opened when FileDesc::getFd() is called.
	* @param path Filename.
	* @param mode File access mode.
	* @param tryDowngrade
	* @return FileDesc object for the requested file.
	*/
	FileDesc *open(const char *path, int mode, bool tryDowngrade);

	/** Open a file and return a FileDesc for it.
	* The file itself will only be opened when FileDesc::getFd() is called.
	* @param path Filename.
	* @param mode File access mode.
	* @param perms Permissions.
	* @param tryDowngrade
	* @return FileDesc object for the requested file.
	*/
	FileDesc *open(const char *path, int mode, int perms = S_IREAD | S_IWRITE, bool tryDowngrade = false);

	/** Close a given file and delete its FileDesc object.
	* Will only close the file if it was created by this FileMgr object.
	* @param file The file to close.
	*/
	void close(FileDesc * file);

	/** Cacher methods overridden
	 */
	virtual void flush();
	virtual long resourceConsumption();

	/** Checks for the existence of a file.
	* @param ipath Path to file.
	* @param ifileName Name of file to check for.
	*/
	static signed char existsFile(const char *ipath, const char *ifileName = 0);

	/** Checks for the existence of a directory.
	* @param ipath Path to directory.
	* @param idirName Name of directory to check for.
	*/
	static signed char existsDir(const char *ipath, const char *idirName = 0);

	/** Truncate a file at its current position
	* leaving byte at current possition intact deleting everything afterward.
	* @param file The file to operate on.
	*/
	signed char trunc(FileDesc *file);

	static char isDirectory(const char *path);
	static int createParent(const char *pName);
	static int createPathAndFile(const char *fName);
	static int copyFile(const char *srcFile, const char *destFile);
	static int copyDir(const char *srcDir, const char *destDir);
	static int removeDir(const char *targetDir);
	static int removeFile(const char *fName);
	static char getLine(FileDesc *fDesc, SWBuf &line);

};


SWORD_NAMESPACE_END
#endif
