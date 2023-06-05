# GeneticAlgorithm-UMApHMP
Simple hybrid GA for solving Uncapacitated Multiple Allocation p-Hub Median Problem using local search to enhance the best solution of a generation.
## UMApHMP
Uncapacitated Multiple Allocation p-hub Median Problem (UMApHMP) is one of the many hub location problems that were studied in the recent history. The hub location problem is concerned with locating hub facilities and allocatin non-hub nodes to hubs. Some non-hub nodes can be allocated to a single hub or multiple.  The UMApHMP assumes the multiple allocation scheme, which allows each non-hub node to be allocated to more than one hub and the objective is to locate exactly p hubs, such that the total flow cost is minimized.

* **Research used**: Zorica Stanimirovic - "An efficient genetic algorithm for the ucapacitated multiple allocation p-hub median problem"
* **Data used**: AP and CAB instances - [LINK](https://andreas-ernst.github.io/Mathprog-ORlib/info/readmeAP.html)
* **Results**: Results of the GA (with and without local search) can be found in the folder results and down bellow:
**AP instances**


| Number of facilities | Number of hubs | Minimal duration | Number of iterations | Iteration threshold | Average duration |
| --- | --- | --- | --- | --- | --- |
| 10 | 2 | 1.45 | 200 | 200 | 1.49 |
| 10 | 3 | 1.74 | 200 | 200 | 1.85 |
| 10 | 4 | 2.08 | 201 | 200 | 2.22 |
| 10 | 5 | 2.49 | 201 | 200 | 2.58 |
| 20 | 3 | 4.26 | 200 | 200 | 4.47 |
| 20 | 4 | 5.19 | 203 | 200 | 5.49 |
| 20 | 5 | 6.04 | 202 | 200 | 6.67 |
| 25 | 2 | 4.85 | 200 | 200 | 5.25 |
| 25 | 3 | 6.10 | 203 | 200 | 6.80 |
| 25 | 4 | 7.34 | 206 | 200 | 8.17 |
| 25 | 5 | 9.23 | 220 | 200 | 10.05 |
| 40 | 2 | 10.32 | 202 | 200 | 10.85 |
| 40 | 3 | 14.34 | 221 | 200 | 17.11 |
| 40 | 4 | 16.40 | 221 | 200 | 17.81 |
| 40 | 5 | 19.51 | 229 | 200 | 26.85 |
| 40 | 10 | 396.55 | 2044 | 2000 | 422.18 |
| 50 | 3 | 16.84 | 207 | 200 | 19.22 |
| 50 | 4 | 22.08 | 217 | 200 | 29.32 |
| 50 | 5 | 28.35 | 230 | 200 | 37.30 |
| 50 | 10 | 584.35 | 2437 | 2000 | 669.19 |
| 100 | 2 | 340.09 | 1516 | 1500 | 368.63 |
| 100 | 3 | 436.55 | 1524 | 1500 | 752.85 |
| 100 | 4 | 735.50 | 1704 | 1500 | 913.41 |
| 100 | 5 | 1014.74 | 2151 | 2000 | 1604.78 |
| 200 | 2 | 1704.06 | 1552 | 1500 | 2045.07 |
| 200 | 3 | 2257.90 | 1642 | 1500 | 3098.51 |
| GA with local search |
| Number of facilities | Number of hubs | Minimal duration | Number of iterations | Iteration threshold | Average duration |
| --- | --- | --- | --- | --- |
| 10 | 2 | 1.73 | 200 | 200 | 1.79 |
| 10 | 3 | 2.16 | 200 | 200 | 2.19 |
| 10 | 4 | 2.59 | 200 | 200 |  |
| 10 | 5 | 3.11 | 201 | 200 | 3.37 |
| 20 | 3 | 5.47 | 205 | 200 | 5.78 |
| 20 | 4 | 5.18 | 205 | 200 | 5.32|
| 20 | 5 | 6.23 | 207 | 200 | 6.45 |
| 25 | 2 | 5.89 | 200 | 200 | 6.10 |
| 25 | 3 | 7.32 | 202 | 200 | 8.33 |
| 25 | 4 | 9.93 | 205 | 200 | 10.35 |
| 25 | 5 | 14.15 | 217 | 200 | 17.65 |
| 40 | 2 | 11.85 | 204 | 200 | 13.71 |
| 40 | 3 | 17.54 | 208 | 200 | 19.88 |
| 40 | 4 | 19.88 | 220 | 200 | 22.26 |
| 40 | 5 | 20.64 | 200 | 200 | 25.80 |
| 40 | 10 | 633.63 | 2057 | 2000 | 763.63 |
| 50 | 3 | 21.75 | 206 | 200 | 25.55 |
| 50 | 4 | 28.26 | 217 | 200 | 34.48 |
| 50 | 5 | 33.17 | 218 | 200 | 1350.45 | 43.39 |
| 50 | 10 | 1017.89 | 2083 | 2000 | 1350.45 |
| 100 | 2 | 694.44 | 1507 | 1500 | 776.64 |
| 100 | 3 | 911.13 | 1568 | 1500 | 1032.94 |
| 100 | 4 | 1060.54 | 2027 | 1500 | 1278.34 |
| 100 | 5 | 1223.54 | 2046 | 2000 | 1600.23 |
| 200 | 2 | 2264.81 | 1521 | 1500 | 2514.93 |
| 200 | 3 | 3164.20 | 1767 | 1500 | 4379.31 |
