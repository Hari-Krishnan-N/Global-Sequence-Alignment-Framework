// The headers used
#include<iostream>
#include<cmath>
#include<string> 
#include<algorithm>
#include<vector>

using namespace std;

// Use a structure to store two strings and return the output as a new datatype as we can't return two values

struct Sequences{
    string str1;
    string str2;
};

// Initialise a structure containing two variables to store the location of the nodes in the shortest path in the graph
struct Point{
    int x;
    int y;
};

vector<Point> global;   // The vector of size m+n that stores the points in the shortest path


// Function to compare the points in the shortest path in order to arrange them in the ascending order after inserting them

bool comparePoints(Point p1, Point p2){
    if (p1.x == p2.x) {
        return p1.y < p2.y;
    }
    return p1.x < p2.x; 
}


// The function to calculate the cost of the optimal alignment in a space efficient way

double space_efficient_alignment(Sequences str, double EmptyCost, double MatchCost){
    string str1 = str.str1;   // Variables to store the input strings 
    string str2 = str.str2;
    int m = str1.length(), n = str2.length(), i, j;

    // If any of the values is 0, the optimal cost would be the gap cost multiplied by the other length
    if(m==0){
        return EmptyCost*n;
    }
    if(n==0){
        return EmptyCost*m;
    }

    double A[2][m+1], CurrCost;   // The m x 2 array to store the cost values and find the optimal cost

    for(i=0;i<=m;i++){
        A[0][i] = EmptyCost*i;
    }

    for(i=1;i<=n;i++){
        A[1][0] = EmptyCost*i;
        for(j=1;j<=m;j++){
            CurrCost = 0;
            if(str1[j-1] != str2[i-1]){
                CurrCost = MatchCost;   // Set the mismatch cost if it is not zero
            }
            A[1][j] = min(CurrCost + A[0][j-1], min(EmptyCost + A[0][j], EmptyCost+ A[1][j-1]));   // The recurrence step
        } 

        for(j=0; j<=m; j++){
            A[0][j] = A[1][j];   // The update step to update the values from the first row to the zeroth row
        } 
    }

    return A[1][m];   // Return the optimal cost
}


// The dynammic programming step to calculate the minimum alignment if the length of any of the strings is less than 2

void dynamic_programming(Sequences str, double EmptyCost, double MatchCost, int l1, int l2){
    string str1 = str.str1;    //The variables to store the input strings
    string str2 = str.str2;
    int m = str1.length(), n = str2.length(), i, j;

    // Push all the nodes into the vector when the length of any one the strings is zero
    if(m==0){
        for(i=1;i<n;i++){
            global.push_back({l1,l2+i});
        }
        return;
    }
    if(n==0){
        for(i=1;i<m;i++){
            global.push_back({l1+i,l2});
        }
        return;
    }

    double A[m+1][n+1], CurrCost = 0;   // Array to store the costs 

    for(int i=0; i<=m; i++){
        A[i][0] = i*EmptyCost;
    }
    for(int j=0; j<=n; j++){
        A[0][j] = j*EmptyCost;
    }

    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            CurrCost = 0;
            if(str1[i-1] != str2[j-1]){
                CurrCost = MatchCost;
            }
            A[i][j] = min(CurrCost + A[i-1][j-1], min(EmptyCost + A[i-1][j], EmptyCost+ A[i][j-1]));   // The recurrence relation
        }
    }

    // Traceback the 2D array formed to obtain the optimal sequnce alignment formed
    i=m; 
    j=n;
    double v1, v2, v3;
    while(i!=0 && j!=0){
        CurrCost = 0;
        if(str1[i-1] != str2[j-1]){
            CurrCost = MatchCost;
        }

        v1 = EmptyCost + A[i][j-1];
        v2 = EmptyCost + A[i-1][j];
        v3 = CurrCost + A[i-1][j-1];

        if(v1<v2 && v1<v3){
            j--;
        }
        else if(v2<v3){
            i--;
        }
        else{
            i--;
            j--;
        }
        if(i!=0 || j!= 0){
            global.push_back({l1+i,l2+j}); 
        }
    }

    while(i != 0){
        i--;
        if(i!=0){
            global.push_back({l1+i,l2});
        }
    }

    while(j != 0){
        j--;
        if(j!=0){
            global.push_back({l1,l2+j});
        }
    }
}


// The recursive function to calculate the nodes in the shortest path using divide and conquer

