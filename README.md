# Investment Performance Analyzer (C)

This project is a C program developed to compare the performance of different financial investments over time using historical monthly data.

It was built as part of an academic assignment and focuses on modular design, file processing, and financial calculations using compound interest.

---

## 📌 Features

- Calculate accumulated capital over a given time period
- Compare multiple investments (e.g., SELIC, IPCA, USD)
- Support for two types of data:
  - `.tax` → annual interest rates (% per year)
  - `.cot` → asset quotations (e.g., currency)
- Convert annual rates to monthly compound rates
- Perform analysis using **sliding time windows**
- Determine which investment performs best over time

---

## 📂 Project Structure
am25/
│
├── bin/ # Compiled executable
│ └── juros
│
├── src/ # Source code
│ ├── Makefile
│ ├── juros.c
│ ├── calculos.c / calculos.h
│ ├── prints.c / prints.h
│ ├── vetor.c / vetor.h
│
└── LEIAME.txt # Documentation (Portuguese)


---

## ⚙️ Compilation

Navigate to the `src` directory and run:

```bash
make tudo

The executable will be generated in:
../bin/juros

Basic example
./juros -c 1000 dolar.cot

With costum period
./juros -c 1000 -i 2000 -f 2020 dolar.cot selic.tax ipca.tax

With sliding window analysis
./juros -c 1000 -w 6 dolar.cot selic.tax

| Parameter | Description                     |
| --------- | ------------------------------- |
| `-c`      | Initial capital (required)      |
| `-i`      | Initial year (default: 2000)    |
| `-f`      | Final year (default: 2025)      |
| `-w`      | Window size in months (6–12)    |
| files     | Input data files (.tax or .cot) |


## How It Works
.tax files (Interest Rates)
Annual rates are converted into monthly compound rates using:
(1+r)1/12−1
(1+r)
1/12
−1

.cot files (Quotations)
Capital is converted into asset units:
D=CapitalPrice
D=
Price
Capital
	​

At the end, it is converted back to currency.
Sliding Windows
The time range is divided into overlapping windows
Each window:
Resets initial capital
Computes final value
Determines the best-performing investment
Final output shows how many windows each investment "won"


Technologies
C (C99 standard)
GCC
Makefile (modular build system)


