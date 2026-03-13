#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <any>
#include <optional>

enum class EventType : uint8_t {
	UNKNOWN = '\0',
	ADD = 'A',
	UPDATE = 'U',
	DELETE = 'D',
	EXECUTE = 'E',
};

enum class Side : uint8_t {
	UNKNOWN = '\0',
	BUY = 'B',
	SELL = 'S',
};

#pragma pack(push, 1)
struct Header {
	int32_t seq_num;
	int32_t msg_size;
	EventType msg_type;

	std::string String() {
		return std::to_string(seq_num) + "/" + static_cast<char>(msg_type);
	}
};

// 1 + 3 + 8 + 1 + 3 + 8 + 4 + 4 = 32
struct OrderAdd {
	char symbol[3];
	uint64_t order_id;
	Side side;
	int8_t _reserved1[3];
	uint64_t size;
	int32_t price;
	int8_t _reserved2[4];
};

// 1 + 3 + 8 + 1 + 3 + 8 + 4 + 4 = 32
struct OrderUpdate {
	char symbol[3];
	uint64_t order_id;
	Side side;
	int8_t _reserved1[3];
	uint64_t size;
	int32_t price;
	int8_t _reserved2[4];
};


// 1 + 3 + 8 + 1 + 3 = 16
struct OrderDelete {
	char symbol[3];
	uint64_t order_id;
	Side side;
	int8_t _reserved1[3];
};

// 1 + 3 + 8 + 1 + 3 + 8 = 24
struct OrderExecute {
	char symbol[3];
	uint64_t order_id;
	Side side;
	int8_t _reserved1[3];
	uint64_t volume;
};

#pragma pack(pop) // pack(push, 1)

struct MsgWithHeader {
	Header header;
	std::any msg;
};

class MessageReader {
public:
	static std::optional<MsgWithHeader> ReadNext(std::istream& s) {
		MsgWithHeader msg;
		msg.header = ReadStruct<Header>(s);
		if (!s.good())
			return std::nullopt;

		switch (msg.header.msg_type) {
			case EventType::ADD:
				msg.msg = ReadStruct<OrderAdd>(s);
				break;
			case EventType::UPDATE:
				msg.msg = ReadStruct<OrderUpdate>(s);
				break;
			case EventType::DELETE:
				msg.msg = ReadStruct<OrderDelete>(s);
				break;
			case EventType::EXECUTE:
				msg.msg = ReadStruct<OrderExecute>(s);
				break;
			default:
				return std::nullopt;
		}

		if (!s.good()) return std::nullopt;
		return msg;
	}
private:
	template<typename T>
	static T ReadStruct(std::istream& s) {
		T t;
		s.read(reinterpret_cast<char*>(&t), sizeof(T));
		return t;
	}
};

