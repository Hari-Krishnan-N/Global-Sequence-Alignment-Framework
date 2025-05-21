// The headers used
#include<iostream>
#include<cmath>
#include<string> 
#include<algorithm>

using namespace std;

// Use a structure to store two strings and return the output as a new datatype as we can't return two values

struct Sequences{
    string str1;
    string str2;
};


// Function to display the 2D array contatining the costs in order to check if the algorithm works

void display_cost(double *A, int m, int n){
    for(int i=m;i>=0;i--){
        for(int j=0;j<=n;j++){
            cout << A[(i)*(n+1) + j] << " ";
        }   
        cout << endl;
    }
    cout << endl;
}


// The algorithm to calculate the optimal sequence alignment using dynamic programming

Sequences optimal_sequence_alignment(Sequences str, double EmptyCost, double MatchCost){
    string str1 = str.str1;   // Initialise variables to store the input obtained as a Sequences data type
    string str2 = str.str2;
    int m = str1.length(), n = str2.length(), i, j;   

    // If the length of the first sequence is 0, align it with the second sequence by adding n gaps and return the output
    if(m==0){
        Sequences ans;
        string ans1 = "";
        for(i=0;i<n;i++){
            ans1 += " ";
        }
        ans = {ans1, str2};
        return ans;
    }
    // If the length of the second sequence is 0, align it with the second sequence by adding m gaps and return the output
    if(n==0){
        Sequences ans;
        string ans2 = "";
        for(i=0;i<m;i++){
            ans2 += " ";
        }
        ans = {str1, ans2};
        return ans;
    }

    // Initialise the 2D array to store the cost values 
    double A[m+1][n+1], CurrCost = 0;

    // Initialise the first row and first column of the 2D array created with gap costs multipled by the number of gaps encountered so far
    for(int i=0; i<=m; i++){
        A[i][0] = i*EmptyCost;
    }
    for(int j=0; j<=n; j++){
        A[0][j] = j*EmptyCost;
    }

    // Iterate through the array row wise first and then column wise. Then use the recurrence relation at each iteration to build the 2D dynamic programming array
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            CurrCost = 0;   // Set the CurrCost to 0. This variable holds the match or mismatch cost
            if(str1[i-1] != str2[j-1]){
                CurrCost = MatchCost;   // If a mismatch is encountered, change the CurrCost to the mismatch cost, else it will be 0
            }
            A[i][j] = min(CurrCost + A[i-1][j-1], min(EmptyCost + A[i-1][j], EmptyCost+ A[i][j-1]));   // The recurrence relation
        }
    }

    // Traceback the 2D array formed to obtain the optimal sequnce alignment formed

    i=m;   // Start from the end and reach (0,0)
    j=n;
    string ans1 = "", ans2 = "";   // Variables to store the output
    double v1, v2, v3;
    while(i!=0 && j!=0){
        // Get the matchcost at each step
        CurrCost = 0;
        if(str1[i-1] != str2[j-1]){
            CurrCost = MatchCost;  
        }

        /*
        Calaculate the costs of the 3 possible positions from where we obtained our current position (i,j). This can be from a 
            (i) Match/Mismatch and (i-1,j-1)
            (ii) Gap and (i-1,j)
            (iii) Gap and (i,j-1)
        */ 
        v1 = EmptyCost + A[i][j-1];
        v2 = EmptyCost + A[i-1][j];
        v3 = CurrCost + A[i-1][j-1];

        // Update the string variables created with either the characters from the strings or gap and character from one string.
        // It depends on which path the algorithm took to reach the current position calculated from the above values
        if(v1<v2 && v1<v3){
            ans1 = " " + ans1;
            ans2 = str2[--j] + ans2;
        }
        else if(v2<v3){
            ans2 = " " + ans2;
            ans1 = str1[--i] + ans1;
        }
        else{
            ans1 = str1[--i] + ans1;
            ans2 = str2[--j] + ans2;
        }
    }

    // If any one of the values reach zero i.e. (i,0) or (0,j), we add gaps until the other value becomes zero
    while(i != 0){
        ans2 = " " + ans2;
        ans1 = str1[--i] + ans1;
    }

    while(j != 0){
        ans1 = " " + ans1;
        ans2 = str2[--j] + ans2;
    }

    // Store the two strings into the sequences datatype
    Sequences output = {ans1, ans2};

    //display_cost(A[0], m, n);
    return output;   // Return the output
}


// Main function containing sample values to check for the correctness of our algorithm 

int main(){
    int n = 9;   // Number of examples used
    double EmptyCost = 1;  // Empty cost (gap) is 1 
    double MatchCost = 2;  // Cost for all mismatchs are 2 and all matchs are 0. This is in general. We can change this depending on the field in which the algotihm is used.
    // Array of samples
    Sequences inputs[] = {{"correct", "corract"}, {"fast","fasting"}, {"cat", "dog"}, {"dog", "dig"}, {"internet", "interest"}, {"happiness", "happening"}, {"computer", "commuter"}, {"programming", "program"}, {"transform", "transaction"}};
    Sequences output;   // Variable to store the output

    // Iterate through each smaple and print the output for each
    for(int i=0; i<n; i++){    
        output = optimal_sequence_alignment(inputs[i], EmptyCost, MatchCost);
        cout << "Case " << i+1 << " :-" << endl <<
        "Sequence 1 : '" << output.str1 << "'" << endl <<
        "Sequence 2 : '" << output.str2 << "'" << endl << endl;
    }
}