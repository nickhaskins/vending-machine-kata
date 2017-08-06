#include "vending_machine.h"

#include <iomanip>
#include <sstream>

namespace vending_machine_kata {

VendingMachine::VendingMachine()
    : current_amount_(0) {}

std::string VendingMachine::GetDisplay() const {
	if (current_amount_ == 0) {
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


}  // namespace vending_machine_kata
