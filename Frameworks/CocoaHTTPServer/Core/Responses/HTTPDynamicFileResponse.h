
#import "HTTPResponse.h"
#import "HTTPAsyncFileResponse.h"

/**
 * This class is designed to assist with dynamic content.
 * Imagine you have a file that you want to make dynamic:
 * 
 * <html>
 * <body>
 *   <h1>ComputerName Control Panel</h1>
 *   ...
 *   <li>System Time: SysTime</li>
 * </body>
 * </html>
 * 
 * Now you could generate the entire file in Objective-C,
 * but this would be a horribly tedious process.
 * Beside, you want to design the file with professional tools to make it look pretty.
 * 
 * So all you have to do is escape your dynamic content like this:
 * 
 * ...
 *   <h1>%%ComputerName%% Control Panel</h1>
 * ...
 *   <li>System Time: %%SysTime%%</li>
 * 
 * And then you create an instance of this class with:
 * 
 * - separator = @"%%"
 * - replacementDictionary = { "ComputerName"="Black MacBook", "SysTime"="2010-04-30 03:18:24" }
 * 
 * This class will then perform the replacements for you, on the fly, as it reads the file data.
 * This class is also asynchronous, so it will perform the file IO using its own GCD queue.
 * 
 * All keys for the replacementDictionary must be NSString's.
 * Values for the replacementDictionary may be NSString's, or any object that
 * returns what you want when its description method is invoked.

Example 2: The socket.js file contains a URL template that needs to be completed:
	
 * The socket.js file contains a URL template that needs to be completed:
	
		ws = new WebSocket("%%WEBSOCKET_URL%%");

 * We need to replace "%%WEBSOCKET_URL%%" with whatever URL the server is running on.
 * We can accomplish this easily with the HTTPDynamicFileResponse class, which takes a dictionary
 * of replacement key-value pairs, and performs replacements on the fly as it uploads the file. 

	- (NSObject<HTTPResponse> *)httpResponseForMethod:(NSString *)method URI:(NSString *)path {

	if (![path isEqualToString:@"/WebSocketTest2.js"]) return [super httpResponseForMethod:method URI:path];

		NSString *wsHost = [request headerField:@"Host"];
		NSString *wsLocation = !wsHost ? [NSString stringWithFormat:@"ws://localhost:%hu/service", asyncSocket.localPort]
		                               : [NSString stringWithFormat:@"ws://%@/service", wsHost];

		return [HTTPDynamicFileResponse.alloc initWithFilePath:[self filePathForURI:path]
																						 forConnection:self
																								 separator:@"%%"
																		 replacementDictionary:@{@"WEBSOCKET_URL":wsLocation}];
	}

**/

@interface HTTPDynamicFileResponse : HTTPAsyncFileResponse
{
	NSData *separator;
	NSDictionary *replacementDict;
}

- (id)initWithFilePath:(NSString *)filePath
         forConnection:(HTTPConnection *)connection
             separator:(NSString *)separatorStr
 replacementDictionary:(NSDictionary *)dictionary;

@end

@interface JQueriedResponse : HTTPDynamicFileResponse

- (id)initWithFilePath:(NSString *)filePath
         forConnection:(HTTPConnection *)connection;
@end
