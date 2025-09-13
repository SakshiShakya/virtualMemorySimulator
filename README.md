## **Virtual Memory Simulator** 

This is a C++ program that simulates a **virtual memory management system**. It translates logical addresses to physical addresses using a **Translation Lookaside Buffer (TLB)** and a **Page Table**. The simulation also calculates key performance metrics like **page fault rate** and **TLB hit rate**.

<br>

-----

<br>

## **Why This Program?** 

Virtual memory is a fundamental concept in modern operating systems. It allows a process to use a large virtual address space that can be much bigger than the available physical memory. This program provides a hands-on way to understand how a virtual memory system works, specifically how it handles address translation, page faults, and the role of the TLB in speeding up memory access.

<br>

-----

<br>

## **How It Works** 

The program simulates a virtual memory system with the following components:

  - **Virtual Address Space:** A 16-bit address space (256 pages, each 256 bytes).
  - **Physical Address Space:** A 16-bit address space (256 frames, each 256 bytes).
  - **Page Table:** An array that maps virtual page numbers to physical frame numbers.
  - **Translation Lookaside Buffer (TLB):** A small, fast cache that stores recent page-to-frame translations. It uses a **First-In, First-Out (FIFO)** replacement policy.
  - **Main Memory:** A 2D array representing the physical memory frames.

The simulation processes a list of logical addresses from an input file (`addresses.txt`). For each address, it first checks the **TLB** for a quick translation. If a **TLB hit** occurs, the corresponding physical address is used. If not, it checks the **Page Table**. If the page is in memory, a **TLB miss** occurs, and the TLB is updated. If the page is not in memory, a **page fault** occurs, and the required page is brought from "disk" (simulated by adding content to a free frame in physical memory) and then added to both the **Page Table** and **TLB**. Finally, the simulation outputs a CSV file with the translations and prints summary statistics to the console.

<br>

-----

<br>

## **How to Execute** 

1.  **Clone the Repository:** 

    ```
    git clone https://github.com/PiyushKhurana/Virtual-Memory-Simulator
    ```

2.  **Navigate to the Directory:**

    ```bash
    cd Virtual-Memory-Simulator
    ```

3.  **Create Input File:**
    Create a file named `addresses.txt` in the same directory. Each line of this file should contain a single decimal integer representing a logical address.
    **Example:**

    ```
    17325
    28676
    ...
    ```

4.  **Compile the Code:**
    Use a C++ compiler like g++.

    ```bash
    g++ -o main main.cpp
    ```

5.  **Run the Executable:**
    Execute the compiled program. It will read `addresses.txt` and generate `output.csv`.

    ```bash
    ./main
    ```

<br>

-----

<br>

## **Output**

The program will generate two types of output:

  - **Console Output:** A summary of the simulation results, including the total number of addresses translated, TLB hits, page faults, and the calculated hit and fault rates.
  - **File Output:** A file named `output.csv` containing two columns: the logical address and its corresponding physical address for each translation.

<br>

  ![Demo](demo/demo.gif)
