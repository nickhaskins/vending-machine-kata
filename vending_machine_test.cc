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

TEST(VendingMachineTest, CurrentAmountDependsOnCoinAdded) {
	VendingMachine vending_machine;
	vending_machine.AddCoin(DIME);
	EXPECT_EQ(vending_machine.GetDisplay(), "0.10");

	vending_machine = VendingMachine();
	vending_machine.AddCoin(NICKEL);
	EXPECT_EQ(vending_machine.GetDisplay(), "0.05");
}

TEST(VendingMachineTest, AddingMultipleCoinsSumsCurrentAmount) {
	VendingMachine vending_machine;
	vending_machine.AddCoin(DIME);
	vending_machine.AddCoin(QUARTER);
	EXPECT_EQ(vending_machine.GetDisplay(), "0.35");
}

TEST(VendingMachineTest, AddingPennyRejected) {
	VendingMachine vending_machine;
	vending_machine.AddCoin(PENNY);
	EXPECT_EQ(vending_machine.GetDisplay(), "INSERT COIN");
	std::vector<Coin> expected_coin_return;
	expected_coin_return.push_back(PENNY);
	EXPECT_EQ(vending_machine.GetCoinReturn(), expected_coin_return);
}

}  // namespace
}  // namespace vending_machine_kata
