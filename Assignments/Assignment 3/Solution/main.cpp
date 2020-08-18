/*
Name: Arpit Garg
ADSA Assignment 3
Task:
HashTable with Linear Probing
ID: A1784072
 */
// Importing all the required header files and clang is used for formatting
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
/* Creating a structure which will contain hash key, data at node and status of
node and allowed status are never used, tombstone and occupied */
struct LinearHash {
  // three vector key, data and status
  std::vector<char> key;
  std::vector<std::string> data;
  std::vector<std::string> status;
};
//creating class HashProb
class HashProb{
public:
  // functions
  char getHashKey(std::string data);              // return hash key
  int searchData(LinearHash *, unsigned int, std::string); // search data
  void printHash(LinearHash *);                   // print hash table
  LinearHash *insertData(LinearHash *, std::string); // insert data
  LinearHash *deleteData(LinearHash *, std::string); // delete data 
};
// return the hash key menas the last character od the data
char HashProb::getHashKey(std::string data) {
  return (data.at(data.length() - 1));
}
// printing the hash table if occupied
void HashProb::printHash(LinearHash *linearHash) {
  if (linearHash == NULL) {
    std::cout << "Empty"; // if table is empty
  } else {
    unsigned int i = 0;
    while (i < linearHash->key.size()) {
      // checking the occupied status
      if (linearHash->status[i] == "occupied") {
        std::cout << linearHash->data[i] << " ";
      }
      i++;
    }
  }
}
// search data in hashtable
int HashProb::searchData(LinearHash *linearHash, unsigned int pos, std::string data) {
  // if status is neverused or tombstone then return that position  as we
  // can use that location
  if (linearHash->status[pos] == "never used" ||
      linearHash->status[pos] == "tombstone") {
    return pos;

  }
  // if data is already present then skip so return -1
  else if (linearHash->status[pos] != "never used" &&
           linearHash->data[pos] == data) {
    return -1;

  }
  /*check for the empty space from current position to end of the hashtable and
     return the empty space means if status is never used or tombstone*/
  else {
    for (unsigned int i = pos + 1; i < linearHash->key.size(); i++) {
      if (linearHash->status[i] == "never used" ||
          linearHash->status[i] == "tombstone") {
        return i;
      } // if data already present
      else if (linearHash->status[i] != "never used" &&
               linearHash->data[i] == data) {
        return -1;
      }
    }
    /*if no empty space found from current to end of hash table then wrap it up
     * and serach from starting to current position for empty space*/
    for (unsigned int i = 0; i < pos; i++) {
      if (linearHash->status[i] == "never used" ||
          linearHash->status[i] == "tombstone") {
        return i;
      } // if data already present
      else if (linearHash->status[i] != "never used" &&
               linearHash->data[i] == data) {
        return -1;
      }
    }
    return -1;
  }
}
// inserting data
LinearHash *HashProb::insertData(LinearHash *linearHash, std::string data) {
  signed int sh=0;
  HashProb h;
  // get the hashkey where we need to enter
  char key = h.getHashKey(data);
  if (linearHash == NULL) {
    // if no previous table present create a new hashtable
    linearHash = new LinearHash();
    unsigned int i = 0;
    while (i < 26) {
      linearHash->key.push_back(
          (char)(i + 97)); // key will contain all the small letters
      linearHash->status.push_back("never used"); // deafult status never used
      linearHash->data.push_back(" "); // no values in starting in data so space
      i++;
    }
  }
  unsigned int i = 0;
  while (i < linearHash->key.size()) {
    if (key == linearHash->key[i]) {
      sh = h.searchData(linearHash, i, data); // search for the empty position
    }
    i++;
  }
  if (sh != -1) {                        // if data not already present
    linearHash->data[sh] = data;         // enter the data at empty position
    linearHash->status[sh] = "occupied"; // change the status to occupied
  }
  return linearHash;
}
// delete data
LinearHash *HashProb::deleteData(LinearHash *linearHash, std::string data) {
  if (linearHash != NULL) {
    unsigned int i = 0;
    while (i < 26) {
      // search for the data needs to be deleted change the status to tombstone
      // and data to space
      if (linearHash->data[i] == data) {
        linearHash->data[i] = " ";
        linearHash->status[i] = "tombstone";
      }
      i++;
    }
  } else {
    return linearHash;
  }
  return linearHash;
}
// Main function
/*A different approach is used for entering the elements to make the program
more generalised Steps: 1:Input is taken using inline 2:According to spaces
between them all are added to vector 3: Now in vector if first char is
A then add or if D then remove is called.
4. Then A or D is removed and data is added to table
5. Return 0
END*/
int main(int argc, char const *argv[]) {
  std::vector<char *> vec;       // vector for input
  LinearHash *linearHash = NULL; // empty structure
  HashProb h;
  char data[300];
  std::cin.getline(data, 300);            // take input
  char *token_arrays = strtok(data, " "); // divide according to spaces
  while (token_arrays) {
    vec.push_back(token_arrays); // add to vector based on spaces
    token_arrays = strtok(NULL, " ");
  }
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (it[0][0] == 'A') {
      for (unsigned int i = 1; i <= strlen(it[0]);
           i++) { //'A' from starting is removed
        it[0][i - 1] = it[0][i];
      }
      linearHash = h.insertData(linearHash, *it); // insert the data
    } else if (it[0][0] == 'D') {
      for (unsigned int i = 1; i <= strlen(it[0]);
           i++) { //'D' from starting is removed
        it[0][i - 1] = it[0][i];
      }
      linearHash = h.deleteData(linearHash, *it); // delete the data
    }
  }
  h.printHash(linearHash); // print the hash table
}