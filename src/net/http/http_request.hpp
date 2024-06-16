#pragma once

#include <net/http/types.hpp>
#include <net/http/http_header.hpp>

#include <string>
#include <map>

namespace net
{

/// @brief HTTP body
class HttpRequest
{
public:
	/// @brief Get reference to buffer
	/// @return Reference to buffer
	std::string& Buffer();

	/// @brief Get HTTP from string
	/// @return Enum error
	HttpParseErrors ParseBuffer();

	/// @brief Get reference to HTTP header
	/// @return Reference to HTTP header
	HttpHeader& Header();

private:
	/// @brief HTTP command description
	struct HttpCommand
	{
		/// @brief HTTP version
		float version;

		/// @brief HTTP method
		HttpMethod method;

		/// @brief HTTP status
		HttpStatus status;

		/// @brief URL
		std::string_view url;
	};

private:
	/// @brief Buffer
	std::string buffer_;

	/// @brief HTTP header
	HttpHeader header_;
};

} // namespace net
