# Sequence Alignment Algorithm Implementations

This repository contains implementations of two major approaches to solve the global sequence alignment problem:

1. **Dynamic Programming** (Needleman-Wunsch algorithm)
2. **Divide and Conquer** (Hirschberg's algorithm)

Both implementations provide optimal solutions for aligning two sequences, but with different space complexity characteristics. This makes them suitable for different scenarios depending on sequence lengths and available memory.

## What is Sequence Alignment?

Sequence alignment is a fundamental problem in computational biology, text processing, and pattern recognition. It involves arranging two sequences to identify regions of similarity or difference. This process is essential for:

- Comparing DNA, RNA, or protein sequences in bioinformatics
- Detecting similarities between texts in natural language processing
- Finding common patterns in data sequences
- Measuring similarity between strings for spell checking or text correction

The goal is to align sequences in a way that optimizes an alignment score, which typically involves:
- Maximizing matches
- Minimizing mismatches and gaps

## Algorithm Implementations

### 1. Dynamic Programming Approach (Needleman-Wunsch)

The `dynamic_programming.cpp` file implements the classic Needleman-Wunsch algorithm, which:

- Uses a dynamic programming matrix to store alignment scores
- Ensures optimal alignment by considering all possible alignments
- Employs a traceback mechanism to reconstruct the optimal path
- Has O(mn) time complexity and O(mn) space complexity

#### How It Works:

1. Creates a 2D matrix of size (m+1)×(n+1) where m and n are the lengths of the two sequences
2. Initializes the first row and column with gap penalties
3. Fills the matrix using the recurrence relation:
   ```
   OPT(i, j) = min[αxiyj + OPT(i-1, j-1), δ + OPT(i-1, j), δ + OPT(i, j-1)]
   ```
   where αxiyj is the mismatch cost and δ is the gap penalty
4. Traces back from the bottom-right cell to reconstruct the optimal alignment

### 2. Divide and Conquer Approach (Hirschberg's Algorithm)

The `divide_and_conquer.cpp` file implements Hirschberg's space-efficient algorithm, which:

- Reduces space complexity to O(m+n) while maintaining O(mn) time complexity
- Uses a divide-and-conquer strategy to break down the problem
- Is particularly valuable for very long sequences where memory is a constraint
- Efficiently computes the optimal alignment path through recursive division

#### How It Works:

1. Divides the problem at column n/2
2. Computes the forward cost from (0,0) to (i,n/2) for all i
3. Computes the backward cost from (i,n/2) to (m,n) for all i
4. Finds the row q that minimizes the sum of these costs
5. Recursively solves the two subproblems:
   - Alignment from (0,0) to (q,n/2)
   - Alignment from (q,n/2) to (m,n)
6. Combines the results to obtain the complete alignment

## Key Differences

| Feature | Dynamic Programming | Divide and Conquer |
|---------|---------------------|-------------------|
| Time Complexity | O(mn) | O(mn) |
| Space Complexity | O(mn) | O(m+n) |
| Scalability | Limited by memory for large sequences | Better for very large sequences |
| Implementation Complexity | Simpler | More complex |

## Usage

### Compiling and Running the Dynamic Programming Implementation

```sh
# Compile the code
g++ dynamic_programming.cpp -o dynamic_programming

# Run the executable
./dynamic_programming
```

### Compiling and Running the Divide and Conquer Implementation

```sh
# Compile the code
g++ divide_and_conquer.cpp -o divide_and_conquer

# Run the executable
./divide_and_conquer
```

## Examples and Output

The implementations are tested with the following example pairs of strings:

```cpp
Sequences inputs[] = {
    {"correct", "corract"}, 
    {"fast", "fasting"}, 
    {"cat", "dog"}, 
    {"dog", "dig"}, 
    {"internet", "interest"}, 
    {"happiness", "happening"}, 
    {"computer", "commuter"}, 
    {"programming", "program"}, 
    {"transform", "transaction"}
};
```

### Example Output:

Case 1:
- Sequence 1: 'corr ect'
- Sequence 2: 'corra ct'

Case 2:
- Sequence 1: 'fast   '
- Sequence 2: 'fasting'

Case 3:
- Sequence 1: ' cat'
- Sequence 2: 'd og'

Case 4:
- Sequence 1: 'dog'
- Sequence 2: 'dig'

Case 5:
- Sequence 1: 'interne t'
- Sequence 2: 'inter est'

Case 6:
- Sequence 1: 'happ  iness'
- Sequence 2: 'happenin  g'

Case 7:
- Sequence 1: 'co mputer'
- Sequence 2: 'comm uter'

Case 8:
- Sequence 1: 'programming'
- Sequence 2: 'progra m   '

Case 9:
- Sequence 1: 'trans    form'
- Sequence 2: 'transacti o n'

## Cost Model

Both implementations use the same cost model for alignment:
- Gap penalty (EmptyCost): 1
- Mismatch penalty (MatchCost): 2
- Match cost: 0

These values can be modified in the code to suit different alignment requirements.

## Algorithm Analysis

### Time Complexity

Both algorithms have a time complexity of O(mn), where m and n are the lengths of the two input sequences. This is because:

- **Dynamic Programming**: The algorithm fills an m×n matrix, with constant work per cell.
- **Divide and Conquer**: While this approach recursively divides the problem, the total work remains proportional to the product of the sequence lengths.

### Space Complexity

- **Dynamic Programming**: O(mn) as it requires storage of the entire dynamic programming matrix.
- **Divide and Conquer**: O(m+n) as it only needs to store two rows of the matrix at any given time, plus the path information.

## Applications

These sequence alignment algorithms have applications in:

1. **Bioinformatics**: Aligning DNA, RNA, or protein sequences to identify evolutionary relationships or functional similarities.
2. **Text Processing**: Spell checking, plagiarism detection, and text similarity analysis.
3. **Speech Recognition**: Aligning phonetic sequences.
4. **Pattern Recognition**: Finding similarities in general data sequences.

## Implementation Details

### Data Structures

Both implementations use:
- A `Sequences` structure to hold the two strings
- Temporary arrays to store the dynamic programming values
- In the divide and conquer approach, a vector of `Point` structures to store the path

### Parameters

- `EmptyCost`: The penalty for inserting a gap (default: 1)
- `MatchCost`: The penalty for a mismatch (default: 2)

## Contributors

This project was developed by:
- PRANAV G (CB.EN.U4AIE22016)
- GANESH SUNDHAR S (CB.EN.U4AIE22017)
- SIRI REDDY (CB.EN.U4AIE22019)
- HARI KRISHNAN N (CB.EN.U4AIE22020)

## License

This project is part of academic coursework for Design and Analysis of Algorithms (22AIE212) at Amrita School of Artificial Intelligence, Amrita Vishwa Vidyapeetham.