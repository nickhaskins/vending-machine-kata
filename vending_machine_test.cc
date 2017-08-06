#include "vending_machine.h"

#include "gtest/gtest.h"

namespace vending_machine_kata {
namespace {

class VendingMachineTest : public ::testing::Test {
 protected:
  VendingMachine vending_machine_;
};

TEST_F(VendingMachineTest, DisplaysInsertCoinsWhenNoCoinsAdded) {
	EXPECT_EQ(vending_machine_.GetDisplay(), "INSERT COIN");
}

TEST_F(VendingMachineTest, AddQuarterDisplaysCurrentAmount) {
	vending_machine_.AddCoin(QUARTER);
	EXPECT_EQ(vending_machine_.GetDisplay(), "0.25");
}

TEST_F(VendingMachineTest, CurrentAmountDependsOnCoinAdded) {
	vending_machine_.AddCoin(DIME);
	EXPECT_EQ(vending_machine_.GetDisplay(), "0.10");

	vending_machine_ = VendingMachine();
	vending_machine_.AddCoin(NICKEL);
	EXPECT_EQ(vending_machine_.GetDisplay(), "0.05");
}

TEST_F(VendingMachineTest, AddingMultipleCoinsSumsCurrentAmount) {
	vending_machine_.AddCoin(DIME);
	vending_machine_.AddCoin(QUARTER);
	EXPECT_EQ(vending_machine_.GetDisplay(), "0.35");
}

TEST_F(VendingMachineTest, AddingPennyRejected) {
	vending_machine_.AddCoin(PENNY);
	EXPECT_EQ(vending_machine_.GetDisplay(), "INSERT COIN");
	std::vector<Coin> expected_coin_return;
	expected_coin_return.push_back(PENNY);
	EXPECT_EQ(vending_machine_.GetCoinReturn(), expected_coin_return);
}

}  // namespace
}  // namespace vending_machine_kata
