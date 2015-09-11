//
//  ISSPropertyDeclarations.m
//  Part of InterfaCSS - http://www.github.com/tolo/InterfaCSS
//
//  Created by Tobias Löfstrand on 2012-02-22.
//  Copyright (c) 2012 Leafnode AB.
//  License: MIT (http://www.github.com/tolo/InterfaCSS/LICENSE)
//

#import "ISSPropertyDeclarations.h"

#import "ISSSelectorChain.h"
#import "ISSUIElementDetails.h"
#import "ISSStylingContext.h"
#import "ISSPropertyDeclaration.h"


@implementation ISSPropertyDeclarations

#pragma mark - ISSPropertyDeclarations interface


- (id) initWithSelectorChains:(NSArray*)selectorChains andProperties:(NSArray*)properties {
    if( self = [super init] ) {
        _selectorChains = selectorChains;
        _properties = properties;
        for(ISSSelectorChain* chain in selectorChains) {
            if( chain.hasPseudoClassSelector ) {
                _containsPseudoClassSelector = _containsPseudoClassSelectorOrDynamicProperties = YES;
                break;
            }
        }
        if( !_containsPseudoClassSelectorOrDynamicProperties ) {
            for(ISSPropertyDeclaration* decl in properties) {
                if( decl.dynamicValue ) {
                    _containsPseudoClassSelectorOrDynamicProperties = YES;
                    break;
                }
            }
        }
    }
    return self;
}

- (BOOL) matchesElement:(ISSUIElementDetails*)elementDetails stylingContext:(ISSStylingContext*)stylingContext {
    for(ISSSelectorChain* selectorChain in _selectorChains) {
        if ( [selectorChain matchesElement:elementDetails stylingContext:stylingContext] ) return YES;
    }
    return NO;
}

- (ISSPropertyDeclarations*) propertyDeclarationsMatchingElement:(ISSUIElementDetails*)elementDetails stylingContext:(ISSStylingContext*)stylingContext {
    NSMutableArray* matchingChains = self.containsPseudoClassSelector ? [NSMutableArray array] : nil;
    for(ISSSelectorChain* selectorChain in _selectorChains) {
        if ( [selectorChain matchesElement:elementDetails stylingContext:stylingContext] ) {
            if( !self.containsPseudoClassSelector ) {
                return self; // If this style sheet declarations block doesn't contain any pseudo classes - return the declarations object itself directly when first selector chain match is found (since no additional matching needs to be done)
            }
            [matchingChains addObject:selectorChain];
        }
    }
    if( matchingChains.count ) return [[ISSPropertyDeclarations alloc] initWithSelectorChains:matchingChains andProperties:self.properties];
    else return nil;
}

- (NSUInteger) specificity {
    NSUInteger specificity = 0;
    for(ISSSelectorChain* selectorChain in _selectorChains) {
        specificity += selectorChain.specificity;
    }
    return specificity;
}

- (NSString*) displayDescription:(BOOL)withProperties {
    NSMutableArray* chainsCopy = [_selectorChains mutableCopy];
    [chainsCopy enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) { chainsCopy[idx] = [obj displayDescription]; }];
    NSString* chainsDescription = [chainsCopy componentsJoinedByString:@", "];

    if( withProperties ) return [NSString stringWithFormat:@"%@ : %@", chainsDescription, _properties];
    else return chainsDescription;
}

- (NSString*) displayDescription {
    return [self displayDescription:YES];
}


#pragma mark - NSObject overrides


- (NSString*) description {
    return [NSString stringWithFormat:@"ISSPropertyDeclarations[%@]", self.displayDescription];
}

- (BOOL) isEqual:(id)object {
    if( object == self ) return YES;
    else return [object isKindOfClass:ISSPropertyDeclarations.class] && [_selectorChains isEqualToArray:[object selectorChains]] &&
                                                         [_properties isEqualToArray:[(ISSPropertyDeclarations*)object properties]];
}

- (NSUInteger) hash {
    return self.description.hash;
}


@end