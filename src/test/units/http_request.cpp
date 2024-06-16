#include <gtest/gtest.h>

#include <net/http.hpp>

TEST(HttpRequest, ParseSimpleCrlf)
{
	constexpr char data[] = "HTTP/1.1 200 OK\r\n"
							"Date: Thu, 29 Jul 2021 19:20:01 GMT\r\n"
							"Content-Type: text/html; charset=utf-8\r\n"
							"Content-Length: 2\r\n"
							"Connection: close\r\n"
							"Server: gunicorn/19.9.0\r\n"
							"Access-Control-Allow-Origin: *\r\n"
							"Access-Control-Allow-Credentials: true\r\n";
}

TEST(HttpRequest, ParseSimpleLf)
{
	constexpr char data[] = "HTTP/1.1 200 OK\n"
							"Date: Thu, 29 Jul 2021 19:20:01 GMT\n"
							"Content-Type: text/html; charset=utf-8\n"
							"Content-Length: 2\n"
							"Connection: close\n"
							"Server: gunicorn/19.9.0\n"
							"Access-Control-Allow-Origin: *\n"
							"Access-Control-Allow-Credentials: true\n";
}

TEST(HttpRequest, ParseSimpleReverse)
{
	constexpr char data[] = "GET / HTTP/1.1\n"
							"Date: Thu, 29 Jul 2021 19:20:01 GMT\n"
							"Content-Type: text/html; charset=utf-8\n"
							"Content-Length: 2\n"
							"Connection: close\n"
							"Server: gunicorn/19.9.0\n"
							"Access-Control-Allow-Origin: *\n"
							"Access-Control-Allow-Credentials: true\n";
}

TEST(HttpRequest, ParseNotFound)
{
	constexpr char data[] = "HTTP/1.1 404 Not Found\n"
							"Date: Thu, 29 Jul 2021 19:20:01 GMT\n"
							"Content-Type: text/html; charset=utf-8\n"
							"Content-Length: 13\n"
							"Connection: close\n"
							"Server: gunicorn/19.9.0\n"
							"Access-Control-Allow-Origin: *\n"
							"Access-Control-Allow-Credentials: true\n";
}

TEST(HttpRequest, ParseInternalServerError)
{
	constexpr char data[] = "HTTP/1.1 500 Internal Server Error\n"
							"Date: Thu, 29 Jul 2021 19:20:01 GMT\n"
							"Content-Type: text/html; charset=utf-8\n"
							"Content-Length: 21\n"
							"Connection: close\n"
							"Server: gunicorn/19.9.0\n"
							"Access-Control-Allow-Origin: *\n"
							"Access-Control-Allow-Credentials: true\n";
}

TEST(HttpRequest, ParsePostData)
{
	constexpr char data[] = "POST /login HTTP/1.0\n"
							"Host: example.com\n"
							"Content-Type: application/x-www-form-urlencoded; charset=utf-8\n"
							"Content-Length: 26\n"
							"login=user&password=123=45\n";
}
