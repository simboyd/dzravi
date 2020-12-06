/*
 * HTTP Status Codes - C Variant
 *
 * https://github.com/j-ulrich/http-status-codes-cpp
 *
 * version 1.3.0
 * author Jochen Ulrich <jochenulrich@t-online.de>
 * copyright Licensed under Creative Commons CC0 (http://creativecommons.org/publicdomain/zero/1.0/)
 */

enum HttpStatus_Code
{
	/*####### 1xx - Informational #######*/
	/* Indicates an interim response for communicating connection status
	 * or request progress prior to completing the requested action and
	 * sending a final response.
	 */
	HttpStatus_Continue           = 100, 
	HttpStatus_SwitchingProtocols = 101, 
	HttpStatus_Processing         = 102, 
	HttpStatus_EarlyHints         = 103, 

	/*####### 2xx - Successful #######*/
	/* Indicates that the client's request was successfully received,
	 * understood, and accepted.
	 */
	HttpStatus_OK                          = 200,
	HttpStatus_Created                     = 201,
	HttpStatus_Accepted                    = 202,
	HttpStatus_NonAuthoritativeInformation = 203,
	HttpStatus_NoContent                   = 204,
	HttpStatus_ResetContent                = 205,
	HttpStatus_PartialContent              = 206,
	HttpStatus_MultiStatus                 = 207,
	HttpStatus_AlreadyReported             = 208,
	HttpStatus_IMUsed                      = 226,

	/*####### 3xx - Redirection #######*/
	/* Indicates that further action needs to be taken by the user agent
	 * in order to fulfill the request.
	 */
	HttpStatus_MultipleChoices   = 300, 
	HttpStatus_MovedPermanently  = 301, 
	HttpStatus_Found             = 302, 
	HttpStatus_SeeOther          = 303, 
	HttpStatus_NotModified       = 304, 
	HttpStatus_UseProxy          = 305, 
	HttpStatus_TemporaryRedirect = 307, 
	HttpStatus_PermanentRedirect = 308, 

	/*####### 4xx - Client Error #######*/
	/* Indicates that the client seems to have erred.
	 */
	HttpStatus_BadRequest                  = 400,
	HttpStatus_Unauthorized                = 401,
	HttpStatus_PaymentRequired             = 402,
	HttpStatus_Forbidden                   = 403,
	HttpStatus_NotFound                    = 404,
	HttpStatus_MethodNotAllowed            = 405,
	HttpStatus_NotAcceptable               = 406,
	HttpStatus_ProxyAuthenticationRequired = 407,
	HttpStatus_RequestTimeout              = 408,
	HttpStatus_Conflict                    = 409, 
	HttpStatus_Gone                        = 410, 
	HttpStatus_LengthRequired              = 411, 
	HttpStatus_PreconditionFailed          = 412, 
	HttpStatus_PayloadTooLarge             = 413, 
	HttpStatus_URITooLong                  = 414,
	HttpStatus_UnsupportedMediaType        = 415,
	HttpStatus_RangeNotSatisfiable         = 416, 
	HttpStatus_ExpectationFailed           = 417, 
	HttpStatus_ImATeapot                   = 418, 
	HttpStatus_UnprocessableEntity         = 422, 
	HttpStatus_Locked                      = 423, 
	HttpStatus_FailedDependency            = 424, 
	HttpStatus_UpgradeRequired             = 426, 
	HttpStatus_PreconditionRequired        = 428, 
	HttpStatus_TooManyRequests             = 429, 
	HttpStatus_RequestHeaderFieldsTooLarge = 431, 
	HttpStatus_UnavailableForLegalReasons  = 451, 

	/*####### 5xx - Server Error #######*/
	/* Indicates that the server is aware that it has erred
	 * or is incapable of performing the requested method.
	 */
	HttpStatus_InternalServerError           = 500, 
	HttpStatus_NotImplemented                = 501,
	HttpStatus_BadGateway                    = 502,
	HttpStatus_ServiceUnavailable            = 503, 
	HttpStatus_GatewayTimeout                = 504, 
	HttpStatus_HTTPVersionNotSupported       = 505, 
	HttpStatus_VariantAlsoNegotiates         = 506, 
	HttpStatus_InsufficientStorage           = 507, 
	HttpStatus_LoopDetected                  = 508, 
	HttpStatus_NotExtended                   = 510, 
	HttpStatus_NetworkAuthenticationRequired = 511, 
	
	HttpStatus_xxx_max = 1023
};
