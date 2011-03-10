//
//  SwordVerseKey.h
//  MacSword2
//
//  Created by Manfred Bergmann on 17.03.09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SwordKey.h"

#ifdef __cplusplus
#include <versekey.h>
#endif

@interface SwordVerseKey : SwordKey {
}

+ (id)verseKey;
+ (id)verseKeyWithVersification:(NSString *)scheme;
+ (id)verseKeyWithRef:(NSString *)aRef;
+ (id)verseKeyWithRef:(NSString *)aRef v11n:(NSString *)scheme;

#ifdef __cplusplus
+ (id)verseKeyWithSWVerseKey:(sword::VerseKey *)aVk;
+ (id)verseKeyWithSWVerseKey:(sword::VerseKey *)aVk makeCopy:(BOOL)copy;
- (id)initWithSWVerseKey:(sword::VerseKey *)aVk;
- (id)initWithSWVerseKey:(sword::VerseKey *)aVk makeCopy:(BOOL)copy;
- (sword::VerseKey *)swVerseKey;
#endif

- (id)initWithVersification:(NSString *)scheme;
- (id)initWithRef:(NSString *)aRef;
- (id)initWithRef:(NSString *)aRef v11n:(NSString *)scheme;

- (int)index;
- (int)testament;
- (void)setTestament:(int)val;
- (int)book;
- (void)setBook:(int)val;
- (int)chapter;
- (void)setChapter:(int)val;
- (int)verse;
- (void)setVerse:(int)val;
- (BOOL)headings;
- (void)setHeadings:(BOOL)flag;
- (BOOL)autoNormalize;
- (void)setAutoNormalize:(BOOL)flag;
- (NSString *)bookName;
- (NSString *)osisBookName;
- (NSString *)osisRef;
- (void)setVersification:(NSString *)versification;
- (NSString *)versification;

@end
