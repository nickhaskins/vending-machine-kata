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
  VendingMachine(int num_colas, int num_chips, int num_candies);

  std::string GetDisplay();

  void AddCoin(Coin coin);

  std::vector<Coin> GetCoinReturn();

  void PurchaseProduct(Product product);

  std::vector<std::string> GetDispensedProducts();

 private:
  int current_amount_;

  bool display_notification_;
  std::string notification_;

  std::vector<std::string> dispensed_products_;
  std::vector<Coin> coin_return_;
  int colas_;
  int chips_;
  int candies_;
};


}  // namespace vending_machine_kata


#endif  // VENDING_MACHINE_KATA_VENDING_MACHINE_H_
