# Matrix–Vector Multiplication with OpenMP

This project implements **matrix–vector multiplication** in C++ and analyzes the performance differences between **serial execution** and **parallel execution using OpenMP**.

The main goal of the project is to observe how execution time and speedup change when different **OpenMP scheduling strategies** and **thread counts** are used. 

---

## Project Scope

In this project:
- A serial matrix–vector multiplication algorithm is implemented
- The same algorithm is parallelized using OpenMP
- Different OpenMP scheduling methods are tested
- Execution times and speedup values are measured
- Results are compared using tables and graphs

---

## Parallelization Approach

Parallelization is applied by distributing matrix rows among threads using OpenMP.  
Each thread computes the result for different rows independently, which avoids race conditions and ensures correctness.

The following approaches are included:
- **Basic parallelization**
- **Static scheduling**
- **Dynamic scheduling**
- **Guided scheduling**

All parallel versions produce the same output as the serial version.

---

## Experimental Setup

- Matrix size: **3000 × 3000**
- Vector size: **3000**
- Thread counts tested: **1, 2, 4, 8**
- Same input sizes are used for all experiments to ensure fair comparison
- Each experiment measures:
  - Execution time (seconds)
  - Speedup relative to serial execution

---

## Performance Analysis

Execution time results are presented in a table and visualized using a time measurement graph.  
Speedup values are calculated as the ratio of serial execution time to parallel execution time and are also presented in both tabular and graphical form.

Key observations:
- With **1 thread**, parallel versions are slower due to thread creation and scheduling overhead
- As thread count increases, speedup increases significantly
- **Static scheduling** generally provides the most stable performance
- **Dynamic and guided scheduling** introduce additional overhead but reach similar speedup values at higher thread counts
- Near-linear speedup is observed for 4 and 8 threads

---

## Conclusion

This project demonstrates that OpenMP can significantly improve the performance of matrix–vector multiplication when an appropriate scheduling strategy and sufficient number of threads are used.  
The results highlight the impact of scheduling overhead and show that static scheduling is often the most efficient choice for regular workloads.

---

## Technologies Used

- C++
- OpenMP
- GCC (with `-fopenmp`)
- Execution time measurement using standard timing utilities





