#include "vending_machine.h"

#include <iomanip>
#include <sstream>

namespace vending_machine_kata {

VendingMachine::VendingMachine()
    : current_amount_(0), just_purchased_(false),
	  display_price_(false), price_to_display_(0) {}

std::string VendingMachine::GetDisplay() {
	if (just_purchased_) {
		just_purchased_ = false;
		return "THANK YOU";
	} else if (display_price_) {
		display_price_ = false;
		std::stringstream sstream;
		sstream << "PRICE ";
		sstream << std::fixed << std::setprecision(2)
		        << (price_to_display_ / 100.0);
		price_to_display_ = 0;
		return sstream.str();

	} else if (current_amount_ == 0) {
		return "INSERT COIN";
	} else {
		std::stringstream sstream;
		sstream << std::fixed << std::setprecision(2)
		        << (current_amount_ / 100.0);
		return sstream.str();
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
			break;
	}
}

std::vector<Coin> VendingMachine::GetCoinReturn() {
	return std::vector<Coin>(1, PENNY);
}

void VendingMachine::PurchaseProduct(Product product) {
	if (current_amount_ == 100) {
		just_purchased_ = true;
		current_amount_ = 0;
		dispensed_products_.push_back("cola");
	} else {
		display_price_ = true;
		price_to_display_ = 100;
	}
}

std::vector<std::string> VendingMachine::GetDispensedProducts() {
	return dispensed_products_;
}


}  // namespace vending_machine_kata
