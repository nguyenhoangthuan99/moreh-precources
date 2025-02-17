#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_BOOK_TITLE 30
#define MAX_AUTHOR_NAME 16
#define MAX_BOOKS 2


// You CAN NOT REMOVE or CHANGE exist declaration
// But, CAN ADD whatever you want
#include <fstream>
#include <iostream>

// Total 54 bytes data
typedef struct book_{
    char title[MAX_BOOK_TITLE]; // 30 bytes
    char author[MAX_AUTHOR_NAME]; // 16 bytes
    uint32_t volume_number; // 4 bytes
    uint32_t ISBN; // 4 bytes
} book;
//__attribute__ ((packed))
typedef struct library_{
  book *books;
} library;

// Function to save the books data of the library
void serialize(char* path, library* lib, int number_of_books){
  /*
    pseudo implement, please remove
    write(path, lib->books);
  */
  
  // freopen(path,"w",stdout);
  FILE* fp = fopen(path,"w");
  for (int idx = 0 ; idx < number_of_books;idx++){
    fwrite(&lib->books[idx].title,1,sizeof(lib->books[idx].title),fp);
    fwrite(&lib->books[idx].author,1,sizeof(lib->books[idx].author),fp);
    fwrite(&lib->books[idx].volume_number,1,sizeof(lib->books[idx].volume_number),fp);
    fwrite(&lib->books[idx].ISBN,1,sizeof(lib->books[idx].ISBN),fp);
  }
  fclose(fp);
  std::cout<<"done"<<std::endl;

  // serialize whole object
  
  // fwrite(lib->books , number_of_books , sizeof(lib->books[0]) , fp );
  // fclose(fp);
  // std::cout<<"size of a book when call serialize whole object: "<<sizeof(lib->books[0])<<std::endl;
}

// Function to load the books data of the library
void deserialize(char* path, library *lib, int number_of_books){
  /*
    pseudo implement, please remove
    read(path, lib->books);
  */
 FILE* fp = fopen(path,"r");
  for (int idx = 0 ; idx < number_of_books;idx++){
    fread(&lib->books[idx].title,sizeof(lib->books[idx].title),1,fp);
    fread(&lib->books[idx].author,sizeof(lib->books[idx].author),1,fp);
    fread(&lib->books[idx].volume_number,sizeof(lib->books[idx].volume_number),1,fp);
    fread(&lib->books[idx].ISBN,sizeof(lib->books[idx].ISBN),1,fp);
  }
  fclose(fp);

 // deserialize whole object
//  FILE* fp = fopen(path,"r");
//  std::size_t s =  fread (lib->books, sizeof(lib->books[0]), number_of_books, fp);
//  fclose(fp);

//  std::cout<< "Total bytes read from file: "<<s<<std::endl;

}

// Function to fill defaults data
// Do Not Edit This Functions
void insert_books(library *lib){

  strcpy(lib->books[0].title,"The Songs of Stardust:Harmony");
  strcpy(lib->books[0].author,"John Bolton");
  lib->books[0].ISBN = 15952557;
  lib->books[0].volume_number = 1;

  strcpy(lib->books[1].title,"Whispers Secrets are Unveiled");
  strcpy(lib->books[1].author,"donald trump");
  lib->books[1].ISBN = 67652241;
  lib->books[1].volume_number = 99;
}

// Function to print data
// Do Not Edit This Functions
void print_contents(library *lib){
  printf("\nPrint All Contents of The Library\n");
  for (int idx = 0 ; idx < MAX_BOOKS ; ++idx){
    printf("------------------------------------------------------\n");
    printf("Title : %s\n",lib->books[idx].title);
    printf("Author : %s\n",lib->books[idx].author);
    printf("ISBN : %d\n",lib->books[idx].ISBN);
    printf("volume_number : %d\n",lib->books[idx].volume_number);
    printf("------------------------------------------------------\n");
  }
}

// Do Not Edit This Functions
int main(int argc, char* argv[]){

  // Declare 2 library instance
  library lib, backup;
  void* memory_pool = malloc(54 * MAX_BOOKS * 2);

  lib.books = (book*)memory_pool;
  backup.books = (book*)((char*)memory_pool + 54 * MAX_BOOKS);

  insert_books(&lib);
  print_contents(&lib);

  // save the data of lib instance
  serialize("data.bin", &lib, MAX_BOOKS);
  
  // load the data to backup instance
  deserialize("data.bin", &backup, MAX_BOOKS);

  // The value might be changed ?
  print_contents(&backup);

  return 0;
}
