/******************************************************************************
 * canon.h - Canonical text information to be included by VerseKey.cpp
 *
 * $Id$
 *
 * Copyright 1998-2005 CrossWire Bible Society (http://www.crosswire.org)
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

/******************************************************************************
 * [on]tbooks - initialize static instance for all canonical text names
 *		and chapmax
 */

#include <defs.h>
//SWORD_NAMESPACE_START

/******************************************************************************
 *
 * The list of books as enum to make the 'abbreviation
 *	easier to read.
 *	
 *   They are OSIS ids with the exception that the enums can't start with an
 *    	integer so they use roman numerals instead
 *
 *   Locale files will use OSIS ids
 *   
*/
   
enum canon_books {
#ifdef INTRO_BOOKS
	OT,
#endif
	Gen, Exod, Lev, Num, Deut, Josh, Judg, Ruth, ISam, IISam,
	IKgs, IIKgs, IChr, IIChr, Ezra, Neh, Esth, Job, Ps,
	Prov, Eccl,
	Song, Isa, Jer, Lam, Ezek, Dan, Hos, Joel, Amos, Obad,
	Jonah, Mic, Nah, Hab, Zeph, Hag, Zech, Mal,
#ifdef INTRO_BOOKS
	NT,
#endif
	Matt, Mark, Luke, John, Acts, Rom, ICor, IICor, Gal, Eph,
	Phil, Col, IThess, IIThess, ITim, IITim, Titus, Phlm, Heb, Jas,
	IPet, IIPet, IJohn, IIJohn, IIIJohn, Jude, Rev
};
	

struct sbook
  VerseKey::otbooks[] = {
#ifdef INTRO_BOOKS
  {"Old Testament", "OT", 0},
#endif
  {"Genesis", "Gen", 50},
  {"Exodus", "Exod", 40},
  {"Leviticus", "Lev", 27},
  {"Numbers", "Num", 36},
  {"Deuteronomy", "Deut", 34},
  {"Joshua", "Josh", 24},
  {"Judges", "Judg", 21},
  {"Ruth", "Ruth", 4},
  {"I Samuel", "1Sam", 31},
  {"II Samuel", "2Sam", 24},
  {"I Kings", "1Kgs", 22},
  {"II Kings", "2Kgs", 25},
  {"I Chronicles", "1Chr", 29},
  {"II Chronicles", "2Chr", 36},
  {"Ezra", "Ezra", 10},
  {"Nehemiah", "Neh", 13},
  {"Esther", "Esth", 10},
  {"Job", "Job", 42},
  {"Psalms", "Ps", 150},
  {"Proverbs", "Prov", 31},
  {"Ecclesiastes", "Eccl", 12},
  {"Song of Solomon", "Song", 8},
  {"Isaiah", "Isa", 66},
  {"Jeremiah", "Jer", 52},
  {"Lamentations", "Lam", 5},
  {"Ezekiel", "Ezek", 48},
  {"Daniel", "Dan", 12},
  {"Hosea", "Hos", 14},
  {"Joel", "Joel", 3},
  {"Amos", "Amos", 9},
  {"Obadiah", "Obad", 1},
  {"Jonah", "Jonah", 4},
  {"Micah", "Mic", 7},
  {"Nahum", "Nah", 3},
  {"Habakkuk", "Hab", 3},
  {"Zephaniah", "Zeph", 3},
  {"Haggai", "Hag", 2},
  {"Zechariah", "Zech", 14},
  {"Malachi", "Mal", 4}
};

struct sbook
  VerseKey::ntbooks[] = {
#ifdef INTRO_BOOKS
  {"New Testament", "NT", 0},
#endif
  {"Matthew", "Matt", 28},
  {"Mark", "Mark", 16},
  {"Luke", "Luke", 24},
  {"John", "John", 21},
  {"Acts", "Acts", 28},
  {"Romans", "Rom", 16},
  {"I Corinthians", "1Cor", 16},
  {"II Corinthians", "2Cor", 13},
  {"Galatians", "Gal", 6},
  {"Ephesians", "Eph", 6},
  {"Philippians", "Phil", 4},
  {"Colossians", "Col", 4},
  {"I Thessalonians", "1Thess", 5},
  {"II Thessalonians", "2Thess", 3},
  {"I Timothy", "1Tim", 6},
  {"II Timothy", "2Tim", 4},
  {"Titus", "Titus", 3},
  {"Philemon", "Phlm", 1},
  {"Hebrews", "Heb", 13},
  {"James", "Jas", 5},
  {"I Peter", "1Pet", 5},
  {"II Peter", "2Pet", 3},
  {"I John", "1John", 5},
  {"II John", "2John", 1},
  {"III John", "3John", 1},
  {"Jude", "Jude", 1},
  {"Revelation of John", "Rev", 22}
};


/******************************************************************************
 *	Abbreviations - MUST be in alphabetical order & by PRIORITY
 *		RULE: first match of entire key
 *			(e.g. key: "1CH"; match: "1CHRONICLES")
 */

