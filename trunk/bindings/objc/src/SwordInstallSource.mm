//
//  SwordInstallSource.mm
//  Eloquent
//
//  Created by Manfred Bergmann on 13.08.07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import "SwordInstallSource.h"
#import "SwordInstallSourceManager.h"
#import "SwordManager.h"

@interface SwordInstallSource ()

@end

@implementation SwordInstallSource

// init
- (id)init {
    self = [super init];
    if(self) {
        temporarySource = NO;

        // at first we have no sword manager
        [self setSwordManager:nil];
        
        // init InstallMgr
        swInstallSource = new sword::InstallSource("", "");
        if(swInstallSource == nil) {
            ALog(@"Could not init sword install source!");
        }
    }
    
    return self;
}

- (id)initWithType:(NSString *)aType {
    self = [self init];
    if(self) {
        // set type
        swInstallSource->type = [aType cStringUsingEncoding:NSUTF8StringEncoding];
    }
    
    return self;
}

/** init with given source */
- (id)initWithSource:(sword::InstallSource *)is {
    self = [super init];
    if(self) {
        temporarySource = YES;
        
        // at first we have no sword manager
        [self setSwordManager:nil];
        
        swInstallSource = is;
    }
    
    return self;
}

- (void)finalize {
    if(temporarySource == NO) {
        //LogL(LOG_DEBUG, @"[SwordInstallSource -finalize] deleting swInstalSource");
        //delete swInstallSource;
    }
    
    [super finalize];
}

- (void)dealloc {
    [super dealloc];
}

- (void)setSwordManager:(SwordManager *)swManager {
    [swManager retain];
    [swordManager release];
    swordManager = swManager;
}

// accessors
- (NSString *)caption {
    const char *str = swInstallSource->caption;
    return [[[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding] autorelease];
}

- (void)setCaption:(NSString *)aCaption {
    swInstallSource->caption = [aCaption cStringUsingEncoding:NSUTF8StringEncoding];
}

- (NSString *)type {
    const char *str = swInstallSource->type;
    return [[[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding] autorelease];
}

- (void)setType:(NSString *)aType {
    swInstallSource->type = [aType cStringUsingEncoding:NSUTF8StringEncoding];
}

- (NSString *)source {
    const char *str = swInstallSource->source;
    return [[[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding] autorelease];
}

- (void)setSource:(NSString *)aSource {
    swInstallSource->source = [aSource cStringUsingEncoding:NSUTF8StringEncoding];
}

- (NSString *)directory {
    const char *str = swInstallSource->directory;
    return [[[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding] autorelease];
}

- (void)setDirectory:(NSString *)aDir {
    swInstallSource->directory = [aDir cStringUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)isLocalSource {
    return [[self source] isEqualToString:@"localhost"];
}

// get config entry
- (NSString *)configEntry {
    return [NSString stringWithFormat:@"%@|%@|%@", [self caption], [self source], [self directory]];
}

/** install module */
- (void)installModuleWithName:(NSString *)mName usingManager:(SwordManager *)swManager withInstallController:(SwordInstallSourceManager *)sim {
    sword::InstallMgr *im = [sim installMgr];
    im->installModule([swManager swManager], 0, [mName UTF8String], swInstallSource);
}

/** list all modules of this source */
- (NSArray *)listModules {
    NSArray *ret = [NSArray array];
    
    SwordManager *sm = [self swordManager];
    if(sm) {
        ret = [sm listModules];
    } else {
        ALog(@"Have nil SwordManager");        
    }
    
    return ret;
}

- (NSArray *)listModulesForType:(ModuleType)aType {
    NSArray *ret = [NSArray array];

    SwordManager *sm = [self swordManager];
    if(sm) {
        ret = [sm modulesForType:aType];
    } else {
        ALog(@"Have nil SwordManager");        
    }    
    
    return ret;
}

/** list module types */
- (NSArray *)listModuleTypes {
    NSArray *ret = nil;
    
    DLog(@"");
    ret = [SwordManager moduleTypes];
    
    return ret;    
}

// get associated SwordManager
- (SwordManager *)swordManager {

    if(swordManager == nil) {
        // create SwordManager from the SWMgr of this source
        sword::SWMgr *mgr;
        if([[self source] isEqualToString:@"localhost"]) {
            // create SwordManager from new SWMgr of path
            mgr = (sword::SWMgr *)new sword::SWMgr([[self directory] UTF8String], true, NULL, false, false);
        } else {
            // create SwordManager from the SWMgr of this source
            mgr = swInstallSource->getMgr();    
        }
        
        if(mgr == nil) {
            ALog(@"Have a nil SWMgr!");
        } else {
            swordManager = [[SwordManager alloc] initWithSWMgr:mgr];    
        }
    }
    
    return swordManager;
}

/** low level API */
- (sword::InstallSource *)installSource {
    return swInstallSource;
}

@end
