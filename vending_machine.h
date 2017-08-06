#ifndef VENDING_MACHINE_KATA_VENDING_MACHINE_H_
#define VENDING_MACHINE_KATA_VENDING_MACHINE_H_

#include <set>
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
  VendingMachine(int num_colas, int num_chips, int num_candies,
                 int init_num_quarters, int init_num_dimes,
				 int init_num_nickels);

  std::string GetDisplay();

  void AddCoin(Coin coin);

  std::multiset<Coin> GetCoinReturn();

  void PurchaseProduct(Product product);

  std::vector<std::string> GetDispensedProducts();

  void ReturnCoins();

 private:
  int current_amount_;

  bool display_notification_;
  std::string notification_;

  std::vector<std::string> dispensed_products_;
  std::multiset<Coin> coin_return_;
  int colas_;
  int chips_;
  int candies_;

  int quarters_;
  int dimes_;
  int nickels_;
};


}  // namespace vending_machine_kata


#endif  // VENDING_MACHINE_KATA_VENDING_MACHINE_H_
