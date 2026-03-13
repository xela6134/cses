#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include "message.h"

struct PriceLevel {
	int32_t price;
	uint64_t volume;

	bool operator==(const PriceLevel& other) const {
		return price == other.price && volume == other.volume;
	}
};

// Spec says 
// price: can be negative
// size (volume): is unsigned
struct Order {
    int32_t price;
    uint64_t volume;
};

class OrderBook {
public:
	OrderBook(size_t depth) : depth_(depth) {}

	void add_order(Side side, uint64_t order_id, int32_t price, uint64_t volume) {
		// Add to order book, appropriate side
		auto& order = orders(side);
        order[order_id] = {price, volume};

		// Add the volume
		add_volume(side, price, volume);
	}

	void update_order(Side side, uint64_t order_id, int32_t new_price, uint64_t new_volume) {
		auto& order = orders(side);
		auto it = order.find(order_id);

		// If found: remove volume, update order, add volume
		if (it != order.end()) {
			remove_volume(side, it->second.price, it->second.volume);
			it->second = {new_price, new_volume};
			add_volume(side, new_price, new_volume);
		}
	}

	void delete_order(Side side, uint64_t order_id) {
		auto& order = orders(side);
		auto it = order.find(order_id);

		if (it != order.end()) {
			remove_volume(side, it->second.price, it->second.volume);
			order.erase(it);
		}
	}

	void execute_order(Side side, uint64_t order_id, uint64_t volume) {
		auto& order = orders(side);
		auto it = order.find(order_id);

		if (it != order.end()) {
			uint64_t old_vol = it->second.volume;
			uint64_t new_vol = std::min(volume, old_vol);
			it->second.volume = old_vol - new_vol;

			// Remove minimum quantity
			remove_volume(side, it->second.price, new_vol);
		}
	}

	// Returns true if top-N snapshot changed from last printed
	bool snapshot_changed() {
		auto bids = top_bids();
		auto asks = top_asks();

		// Why we define == operator for PriceLevel
		if (bids == last_bids_ && asks == last_asks_) return false;

		// technically we don't need 'bids' & 'asks' anymore
		last_bids_ = std::move(bids);
		last_asks_ = std::move(asks);
		return true;
	}

	std::string format_snapshot(int32_t seq_num, const std::string& symbol) const {
		std::ostringstream oss;
		oss << seq_num << ", " << symbol << ", [";
		for (size_t i = 0; i < last_bids_.size(); ++i) {
			if (i > 0) oss << ", ";
			oss << "(" << last_bids_[i].price << ", " << last_bids_[i].volume << ")";
		}
		oss << "], [";
		for (size_t i = 0; i < last_asks_.size(); ++i) {
			if (i > 0) oss << ", ";
			oss << "(" << last_asks_[i].price << ", " << last_asks_[i].volume << ")";
		}
		oss << "]";
		return oss.str();
	}
private:
    // 2 unordered_maps for each side
	// {order_id, Order}
	// Order contains price & volume
	std::unordered_map<uint64_t, Order> bid_orders_;
	std::unordered_map<uint64_t, Order> ask_orders_;

    // {price, volume}
	// maintain the aggregated view for output
	// (didn't make it max heap for bid_depth_ because it messes up with helper func)
	std::map<int32_t, uint64_t> bid_depth_;
	std::map<int32_t, uint64_t> ask_depth_;

	// Last printed snapshot for change detection
    // Store most recently printed snapshots
	std::vector<PriceLevel> last_bids_;
	std::vector<PriceLevel> last_asks_;

	size_t depth_;

	std::unordered_map<uint64_t, Order>& orders(Side s) {
		return s == Side::BUY ? bid_orders_ : ask_orders_;
	}

	std::map<int32_t, uint64_t>& depth(Side s) {
		return s == Side::BUY ? bid_depth_ : ask_depth_;
	}

	void add_volume(Side side, int32_t price, uint64_t vol) {
		if (vol == 0) return;

		auto& d = depth(side);
        d[price] += vol;
	}

	void remove_volume(Side side, int32_t price, uint64_t vol) {
		if (vol == 0) return;
		
		auto& d = depth(side);
		auto it = d.find(price);

		if (it != d.end()) {
			// Edge case handling so we don't remove more than we got
			if (it->second <= vol) d.erase(it);
			else it->second -= vol;
		}
	}

	std::vector<PriceLevel> top_bids() const {
		std::vector<PriceLevel> result;
		// Get last elements, depth_ size
		for (auto it = bid_depth_.rbegin(); it != bid_depth_.rend() && result.size() < depth_; ++it) {
			result.push_back({it->first, it->second});
		}
		return result;
	}

	std::vector<PriceLevel> top_asks() const {
		std::vector<PriceLevel> result;
		// Get first elements, depth_ size
		for (auto it = ask_depth_.begin(); it != ask_depth_.end() && result.size() < depth_; ++it) {
			result.push_back({it->first, it->second});
		}
		return result;
	}
};
