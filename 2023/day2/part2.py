
file = open('day2/inputs.txt')

powers = []

for i, row in enumerate(file, 1):
  index = row.find(':')
  formatted_string = row.replace('\n', '').replace(';', ',')[index + 2:]
  values = formatted_string.split(', ')

  red_max = 0
  green_max = 0
  blue_max = 0

  for value in values:
    count, color = value.split(' ')
    if color == 'red' and int(count) > red_max:
      red_max = int(count) 
    elif color == 'green' and int(count) > green_max:
      green_max = int(count) 
    elif color == 'blue' and int(count) > blue_max:
      blue_max = int(count) 
  
  powers.append(red_max * green_max * blue_max)

print(sum(powers))

    


