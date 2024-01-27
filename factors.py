#!/usr/bin/python3

import sys

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <file>")
        sys.exit(EXIT_FAILURE)

    try:
        with open(sys.argv[1], "r") as stream:
            for line in stream:
                number = int(line.strip())
                flag = 1
                div = 2
                while flag:
                    rest = number % div
                    if rest == 0:
                        counter = number // div
                        print(f"{number}={counter}*{div}")
                        flag = 0
                    div += 1
    except FileNotFoundError:
        print(f"File {sys.argv[1]} not found.")
        sys.exit(EXIT_FAILURE)

if __name__ == "__main__":
    main()
