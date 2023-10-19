//
// Created by tricc on 2023/10/12.
//
#include <stdexcept>
#include <iostream>
#include "OpenFile.h"

FILE* OpenFile::open_r(const char *rFilePath) {
  FILE* rFile=fopen(rFilePath,"r");
  try{
    if(rFile== nullptr){
      throw std::invalid_argument("File not found: "+std::string(rFilePath));
    }
  }
  catch (const std::exception &e){
    std::cerr<<e.what()<<std::endl;
  }
  return rFile;
}
FILE* OpenFile::open_w(const char *wFilePath) {
  FILE* wFile=fopen(wFilePath,"w");
  try{
    if(wFile== nullptr){
      throw std::invalid_argument("Cannot create file: "+std::string(wFilePath));
    }
  }
  catch (const std::exception &e){
    std::cerr<<e.what()<<std::endl;
  }
  return wFile;
}
bool OpenFile::file_exist(const char *checkPath) {
  FILE* file= fopen(checkPath,"r");
  if(file){
    fclose(file);
    return true;
  }
  return false;
}
