#include "vending_machine.h"

#include "gtest/gtest.h"

namespace vending_machine_kata {
namespace {

class VendingMachineTest : public ::testing::Test {
 protected:
  VendingMachineTest() : vending_machine_(5, 2, 1,
                                          5, 5, 5) {}

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

	vending_machine_ = VendingMachine(5, 5, 5, 5, 5, 5);
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
	std::multiset<Coin> expected_coin_return;
	expected_coin_return.insert(PENNY);
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
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(DIME);
	vending_machine_.PurchaseProduct(CANDY);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "PRICE 0.65");

	vending_machine_.AddCoin(NICKEL);
	vending_machine_.PurchaseProduct(CANDY);
	expected_products.clear();
	expected_products.push_back("candy");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");
}

TEST_F(VendingMachineTest, ReturnsChangeWhenCurrentAmountGreaterThanPrice) {
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(CHIPS);
	std::vector<std::string> expected_products;
	expected_products.push_back("chips");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");
	std::multiset<Coin> expected_coin_return;
	expected_coin_return.insert(QUARTER);
	EXPECT_EQ(vending_machine_.GetCoinReturn(),  expected_coin_return);
}

TEST_F(VendingMachineTest, ChangeReturnedVariesBasedOnCurrentAmount) {
	vending_machine_.AddCoin(NICKEL);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(CHIPS);
	std::vector<std::string> expected_products;
	expected_products.push_back("chips");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");
	std::multiset<Coin> expected_coin_return;
	expected_coin_return.insert(NICKEL);
	EXPECT_EQ(vending_machine_.GetCoinReturn(),  expected_coin_return);
}

TEST_F(VendingMachineTest, ReturnsCoinsWhenRequested) {
	vending_machine_.AddCoin(NICKEL);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.ReturnCoins();
	std::multiset<Coin> expected_coin_return;
	expected_coin_return.insert(NICKEL);
	expected_coin_return.insert(QUARTER);
	EXPECT_EQ(vending_machine_.GetCoinReturn(), expected_coin_return);
	EXPECT_EQ(vending_machine_.GetDisplay(), "INSERT COIN");
}

TEST_F(VendingMachineTest, DisplaysSoldOutDoesNotDispenseWhenOutOfProduct) {
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(DIME);
	vending_machine_.AddCoin(NICKEL);
	vending_machine_.PurchaseProduct(CANDY);
	std::vector<std::string> expected_products;
	expected_products.push_back("candy");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(DIME);
	vending_machine_.AddCoin(NICKEL);
	vending_machine_.PurchaseProduct(CANDY);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "SOLD OUT");
}

TEST_F(VendingMachineTest, ProductsSellOutSeparately) {
	vending_machine_ = VendingMachine(1, 1, 1, 5, 5, 5);

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(COLA);
	std::vector<std::string> expected_products;
	expected_products.push_back("cola");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(COLA);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "SOLD OUT");
	vending_machine_.ReturnCoins();

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(CHIPS);
	expected_products.clear();
	expected_products.push_back("chips");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.PurchaseProduct(CHIPS);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "SOLD OUT");
	vending_machine_.ReturnCoins();

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(DIME);
	vending_machine_.AddCoin(NICKEL);
	vending_machine_.PurchaseProduct(CANDY);
	expected_products.clear();
	expected_products.push_back("candy");
	EXPECT_EQ(vending_machine_.GetDispensedProducts(), expected_products);
	EXPECT_EQ(vending_machine_.GetDisplay(), "THANK YOU");

	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(QUARTER);
	vending_machine_.AddCoin(DIME);
	vending_machine_.AddCoin(NICKEL);
	vending_machine_.PurchaseProduct(CANDY);
	EXPECT_EQ(vending_machine_.GetDispensedProducts(),
	          std::vector<std::string>());
	EXPECT_EQ(vending_machine_.GetDisplay(), "SOLD OUT");
	vending_machine_.ReturnCoins();
}

// It seems like there's some insight I'm missing here about when exact change
// would be required or how the machine would get in that state.  Being able to
// make change depends on what coins there are in the machine, what money the
// customer gives, and what the price is of the item being purchased, so the
// machine wouldn't necessarily be unable to make change unless it had no coins
// at all.  Also, unless the machine is emptied of coins through some other
// process, such as never having any as I've set up here, it doesn't seem
// possible for it to run out of *all* coins, as a customer always has to
// provide some coins that the machine will not return.  Like I say, it seems
// like there's something I'm missing about this part of the kata.
TEST_F(VendingMachineTest, DisplaysExactChangeWhenItHasNoCoins) {
	vending_machine_ = VendingMachine(5, 5, 5, 0, 0, 0);
	EXPECT_EQ(vending_machine_.GetDisplay(), "EXACT CHANGE ONLY");
}

}  // namespace
}  // namespace vending_machine_kata
