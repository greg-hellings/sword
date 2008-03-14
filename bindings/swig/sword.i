%include <stl.i>
%include <std_map.i>

#define SWDLLEXPORT  

%module "Sword"
%module(directors="1") Sword;

%feature("director") sword::SWLog::logMessage;

%feature("director") RenderCallback;
%feature("director") MarkupCallback;

%feature("director") SWSearcher;

%feature("director") sword::StatusReporter;


%feature("director:except") {
    if ($error != NULL) {
        throw Swig::DirectorMethodException();
    }
}

%exception {
    try { $action }
    catch (Swig::DirectorException &e) { SWIG_fail; }
}




%ignore *::operator=;
%ignore *::operator++;
%ignore *::operator--;
%ignore *::operator const char *;
%ignore *::operator sword::SWKey &;
%ignore *::operator sword::SWKey *;


%include "defs.i"

%include "swbuf.i"

%include "swconfig.i"
%include "swobject.i"


%include "swkey.i"
%include "listkey.i"
%include "versekey.i"
%include "treekey.i"
%include "treekeyidx.i"
%include "versetreekey.i"

%include "swdisp.i"

%include "swfilter.i"
%include "swoptfilter.i"
%include "swfiltermgr.i"


%include "swsearchable.i"
//%include "swcacher.i"
%include "swmodule.i"


%include "swmgr.i"

%include "encfiltmgr.i"
%include "markupfiltmgr.i"

%include "swlocale.i"

%include "swcomprs.i"
%include "lzsscomprs.i"
%include "zipcomprs.i"


%include "swcom.i"
%include "rawcom.i"
%include "zcom.i"

%include "swgenbook.i"
%include "rawgenbook.i"

%include "swld.i"
%include "rawld.i"
%include "rawld4.i"
%include "zld.i"

%include "swtext.i"
%include "rawtext.i"
%include "ztext.i"

%include "localemgr.i"

%include "url.i"

%include "bases.i"
%include "osishtmlhref.i"
%include "extras.i"
%include "swlog.i"
%include "installmgr.i"
