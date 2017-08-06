#include "vending_machine.h"

#include <iomanip>
#include <sstream>

namespace vending_machine_kata {
namespace {

std::multiset<Coin> MakeChange(int amount) {
	int quarters = amount / 25;
	amount -= quarters * 25;
	int dimes = amount / 10;
	amount -= dimes * 10;
	int nickels = amount / 5;

	std::multiset<Coin> result;
	for (int i = 0; i < quarters; ++i) {
		result.insert(QUARTER);
	}
	for (int i = 0; i < dimes; ++i) {
		result.insert(DIME);
	}
	for (int i = 0; i < nickels; ++i) {
		result.insert(NICKEL);
	}
	return result;
}

std::string FormatMoneyString(int amount_in_cents) {
	std::stringstream sstream;
	sstream << std::fixed << std::setprecision(2)
			<< (amount_in_cents / 100.0);
	return sstream.str();
}

}  // namespace

VendingMachine::VendingMachine(int num_colas, int num_chips, int num_candies)
    : current_amount_(0), display_notification_(false),
	  colas_(num_colas), chips_(num_chips), candies_(num_candies) {}

std::string VendingMachine::GetDisplay() {
	if (display_notification_) {
		display_notification_ = false;
		return notification_;
	} else if (current_amount_ == 0) {
		return "INSERT COIN";
	} else {
		return FormatMoneyString(current_amount_);
	}
}

void VendingMachine::AddCoin(Coin coin) {
	switch (coin) {
		case QUARTER:
			current_amount_ += 25;
			break;
		case DIME:
			current_amount_ += 10;
			break;
		case NICKEL:
			current_amount_ += 5;
			break;
		default:
			coin_return_.insert(coin);
			break;
	}
}

std::multiset<Coin> VendingMachine::GetCoinReturn() {
	return coin_return_;
}

void VendingMachine::PurchaseProduct(Product product) {
	if (product == CANDY && candies_ == 0) {
		display_notification_ = true;
		notification_ = "SOLD OUT";
		return;
	}
	int price = 0;
	std::string product_to_dispense = "";
	switch (product) {
		case COLA:
			price = 100;
			product_to_dispense = "cola";
			break;
		case CHIPS:
			price = 50;
			product_to_dispense = "chips";
			break;
		case CANDY:
			price = 65;
			product_to_dispense = "candy";
			break;
	}
	if (current_amount_ >= price) {
		display_notification_ = true;
		notification_ = "THANK YOU";
		if (product == CANDY) {
			candies_ -= 1;
		}
		std::multiset<Coin> change = MakeChange(current_amount_ - price);
		coin_return_.insert(change.begin(), change.end());
		current_amount_ = 0;
		dispensed_products_.push_back(product_to_dispense);
	} else {
		display_notification_ = true;
		notification_ = "PRICE " + FormatMoneyString(price);
	}
}

std::vector<std::string> VendingMachine::GetDispensedProducts() {
	std::vector<std::string> to_return;
	to_return.swap(dispensed_products_);
	return to_return;
}

void VendingMachine::ReturnCoins() {
	std::multiset<Coin> to_return = MakeChange(current_amount_);
	coin_return_.insert(to_return.begin(), to_return.end());
	current_amount_ = 0;
}


}  // namespace vending_machine_kata
