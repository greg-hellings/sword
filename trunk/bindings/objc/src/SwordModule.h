/*	SwordModule.h - Sword API wrapper for Modules.

    Copyright 2008 Manfred Bergmann
    Based on code by Will Thimbleby
  
	This program is free software; you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software Foundation version 2.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
	even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	General Public License for more details. (http://www.gnu.org/licenses/gpl.html)
*/

#import <Cocoa/Cocoa.h>

#ifdef __cplusplus
#import "swmodule.h"
#endif

#define My_SWDYNAMIC_CAST(className, object) (sword::className *)((object)?((object->getClass()->isAssignableFrom(#className))?object:0):0)

// defines for dictionary entries for passagestudy
#define ATTRTYPE_TYPE       @"type"
#define ATTRTYPE_PASSAGE    @"passage"
#define ATTRTYPE_MODULE     @"modulename"
#define ATTRTYPE_NOTENUMBER @"notenumber"
#define ATTRTYPE_ACTION     @"action"
#define ATTRTYPE_VALUE      @"value"

// positions
#define SWPOS_BOTTOM   2
#define SWPOS_TOP      1


@class SwordManager, SwordModuleTextEntry, SwordKey;

typedef enum {
    TextTypeStripped = 1,
    TextTypeRendered
}TextPullType;

typedef enum {
	bible       = 0x0001, 
    commentary  = 0x0002, 
    dictionary  = 0x0004,
    genbook     = 0x0008, 
    devotional  = 0x0010
}ModuleType;

@protocol SwordModuleAccess

/** 
 number of entries
 abstract method, should be overriden by subclasses
 */
- (long)entryCount;

/**
 abstract method, override in subclass
 This method generates stripped text string for a given reference.
 @param[in] reference bible reference
 @return Array of SwordModuleTextEntry instances
 */
- (NSArray *)strippedTextEntriesForRef:(NSString *)reference;

/** 
 abstract method, override in subclass
 This method generates HTML string for a given reference.
 @param[in] reference bible reference
 @return Array of SwordModuleTextEntry instances
 */
- (NSArray *)renderedTextEntriesForRef:(NSString *)reference;

/** 
 write value to reference
 */
- (void)writeEntry:(SwordModuleTextEntry *)anEntry;

@end

@interface SwordModule : NSObject <SwordModuleAccess> {
    
    NSMutableDictionary *configEntries;
	ModuleType type;
    int status;
	SwordManager *swManager;	
	NSRecursiveLock *moduleLock;
    NSLock *indexLock;
    
    /** we store the name separately */
    NSString *name;
    
    /** yes, we have a delegate to report any action to */
    id delegate;

#ifdef __cplusplus
	sword::SWModule	*swModule;
#endif
}

// ------------- properties ---------------
@property (readwrite) ModuleType type;
@property (readwrite) int status;
@property (retain, readwrite) NSRecursiveLock *moduleLock;
@property (retain, readwrite) NSLock *indexLock;
@property (retain, readwrite) NSString *name;
@property (retain, readwrite) SwordManager *swManager;

// -------------- class methods --------------
/**
 maps type string to ModuleType enum
 @param[in] typeStr type String as in -type(SwordModule)
 @return type according to ModuleType enum
 */
+ (ModuleType)moduleTypeForModuleTypeString:(NSString *)typeStr;

// ------------- instance methods ---------------

- (id)initWithName:(NSString *)aName swordManager:(SwordManager *)aManager;
#ifdef __cplusplus
- (id)initWithSWModule:(sword::SWModule *)aModule;
- (id)initWithSWModule:(sword::SWModule *)aModule swordManager:(SwordManager *)aManager;
- (sword::SWModule *)swModule;
#endif
- (void)finalize;

- (NSInteger)error;
- (NSString *)descr;
- (NSString *)lang;
- (NSString *)typeString;
- (NSString *)version;
- (NSString *)minVersion;
- (NSString *)aboutText;
- (NSString *)versification;
- (NSAttributedString *)fullAboutText;
- (BOOL)isUnicode;
- (BOOL)isEncrypted;
- (BOOL)isLocked;
- (BOOL)isEditable;
- (BOOL)isRTL;
- (BOOL)unlock:(NSString *)unlockKey;

- (void)aquireModuleLock;
- (void)releaseModuleLock;

- (BOOL)hasFeature:(NSString *)feature;
- (NSString *)configFileEntryForConfigKey:(NSString *)entryKey;

- (void)incKeyPosition;
- (void)decKeyPosition;
- (void)setKeyString:(NSString *)aKeyString;
- (void)setKey:(SwordKey *)aKey;

- (id)createKey;
- (id)getKey;
- (id)getKeyCopy;

- (void)setProcessEntryAttributes:(BOOL)flag;
- (BOOL)processEntryAttributes;

- (NSString *)renderedText;
- (NSString *)renderedTextFromString:(NSString *)aString;
- (NSString *)strippedText;
- (NSString *)strippedTextFromString:(NSString *)aString;

/**
 returns attribute values from the engine for notes, cross-refs and such for the given link type
 @return NSArray for references
 @return NSString for text data
 */
- (id)attributeValueForParsedLinkData:(NSDictionary *)data;

/** returns the pre-verse entry value */
- (NSString *)entryAttributeValuePreverse;
- (NSString *)entryAttributeValuePreverseForKey:(SwordKey *)aKey;

- (NSString *)entryAttributeValueFootnoteOfType:(NSString *)fnType indexValue:(NSString *)index;
- (NSString *)entryAttributeValueFootnoteOfType:(NSString *)fnType indexValue:(NSString *)index forKey:(SwordKey *)aKey;

- (NSArray *)entryAttributeValuesLemma;

/**
 return a dictionary with key and text
 type can be: "rendered" or "stripped"
 */
- (SwordModuleTextEntry *)textEntryForKey:(SwordKey *)aKey textType:(TextPullType)aType;
- (SwordModuleTextEntry *)textEntryForKeyString:(NSString *)aKeyString textType:(TextPullType)aType;

// ------- SwordModuleAccess ---------
- (long)entryCount;
- (NSArray *)strippedTextEntriesForRef:(NSString *)reference;
- (NSArray *)renderedTextEntriesForRef:(NSString *)reference;
- (void)writeEntry:(SwordModuleTextEntry *)anEntry;

@end
