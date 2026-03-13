#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <string>

#include "message.h"
#include "orderbook.h"

// Helper function to get associated orderbook
OrderBook& getBook(const std::string& symbol, size_t depth,
				   std::unordered_map<std::string, OrderBook>& books) {
	auto it = books.find(symbol);

	if (it == books.end()) {
		it = books.emplace(symbol, OrderBook(depth)).first;
	}

	return it->second;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Provide a depth." << std::endl;
		return 1;
	}

	size_t depth = std::atoi(argv[1]);

	// Make an order book per stock
	std::unordered_map<std::string, OrderBook> books;

	auto opt = MessageReader::ReadNext(std::cin);

	for (; opt.has_value(); opt = MessageReader::ReadNext(std::cin)) {
		auto& mh = opt.value();
		std::string symbol;

		// 1. Cast appropriately
		// 2. Trim the symbol
		// 3. Run appropriate function for each functionality (add, update, etc)
		switch (mh.header.msg_type) {
			case EventType::ADD: {
				auto& msg = std::any_cast<OrderAdd&>(mh.msg);
				symbol = std::string(msg.symbol, 3);
				getBook(symbol, depth, books).add_order(msg.side, msg.order_id, msg.price, msg.size);
				break;
			}
			case EventType::UPDATE: {
				auto& msg = std::any_cast<OrderUpdate&>(mh.msg);
				symbol = std::string(msg.symbol, 3);
				getBook(symbol, depth, books).update_order(msg.side, msg.order_id, msg.price, msg.size);
				break;
			}
			case EventType::DELETE: {
				auto& msg = std::any_cast<OrderDelete&>(mh.msg);
				symbol = std::string(msg.symbol, 3);
				getBook(symbol, depth, books).delete_order(msg.side, msg.order_id);
				break;
			}
			case EventType::EXECUTE: {
				auto& msg = std::any_cast<OrderExecute&>(mh.msg);
				symbol = std::string(msg.symbol, 3);
				getBook(symbol, depth, books).execute_order(msg.side, msg.order_id, msg.volume);
				break;
			}
			default:
				continue;
		}

		// Main output
		auto& book = getBook(symbol, depth, books);
		if (book.snapshot_changed()) {
			std::cout << book.format_snapshot(mh.header.seq_num, symbol) << std::endl;
		}
	}

	return 0;
}
