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

    void submitOrder(Order order) {
        if (order.side == Side::BUY) buyOrder(order);
        else sellOrder(order);
    }

    void cancelOrder(uint64_t orderId) {
        auto it = order_info_.find(orderId);
        if (it == order_info_.end()) return;

        auto listIt = order_info_[orderId];
        double price = listIt->price;
        Side side = listIt->side;

        if (side == Side::BUY) {
            buys_[price].erase(listIt);
            if (buys_[price].empty()) buys_.erase(price);
        } else {
            sells_[price].erase(listIt);
            if (sells_[price].empty()) sells_.erase(price);
        }
    }
private:
    int timestamp;

    unordered_map<uint64_t, list<Order>::iterator> order_info_;
    map<double, list<Order>> sells_;
    map<double, list<Order>, greater<double>> buys_;

    vector<Match> matches;

    void buyOrder(Order order) {
        auto it = sells_.begin();

        while (it != sells_.end() && order.volume > 0 && it->first <= order.price) {
            double currPrice = it->first;
            auto& q = it->second;

            while (!q.empty() && order.volume > 0) {
                Order& front = q.front();

                int matchedVolume = min(front.volume, order.volume);

                matches.push_back({order.orderId, front.orderId, front.price, matchedVolume, timestamp++});

                front.volume -= matchedVolume;
                order.volume -= matchedVolume;

                if (front.volume == 0) {
                    order_info_.erase(front.orderId);
                    q.pop_front();
                }
            }

            if (q.empty()) it = sells_.erase(it);
            else ++it;
        }

        if (order.volume > 0) {
            buys_[order.price].push_back(order);
            order_info_[order.orderId] = std::prev(buys_[order.price].end());
        }
    }

    void sellOrder(Order order) {

    }
};
