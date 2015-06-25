#include <iostream>
#include <string>

#include <sesstype/parameterised/constant.h>

namespace sesstype {
namespace parameterised {

// Constant ------------------------------------------------------------------

Constant::Constant(std::string name, int type) : name_(name), type_(type)
{
}

Constant::~Constant()
{
}

std::string Constant::name() const
{
    return name_;
}

int Constant::type() const
{
    return type_;
}

// ValueConstant -------------------------------------------------------------

ValueConstant::ValueConstant(std::string name, int value)
    : Constant(name, ST_CONST_VALUE), value_(value)
{
}

ValueConstant::~ValueConstant() {
}

int ValueConstant::value() const
{
    return value_;
}

// BoundedConstant -----------------------------------------------------------

BoundedConstant::BoundedConstant(std::string name, int lbound, int ubound)
    : Constant(name, ST_CONST_RANGE), lbound_(lbound), ubound_(ubound)
{
    if (ubound < lbound) {
        std::cerr << "Warning: " << name << " has lower bound > upper bound\n";
    }
}

BoundedConstant::~BoundedConstant()
{
}

int BoundedConstant::lbound() const
{
    return lbound_;
}

int BoundedConstant::ubound() const
{
    return ubound_;
}

// ScalableConstant ----------------------------------------------------------

ScalableConstant::ScalableConstant(std::string name, int lbound)
    : Constant(name, ST_CONST_SCALABLE), lbound_(lbound)
{
}

ScalableConstant::~ScalableConstant()
{
}

int ScalableConstant::lbound() const
{
    return lbound_;
}

} // namespace parameterised
} // namespace sesstype
