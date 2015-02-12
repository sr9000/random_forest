#pragma once

#include <iostream>
#include <fstream>
#include <vector>

char * read_string(std::fstream &fin)
{
   std::vector <char> readed_symbols;
   char s;
   fin.get(s);
   while (!fin.eof() && s != '\n')
   {

   }
}