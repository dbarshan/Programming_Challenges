#include <iostream>
#include <vector>
#include <queue>
#include <utility>

std::vector<std::vector<int>> C;
int rows, cols;

// function to check if C[i][j] already visited
inline bool isVisited(int i, int j){
	if(C[i][j] == 2)
		return true;

	return false;
}

// function to mark C[i][j] as visited
inline void visit(int i, int j){
	C[i][j] = 2;
}

// fucntion to check if C[i][j] is a choco chip
inline bool isChocoChip(int i,int j){
	if(C[i][j] == 1)
		return true;
	return false;
}

//function to check if i and j are valid row and col
inline bool isValid(int i, int j){
	if(i < 0 || j < 0 || i == rows || j == cols)
		return false;

	return true;
}

// Depth First Search function with a count of number of elements traversed
int DFS_Count(int i, int j){

	// if not a valid matrix row/col then do not proceed
	if( !isValid(i,j))
		return 0;
	
	// if already traversed, then no need proceeding 
	if( isVisited(i,j))
		return 0;

	// if not a choco chip then no need proceeding 
	if(!isChocoChip(i,j))
		return 0;

	// If a valid matrix item, not already traveresd, and is a choco chip, then mark is as visited
	visit(i,j);

	// since we have traversed element (i,j), that counts one chocho chip
	// now recursively traverse horizontally and vertically connected choco chips  
	return 1 + DFS_Count(i-1,j) + DFS_Count(i+1,j) + DFS_Count(i,j-1) + DFS_Count(i,j+1); 
}

// Breadth First Search function with a count of number of elements traversed
int BFS_Count(int i, int j){

	// We need a queue to store adjacent elements
	std::queue<std::pair<int,int>> Q;

	// Enqueue the starting item
	Q.push(std::pair<int,int>(i,j));

	// Initialize count of number of choco chips as 0
	int count = 0;

	while(!Q.empty()){

		// Pop front element of queue 
		std::pair<int,int> v = Q.front();
		Q.pop();

		i = v.first;
		j = v.second;
		
		// If it is a valid matrix element and if it is a choco chip and not already travesed, then
		// 		1. Mark it as visited
		//		2. count this choco chip
		// 		3. Enqueu vertically and horizontallly connected items

		if( isValid(i,j) && isChocoChip(i,j) && !isVisited(i,j)){
			
			count++;
			visit(i,j);

			Q.push(std::pair<int,int>(i-1,j));
			Q.push(std::pair<int,int>(i+1,j));
			Q.push(std::pair<int,int>(i,j-1));
			Q.push(std::pair<int,int>(i,j+1));
			
		}

	}

	return count;
}


// function for finding choco lines
std::vector<int> findChocoLine(){
	
	std::vector<int> chocoLines;

	// for each choco chip ( C[i][j] = 1 ) find connected choc chips
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){

			// if C[i][j] is a choco chip (1) and if it is not visited yet then start graph traversal from this.
			if( isChocoChip(i,j) && !isVisited(i,j) ) {
				
				// find connected choco chips with DFS or BFS traversal starting from C[i][j] 

				//chocoLines.push_back(DFS_Count(i,j));

				chocoLines.push_back(BFS_Count(i,j));

			}
		}
	}
	return chocoLines;
}


//driver function
int main(){

	// rows = 5;
	// cols = 5;

	// C = {
	// 		{1, 0, 0, 1, 0},
	// 		{1, 0, 1, 0, 0},
	// 		{0, 0, 1, 0, 1},
	// 		{1, 0, 1, 0, 1},
	// 		{1, 0, 1, 1, 0}

	// 	};


	// user input: number of rows, number of cols, and the matrix
	std::cout << "Enter rows: ";
	std::cin >> rows;

	std::cout << "Enter cols: ";
	std::cin >> cols;

	for(int i=0; i<rows; i++){
		std::vector<int> row;
		for(int j=0; j<cols; j++){
			int value;
			std::cin >> value;
			row.push_back(value);
		}
		C.push_back(row);
	}

	// Get the chocolines 	
	std::vector<int> chocoLines = findChocoLine();

	// print the chocolines
	std::cout << "[";
	for(std::vector<int>::iterator it = chocoLines.begin(); it != chocoLines.end(); ++it){
		if(it != chocoLines.begin())
			std::cout << ",";
		std::cout << *it;
	}
	std::cout << "]" << std::endl;

	return 0;
}