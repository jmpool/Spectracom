//
//  Enum2String.hpp
//  spectracom
//
//  Created by collinsc on 1/7/16.
//
//

#ifndef ENUM_2_STRING_HPP
#define ENUM_2_STRING_HPP

#include <string>
#include <array>

namespace spectracom {
  
  class Enum2String {
  private:
    // \brief   Number of items in Ids and idStringArray
    size_t totalEntries;
    
    // \brief   Strings corresponding to their enums
    std::string * idStringArray;
    
  public:
    
    Enum2String(size_t entries)
    : totalEntries(entries)
    {
      idStringArray = new std::string[entries];
    }
    
    // \brief   Enum of all valid ids for a message type
    enum class Ids;
    
    std::string toString(Ids inputEnum) {
      return idStringArray[(std::size_t)inputEnum];
    }
    
    Ids toEnum(std::string inputString) {
      std::string result = std::find(idStringArray[0],
                                     idStringArray[totalEntries],
                                     inputString);
      
      //      if (result == stringArray.end()) {
      //        return ;
      //      } // TODO: Add exception throw for if string not valid
      
      return (Ids)(std::distance(&idStringArray[0], &result)-1);
    }
    
    // \brief
    size_t getTotalEntries() {return totalEntries;};

    // \brief   Call in constructor of child classes to set totalEntries
    void setTotalEntries(size_t entries) {totalEntries = entries;};
    
  };
}
#endif /* ENUM_2_STRING_HPP */