const struct abbrev
  VerseKey::builtin_abbrevs[] = {
  {"1 C", ICor},		//   1 Corinthians
  {"1 CHRONICLES", IChr},	//   1 Chronicles
  {"1 CORINTHIANS", ICor},	//   1 Corinthians
  {"1 JN", IJohn},		//    1 John
  {"1 JOHN", IJohn},		//    1 John
  {"1 KGS", IKgs},		//    1 Kings
  {"1 KINGS", IKgs},		//    1 Kings
  {"1 PETER", IPet},		//    1 Peter
  {"1 PTR", IPet},		//    1 Peter
  {"1 SAMUEL", ISam},		//    1 Samuel
  {"1 THESSALONIANS", IThess},	//   1 Thessalonians
  {"1 TIMOTHY", ITim},		//   1 Timothy
  {"1C", ICor},			//   1 Corinthians
  {"1CHRONICLES", IChr},	//   1 Chronicles
  {"1CORINTHIANS", ICor},	//   1 Corinthians
  {"1JN", IJohn},		//    1 John       
  {"1JOHN", IJohn},		//    1 John
  {"1KGS", IKgs},		// 1 Kings
  {"1KINGS", IKgs},		//    1 Kings
  {"1PETER", IPet},		//    1 Peter
  {"1PTR", IPet},		//    1 Peter
  {"1SAMUEL", ISam},		//    1 Samuel
  {"1THESSALONIANS", IThess},	//   1 Thessalonians
  {"1TIMOTHY", ITim},		//   1 Timothy
  {"2 C", IICor},		//   2 Corinthians
  {"2 CHRONICLES", IIChr},	//   2 Chronicles
  {"2 CORINTHIANS", IICor},	//   2 Corinthians
  {"2 JN", IIJohn},		//    2 John
  {"2 JOHN", IIJohn},		//    2 John
  {"2 KGS", IIKgs},		//    2 Kings
  {"2 KINGS", IIKgs},		//    2 Kings
  {"2 PETER", IIPet},		//    2 Peter
  {"2 PTR", IIPet},		//    2 Peter
  {"2 SAMUEL", IISam},		//    2 Samuel
  {"2 THESSALONIANS", IIThess},	//   2 Thessalonians
  {"2 TIMOTHY", IITim},		//   2 Timothy
  {"2C", IICor},		//   2 Corinthians
  {"2CHRONICLES", IIChr},	//   2 Chronicles
  {"2CORINTHIANS", IICor},	//   2 Corinthians
  {"2JN", IIJohn},		//    2 John    
  {"2JOHN", IIJohn},		//    2 John
  {"2KGS", IIKgs},		// 2 Kings
  {"2KINGS", IIKgs},		//    2 Kings
  {"2PETER", IIPet},		//    2 Peter
  {"2PTR", IIPet},		//    2 Peter
  {"2SAMUEL", IISam},		//    2 Samuel
  {"2THESSALONIANS", IIThess},	//   2 Thessalonians
  {"2TIMOTHY", IITim},		//   2 Timothy
  {"3 JN", IIIJohn},		//    3 John
  {"3 JOHN", IIIJohn},		//    3 John
  {"3JN", IIIJohn},		//    3 John
  {"3JOHN", IIIJohn},		//    3 John
  {"ACTS", Acts},		//     Acts
  {"AMOS", Amos},		//    Amos
  {"APOCALYPSE OF ST. JOHN", Rev}, //    Apocalypse of St. John (Rev.)
  {"C", Col},			//    Colossians
  {"CANTICLE OF CANTICLES", Song}, //    Canticle of Canticles (Song of S.)
  {"COLOSSIANS", Col},		//    Colossians
  {"D", Deut},			//     Deuteronomy
  {"DANIEL", Dan},		//    Daniel
  {"DEUTERONOMY", Deut},	//    Deuteronomy
  {"E", Eph},			//     Ephesians
  {"ECCLESIASTES", Eccl},	//    Ecclesiastes
  {"EPHESIANS", Eph},		//    Ephesians
  {"ESTER", Esth},		//    Esther
  {"ESTHER", Esth},		//    Esther
  {"EXODUS", Exod},		//    Exodus
  {"EZEKIEL", Ezek},		//   Ezekiel
  {"EZK", Ezek},		//   Ezekiel
  {"EZRA", Ezra},		//   Ezra
  {"G", Gen},			//     Genesis
  {"GALATIANS", Gal},		//    Galatians
  {"GENESIS", Gen},		//    Genesis
  {"H", Heb},			//     Hebrews
  {"HABAKKUK", Hab},		//    Habakkuk
  {"HAGGAI", Hag},		//   Haggai
  {"HEBREWS", Heb},		//    Hebrews
  {"HOSEA", Hos},		//    Hosea
  {"I C", ICor},		//   1 Corinthians
  {"I CHRONICLES", IChr},	//   1 Chronicles
  {"I CORINTHIANS", ICor},	//   1 Corinthians
  {"I JN", IJohn},		//    1 John
  {"I JOHN", IJohn},		//    1 John
  {"I KGS", IKgs},		// 1 Kings
  {"I KINGS", IKgs},		//    1 Kings
  {"I PETER", IPet},		//    1 Peter
  {"I PTR", IPet},		//    1 Peter
  {"I SAMUEL", ISam},		//    1 Samuel
  {"I THESSALONIANS", IThess},	//   1 Thessalonians
  {"I TIMOTHY", ITim},		//   1 Timothy
  {"IC", ICor},			//   1 Corinthians
  {"ICHRONICLES", IChr},	//   1 Chronicles
  {"ICORINTHIANS", ICor},	//   1 Corinthians
  {"II C", IICor},		//   2 Corinthians
  {"II CHRONICLES", IIChr},	//   2 Chronicles
  {"II CORINTHIANS", IICor},	//   2 Corinthians
  {"II JN", IIJohn},		//    2 John  
  {"II JOHN", IIJohn},		//    2 John
  {"II KGS", IIKgs},		// 2 Kings
  {"II KINGS", IIKgs},		//    2 Kings
  {"II PETER", IIPet},		//    2 Peter
  {"II PTR", IIPet},		//    2 Peter
  {"II SAMUEL", IISam},		//    2 Samuel
  {"II THESSALONIANS", IIThess},//   2 Thessalonians
  {"II TIMOTHY", IITim},	//   2 Timothy
  {"IIC", IICor},		//   2 Corinthians
  {"IICHRONICLES", IIChr},	//   2 Chronicles
  {"IICORINTHIANS", IICor},	//   2 Corinthians
  {"III JN", IIIJohn},		//    3 John 
  {"III JOHN", IIIJohn},	//    3 John
  {"IIIJN", IIIJohn},		//    3 John
  {"IIIJOHN", IIIJohn},		//    3 John
  {"IIJN", IIJohn},		//    2 John
  {"IIJOHN", IIJohn},		//    2 John
  {"IIKGS", IIKgs},		// 2 Kings
  {"IIKINGS", IIKgs},		//    2 Kings
  {"IIPETER", IIPet},		//    2 Peter
  {"IIPTR", IIPet},		//    2 Peter
  {"IISAMUEL", IISam},		//    2 Samuel
  {"IITHESSALONIANS", IIThess},	//   2 Thessalonians
  {"IITIMOTHY", IITim},		//   2 Timothy
  {"IJN", IJohn},		//    1 John
  {"IJOHN", IJohn},		//    1 John
  {"IKGS", IKgs},		// 1 Kings
  {"IKINGS", IKgs},		//    1 Kings
  {"IPETER", IPet},		//    1 Peter
  {"IPTR", IPet},		//    1 Peter
  {"ISA", Isa},			//     Isaiah
  {"ISAIAH", Isa},		//     Isaiah
  {"ISAMUEL", ISam},		//    1 Samuel
  {"ITHESSALONIANS", IThess},	//   1 Thessalonians
  {"ITIMOTHY", ITim},		//   1 Timothy
  {"J", Luke},			//     John
  {"JAMES", Jas},		//    James
  {"JAS", Jas},			//    James
  {"JDGS", Judg},		//  Judges
  {"JEREMIAH", Jer},		//    Jeremiah
  {"JHN", John},		//    John
  {"JN", John},			//    John
  {"JO", John},			//    John
  {"JOB", Job},			//   Job
  {"JOEL", Joel},		//   Joel
  {"JOHN", John},		//   John
  {"JOL", Joel},		//   Joel
  {"JONAH", Jonah},		//   Jonah
  {"JOSHUA", Josh},		//   Joshua
  {"JUDE", Jude},		//  Jude
  {"JUDGES", Judg},		//  Judges
  {"L", Luke},			//     Luke
  {"LAMENTATIONS", Lam},	//    Lamentations
  {"LEVITICUS", Lev},		//    Leviticus
  {"LK", Luke},			//    Luke
  {"LUKE", Luke},		//    Luke
  {"MA", Matt},			//    Matthew
  {"MALACHI", Mal},		//   Malachi
  {"MARK", Mark},		//   Mark
  {"MATTHEW", Matt},		//   Matthew
  {"MICAH", Mic},		//    Micah
  {"MK", Mark},			//    Mark
  {"MRK", Mark},		//    Mark
  {"MT", Matt},			//    Matthew
  {"N", Num},			//     Numbers
  {"NAHUM", Nah},		//    Nahum
  {"NAM", Nah},			//    Nahum
  {"NEHEMIAH", Neh},		//    Nehemiah
#ifdef INTRO_BOOKS
  {"NEW TESTAMENT", NT},	//    New Testament
  {"NT", NT},			//    New Testament
#endif
  {"NUMBERS", Num},		//    Numbers
  {"OBADIAH", Obad},		//     Obadiah
#ifdef INTRO_BOOKS
  {"OLD TESTAMENT", OT},	//     Old Testament
  {"OT", OT},			//     Old Testament
#endif
  {"P", Ps},			//     Psalms
  {"PHIL", Phil},		//    Philippians
  {"PHILEMON", Phlm},		// Philemon
  {"PHILIPPIANS", Phil},	// Philippians
  {"PHLM", Phlm},		// Philemon
  {"PHM", Phlm},		//   Philemon
  {"PHP", Phil},		//   Philippians
  {"PROVERBS", Prov},		//    Proverbs
  {"PSALMS", Ps},		//    Psalms
  {"PSM", Ps},			// Psalms
  {"PSS", Ps},			// Psalms
  {"QOHELETH", Eccl},           // Qohelet (Ecclesiastes)
  {"REVELATION OF JOHN", Rev},	//     Revelation
  {"ROMANS", Rom},		//    Romans
  {"RUTH", Ruth},		//    Ruth
  {"SNG", Song},		//     Song of Solomon
  {"SOLOMON", Song},		//     Song of Solomon
  {"SONG OF SOLOMON", Song},	//     Song of Solomon
  {"SONG OF SONGS", Song},	//     Song of Solomon
  {"SOS", Song},		//     Song of Solomon
  {"TITUS", Titus},		//     Titus
  {"ZECHARIAH", Zech},		//   Zechariah
  {"ZEPHANIAH", Zeph},		//   Zephaniah
  {"", -1}
};


