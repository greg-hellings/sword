/*	SwordModule.h - Sword API wrapper for Modules.

    Copyright 2008 Manfred Bergmann
    Based on code by Will Thimbleby
  
	This program is free software; you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software Foundation version 2.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
	even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	General Public License for more details. (http://www.gnu.org/licenses/gpl.html)
*/

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "swmodule.h"
#endif

#define My_SWDYNAMIC_CAST(className, object) (sword::className *)((object)?((object->getClass()->isAssignableFrom(#className))?object:0):0)

// defines for dictionary entries for passage study
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

/** These are the main module types as returned in -typeString */
typedef enum {
    All         = 0x0000,
	Bible       = 0x0001, 
    Commentary  = 0x0002, 
    Dictionary  = 0x0004,
    Genbook     = 0x0008
}ModuleType;

/**
 These are the main module categories as returned in -categoryString
 Remember that modules type bible, commentary, dictionary and genbook not necessarily have a category
 */
typedef enum {
    Unset           = -1,
    NoCategory      = 0,
	DailyDevotion   = 0x0001, 
    Maps            = 0x0002, 
    Glossary        = 0x0004,
    Images          = 0x0008,
    Essays          = 0x0010,
    Cults           = 0x0011    
}ModuleCategory;


@interface SwordModule : NSObject {
    
    NSMutableDictionary *configEntries;
	ModuleType type;
	ModuleCategory category;
    int status;
	SwordManager *swManager;	
	NSRecursiveLock *moduleLock;
    NSLock *indexLock;
    
