#pragma once

namespace net
{

/// @brief HTTP parse errors
enum HttpParseErrors
{
	/// @brief No error
	Ok,

	/// @brief Invalid HTTP header
	InvalidHeader,

	/// @brief Invalid HTTP body
	InvalidBody,

	/// @brief Invalid HTTP version
	InvalidVersion,

	/// @brief HTTP status empty
	EmptyStatus,

	/// @brief Method has no URL in HTTP request
	MethodWithoutUrl,
};

/// @brief Enum with HTTP methods
enum HttpMethod
{
	/// @brief HTTP method not spiecified
	Empty,

	/// @brief HTTP GET method
	Get,

	/// @brief HTTP POST method
	Post,

	/// @brief HTTP PUT method
	Put,

	/// @brief HTTP DELETE method
	Delete,

	/// @brief HTTP HEAD method
	Head,

	/// @brief HTTP OPTIONS method
	Options,

	/// @brief HTTP PATCH method
	Patch,

	/// @brief HTTP TRACE method
	Trace,

	/// @brief HTTP CONNECT method
	Connect,
};

/// @brief HTTP statuses
enum HttpStatus
{
	// 100
	Continue = 100,
	SwitchingProtocols = 101,
	Processing = 102,
	EarlyHints = 103,

	// 200
	OK = 200,
	Created = 201,
	Accepted = 202,
	NonAuthoritativeInfo = 203,
	NoContent = 204,
	ResetContent = 205,
	PartialContent = 206,
	Multi = 207,
	AlreadyReported = 208,
	IMUsed = 226,

	// 300
	MultipleChoices = 300,
	MovedPermanently = 301,
	Found = 302,
	SeeOther = 303,
	NotModified = 304,
	UseProxy = 305,
	StatusReserved = 306,
	TemporaryRedirect = 307,
	PermanentRedirect = 308,

	// 400
	BadRequest = 400,
	Unauthorized = 401,
	PaymentRequired = 402,
	Forbidden = 403,
	NotFound = 404,
	MethodNotAllowed = 405,
	NotAcceptable = 406,
	ProxyAuthRequired = 407,
	RequestTimeout = 408,
	Conflict = 409,
	Gone = 410,
	LengthRequired = 411,
	PreconditionFailed = 412,
	RequestEntityTooLarge = 413,
	RequestURITooLong = 414,
	UnsupportedMediaType = 415,
	RequestedRangeNotSatisfiable = 416,
	ExpectationFailed = 417,
	Teapot = 418,
	MisdirectedRequest = 421,
	UnprocessableEntity = 422,
	Locked = 423,
	FailedDependency = 424,
	TooEarly = 425,
	UpgradeRequired = 426,
	PreconditionRequired = 428,
	TooManyRequests = 429,
	RequestHeaderFieldsTooLarge = 431,
	UnavailableForLegalReasons = 451,

	// 500
	InternalServerError = 500,
	NotImplemented = 501,
	BadGateway = 502,
	ServiceUnavailable = 503,
	GatewayTimeout = 504,
	HTTPVersionNotSupported = 505,
	VariantAlsoNegotiates = 506,
	InsufficientStorage = 507,
	LoopDetected = 508,
	NotExtended = 510,
	NetworkAuthenticationRequired = 511,
};

} // namespace net
