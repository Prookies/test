#include <iostream>
#include <memory>
#include <map>

using namespace std;

struct Stock {
	int key;
	int data;
};

class StockFactory : enable_shared_from_this<StockFactory>
{
public:
	shared_ptr<Stock> get(const string& key)
	{
		MutexLockGuard lock(mutex_);
		weak_ptr<Stock>& wkStock = stocks_[key];
		if (!pStock)
		{
			pStock.reset(new Stock(key),
						bind(&StockFactory::weakDeleteCallback,
							weak_ptr<StockFactory>(shared_from_this()),
							-1));
			wkStock = pStock;
		}
		return pStock;
	}
private:
	static void weakDeleteCallback(const weak_ptr<StockFactory>& wkFactory, Stock* stock)
	{
		shared_ptr<StockFactory> factory(wkFactory.lock());
		if (factory)
		{
			factory->removeStock(stock);
		}
		delete stock;
	}

	void removeStock(Stock* stock)
	{
		if (stock)
		{
			MutexLockGuard lock(mutex_);
			stocks_.erase(stock->key());
		}
	}

	private:
		mutable MutexLock mutex_;
		std::map<string, weak_ptr<Stock> > stocks_;
};

void testLongLifeFactory()
{
	shared_ptr<StockFactory> factory(new StockFactory);
	{
		shared_ptr<Stock> stock = factory->get("NYSE:IBM");
		shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
		assert(stock == stock2);
	}
}

void testShortLifeFactory()
{
	shared_ptr<Stock> stock;
	{
		shared_ptr<StockFactory> factory(new StockFactory);
		stock = factory->get("NYSE:IBM");
		shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
		assert(stock == stock2);
	}
}

int main()
{
	testLongLifeFactory();
	testShortLifeFactory();
}
