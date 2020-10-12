from cs50 import get_int

# Main function
def main():
    height = get_height()
    print_blocks(height)

# Function to display blocks
# @param height
def print_blocks(height):
    result = ""
    for i in range(height + 1):
        addLine = False
        for j in range(height - i + 1):
            if j > 0:
                result += " "
        for k in range(i + 1):
            if k > 0:
                result += "#"
                addLine = True

        result += "  "

        for k in range(i + 1):
            if k > 0:
                result += "#"
                addLine = True
        if (addLine):
            result += "\n"

    print(result)

# Function to get the height from the user
def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

main()