    /** we store the name separately */
    NSString *typeString;
    NSString *name;
    NSString *descr;
    NSString *lang;

    
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
@property (retain, readwrite) SwordManager *swManager;

// swmodule properties
@property (retain, readonly) NSString *name;
@property (retain, readonly) NSString *typeString;
@property (retain, readonly) NSString *descr;
@property (retain, readonly) NSString *lang;

#ifdef __cplusplus
/**
 Convenience initializers
 */
+ (id)moduleForSWModule:(sword::SWModule *)aModule;
+ (id)moduleForSWModule:(sword::SWModule *)aModule swordManager:(SwordManager *)aManager;
/**
 Factory method that creates the correct module type instance for the given type
 */
+ (id)moduleForType:(ModuleType)aType swModule:(sword::SWModule *)swModule swordManager:(SwordManager *)aManager;
#endif

/**
 maps type string to ModuleType enum
 @param[in] typeStr type String as in -typeString(SwordModule)
 @return type according to ModuleType enum
 */
+ (ModuleType)moduleTypeForModuleTypeString:(NSString *)typeStr;

/**
 maps type string to ModuleType enum
 @param[in] categoryStr category String as in -categoryString(SwordModule)
 @return type according to ModuleCategory enum
 */
+ (ModuleCategory)moduleCategoryForModuleCategoryString:(NSString *)categoryStr;

// ------------- instance methods ---------------

/**
 Initializes module with a given name and SwordManager.
 The SwordManager is needed because the underlying SWModule is retrieved from SwordManager.
 */
- (id)initWithName:(NSString *)aName swordManager:(SwordManager *)aManager;
#ifdef __cplusplus
/**
 Initialize this module with an the SWModule.
 This initializer should normally not need to be used.
 */
- (id)initWithSWModule:(sword::SWModule *)aModule;
/**
 Initialize this module with an the SWModule and a SwordManager instance.
 This initializer should normally not need to be used.
 */
- (id)initWithSWModule:(sword::SWModule *)aModule swordManager:(SwordManager *)aManager;
/**
 Retrieve the underlying SWModule instance
 */
- (sword::SWModule *)swModule;
#endif

/**
 Any error while processing the module?
 */
- (NSInteger)error;

// --------------- Conf entries --------------

/**
 Module category as string
 */
- (NSString *)categoryString;
/**
 Module category
 */
- (ModuleCategory)category;
/**
 Module version
 */
- (NSString *)version;
/**
 Module minimum Sword version
 */
- (NSString *)minVersion;
/**
 Module about text
 */
- (NSString *)aboutText;
/**
 Override to get custom behaviour.
 */
- (NSAttributedString *)fullAboutText;
/**
 Module versification type
 */
- (NSString *)versification;
/**
 Is module Unicode UTF-8?
 */
- (BOOL)isUnicode;
/**
 Is module encrypted
 */
- (BOOL)isEncrypted;
/**
 Is module locked, that is encrypted but not unlocked?
 */
- (BOOL)isLocked;
/**
 Is module editable, i.e. is it's a personal commentary?
 */
- (BOOL)isEditable;
/**
 Is module writing direction Right to Left?
 */
- (BOOL)isRTL;
/**
 Has module this feature?
 See SWMOD_FEATURE_* in SwordManager
 */
- (BOOL)hasFeature:(NSString *)feature;
/**
 Returns a config entry for a given config key
 */
- (NSString *)configFileEntryForConfigKey:(NSString *)entryKey;

// ------------------ module unlocking ------------------

/**
 Unlock this module with a cipher key, if it is encrypted.
 */
- (BOOL)unlock:(NSString *)unlockKey;

// ------------------ module access semaphores -----------------

/**
 Aquires a module access lock so that no other thread may access this module.
 */
- (void)lockModuleAccess;
/**
 Unlock module access. Make it accessible to other threads.
 */
- (void)unlockModuleAccess;

// ----------------- module positioning ------------------------

/**
 Increment module key position
 */
- (void)incKeyPosition;
/**
 Decrement module key position
 */
- (void)decKeyPosition;
/**
 Set position key from a string
 */
- (void)setKeyString:(NSString *)aKeyString;
/**
 Set position from a key
 */
- (void)setKey:(SwordKey *)aKey;

/**
 Module key. New instance created by module.
 */
- (id)createKey;
/**
 Module key. Reference only.
 */
- (id)getKey;
/**
 Module key. Reference only but cloned.
 */
- (id)getKeyCopy;

// ------------------- module metadata processing ------------------

/**
 Process metadata attributes of module entry.
 */
- (void)setProcessEntryAttributes:(BOOL)flag;
/**
 Are metadata attributes of module entry processed?
 */
- (BOOL)processEntryAttributes;

/**
 returns attribute values from the engine for notes, cross-refs and such for the given link type
 @return NSArray for references
 @return NSString for text data
 */
- (id)attributeValueForParsedLinkData:(NSDictionary *)data;
- (id)attributeValueForParsedLinkData:(NSDictionary *)data withTextRenderType:(TextPullType)textType;

/** returns the pre-verse entry value */
- (NSString *)entryAttributeValuePreverse;
- (NSString *)entryAttributeValuePreverseForKey:(SwordKey *)aKey;

- (NSString *)entryAttributeValueFootnoteOfType:(NSString *)fnType indexValue:(NSString *)index;
- (NSString *)entryAttributeValueFootnoteOfType:(NSString *)fnType indexValue:(NSString *)index forKey:(SwordKey *)aKey;

- (NSArray *)entryAttributeValuesLemma;

// ----------------- Module text access ----------------------

/**
 Retrieves a text entry for a given key.
 Type can be: "rendered" or "stripped"
 */
- (SwordModuleTextEntry *)textEntryForKey:(SwordKey *)aKey textType:(TextPullType)aType;
/**
 Convenience method with a key-string
 */
- (SwordModuleTextEntry *)textEntryForKeyString:(NSString *)aKeyString textType:(TextPullType)aType;
/**
 Pulls all text entries for the given reference
 @return Array of SwordModuleTextEntry
 */
- (NSArray *)textEntriesForReference:(NSString *)aReference textType:(TextPullType)textType;

/**
 Returns a rendered text for the text at the current module position
 */
- (NSString *)renderedText;
/**
 Renders the given string with the modules render filters
 */
- (NSString *)renderedTextFromString:(NSString *)aString;
/** 
 Returns a stripped text for the text at the current module position
 */
- (NSString *)strippedText;
/**
 Strips the given string with the modules strip filters
 */
- (NSString *)strippedTextFromString:(NSString *)aString;

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
 number of entries
 abstract method, should be overriden by subclasses
 */
- (long)entryCount;

/**
 Write text to module position
 */
- (void)writeEntry:(SwordModuleTextEntry *)anEntry;

@end
