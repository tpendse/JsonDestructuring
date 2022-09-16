#pragma once

#include <string>

namespace JsonDestructure
{

#pragma region CHttpStatusCode

	//
	// Mapped from .NET enum System.Net.HttpStatusCode
	// 
	// Summary:
	//     Contains the values of status codes defined for HTTP.
	enum class CHttpStatusCode
	{
		CHttpStatusCode_Continue                      = 100,
		CHttpStatusCode_SwitchingProtocols            = 101,
		CHttpStatusCode_OK                            = 200,
		CHttpStatusCode_Created                       = 201,
		CHttpStatusCode_Accepted                      = 202,
		CHttpStatusCode_NonAuthoritativeInformation   = 203,
		CHttpStatusCode_NoContent                     = 204,
		CHttpStatusCode_ResetContent                  = 205,
		CHttpStatusCode_PartialContent                = 206,
		CHttpStatusCode_MultipleChoices               = 300,
		CHttpStatusCode_Ambiguous                     = 300,
		CHttpStatusCode_MovedPermanently              = 301,
		CHttpStatusCode_Moved                         = 301,
		CHttpStatusCode_Found                         = 302,
		CHttpStatusCode_Redirect                      = 302,
		CHttpStatusCode_SeeOther                      = 303,
		CHttpStatusCode_RedirectMethod                = 303,
		CHttpStatusCode_NotModified                   = 304,
		CHttpStatusCode_UseProxy                      = 305,
		CHttpStatusCode_Unused                        = 306,
		CHttpStatusCode_TemporaryRedirect             = 307,
		CHttpStatusCode_RedirectKeepVerb              = 307,
		CHttpStatusCode_BadRequest                    = 400,
		CHttpStatusCode_Unauthorized                  = 401,
		CHttpStatusCode_PaymentRequired               = 402,
		CHttpStatusCode_Forbidden                     = 403,
		CHttpStatusCode_NotFound                      = 404,
		CHttpStatusCode_MethodNotAllowed              = 405,
		CHttpStatusCode_NotAcceptable                 = 406,
		CHttpStatusCode_ProxyAuthenticationRequired   = 407,
		CHttpStatusCode_RequestTimeout                = 408,
		CHttpStatusCode_Conflict                      = 409,
		CHttpStatusCode_Gone                          = 410,
		CHttpStatusCode_LengthRequired                = 411,
		CHttpStatusCode_PreconditionFailed            = 412,
		CHttpStatusCode_RequestEntityTooLarge         = 413,
		CHttpStatusCode_RequestUriTooLong             = 414,
		CHttpStatusCode_UnsupportedMediaType          = 415,
		CHttpStatusCode_RequestedRangeNotSatisfiable  = 416,
		CHttpStatusCode_ExpectationFailed             = 417,
		CHttpStatusCode_UpgradeRequired               = 426,
		CHttpStatusCode_InternalServerError           = 500,
		CHttpStatusCode_NotImplemented                = 501,
		CHttpStatusCode_BadGateway                    = 502,
		CHttpStatusCode_ServiceUnavailable            = 503,
		CHttpStatusCode_GatewayTimeout                = 504,
		CHttpStatusCode_HttpVersionNotSupported       = 505
	};

#pragma endregion
}