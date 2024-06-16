#pragma once

#include <net/http/types.hpp>

#include <string_view>
#include <map>

namespace net
{

/// @brief  Http header parser
class HttpHeader
{
public:
	/// @brief Create from string_view
	/// @param headers string_view with headers
	/// @return Parsing status
	HttpParseErrors FromString(const std::string_view headers);

	/// @brief Clear data
	void Clear();

	/// @brief Get header value
	/// @param key header key
	/// @return Const reference to header value
	const std::string_view& operator[](const std::string_view key) const;

private:
	/// @brief HTTP headers as key/value pairs
	std::map<const std::string_view, const std::string_view> headers_;
};

} // namespace net
