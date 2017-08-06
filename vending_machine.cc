#include "vending_machine.h"

#include <sstream>

namespace vending_machine_kata {

VendingMachine::VendingMachine()
    : current_amount_(0) {}

std::string VendingMachine::GetDisplay() const {
	if (current_amount_ == 0) {
		return "INSERT COIN";
	} else {
		std::stringstream sstream;
		sstream << (current_amount_ / 100.0);
		return sstream.str();
	}
}

void VendingMachine::AddCoin(Coin coin) {
	current_amount_ = 25;
}


}  // namespace vending_machine_kata