/******************************************************************************
 *	Maximum verses per chapter
 */

int
  VerseKey::vm[] = {
  // Genesis
  31, 25, 24, 26, 32, 22, 24, 22, 29, 32, 32, 20, 18, 24, 21, 16, 27, 33, 38,
    18, 34, 24, 20, 67, 34, 35, 46, 22, 35, 43, 55, 32, 20, 31, 29, 43, 36,
    30, 23, 23, 57, 38, 34, 34, 28, 34, 31, 22, 33, 26,
  // Exodus
  22, 25, 22, 31, 23, 30, 25, 32, 35, 29, 10, 51, 22, 31, 27, 36, 16, 27, 25,
    26, 36, 31, 33, 18, 40, 37, 21, 43, 46, 38, 18, 35, 23, 35, 35, 38, 29,
    31, 43, 38,
  // Leviticus
  17, 16, 17, 35, 19, 30, 38, 36, 24, 20, 47, 8, 59, 57, 33, 34, 16, 30, 37,
    27, 24, 33, 44, 23, 55, 46, 34,
  // Numbers
  54, 34, 51, 49, 31, 27, 89, 26, 23, 36, 35, 16, 33, 45, 41, 50, 13, 32, 22,
    29, 35, 41, 30, 25, 18, 65, 23, 31, 40, 16, 54, 42, 56, 29, 34, 13,
  // Deuteronomy
  46, 37, 29, 49, 33, 25, 26, 20, 29, 22, 32, 32, 18, 29, 23, 22, 20, 22, 21,
    20, 23, 30, 25, 22, 19, 19, 26, 68, 29, 20, 30, 52, 29, 12,
  // Joshua
  18, 24, 17, 24, 15, 27, 26, 35, 27, 43, 23, 24, 33, 15, 63, 10, 18, 28, 51,
    9, 45, 34, 16, 33,
  // Judges
  36, 23, 31, 24, 31, 40, 25, 35, 57, 18, 40, 15, 25, 20, 20, 31, 13, 31, 30,
    48, 25,
  // Ruth
  22, 23, 18, 22,
  // I Samual
  28, 36, 21, 22, 12, 21, 17, 22, 27, 27, 15, 25, 23, 52, 35, 23, 58, 30, 24,
    42, 15, 23, 29, 22, 44, 25, 12, 25, 11, 31, 13,
  // II Samuel
  27, 32, 39, 12, 25, 23, 29, 18, 13, 19, 27, 31, 39, 33, 37, 23, 29, 33, 43,
    26, 22, 51, 39, 25,
  // I Kings
  53, 46, 28, 34, 18, 38, 51, 66, 28, 29, 43, 33, 34, 31, 34, 34, 24, 46, 21,
    43, 29, 53,
  // II Kings
  18, 25, 27, 44, 27, 33, 20, 29, 37, 36, 21, 21, 25, 29, 38, 20, 41, 37, 37,
    21, 26, 20, 37, 20, 30,
  // I Chronicles
  54, 55, 24, 43, 26, 81, 40, 40, 44, 14, 47, 40, 14, 17, 29, 43, 27, 17, 19,
    8, 30, 19, 32, 31, 31, 32, 34, 21, 30,
  // II Chronicles
  17, 18, 17, 22, 14, 42, 22, 18, 31, 19, 23, 16, 22, 15, 19, 14, 19, 34, 11,
    37, 20, 12, 21, 27, 28, 23, 9, 27, 36, 27, 21, 33, 25, 33, 27, 23,
  // Ezra
  11, 70, 13, 24, 17, 22, 28, 36, 15, 44,
  // Nehemiah
  11, 20, 32, 23, 19, 19, 73, 18, 38, 39, 36, 47, 31,
  // Esther
  22, 23, 15, 17, 14, 14, 10, 17, 32, 3,
  // Job
  22, 13, 26, 21, 27, 30, 21, 22, 35, 22, 20, 25, 28, 22, 35, 22, 16, 21, 29,
    29, 34, 30, 17, 25, 6, 14, 23, 28, 25, 31, 40, 22, 33, 37, 16, 33, 24, 41,
    30, 24, 34, 17,
  // Psalms
  6, 12, 8, 8, 12, 10, 17, 9, 20, 18, 7, 8, 6, 7, 5, 11, 15, 50, 14, 9, 13,
    31, 6, 10, 22, 12, 14, 9, 11, 12, 24, 11, 22, 22, 28, 12, 40, 22, 13, 17,
    13, 11, 5, 26, 17, 11, 9, 14, 20, 23, 19, 9, 6, 7, 23, 13, 11, 11, 17, 12,
    8, 12, 11, 10, 13, 20, 7, 35, 36, 5, 24, 20, 28, 23, 10, 12, 20, 72, 13,
    19, 16, 8, 18, 12, 13, 17, 7, 18, 52, 17, 16, 15, 5, 23, 11, 13, 12, 9, 9,
    5, 8, 28, 22, 35, 45, 48, 43, 13, 31, 7, 10, 10, 9, 8, 18, 19, 2, 29, 176,
    7, 8, 9, 4, 8, 5, 6, 5, 6, 8, 8, 3, 18, 3, 3, 21, 26, 9, 8, 24, 13, 10, 7,
    12, 15, 21, 10, 20, 14, 9, 6,
  // Proverbs
  33, 22, 35, 27, 23, 35, 27, 36, 18, 32, 31, 28, 25, 35, 33, 33, 28, 24, 29,
    30, 31, 29, 35, 34, 28, 28, 27, 28, 27, 33, 31,
  // Ecclesiastes
  18, 26, 22, 16, 20, 12, 29, 17, 18, 20, 10, 14,
  // Song of Solomon
  17, 17, 11, 16, 16, 13, 13, 14,
  // Isaiah
  31, 22, 26, 6, 30, 13, 25, 22, 21, 34, 16, 6, 22, 32, 9, 14, 14, 7, 25, 6,
    17, 25, 18, 23, 12, 21, 13, 29, 24, 33, 9, 20, 24, 17, 10, 22, 38, 22, 8,
    31, 29, 25, 28, 28, 25, 13, 15, 22, 26, 11, 23, 15, 12, 17, 13, 12, 21,
    14, 21, 22, 11, 12, 19, 12, 25, 24,
  // Jeremiah
  19, 37, 25, 31, 31, 30, 34, 22, 26, 25, 23, 17, 27, 22, 21, 21, 27, 23, 15,
    18, 14, 30, 40, 10, 38, 24, 22, 17, 32, 24, 40, 44, 26, 22, 19, 32, 21,
    28, 18, 16, 18, 22, 13, 30, 5, 28, 7, 47, 39, 46, 64, 34,
  // Lamentations
  22, 22, 66, 22, 22,
  // Ezekiel
  28, 10, 27, 17, 17, 14, 27, 18, 11, 22, 25, 28, 23, 23, 8, 63, 24, 32, 14,
    49, 32, 31, 49, 27, 17, 21, 36, 26, 21, 26, 18, 32, 33, 31, 15, 38, 28,
    23, 29, 49, 26, 20, 27, 31, 25, 24, 23, 35,
  // Daniel
  21, 49, 30, 37, 31, 28, 28, 27, 27, 21, 45, 13,
  // Hosea
  11, 23, 5, 19, 15, 11, 16, 14, 17, 15, 12, 14, 16, 9,
  // Joel
  20, 32, 21,
  // Amos
  15, 16, 15, 13, 27, 14, 17, 14, 15,
  // Obadiah
  21,
  // Jonah
  17, 10, 10, 11,
  // Micah
  16, 13, 12, 13, 15, 16, 20,
  // Nahum
  15, 13, 19,
  // Habakkuk
  17, 20, 19,
  // Zephaniah
  18, 15, 20,
  // Haggai
  15, 23,
  // Zechariah
  21, 13, 10, 14, 11, 15, 14, 23, 17, 12, 17, 14, 9, 21,
  // Malachi
  14, 17, 18, 6,
  // -----------------------------------------------------------------
  // Matthew
  25, 23, 17, 25, 48, 34, 29, 34, 38, 42, 30, 50, 58, 36, 39, 28, 27, 35, 30,
    34, 46, 46, 39, 51, 46, 75, 66, 20,
  // Mark
  45, 28, 35, 41, 43, 56, 37, 38, 50, 52, 33, 44, 37, 72, 47, 20,
  // Luke
  80, 52, 38, 44, 39, 49, 50, 56, 62, 42, 54, 59, 35, 35, 32, 31, 37, 43, 48,
    47, 38, 71, 56, 53,
  // John
  51, 25, 36, 54, 47, 71, 53, 59, 41, 42, 57, 50, 38, 31, 27, 33, 26, 40, 42,
    31, 25,
  // Acts
  26, 47, 26, 37, 42, 15, 60, 40, 43, 48, 30, 25, 52, 28, 41, 40, 34, 28, 41,
    38, 40, 30, 35, 27, 27, 32, 44, 31,
  // Romans
  32, 29, 31, 25, 21, 23, 25, 39, 33, 21, 36, 21, 14, 23, 33, 27,
  // I Corinthians
  31, 16, 23, 21, 13, 20, 40, 13, 27, 33, 34, 31, 13, 40, 58, 24,
  // II Corinthians
  24, 17, 18, 18, 21, 18, 16, 24, 15, 18, 33, 21, 14,
  // Galatians
  24, 21, 29, 31, 26, 18,
  // Ephesians
  23, 22, 21, 32, 33, 24,
  // Philippians
  30, 30, 21, 23,
  // Colossians
  29, 23, 25, 18,
  // I Thessalonians
  10, 20, 13, 18, 28,
  // II Thessalonians
  12, 17, 18,
  // I Timothy
  20, 15, 16, 16, 25, 21,
  // II Timothy
  18, 26, 17, 22,
  // Titus
  16, 15, 15,
  // Philemon
  25,
  // Hebrews
  14, 18, 19, 16, 14, 20, 28, 13, 28, 39, 40, 29, 25,
  // James
  27, 26, 18, 17, 20,
  // I Peter
  25, 25, 22, 19, 14,
  // II Peter
  21, 22, 18,
  // I John
  10, 29, 24, 21, 21,
  // II John
  13,
  // III John
  14,
  // Jude
  25,
  // Revelation of John
  20, 29, 22, 11, 14, 17, 17, 13, 21, 11, 19, 17, 18, 20, 8, 21, 18, 24, 21,
    15, 27, 21
};


