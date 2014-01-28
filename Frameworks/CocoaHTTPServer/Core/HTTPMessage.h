/**
 * The HTTPMessage class is a simple Objective-C wrapper around Apple's CFHTTPMessage class.
**/



#if TARGET_OS_IPHONE
  // Note: You may need to add the CFNetwork Framework to your project
  #import <CFNetwork/CFNetwork.h>
#endif

#define HTTPVersion1_0  ((NSString *)kCFHTTPVersion1_0)
#define HTTPVersion1_1  ((NSString *)kCFHTTPVersion1_1)

@interface HTTPMessage : NSObject {	CFHTTPMessageRef message; }

+   (instancetype) emptyRequest;
-   (id) initEmptyRequest;
-   (id) initRequestWithMethod:		  (NSString*)method			  URL:(NSURL*)url						 version:(NSString *)version;
-   (id) initResponseWithStatusCode:(NSInteger)code description:(NSString*)description version:(NSString *)version;
- (BOOL) appendData:									(NSData*)data;

@property (readonly)         BOOL   isHeaderComplete;
@property (readonly)     NSString * version, * method;
@property (readonly)        NSURL * url;
@property (readonly)    NSInteger   statusCode;
@property (readonly) NSDictionary * allHeaderFields;
@property (readonly)       NSData * messageData;
@property						       NSData * body;

- (NSString*) objectForKeyedSubscript:(NSString*)field;
- (void)setObject:(NSString*)headerValue forKeyedSubscript:(id <NSCopying>)field;

- (NSString*)headerField:(NSString *)headerField;
- (void)setHeaderField:(NSString *)headerField value:(NSString *)headerFieldValue;


@end