void sequence_alignment_rec(Sequences str, double EmptyCost, double MatchCost, int l1, int l2){
    string str1 = str.str1;   // Strings to store the inputs
    string str2 = str.str2;
    int m = str1.length(), n = str2.length(), i, j, mid;
    if(m<=2 || n<=2){
        dynamic_programming(str, EmptyCost, MatchCost, l1, l2);   // Calculate the optimal alignment using dynammic programming if the length of any of the strings is less than 2
        return;
    }

    mid = (int)(floor((double)(n)/2)) - 1;   // The mid column index
    double cost = space_efficient_alignment({"", str2.substr(0,mid+1)}, EmptyCost, MatchCost) + space_efficient_alignment({str1, str2.substr(mid+1, n-mid-1)}, EmptyCost, MatchCost);   // Initialise the cost when the minimum path cost is at the node (0,n/2)
    double temp;
    int pos = -1;   // The position variable initialised to -1
    for(i=0;i<m;i++){
        // For loop to calculate the node at which the shortest path passes in order to get the minimum cost alignment
        temp = space_efficient_alignment({str1.substr(0,i+1), str2.substr(0,mid+1)}, EmptyCost, MatchCost) + space_efficient_alignment({str1.substr(i+1, m-i-1), str2.substr(mid+1, n-mid-1)}, EmptyCost, MatchCost);
        if(temp < cost){
            cost = temp;
            pos = i;
        }
    }
    // Calculate the cost for the last node in the n/2 column
    temp = space_efficient_alignment({str1, str2.substr(0,mid+1)}, EmptyCost, MatchCost) + space_efficient_alignment({"", str2.substr(mid+1, n-mid-1)}, EmptyCost, MatchCost);
    if(temp < cost){
        cost = temp;
        pos = m;
    }

    // Push that point into the vector containing the points in the shortest path
    global.push_back({l1+ pos + 1, l2 + mid + 1});
    

    // Recursive calls to calulate the results for the subproblems generated
    if(pos==-1){
        // If the node is the first node
        sequence_alignment_rec({"", str2.substr(0,mid+1)}, EmptyCost, MatchCost, l1, l2);
        sequence_alignment_rec({str1, str2.substr(mid+1, n-mid-1)}, EmptyCost, MatchCost, l1, l2+mid+1);
    }
    else if(pos==m){
        // If the node is in the middle
        sequence_alignment_rec({str1, str2.substr(0,mid+1)}, EmptyCost, MatchCost, l1, l2);
        sequence_alignment_rec({"", str2.substr(mid+1, n-mid-1)}, EmptyCost, MatchCost, l1+m, l2+mid+1);
    }
    else{
        // If the node is at the last
        sequence_alignment_rec({str1.substr(0,pos+1), str2.substr(0,mid+1)}, EmptyCost, MatchCost, l1, l2);
        sequence_alignment_rec({str1.substr(pos+1,m-pos-1), str2.substr(mid+1, n-mid-1)}, EmptyCost, MatchCost, l1+pos+1, l2+mid+1);
    }
}


// Function to take the inputs, calculate the optimal alignment using the rcursion and sort them

Sequences optimal_sequence_alignment(Sequences str, double EmptyCost, double MatchCost){
    string str1 = str.str1;
    string str2 = str.str2;
    int m = str1.length(), n = str2.length(), i, j, ind1, ind2, a1=0, a2=0;
    global.push_back({0,0});
    global.push_back({m,n});

    // Use the recursive call to get the optimal alignment
    sequence_alignment_rec(str, EmptyCost, MatchCost, 0, 0);
    
    // Processing the nodes to get the alignment using the sorting function
    sort(global.begin(), global.end(), comparePoints);   // Builtin function to sort
    string ans1 = "", ans2 = "";
    
    // Create the alignment itself from the sorted list of nodes
    for(i=1; i<global.size(); i++){
        ind1 = global[i].x - global[i-1].x;
        ind2 = global[i].y - global[i-1].y;

        if(ind1 == 1 && ind2 == 1){
            // If the difference is 1, we use the characters from each string, it would either be a match or a mismatch
            ans1 += str1[a1++];
            ans2 += str2[a2++];
        }
        else if(ind1 == 1){
            // If there is a gap in the second string
            ans1 += str1[a1++];
            ans2 += " ";
        }
        else{
            // If there is a gap in the first string
            ans1 += " ";
            ans2 += str2[a2++];
        }
    }

    return {ans1, ans2};   // Return the output
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
        global.clear();
        cout << "Case " << i+1 << " :-" << endl <<
        "Sequence 1 : '" << output.str1 << "'" << endl <<
        "Sequence 2 : '" << output.str2 << "'" << endl << endl;
    }
}