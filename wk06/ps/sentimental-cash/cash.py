from cs50 import get_float


def main():
    dollars = get_dollars()

    quarters, balance = get_change(dollars, 0.25)
    dimes, balance = get_change(balance, 0.10)
    nickels, balance = get_change(balance, 0.05)
    pennies, balance = get_change(balance, 0.01)

    print(int(quarters + dimes + nickels + pennies))


def get_dollars():
    while (True):
        n = get_float("Change owed: ")
        if n >= 0:
            return n
        else:
            print("Please enter positive amount.")


def get_change(dollars, amount):
    coins = dollars // amount
    balance = round(dollars - coins * amount, 2)
    return coins, balance


if __name__ == "__main__":
    main()