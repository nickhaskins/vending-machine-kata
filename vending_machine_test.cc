#include "vending_machine.h"

#include "gtest/gtest.h"

namespace vending_machine_kata {
namespace {

TEST(VendingMachineTest, DisplaysInsertCoinsWhenNoCoinsAdded) {
	VendingMachine vending_machine;
	EXPECT_EQ(vending_machine.GetDisplay(), "INSERT COIN");
}

TEST(VendingMachineTest, AddQuarterDisplaysCurrentAmount) {
	VendingMachine vending_machine;
	vending_machine.AddCoin(QUARTER);
	EXPECT_EQ(vending_machine.GetDisplay(), "0.25");
}

}  // namespace
}  // namespace vending_machine_kata
