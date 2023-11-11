#pragma once

class Wallet
{
private:
	int coins = 20;

public:
	Wallet(/* args */);
	~Wallet();

	int GetCoins() { return coins; }

	void AddCoins(int pCoins) { coins += pCoins; }
};

