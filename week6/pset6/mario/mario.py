from cs50 import get_int

# ask for the number of blocks of the piramid
# ...and keep asking until the number is between 1 and 8
while True:
    numberOfBlocks = get_int("Height: ")
    if numberOfBlocks > 0 and numberOfBlocks < 9:
        break
# move across the piramid levels
for currentLevel in range(1, numberOfBlocks + 1, 1):
    # print the spaces on the right side
    numberOfSpaces = numberOfBlocks - currentLevel
    if numberOfSpaces > 0:
        for spaceIndex in range(0, numberOfSpaces, 1):
            print(' ', end='')
    # print the bricks for each level of the piramid
    for brickIndex in range(0, currentLevel, 1):
        print('#', end='')
    print('  ', end='')
    # print the bricks for each level of the piramid
    for brickIndex in range(0, currentLevel, 1):
        print('#', end='')
    print('\n', end='')