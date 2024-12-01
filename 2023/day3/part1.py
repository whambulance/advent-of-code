
file = open('day3/inputs.txt')

specials = '#$%&*+-/=@'

chessboard = {}

for y, row in enumerate(file, 1):
  for x, char in enumerate(row, 1):
    if x not in chessboard.keys():
      chessboard[x] = {}
    chessboard[x][y] = char

def checkvalid(coords):
  xvals = []
  y = 0
  for (x, y) in coords:
    xvals.append(x)
    y = y
  
  coords = []
  xmin = min(xvals)
  xmax = max(xvals)

  coords.append([xmin - 1, y + 1])
  coords.append([xmin - 1, y])
  coords.append([xmin - 1, y - 1])
  coords.append([xmax + 1, y + 1])
  coords.append([xmax + 1, y])
  coords.append([xmax + 1, y - 1])

  for x in xvals:
    coords.append([x, y - 1])
    coords.append([x, y + 1])

  print()
  
  for coord in coords:
    x = coord[0]
    y = coord[1]
    if x not in range(1, 140) or y not in range(1, 140):
      continue
    
    char = chessboard[coord[0]][coord[1]]
    if char in specials:
      return True
  
  return False


validnums = []

file = open('day3/inputs.txt')
for y, row in enumerate(file, 1):
  current = ''
  coords = []
  for x, char in enumerate(row, 1):
    if char.isnumeric():
      current += str(char)
      coords.append([x, y])
    elif current and not char.isnumeric():
      valid = checkvalid(coords)
      if valid:
        validnums.append(int(current))
      current = ''
      coords = []
  
  # if current and char == '.':
  #   valid = checkvalid(coords)
  #   if valid:
  #     validnums.append(int(current))
  #   current = ''
  #   coords = []

# for num in validnums:
#   print(num)
print(sum(validnums))
