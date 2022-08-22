
#pragma once

#include <WString.h>
#include <vector>

class Matrix 
{
    private:
        std::vector<int> _columns;
        std::vector<int> _rows;

        std::vector<int> _states;

    public:
        Matrix(std::vector<int> columns, std::vector<int> rows);
        Matrix();
        void Init();
        void Scan();
        int Length();
        int GetState(int index);
};
