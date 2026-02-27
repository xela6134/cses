#include <bits/stdc++.h>
using namespace std;

struct Order {
    int id;
    string symbol;
    int price;
    int quantity;
    int timestamp;
};

struct Transaction {
    int buyOrderId;
    int sellOrderId;
    int price;
    int quantity;
};

struct BuyComparator {
    bool operator()(const Order& a, const Order& b) {
        if (a.price != b.price) return a.price < b.price;
        return a.timestamp > b.timestamp;
    }
};

struct SellComparator {
    bool operator()(const Order& a, const Order& b) {
        if (a.price != b.price) return a.price > b.price;
        return a.timestamp > b.timestamp;
    }
};

using BuyHeap  = priority_queue<Order, vector<Order>, BuyComparator>;
using SellHeap = priority_queue<Order, vector<Order>, SellComparator>;

struct SymbolBook {
    BuyHeap buys;
    SellHeap sells;
};

class OrderBook {
    unordered_map<string, SymbolBook> books;
    vector<Transaction> transactions;
    int clock = 0;

public:
    void addBuyOrder(int id, const string& symbol, int price, int quantity) {
        Order order = {id, symbol, price, quantity, clock++};
        auto& book = books[symbol];

        while (order.quantity > 0 && !book.sells.empty() 
               && book.sells.top().price <= order.price) {
            Order sell = book.sells.top();
            book.sells.pop();

            int traded = std::min(order.quantity, sell.quantity);
            transactions.push_back({order.id, sell.id, sell.price, traded});

            order.quantity -= traded;
            sell.quantity -= traded;
            if (sell.quantity > 0) book.sells.push(sell);
        }

        if (order.quantity > 0) book.buys.push(order);
    }

    void addSellOrder(int id, const std::string& symbol, int price, int quantity) {
        Order order = {id, symbol, price, quantity, clock++};
        auto& book = books[symbol];

        while (order.quantity > 0 && !book.buys.empty() 
               && book.buys.top().price >= order.price) {
            Order buy = book.buys.top();
            book.buys.pop();

            int traded = std::min(order.quantity, buy.quantity);
            transactions.push_back({buy.id, order.id, buy.price, traded});

            order.quantity -= traded;
            buy.quantity -= traded;
            if (buy.quantity > 0) book.buys.push(buy);
        }

        if (order.quantity > 0) book.sells.push(order);
    }

    const std::vector<Transaction>& getTransactions() const {
        return transactions;
    }
};

int main() {
    OrderBook book;

    book.addBuyOrder(1, "AAPL", 150, 10);
    book.addBuyOrder(2, "GOOG", 2800, 5);
    book.addSellOrder(3, "AAPL", 148, 6);    // matches AAPL buy#1
    book.addSellOrder(4, "GOOG", 2795, 8);   // matches GOOG buy#2 (5), remainder sits
    book.addSellOrder(5, "AAPL", 149, 7);    // matches AAPL buy#1 remaining (4), remainder sits

    for (const auto& t : book.getTransactions()) {
        std::cout << "Trade: Buy#" << t.buyOrderId
                  << " x Sell#" << t.sellOrderId
                  << " | " << t.quantity << " @ $" << t.price << "\n";
    }
}
