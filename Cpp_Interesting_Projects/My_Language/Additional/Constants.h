#pragma once

enum class TypeName {Empty = 0, 
                     Variables,
                     Type,
                     Function};


enum class TypeVariable {Empty = 0,
                         New,
                         If,
                         While,
                         SHOW,
                         GET,
                         Result};

enum class ComparingAction { Empty = 0,
                             Bigger,
                             Smaller,
                             Equal,
                             NotEqual};