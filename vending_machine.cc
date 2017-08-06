#include "vending_machine.h"

#include <iomanip>
#include <sstream>

namespace vending_machine_kata {

VendingMachine::VendingMachine()
    : current_amount_(0), just_purchased_(false) {}

std::string VendingMachine::GetDisplay() {
	if (just_purchased_) {
		just_purchased_ = false;
		return "THANK YOU";
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
	just_purchased_ = true;
	current_amount_ = 0;
}

std::vector<std::string> VendingMachine::GetDispensedProducts() {
	return std::vector<std::string>(1, "cola");
}


}  // namespace vending_machine_kata
