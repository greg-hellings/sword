//
//  SwordInstallSource.h
//  Eloquent
//
//  Created by Manfred Bergmann on 13.08.07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SwordModule.h"

#ifdef __cplusplus
#include <swmgr.h>
#include <installmgr.h>
class sword::SWModule;
#endif

@class SwordManager;
@class SwordInstallSourceController;

#define INSTALLSOURCE_TYPE_FTP  @"FTP"

@interface SwordInstallSource : NSObject {
    
#ifdef __cplusplus
    sword::InstallSource *swInstallSource;
#endif
    
    BOOL temporarySource;

    /** the sword manager for this source */
    SwordManager *swordManager;    
}

// init
- (id)init;
#ifdef __cplusplus
- (id)initWithSource:(sword::InstallSource *)is;
#endif
- (id)initWithType:(NSString *)aType;

// accessors
- (NSString *)caption;
- (void)setCaption:(NSString *)aCaption;
- (NSString *)type;
- (void)setType:(NSString *)aType;
- (NSString *)source;
- (void)setSource:(NSString *)aSource;
- (NSString *)directory;
- (void)setDirectory:(NSString *)aDir;

- (BOOL)isLocalSource;

// get config entry
- (NSString *)configEntry;

// install module
- (void)installModuleWithName:(NSString *)mName 
                 usingManager:(SwordManager *)swManager 
        withInstallController:(SwordInstallSourceController *)sim;

/** List of available InstallSources */
- (NSArray *)listModules;

/** List of modules for given type */
- (NSArray *)listModulesForType:(ModuleType)aType;

/** list module types */
- (NSArray *)listModuleTypes;

/** Returns the SwordManager attached to this SwordInstallSourceController */
- (SwordManager *)swordManager;
- (void)setSwordManager:(SwordManager *)swManager;

#ifdef __cplusplus
- (sword::InstallSource *)installSource;
#endif

@end
