#ifndef INSTALLMGR_H
#define INSTALLMGR_H

#include <defs.h>
#include <swbuf.h>
#include <map>
#include <set>
#include <ftptrans.h>

SWORD_NAMESPACE_START

class SWMgr;
class SWConfig;


class InstallSource {
	SWMgr *mgr;
public:
	InstallSource(const char *type, const char *confEnt = 0);
	virtual ~InstallSource();
	SWBuf getConfEnt() {
		return caption +"|" + source + "|" + directory;
	}
	SWBuf type;
	SWBuf source;
	SWBuf directory;
	SWBuf caption;
	SWBuf localShadow;
	void *userData;
	SWMgr *getMgr();
	void flush();
};

typedef std::map<SWBuf, InstallSource *> InstallSourceMap;

class InstallMgr {

protected:
	std::set<SWBuf> defaultMods;
	char *privatePath;
	StatusReporter *statusReporter;
	bool passive;
	
	// override this method and provide your own custom FTPTransport subclass
	virtual FTPTransport *createFTPTransport(const char *host, StatusReporter *statusReporter);

	// we have a transport member to set as current running transport so we
	// can ask it to terminate below, if user requests
	FTPTransport *transport;	
	
public:
	SWConfig *installConf;
	InstallSourceMap sources;
	bool term;

	InstallMgr(const char *privatePath = "./", StatusReporter *statusReporter = 0);
	virtual ~InstallMgr();

	virtual int removeModule(SWMgr *manager, const char *modName);
	virtual int ftpCopy(InstallSource *is, const char *src, const char *dest, bool dirTransfer = false, const char *suffix = "");
	virtual int installModule(SWMgr *destMgr, const char *fromLocation, const char *modName, InstallSource *is = 0);
	
	virtual int refreshRemoteSource(InstallSource *is);
	virtual bool getCipherCode(const char *modName, SWConfig *config);
	void setFTPPassive(bool passive) { this->passive = passive; }
	void terminate() { if (transport) transport->terminate(); }

	/************************************************************************
	 * isDefaultModule - allows an installation to provide a set of modules
	 *   in installMgr.conf like:
	 *     [General]
	 *     DefaultMod=KJV
	 *     DefaultMod=StrongsGreek
	 *     DefaultMod=Personal
	 *   This method allows a user interface to ask if a module is specified
	 *   as a default in the above way.  The logic is, if no modules are
	 *   installed then all default modules should be automatically selected for install
	 *   to help the user select a basic foundation of useful modules
	 */
	bool isDefaultModule(const char *modName);
};


SWORD_NAMESPACE_END

#endif
