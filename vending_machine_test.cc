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

TEST_F(VendingMachineTest, AddingADollarAndPurchasingColaDispensesCola) {
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(COLA);
	std::vector<std::string> expected_products;
	expected_products.push_back("cola");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");
	EXPECT_EQ(vending_machine_.GetDisplay(), "INSERT COIN");
}

TEST_F(VendingMachineTest, PurchasingProductDisplaysThankYouThenResets) {
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(COLA);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");
	EXPECT_EQ(vending_machine_.GetDisplay(), "INSERT COIN");

	vending_machine_.AddCoin(NICKEL);
	EXPECT_EQ(vending_machine_.GetDisplay(), "0.05");
}

TEST_F(VendingMachineTest, PurchasingWithoutEnoughFundsDisplaysPrice) {
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(COLA);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "PRICE 1.00");
	EXPECT_EQ(vending_machine_.GetDisplay(), "0.50");
}

TEST_F(VendingMachineTest, ProductPriceAndDispensedDependsOnProduct) {
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(CHIPS);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "PRICE 0.50");

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(CHIPS);
	std::vector<std::string> expected_products;
	expected_products.push_back("chips");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
}

}  // namespace
}  // namespace vending_machine_kata
