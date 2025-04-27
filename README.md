# C Project / Final Term - 20 Points
## EN
For the final term of the C project, you must implement the whole application (mandatory to obtain the following points):

### (5p) Validations
> [!note]
> Validate all the inputs when requiring them.<br/>
> Be explicit, add the expected format.

#### Example

```cpp
'🚫 Please input date:'
// User doesn't know the expected format
// User doesn't know what the date is for

'✅ Date of aquisition (dd/mm/yyyy):'
// User knows the format
// User knows the date refers to the aquisition date
```


### (5p) Colors
> [!note]
> Add colors to the app.<br/>
> Colors must not take the whole line.<br/>
> Color only some elements, like the name of the product, parking lot etc. depending on the project.

#### Example

🚫 $${\color{red}4. \space Kiwi - 0.68eur \space \(7 pieces\)}$$<br/>
```cpp
// All the line is colored. This is the same as all being white, so it's not counted as you using colors
```

✅ $${\color{darkgray}4. \space \color{lightblue}Kiwi \color{darkgray}- \color{lightgreen}0.68\color{darkgray}eur \space \(\color{orange}7 \color{darkgray}pieces\)}$$<br/>
```cpp
// Only the important elements are colored: product name, price and amount
```

### (5p) Structs
> [!note]
> Use C's `struct` to store in app data. For example:
```cpp
struct Product {
  char name[100];
  int amount;
  float price;
}
```

### (5p) Functions
> [!note]
> Extract core logic to separate functions.<br/>
> For example: `read_file()`, `write_file()`, `add_product(char* name, int amount, ...)` etc.

