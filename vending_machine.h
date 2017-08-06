#ifndef VENDING_MACHINE_KATA_VENDING_MACHINE_H_
#define VENDING_MACHINE_KATA_VENDING_MACHINE_H_

#include <string>
#include <vector>

namespace vending_machine_kata {


enum Coin {
	PENNY,
	NICKEL,
	DIME,
	QUARTER
};

enum Product {
	COLA,
	CHIPS,
	CANDY
};

class VendingMachine {
 public:
  VendingMachine();

  std::string GetDisplay();

  void AddCoin(Coin coin);

  std::vector<Coin> GetCoinReturn();

  void PurchaseProduct(Product product);

  std::vector<std::string> GetDispensedProducts();

 private:
  std::vector<Coin> MakeChange(int amount);

  int current_amount_;
  bool just_purchased_;
  std::vector<std::string> dispensed_products_;
  bool display_price_;
  int price_to_display_;
  std::vector<Coin> coin_return_;
};


}  // namespace vending_machine_kata


#endif  // VENDING_MACHINE_KATA_VENDING_MACHINE_H_
