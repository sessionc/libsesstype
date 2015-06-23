#include <iostream>
#include <string>

#include <sesstype/constant.h>

namespace sesstype {

// Constant ------------------------------------------------------------------

Constant::Constant(std::string name, enum __st_prot_const_type type)
    : name_(name), type_(type)
{
}

Constant::~Constant()
{
}

std::string Constant::name() const
{
    return name_;
}

enum __st_prot_const_type Constant::type() const
{
    return type_;
}

// ValueConstant -------------------------------------------------------------

ValueConstant::ValueConstant(std::string name, int value)
    : Constant(name, sesstype::ST_CONST_VALUE), value_(value)
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
    : Constant(name, sesstype::ST_CONST_RANGE), lbound_(lbound), ubound_(ubound)
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
    : Constant(name, sesstype::ST_CONST_SCALABLE), lbound_(lbound)
{
}

ScalableConstant::~ScalableConstant()
{
}

int ScalableConstant::lbound() const
{
    return lbound_;
}

} // namespace sesstype
