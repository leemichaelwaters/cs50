from cs50 import get_int


def main():
    n = get_height()
    print_pyramid(n)


def get_height():
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            return n
        else:
            print("Height should be between 1 and 8 inclusive. Please re-enter.")


def print_pyramid(n):
    for i in range(1, n + 1):
        spaces = ' ' * (n - i)
        blocks = '#' * i
        print(spaces + blocks)


if __name__ == "__main__":
    main()