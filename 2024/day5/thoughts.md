
comparisons can be compiled down into a single list, left to right, of the order that the numbers would be in if every single number was present

as per the example, you get this list:

```
97|75|47|61|53|29|13
```

Convert this into a simple lookup array to get the value of each:

```
[
    97: 0,
    75: 1,
    47: 2,
    // etc ...
]
```

Then, loop over our problem:

```
75,47,61,53,29
```

- Lookup the number assigned to 75 (`1`), and save it.
- Lookup the number assigned to 47 (`2`), and check that it's greater than what we previously saved (it is)
- Continue ensuring there are no errors
