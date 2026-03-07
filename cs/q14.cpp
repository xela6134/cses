#include <bits/stdc++.h>
using namespace std;

enum class Side {
    BID,
    ASK
};

// Struct to represent Best Bid and Offer cleanly
struct BBO {
    double best_bid;
    double best_ask;
};

// For a single stock

class OrderBook {
public:
    OrderBook() = default;

    /**
     * @brief Records a new order in the system.
     * @param exchange_id The identifier for the exchange (e.g., "NYSE", "NASDAQ").
     * @param price The price of the order.
     * @param quantity The volume of the order (stored, but doesn't affect ranking).
     * @param side Side::BID for buy orders, Side::ASK for sell orders.
     */
    void add(string exchange_id, double price, int quantity, Side side) {

    }

    /**
     * @brief Retrieves the Best Bid and Offer for a specific exchange.
     * @param exchange_id The identifier for the exchange.
     * @return BBO containing the highest bid and lowest ask for this exchange.
     * Values will be -1 if no bid/ask exists yet.
     */
    BBO get_exchange_bbo(string exchange_id) const {

    }

    /**
     * @brief Retrieves the National Best Bid and Offer across all exchanges.
     * @return BBO containing the global highest bid and global lowest ask.
     * Values will be -1 if the market has no bids/asks.
     */
    BBO get_nbbo() const {

    }

private:
    unordered_map<string, BBO> exchangeBBO;
    BBO globalBBO = {-1, -1};
};
