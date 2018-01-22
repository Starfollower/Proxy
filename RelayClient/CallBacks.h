#pragma once
#include <functional>
#include <memory>

class TcpConnection;
using ReadCallback = std::function<void(std::shared_ptr<TcpConnection>)>;
