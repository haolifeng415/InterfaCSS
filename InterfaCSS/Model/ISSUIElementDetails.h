//
//  ISSUIElementDetails.h
//  Part of InterfaCSS - http://www.github.com/tolo/InterfaCSS
//
//  Created by Tobias Löfstrand on 2014-03-19.
//  Copyright (c) 2012 Leafnode AB.
//  License: MIT (http://www.github.com/tolo/InterfaCSS/LICENSE)
//

#import "InterfaCSS.h"

@class ISSLayout, ISSUpdatableValue, ISSPropertyDeclaration;


extern NSString* const ISSIndexPathKey;
extern NSString* const ISSPrototypeViewInitializedKey;


@interface NSObject (ISSUIElementDetails)
@property (nonatomic, strong) ISSUIElementDetails* elementDetailsISS;
@end


// InterfaCSS class extension
@interface InterfaCSS ()
- (ISSUIElementDetails*) detailsForUIElement:(id)uiElement;
@end


@interface ISSUIElementDetails : NSObject<NSCopying>

@property (nonatomic, weak, readonly) id uiElement;
@property (nonatomic, weak, readonly) UIView* view; // uiElement, if instance of UIView, otherwise nil
@property (nonatomic, weak) id parentElement;
@property (nonatomic, weak, readonly) UIView* parentView; // parentElement, if instance of UIView, otherwise nil

@property (nonatomic, weak, readonly) UIViewController* parentViewController; // Direct parent view controller of element, i.e. parentElement, if instance of UIViewController, otherwise nil

@property (nonatomic, weak, readonly) UIViewController* closestViewController; // Closest ancestor view controller

@property (nonatomic, readonly) NSArray* childElementsForElement;
@property (nonatomic, readonly) NSDictionary* validNestedElements;

@property (nonatomic, strong) NSString* elementId;

@property (nonatomic, strong) ISSLayout* layout;

@property (nonatomic, readonly) BOOL addedToViewHierarchy;
@property (nonatomic, readonly) BOOL stylesCacheable;

@property (nonatomic, strong, readonly) NSString* elementStyleIdentityPath;
@property (nonatomic, readonly) BOOL ancestorHasElementId;
@property (nonatomic, strong) NSString* customElementStyleIdentity;
@property (nonatomic, readonly) BOOL ancestorUsesCustomElementStyleIdentity;

@property (nonatomic, weak) NSMutableArray* cachedDeclarations; // Optimization for quick access to cached declarations
@property (nonatomic) BOOL stylesFullyResolved;

@property (nonatomic, weak) Class canonicalType;
@property (nonatomic, strong) NSSet* styleClasses;

@property (nonatomic) BOOL stylingApplied; // Indicates if styles have been applied to element
@property (nonatomic) BOOL stylingDisabled;
@property (nonatomic, readonly) BOOL stylingAppliedAndDisabled;
@property (nonatomic) BOOL stylesContainPseudoClassesOrDynamicProperties;
@property (nonatomic, readonly) BOOL stylingAppliedAndStatic; // If YES, Indicates that styles have been applied to element and that there are no pseudo classes

@property (nonatomic, copy) ISSWillApplyStylingNotificationBlock willApplyStylingBlock;
@property (nonatomic, copy) ISSDidApplyStylingNotificationBlock didApplyStylingBlock;

@property (nonatomic, strong, readonly) NSSet* disabledProperties;

@property (nonatomic, strong, readonly) NSMutableDictionary* additionalDetails;

@property (nonatomic, strong, readonly) NSMutableDictionary* prototypes;


- (id) initWithUIElement:(id)uiElement;

+ (void) resetAllCachedData;
- (void) resetCachedViewHierarchyRelatedData;
- (void) resetCachedData;

- (void) typeQualifiedPositionInParent:(NSInteger*)position count:(NSInteger*)count;

- (void) addDisabledProperty:(ISSPropertyDefinition*)disabledProperty;
- (void) removeDisabledProperty:(ISSPropertyDefinition*)disabledProperty;
- (BOOL) hasDisabledProperty:(ISSPropertyDefinition*)disabledProperty;
- (void) clearDisabledProperties;

- (id) childElementForKeyPath:(NSString*)keyPath;

- (void) observeUpdatableValue:(ISSUpdatableValue*)value forProperty:(ISSPropertyDeclaration*)propertyDeclaration;
- (void) stopObservingUpdatableValueForProperty:(ISSPropertyDeclaration*)propertyDeclaration;

@end
