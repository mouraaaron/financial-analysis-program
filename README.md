* Investment Performance Comparator (C Programming)
This project is a command-line tool developed in C to compare the historical performance of various financial investments.
It calculates capital growth using compound interest for fixed-income rates and currency fluctuations for quoted assets.

* Key features
-> Compound Interest Calculation: Accurately converts annual rates (SELIC, IPCA) into monthly exponential growth to reflect real-world capitalization.
-> Asset Comparison: Compares fixed rates against quoted assets like the US Dollar or Stock Market indices.
-> Rolling Window Analysis: Implements a moving window algorithm to determine which investment performed better in specific time intervals (e.g., 6 to 12 months) throughout history

* Implementation Details
To achieve the project goals, I utilized several advanced C programming concepts:

->File I/O & String Manipulation: Parsing custom text files and handling file extensions (.tax vs. .cot) to determine calculation logic.

->Dynamic Memory Allocation: Using malloc and realloc to manage investment data arrays based on the input file size.

->Pointer Management: Efficiently handling data structures and passing memory addresses between modules.

->Modular Architecture: Organized into at least three modules, including a dedicated juros.c for the main execution logic.

Data Format Examples
The program accepts two types of input files. Please ensure your data follows these formats:

Quoted Assets (.cot)
Used for assets like the Dollar or Stocks where the price is tracked directlyÇ
"dez./25    5,34
nov./25    5,34
out./25    5,32
set./25    5,43"

Interest Rates (.tax)
Used for annual percentage rates (e.g., SELIC, IPCA).
"dez./25    0,1126
nov./25    0,1146
out./25    0,1168
set./25    0,1217"

* How to Run
Compile the project using the provided Makefile:
make tudo

Execute the program with the following parameters:

-c: Initial Capital (Required)
-i: Start Year (Optional, defaults to 2000)
-f: End Year (Optional, defaults to 2025)
-w: Window size in months (Optional)

Example Command:
./bin/juros -c 1000 -i 2010 -f 2023 dolar.cot selic.tax


