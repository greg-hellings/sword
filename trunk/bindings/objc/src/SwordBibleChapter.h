//
//  SwordBibleChapter.h
//  MacSword2
//
//  Created by Manfred Bergmann on 19.02.09.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SwordBibleBook;

@interface SwordBibleChapter : NSObject {
    /** the back reference */
    SwordBibleBook *book;
    int number;
}

@property (readwrite) int number;
@property (readwrite, assign) SwordBibleBook *book;

- (id)initWithBook:(SwordBibleBook *)aBook andChapter:(int)aNumber;

@end
