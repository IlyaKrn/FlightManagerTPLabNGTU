#pragma once
#include <ostream>
#include <istream>

class IPresenter
{
protected:
    std::ostream *_output;
    std::istream *_input;

public:
    IPresenter(std::ostream* output, std::istream* input): _output(output), _input(input) {}
};