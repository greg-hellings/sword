/******************************************************************************
 *  swconfig.cpp   - implementation of Class SWConfig used for saving and
 *			retrieval of configuration information
 *
 * $Id: swconfig.cpp,v 1.8 2002/06/13 05:19:03 scribe Exp $
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

#include <swconfig.h>
#include <utilfuns.h>


SWConfig::SWConfig(const char * ifilename) {
	filename = ifilename;
	Load();
}


SWConfig::~SWConfig() {
}


char SWConfig::getline(FILE *fp, string &line)
{
	char retval = 0;
	char buf[255];

	line = "";
	
	while (fgets(buf, 254, fp)) {
		while (buf[strlen(buf)-1] == '\n' || buf[strlen(buf)-1] == '\r')
			buf[strlen(buf)-1] = 0;

		if (buf[strlen(buf)-1] == '\\') {
			buf[strlen(buf)-1] = 0;
			line += buf;
			continue;
		}
		line += buf;

		if (strlen(buf) < 253) {
			retval = 1;
			break;
		}
	}
	return retval;
}


void SWConfig::Load() {
	FILE *cfile;
	char *buf, *data;
	string line;
	ConfigEntMap cursect;
	string sectname;
	bool first = true;
	
	Sections.erase(Sections.begin(), Sections.end());
	
	if ((cfile = fopen(filename.c_str(), "r"))) {
		while (getline(cfile, line)) {
			buf = new char [ line.length() + 1 ];
			strcpy(buf, line.c_str());
			if (*strstrip(buf) == '[') {
				if (!first)
					Sections.insert(SectionMap::value_type(sectname, cursect));
				else first = false;
				
				cursect.erase(cursect.begin(), cursect.end());

				strtok(buf, "]");
				sectname = buf+1;
			}
			else {
				strtok(buf, "=");
				if ((*buf) && (*buf != '=')) {
					if ((data = strtok(NULL, "")))
						cursect.insert(ConfigEntMap::value_type(buf, strstrip(data)));
					else cursect.insert(ConfigEntMap::value_type(buf, ""));
				}
			}
			delete [] buf;
		}
		if (!first)
			Sections.insert(SectionMap::value_type(sectname, cursect));

		fclose(cfile);
	}
}


void SWConfig::Save() {
	FILE *cfile;
	string buf;
	SectionMap::iterator sit;
	ConfigEntMap::iterator entry;
	string sectname;
	
	if ((cfile = fopen(filename.c_str(), "w"))) {
		
		for (sit = Sections.begin(); sit != Sections.end(); sit++) {
			buf =  "\n[";
			buf += (*sit).first.c_str();
			buf += "]\n";
			fputs(buf.c_str(), cfile);
			for (entry = (*sit).second.begin(); entry != (*sit).second.end(); entry++) {
				buf = (*entry).first.c_str();
				buf += "=";
				buf += (*entry).second.c_str();
				buf += "\n";
				fputs(buf.c_str(), cfile);
			}
		}
		fputs("\n", cfile);	// so getline will find last line
		fclose(cfile);
	}
}


SWConfig &SWConfig::operator +=(SWConfig &addFrom)
{

	SectionMap::iterator section;
	ConfigEntMap::iterator entry, start, end;

	for (section = addFrom.Sections.begin(); section != addFrom.Sections.end(); section++) {
		for (entry = (*section).second.begin(); entry != (*section).second.end(); entry++) {
			start = Sections[section->first].lower_bound(entry->first);
			end   = Sections[section->first].upper_bound(entry->first);
			if (start != end) {
				if (((++start) != end)
						|| ((++(addFrom.Sections[section->first].lower_bound(entry->first))) != addFrom.Sections[section->first].upper_bound(entry->first))) {
					for (--start; start != end; start++) {
						if (!strcmp(start->second.c_str(), entry->second.c_str()))
							break;
					}
					if (start == end)
						Sections[(*section).first].insert(ConfigEntMap::value_type((*entry).first, (*entry).second));
				}
				else	Sections[section->first][entry->first.c_str()] = entry->second.c_str();
			}		
			else	Sections[section->first][entry->first.c_str()] = entry->second.c_str();
		}
	}
	return *this;
}


ConfigEntMap & SWConfig::operator [] (const char *section) {
    return Sections[section];
}
