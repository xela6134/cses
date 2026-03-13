#include <bits/stdc++.h>
using namespace std;

enum Side { BUY, SELL };

struct Order {
    Side side;
    uint64_t orderId;
    double price;
    int volume;
    int timestamp;
};

struct Match {
    uint64_t buyId;
    uint64_t sellId;
    double price;
    int volume;
    int timestamp;
};

class OrderBook {
public:
    OrderBook() : timestamp(0) {
        
    }

    void submitOrder(Order& order) {
        if (order.side == Side::BUY) buyOrder(order);
        else sellOrder(order);
    }

    void cancelOrder(uint64_t orderId) {
        auto it = order_index_.find(orderId);
        if (it == order_index_.end()) return;

        auto listIt = it->second;
        // Figure out price, and side
        double price = listIt->price;
        Side side = listIt->side;

        if (side == Side::BUY) {
            bids_[price].erase(listIt);
            if (bids_[price].empty()) bids_.erase(price);
        } else {
            asks_[price].erase(listIt);
            if (asks_[price].empty()) asks_.erase(price);
        }
    }
private:    
    unordered_map<uint64_t, list<Order>::iterator> order_index_;
    map<double, list<Order>, greater<>> bids_;  // highest first (buy)
    map<double, list<Order>>            asks_;  // lowest first  (sell)

    vector<Match> matches;

    int timestamp;

    void buyOrder(Order& order) {
        // 1. Match aggressively with asks_
        // 2. Keep remaining in bids_
        auto it = asks_.begin();

        // Each while loop is for one price range
        while (it != asks_.end() && order.volume > 0 && it->first <= order.price) {
            double currPrice = it->first;
            auto& q = it->second;

            while (!q.empty() && order.volume > 0) {
                Order& curr = q.front();

                int matchVolume = min(order.volume, curr.volume);

                matches.push_back({order.orderId, curr.orderId, curr.price, matchVolume, timestamp++});

                order.volume -= matchVolume;
                curr.volume -= matchVolume;

                if (curr.volume == 0) {
                    order_index_.erase(curr.orderId);
                    q.pop_front();
                }
            }

            // nit: .erase() returns next iterator
            if (q.empty()) it = asks_.erase(it);
            else ++it;
        }

        if (order.volume > 0) {
            bids_[order.price].push_back(order);
            order_index_[order.orderId] = std::prev(bids_[order.price].end());
        }
    }

    void sellOrder(Order& order) {
        // 1. Match aggressively with bids_
        // 2. Keep remaining in asks_
        
        auto it = bids_.begin();

        while (it != bids_.end() && order.volume > 0 && it->first >= order.price) {
            auto& q = it->second;

            while (!q.empty() && order.volume > 0) {
                Order& curr = q.front();

                int matchVolume = min(curr.volume, order.volume);

                matches.push_back({curr.orderId, order.orderId, curr.price, matchVolume, timestamp++});

                curr.volume -= matchVolume;
                order.volume -= matchVolume;

                if (curr.volume == 0) {
                    order_index_.erase(curr.orderId);
                    q.pop_front();
                }
            }

            if (q.empty()) ++it;
        }

        if (order.volume > 0) {
            asks_[order.price].push_back(order);
            order_index_[order.orderId] = std::prev(asks_[order.price].end());
        }
    }
};