long
  VerseKey::otbks[] = {
  0, 1, 52, 93, 121, 158,
  193, 218, 240, 245, 277, 302, 325,
  351, 381, 418, 429, 443, 454, 497,
  648, 680, 693, 702, 769, 822, 828,
  877, 890, 905, 909, 919, 921, 926,
  934, 938, 942, 946, 949, 964
};

long
  VerseKey::otcps[] = {
  0, 2, 3, 35, 61, 86,
  113, 146, 169, 194, 217, 247, 280,
  313, 334, 353, 378, 400, 417, 445,
  479, 518, 537, 572, 597, 618, 686,
  721, 757, 804, 827, 863, 907, 963,
  996, 1017, 1049, 1079, 1123, 1160, 1191,
  1215, 1239, 1297, 1336, 1371, 1406, 1435,
  1470, 1502, 1525, 1559, 1586, 1587, 1610,
  1636, 1659, 1691, 1715, 1746, 1772, 1805,
  1841, 1871, 1882, 1934, 1957, 1989, 2017,
  2054, 2071, 2099, 2125, 2152, 2189, 2221,
  2255, 2274, 2315, 2353, 2375, 2419, 2466,
  2505, 2524, 2560, 2584, 2620, 2656, 2695,
  2725, 2757, 2801, 2840, 2841, 2859, 2876,
  2894, 2930, 2950, 2981, 3020, 3057, 3082,
  3103, 3151, 3160, 3220, 3278, 3312, 3347,
  3364, 3395, 3433, 3461, 3486, 3520, 3565,
  3589, 3645, 3692, 3727, 3728, 3783, 3818,
  3870, 3920, 3952, 3980, 4070, 4097, 4121,
  4158, 4194, 4211, 4245, 4291, 4333, 4384,
  4398, 4431, 4454, 4484, 4520, 4562, 4593,
  4619, 4638, 4704, 4728, 4760, 4801, 4818,
  4873, 4916, 4973, 5003, 5038, 5052, 5053,
  5100, 5138, 5168, 5218, 5252, 5278, 5305,
  5326, 5356, 5379, 5412, 5445, 5464, 5494,
  5518, 5541, 5562, 5585, 5607, 5628, 5652,
  5683, 5709, 5732, 5752, 5772, 5799, 5868,
  5898, 5919, 5950, 6003, 6033, 6046, 6047,
  6066, 6091, 6109, 6134, 6150, 6178, 6205,
  6241, 6269, 6313, 6337, 6362, 6396, 6412,
  6476, 6487, 6506, 6535, 6587, 6597, 6643,
  6678, 6695, 6729, 6730, 6767, 6791, 6823,
  6848, 6880, 6921, 6947, 6983, 7041, 7060,
  7101, 7117, 7143, 7164, 7185, 7217, 7231,
  7263, 7294, 7343, 7369, 7370, 7393, 7417,
  7436, 7459, 7460, 7489, 7526, 7548, 7571,
  7584, 7606, 7624, 7647, 7675, 7703, 7719,
  7745, 7769, 7822, 7858, 7882, 7941, 7972,
  7997, 8040, 8056, 8080, 8110, 8133, 8178,
  8204, 8217, 8243, 8255, 8287, 8301, 8302,
  8330, 8363, 8403, 8416, 8442, 8466, 8496,
  8515, 8529, 8549, 8577, 8609, 8649, 8683,
  8721, 8745, 8775, 8809, 8853, 8880, 8903,
  8955, 8995, 9021, 9022, 9076, 9123, 9152,
  9187, 9206, 9245, 9297, 9364, 9393, 9423,
  9467, 9501, 9536, 9568, 9603, 9638, 9663,
  9710, 9732, 9776, 9806, 9860, 9861, 9880,
  9906, 9934, 9979, 10007, 10041, 10062, 10092,
  10130, 10167, 10189, 10211, 10237, 10267, 10306,
  10327, 10369, 10407, 10445, 10467, 10494, 10515,
  10553, 10574, 10605, 10606, 10661, 10717, 10742,
  10786, 10813, 10895, 10936, 10977, 11022, 11037,
  11085, 11126, 11141, 11159, 11189, 11233, 11261,
  11279, 11299, 11308, 11339, 11359, 11392, 11424,
  11456, 11489, 11524, 11546, 11577, 11578, 11596,
  11615, 11633, 11656, 11671, 11714, 11737, 11756,
  11788, 11808, 11832, 11849, 11872, 11888, 11908,
  11923, 11943, 11978, 11990, 12028, 12049, 12062,
  12084, 12112, 12141, 12165, 12175, 12203, 12240,
  12268, 12290, 12324, 12350, 12384, 12412, 12436,
  12437, 12449, 12520, 12534, 12559, 12577, 12600,
  12629, 12666, 12682, 12727, 12728, 12740, 12761,
  12794, 12818, 12838, 12858, 12932, 12951, 12990,
  13030, 13067, 13115, 13147, 13148, 13171, 13195,
  13211, 13229, 13244, 13259, 13270, 13288, 13321,
  13325, 13326, 13349, 13363, 13390, 13412, 13440,
  13471, 13493, 13516, 13552, 13575, 13596, 13622,
  13651, 13674, 13710, 13733, 13750, 13772, 13802,
  13832, 13867, 13898, 13916, 13942, 13949, 13964,
  13988, 14017, 14043, 14075, 14116, 14139, 14173,
  14211, 14228, 14262, 14287, 14329, 14360, 14385,
  14420, 14438, 14439, 14446, 14459, 14468, 14477,
  14490, 14501, 14519, 14529, 14550, 14569, 14577,
  14586, 14593, 14601, 14607, 14619, 14635, 14686,
  14701, 14711, 14725, 14757, 14764, 14775, 14798,
  14811, 14826, 14836, 14848, 14861, 14886, 14898,
  14921, 14944, 14973, 14986, 15027, 15050, 15064,
  15082, 15096, 15108, 15114, 15141, 15159, 15171,
  15181, 15196, 15217, 15241, 15261, 15271, 15278,
  15286, 15310, 15324, 15336, 15348, 15366, 15379,
  15388, 15401, 15413, 15424, 15438, 15459, 15467,
  15503, 15540, 15546, 15571, 15592, 15621, 15645,
  15656, 15669, 15690, 15763, 15777, 15797, 15814,
  15823, 15842, 15855, 15869, 15887, 15895, 15914,
  15967, 15985, 16002, 16018, 16024, 16048, 16060,
  16074, 16087, 16097, 16107, 16113, 16122, 16151,
  16174, 16210, 16256, 16305, 16349, 16363, 16395,
  16403, 16414, 16425, 16435, 16444, 16463, 16483,
  16486, 16516, 16693, 16701, 16710, 16720, 16725,
  16734, 16740, 16747, 16753, 16760, 16769, 16778,
  16782, 16801, 16805, 16809, 16831, 16858, 16868,
  16877, 16902, 16916, 16927, 16935, 16948, 16964,
  16986, 16997, 17018, 17033, 17043, 17050, 17051,
  17085, 17108, 17144, 17172, 17196, 17232, 17260,
  17297, 17316, 17349, 17381, 17410, 17436, 17472,
  17506, 17540, 17569, 17594, 17624, 17655, 17687,
  17717, 17753, 17788, 17817, 17846, 17874, 17903,
  17931, 17965, 17997, 17998, 18017, 18044, 18067,
  18084, 18105, 18118, 18148, 18166, 18185, 18206,
  18217, 18232, 18233, 18251, 18269, 18281, 18298,
  18315, 18329, 18343, 18358, 18359, 18391, 18414,
  18441, 18448, 18479, 18493, 18519, 18542, 18564,
  18599, 18616, 18623, 18646, 18679, 18689, 18704,
  18719, 18727, 18753, 18760, 18778, 18804, 18823,
  18847, 18860, 18882, 18896, 18926, 18951, 18985,
  18995, 19016, 19041, 19059, 19070, 19093, 19132,
  19155, 19164, 19196, 19226, 19252, 19281, 19310,
  19336, 19350, 19366, 19389, 19416, 19428, 19452,
  19468, 19481, 19499, 19513, 19526, 19548, 19563,
  19585, 19608, 19620, 19633, 19653, 19666, 19692,
  19717, 19718, 19738, 19776, 19802, 19834, 19866,
  19897, 19932, 19955, 19982, 20008, 20032, 20050,
  20078, 20101, 20123, 20145, 20173, 20197, 20213,
  20232, 20247, 20278, 20319, 20330, 20369, 20394,
  20417, 20435, 20468, 20493, 20534, 20579, 20606,
  20629, 20649, 20682, 20704, 20733, 20752, 20769,
  20788, 20811, 20825, 20856, 20862, 20891, 20899,
  20947, 20987, 21034, 21099, 21134, 21135, 21158,
  21181, 21248, 21271, 21294, 21295, 21324, 21335,
  21363, 21381, 21399, 21414, 21442, 21461, 21473,
  21496, 21522, 21551, 21575, 21599, 21608, 21672,
  21697, 21730, 21745, 21795, 21828, 21860, 21910,
  21938, 21956, 21978, 22015, 22042, 22064, 22091,
  22110, 22143, 22177, 22209, 22225, 22264, 22293,
  22317, 22347, 22397, 22424, 22445, 22473, 22505,
  22531, 22556, 22580, 22616, 22617, 22639, 22689,
  22720, 22758, 22790, 22819, 22848, 22876, 22904,
  22926, 22972, 22986, 22987, 22999, 23023, 23029,
  23049, 23065, 23077, 23094, 23109, 23127, 23143,
  23156, 23171, 23188, 23198, 23199, 23220, 23253,
  23275, 23276, 23292, 23309, 23325, 23339, 23367,
  23382, 23400, 23415, 23431, 23432, 23454, 23455,
  23473, 23484, 23495, 23507, 23508, 23525, 23539,
  23552, 23566, 23582, 23599, 23620, 23621, 23637,
  23651, 23671, 23672, 23690, 23711, 23731, 23732,
  23751, 23767, 23788, 23789, 23805, 23829, 23830,
  23852, 23866, 23877, 23892, 23904, 23920, 23935,
  23959, 23977, 23990, 24008, 24023, 24033, 24055,
  24056, 24071, 24089, 24108
};

