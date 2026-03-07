#include <bits/stdc++.h>
using namespace std;

struct Order {
    int         id;
    bool        isBuy;      // true = buy, false = sell
    double      price;
    int         quantity;
    long long   timestamp;  // used for FIFO tie-breaking
};

struct Trade {
    int    buyOrderId;
    int    sellOrderId;
    double executionPrice;
    int    executedQuantity;
};

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price != b.price) return a.price < b.price;   // max-heap on price
        return a.timestamp > b.timestamp;                    // min on timestamp
    }
};

struct SellComparator {
    bool operator()(const Order& a, const Order& b) const {
        if (a.price != b.price) return a.price > b.price;   // min-heap on price
        return a.timestamp > b.timestamp;                    // min on timestamp
    }
};

class OrderBook {
public:
    OrderBook() : nextOrderId(1), currentTime(0) {}

    vector<Trade> placeOrder(bool isBuy, double price, int quantity) {
        Order order {
            nextOrderId++,
            isBuy,
            price,
            quantity,
            currentTime++
        };

        std::vector<Trade> trades;

        if (isBuy) matchBuy (order, trades);
        else       matchSell(order, trades);

        return trades;
    }

private:
    priority_queue<Order, vector<Order>, BuyComparator>  buyOrders;
    priority_queue<Order, vector<Order>, SellComparator> sellOrders;

    int       nextOrderId;
    long long currentTime;

    // ── Matching logic ────────────────────────

    void matchBuy(Order& buy, vector<Trade>& trades) {
        // Match against the cheapest available sell orders
        while (buy.quantity > 0 && !sellOrders.empty()) {
            Order sell = sellOrders.top();

            if (buy.price < sell.price) break;   // no match possible

            sellOrders.pop();

            int matchedQty = std::min(buy.quantity, sell.quantity);

            trades.push_back({
                buy.id,
                sell.id,
                sell.price,       // execution price = resting order's price
                matchedQty
            });

            buy.quantity  -= matchedQty;
            sell.quantity -= matchedQty;

            // Remaining sell quantity
            if (sell.quantity > 0) sellOrders.push(sell);
        }

        // Remaining buy quantity
        if (buy.quantity > 0) buyOrders.push(buy);
    }

    void matchSell(Order& sell, std::vector<Trade>& trades) {
        // Match against the most generous available buy orders
        while (sell.quantity > 0 && !buyOrders.empty()) {
            Order buy = buyOrders.top();

            if (sell.price > buy.price) break;   // no match possible

            buyOrders.pop();

            int matchedQty = std::min(sell.quantity, buy.quantity);

            trades.push_back({
                buy.id,
                sell.id,
                buy.price,        // execution price = resting order's price
                matchedQty
            });

            sell.quantity -= matchedQty;
            buy.quantity  -= matchedQty;

            if (buy.quantity > 0)    // partial fill — push remainder back
                buyOrders.push(buy);
        }

        if (sell.quantity > 0)        // unfilled remainder rests in the book
            sellOrders.push(sell);
    }
};
