
file = open('day2/inputs.txt')

valid_indexes = []

for i, row in enumerate(file, 1):
  red = 12
  green = 13
  blue = 14
  index = row.find(':')
  formatted_string = row.replace('\n', '').replace(';', ',')[index + 2:]
  values = formatted_string.split(', ')

  valid = True

  for value in values:
    count, color = value.split(' ')
    if color == 'red' and int(count) > red:
      valid = False
    elif color == 'green' and int(count) > green:
      valid = False
    elif color == 'blue' and int(count) > blue:
      valid = False

  if valid:
    valid_indexes.append(i)

print(sum(valid_indexes))

    