long
  VerseKey::ntbks[] = {
  0, 1, 30, 47, 72, 94,
  123, 140, 157, 171, 178, 185, 190,
  195, 201, 205, 212, 217, 221, 223,
  237, 243, 249, 253, 259, 261, 263,
  265
};

long
  VerseKey::ntcps[] = {
  0, 2, 3, 29, 53, 71,
  97, 146, 181, 211, 246, 285, 328,
  359, 410, 469, 506, 546, 575, 603,
  639, 670, 705, 752, 799, 839, 891,
  938, 1014, 1081, 1102, 1103, 1149, 1178,
  1214, 1256, 1300, 1357, 1395, 1434, 1485,
  1538, 1572, 1617, 1655, 1728, 1776, 1797,
  1798, 1879, 1932, 1971, 2016, 2056, 2106,
  2157, 2214, 2277, 2320, 2375, 2435, 2471,
  2507, 2540, 2572, 2610, 2654, 2703, 2751,
  2790, 2862, 2919, 2973, 2974, 3026, 3052,
  3089, 3144, 3192, 3264, 3318, 3378, 3420,
  3463, 3521, 3572, 3611, 3643, 3671, 3705,
  3732, 3773, 3816, 3848, 3874, 3875, 3902,
  3950, 3977, 4015, 4058, 4074, 4135, 4176,
  4220, 4269, 4300, 4326, 4379, 4408, 4450,
  4491, 4526, 4555, 4597, 4636, 4677, 4708,
  4744, 4772, 4800, 4833, 4878, 4910, 4911,
  4944, 4974, 5006, 5032, 5054, 5078, 5104,
  5144, 5178, 5200, 5237, 5259, 5274, 5298,
  5332, 5360, 5361, 5393, 5410, 5434, 5456,
  5470, 5491, 5532, 5546, 5574, 5608, 5643,
  5675, 5689, 5730, 5789, 5814, 5815, 5840,
  5858, 5877, 5896, 5918, 5937, 5954, 5979,
  5995, 6014, 6048, 6070, 6085, 6086, 6111,
  6133, 6163, 6195, 6222, 6241, 6242, 6266,
  6289, 6311, 6344, 6378, 6403, 6404, 6435,
  6466, 6488, 6512, 6513, 6543, 6567, 6593,
  6612, 6613, 6624, 6645, 6659, 6678, 6707,
  6708, 6721, 6739, 6758, 6759, 6780, 6796,
  6813, 6830, 6856, 6878, 6879, 6898, 6925,
  6943, 6966, 6967, 6984, 7000, 7016, 7017,
  7043, 7044, 7059, 7078, 7098, 7115, 7130,
  7151, 7180, 7194, 7223, 7263, 7304, 7334,
  7360, 7361, 7389, 7416, 7435, 7453, 7474,
  7475, 7501, 7527, 7550, 7570, 7585, 7586,
  7608, 7631, 7650, 7651, 7662, 7692, 7717,
  7739, 7761, 7762, 7776, 7777, 7792, 7793,
  7819, 7820, 7841, 7871, 7894, 7906, 7921,
  7939, 7957, 7971, 7993, 8005, 8025, 8043,
  8062, 8083, 8092, 8114, 8133, 8158, 8180,
  8196, 8224
};


int
  VerseKey::offsize[2][2] =
  { {sizeof (VerseKey::otbks) / sizeof(long), sizeof (VerseKey::otcps) / sizeof(long)}
, {sizeof (VerseKey::ntbks) / sizeof(long), sizeof (VerseKey::ntcps) / sizeof(long)}
};

//SWORD_NAMESPACE_END