
file = open('day3/inputs.txt')

specials = '#$%&*+-/=@'

chessboard = {}

for y, row in enumerate(file, 1):
  for x, char in enumerate(row, 1):
    if x not in chessboard.keys():
      chessboard[x] = {}
    chessboard[x][y] = {'char': char, 'nums': []} 

def determineadjacent(coords, num):
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

  for coord in coords:
    x = coord[0]
    y = coord[1]
    if x not in range(1, 140) or y not in range(1, 140):
      continue
    
    char = chessboard[x][y]['char']
    if char in specials:
      chessboard[x][y]['nums'].append(num)

file = open('day3/inputs.txt')
for y, row in enumerate(file, 1):
  current = ''
  coords = []
  for x, char in enumerate(row, 1):
    if char.isnumeric():
      current += str(char)
      coords.append([x, y])
    elif current and not char.isnumeric():
      determineadjacent(coords, int(current))
      current = ''
      coords = []

to_be_summed = []

for x in chessboard:
  for y in chessboard[x]:
    item = chessboard[x][y]
    if len(item['nums']) == 2:
      to_be_summed.append(item['nums'][0] * item['nums'][1])

print(sum(to_be_summed))
