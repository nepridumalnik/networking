#include <net/http/http_header.hpp>

namespace net
{

HttpParseErrors HttpHeader::FromString(const std::string_view headers)
{
	return Ok;
}

void HttpHeader::Clear()
{
	headers_.clear();
}

const std::string_view& HttpHeader::operator[](const std::string_view key) const
{
	static constexpr std::string_view none;

	auto it = headers_.find(key);

	if (it == headers_.end())
	{
		return none;
	}

	return it->second;
}

} // namespace net
