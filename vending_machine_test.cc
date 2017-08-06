#include "vending_machine.h"

#include "gtest/gtest.h"

namespace vending_machine_kata {
namespace {

TEST(VendingMachineTest, DisplaysInsertCoinsWhenNoCoinsAdded) {
	VendingMachine vending_machine;
	EXPECT_EQ("INSERT COIN", vending_machine.GetDisplay());
}

}  // namespace
}  // namespace vending_machine_kata
