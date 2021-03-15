#include "Network.h"

typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_message(websocketpp::connection_hdl, server::message_ptr msg) {
	Event->Listener(msg->get_payload().c_str());
}

void testparam()
{
	server socket;

	try {
		socket.set_message_handler(&on_message);

		socket.set_access_channels(websocketpp::log::alevel::all);
		socket.clear_access_channels(websocketpp::log::alevel::frame_payload);

		socket.init_asio();

		socket.listen(7331);

		socket.start_accept();

		socket.run();
	}
	catch (...) {

	}
}

bool CNetwork::Initialize(const struct TS3Functions ts3)
{
	if (this->Initialized)
		return false;

	this->Initialized = true;

	this->Functions = ts3;

	std::thread thread(testparam);
	thread.detach();

	std::thread thread_heartbeat(&CEvent::Heartbeat, Event);
	thread_heartbeat.detach();

	return true;
}
