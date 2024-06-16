#include <net/http/http_request.hpp>

namespace net
{

std::string& HttpRequest::Buffer()
{
	return buffer_;
}

HttpHeader& HttpRequest::Header()
{
	return header_;
}

HttpParseErrors HttpRequest::ParseBuffer()
{
	return Ok;
}

} // namespace net
